//
// Created by Martin on 20/01/2020.
//

#include "extlibs/SQLite/sqlite3.h"
#include "SQLiteDriver.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "VerbsContainer.h"

/* The SQLite connexion. */
static sqlite3* db = NULL;

/* The SQL queries that may be run once or many times. */
static sqlite3_stmt* sql_insert_verb = NULL;
static STRING sql_insert_verb_code = "INSERT INTO Verbs VALUES ( ?1, ?2, ?3, ?4 ) ;";
static sqlite3_stmt* sql_count = NULL;
static STRING sql_count_code = "SELECT COUNT(*) FROM Verbs ;";
static sqlite3_stmt* sql_list_all = NULL;
static STRING sql_list_all_code = "SELECT * FROM Verbs ORDER BY infinitive ;";
static sqlite3_stmt* sql_list_all_by_first_letter_of_inf = NULL;
static STRING sql_list_all_by_first_letter_of_inf_code = "SELECT * FROM Verbs WHERE infinitive LIKE @s || '%' ORDER BY infinitive ;";
static sqlite3_stmt* sql_search = NULL;
static STRING sql_search_code = "SELECT * FROM Verbs WHERE (instr(infinitive, @s) > 0) OR (instr(translation, @s) > 0) OR (instr(time1, @s) > 0) OR (instr(time2, @s) > 0) ORDER BY infinitive ;";
static sqlite3_stmt* sql_start_exclusive_transaction = NULL;
static STRING sql_start_exclusive_transaction_code = "BEGIN EXCLUSIVE TRANSACTION;";
static sqlite3_stmt* sql_end_exclusive_transaction = NULL;
static STRING sql_end_exclusive_transaction_code = "COMMIT";
static sqlite3_stmt* sql_get_row_by_id = NULL;
static STRING sql_get_row_by_id_code = "SELECT * FROM Verbs WHERE rowid = ?1;";

/* When verbs are returned by queries using "select *", here are the indices of columns. */
#define INDEX_INFINITIVE   0
#define INDEX_TRANSLATION  1
#define INDEX_TIME_1       2
#define INDEX_TIME_2       3

/* ***** STATIC METHODS DECLARATION ***** */
/**
 * Runs a simple statement that shall not fail and returns true.
 *
 * @param prepared The statement with all parameters ready.
 * @return True if success of query, False otherwise.
 */
static bool _runSimpleQuery(sqlite3_stmt* prepared);

/**
 * Runs a statement that shall not fail.
 * Stores the results (in order) in the output.
 *
 * @param stmt The statement which shall be ready.
 * @param output The object on which results will be written.
 */
static void _makeQueryResults(sqlite3_stmt *stmt, list_t output);

/**
 * Binds the MultiString argument to the statement at the given column index.
 * It is converted to STRING.
 *
 * @param stmt The prepared query.
 * @param id The column index.
 * @param multiStrings The MultiString instance to bind.
 */
static void _bindMultiStringsToStmt(sqlite3_stmt* stmt, int id, MultiStrings* multiStrings);

/**
 * Binds the STRING argument to the statement at the given column index.
 *
 * @param stmt The prepared query.
 * @param id The column index.
 * @param multiStrings The STRING instance to bind.
 */
static void _bindStringToStmt(sqlite3_stmt* stmt, int id, STRING to_bind);

/* ***** STATIC METHODS DEFINITION ***** */
static bool _runSimpleQuery(sqlite3_stmt* prepared) {
    return
            (sqlite3_step(prepared) == SQLITE_DONE) &&
            (sqlite3_reset(prepared) == SQLITE_OK) &&
            (sqlite3_clear_bindings(prepared) == SQLITE_OK);
}

static void _makeQueryResults(sqlite3_stmt *stmt, list_t output) {
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        STRING infinitive = (STRING) sqlite3_column_text(stmt, INDEX_INFINITIVE);
        STRING translation = (STRING) sqlite3_column_text(stmt, INDEX_TRANSLATION);
        STRING time1 = (STRING) sqlite3_column_text(stmt, INDEX_TIME_1);
        STRING time2 = (STRING) sqlite3_column_text(stmt, INDEX_TIME_2);

        list_node* current_node = calloc(1, sizeof(list_node));
        current_node->verb = makeVerbFromStrings(
                infinitive,
                translation,
                time1,
                time2);
        list_add(output, current_node);
    }

    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);
}

static void _bindMultiStringsToStmt(sqlite3_stmt* stmt, int id, MultiStrings* multiStrings) {
    STRING str = makeStringFromMultiStrings(multiStrings);
    _bindStringToStmt(stmt, id, str);
    freeStringFromMultiStrings(str);
}

static void _bindStringToStmt(sqlite3_stmt* stmt, int id, STRING to_bind) {
    sqlite3_bind_text(stmt, id, to_bind, -1, SQLITE_TRANSIENT);
}

void m_sqlite_search_substring(STRING substring, list_t output) {
    _bindStringToStmt(sql_search, 1, substring);
    _makeQueryResults(sql_search, output);
}

bool m_sqlite_addVerb(const Verb* verb) {
    _bindMultiStringsToStmt(sql_insert_verb, 1, verb->infinitive);
    _bindMultiStringsToStmt(sql_insert_verb, 2, verb->translation);
    _bindMultiStringsToStmt(sql_insert_verb, 3, verb->time1);
    _bindMultiStringsToStmt(sql_insert_verb, 4, verb->time2);
    return _runSimpleQuery(sql_insert_verb);
}

size_t m_sqlite_get_count() {
    int result_exec = sqlite3_step(sql_count);
    size_t output = 0;
    if (result_exec == SQLITE_ROW) {
        output = sqlite3_column_int(sql_count, 0);
        sqlite3_reset(sql_count);
    }
    return output;
}

#if defined(DEBUG_MODE) && DEBUG_MODE == 1
void m_sqlite_get_all(list_t output) {
    _makeQueryResults(sql_list_all, output);
}
#endif

void m_sqlite_get_by_first_letters_of_infinitive(STRING start_substring, list_t output) {
    _bindStringToStmt(sql_list_all_by_first_letter_of_inf, 1, start_substring);
    _makeQueryResults(sql_list_all_by_first_letter_of_inf, output);
}

bool m_sqlite_run_in_exclusive_write_transaction(void (*action) (va_list), ...) {
    // 1 - begin exclusive transaction
    // 2 - add verbs within this transaction
    // 3 - commit

    bool results = false;
    if (_runSimpleQuery(sql_start_exclusive_transaction)) {
        va_list va;
        va_start(va, action);
        action(va);
        va_end(va);
        if (_runSimpleQuery(sql_end_exclusive_transaction)) {
            sqlite3_db_cacheflush(db);
            results = true;
        }
    }
    return results;
}

void m_sqlite_get_by_id(int id, list_t results) {
    sqlite3_bind_int(sql_get_row_by_id, 1, id);
    _makeQueryResults(sql_get_row_by_id, results);
}

bool m_sqlite_start_up() {
    if (sqlite3_open_v2(":memory:", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL) == SQLITE_OK) {
        sqlite3_exec(db, "DROP TABLE Verbs;", NULL, NULL, NULL);
        STRING statement_text = "CREATE TABLE Verbs (infinitive TEXT PRIMARY KEY, translation TEXT, time1 TEXT, time2 TEXT) ;";
        if (sqlite3_exec(db, statement_text, NULL, NULL, NULL) == SQLITE_OK) {

            // Prepare all statements
            if (
                    (sqlite3_prepare_v2(db, sql_count_code, -1, &sql_count, NULL) == SQLITE_OK) &&
                    (sqlite3_prepare_v2(db, sql_insert_verb_code, -1, &sql_insert_verb, NULL) == SQLITE_OK) &&
                    (sqlite3_prepare_v2(db, sql_list_all_code, -1, &sql_list_all, NULL) == SQLITE_OK) &&
                    (sqlite3_prepare_v2(db, sql_list_all_by_first_letter_of_inf_code, -1, &sql_list_all_by_first_letter_of_inf, NULL) == SQLITE_OK) &&
                    (sqlite3_prepare_v2(db, sql_search_code, -1, &sql_search, NULL) == SQLITE_OK) &&
                    (sqlite3_prepare_v2(db, sql_start_exclusive_transaction_code, -1, &sql_start_exclusive_transaction, NULL) == SQLITE_OK) &&
                    (sqlite3_prepare_v2(db, sql_end_exclusive_transaction_code, -1, &sql_end_exclusive_transaction, NULL) == SQLITE_OK) &&
                    (sqlite3_prepare_v2(db, sql_get_row_by_id_code, -1, &sql_get_row_by_id, NULL) == SQLITE_OK)
            ) {
                return true;
            } else {
                printf("\n%s\n", sqlite3_errmsg(db));
                m_sqlite_shut_down();
                return false;
            }
        } else {
            printf("\n%s\n", sqlite3_errmsg(db));
            m_sqlite_shut_down();
            return false;
        }
    } else {
        printf("\n%s\n", sqlite3_errmsg(db));
        return false;
    }
}

void m_sqlite_shut_down() {
    sqlite3_finalize(sql_list_all);
    sqlite3_finalize(sql_list_all_by_first_letter_of_inf);
    sqlite3_finalize(sql_insert_verb);
    sqlite3_finalize(sql_count);
    sqlite3_finalize(sql_search);
    sqlite3_finalize(sql_start_exclusive_transaction);
    sqlite3_finalize(sql_end_exclusive_transaction);
    sqlite3_finalize(sql_get_row_by_id);
    sqlite3_close_v2(db);
}

STRING m_sqlite_get_last_error_message() {
    return sqlite3_errmsg(db);
}
