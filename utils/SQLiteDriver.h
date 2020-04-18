//
// Created by mfran on 20/01/2020.
//

#ifndef IRREGULARVERBS_SQLITEDRIVER_H
#define IRREGULARVERBS_SQLITEDRIVER_H

#include "VerbsContainer.h"

/**
 * Searches for any verb with this substring in the database.
 * Fills the output object with the results.
 *
 * @param substring The substring to search.
 * @param output The output to fill.
 */
void m_sqlite_search_substring(STRING substring, list_t output);

/**
 * Runs a simple INSERT query so that :
 * - the verb is converted to STRING's
 * - then bound to the query
 * - then inserted in the database.
 *
 * @param verb The Verb instance to bind.
 * @return true on success, false on failure
 */
bool m_sqlite_addVerb(const Verb* verb);

/**
 * @return The number of values in the table.
 */
size_t m_sqlite_get_count();

/**
 * @param output All verbs will be written here.
 */
void m_sqlite_get_all(list_t output);

/**
 * @param start_substring The starting substring in the infinitive column.
 * @param output All verbs will be written here.
 */
void m_sqlite_get_by_first_letters_of_infinitive(STRING start_substring, list_t output);

/**
 * Performs the given action in a transaction in EXCLUSIVE WRITE mode.
 *
 * @param action The function to run.
 * @return true on success, false on failure.
 */
bool m_sqlite_run_in_exclusive_write_transaction(void (* action) (va_list), ...);

/**
 * Returns a list of 0 or 1 verb, that verb being at the given index. .
 * @param id The row ID
 * @param The list_t to fill
 */
void m_sqlite_get_by_id(int id, list_t results);

/**
 * @return true if the database is well started.
 */
bool m_sqlite_start_up();

/**
 * Shuts down the database and releases all resources.
 */
void m_sqlite_shut_down();

/**
 * @return the error message (don't worry about memory).
 */
STRING m_sqlite_get_last_error_message();

#endif //IRREGULARVERBS_SQLITEDRIVER_H
