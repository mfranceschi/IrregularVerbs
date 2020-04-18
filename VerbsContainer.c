//
// Created by Martin on 16/01/2020.
//

#include <stdarg.h>
#include "Utils.h"
#include "VerbsContainer.h"
#include "SQLiteDriver.h"

/* Count of verbs, in a cache for optimization. */
static size_t cache_count_of_verbs = 0;

/* List of current results. */
LIST(current_results);

/* Indicates whether the container is running now. */
static bool running = false;

static void _addVerbsLoop(va_list arguments) {
    const Verb** verbs = va_arg(arguments, const Verb**);
    size_t number = va_arg(arguments, size_t);
    for (size_t i = 0; i < number; i++) {
        if (!m_sqlite_addVerb(verbs[i])) {
            return;
        }
    }
}

bool container_addVerbs(const Verb** verbs, size_t number) {
    if (m_sqlite_run_in_exclusive_write_transaction(_addVerbsLoop, verbs, number)) {
        cache_count_of_verbs = 0;
        return true;
    } else {
        return false;
    }
}

list_t container_getVerbsBySubstring(STRING str) {
    container_freeResults();
    list_init(current_results);
    m_sqlite_search_substring(str, current_results);
    return current_results;
}

list_t container_getVerbsByFirstLetter(CHARACTER character) {
    static CHARACTER str_to_put_in_query [2] = {'\0', '\0'};
    str_to_put_in_query[0] = character;
    container_freeResults();
    list_init(current_results);
    m_sqlite_get_by_first_letters_of_infinitive(str_to_put_in_query, current_results);
    return current_results;
}

#if defined(DEBUG_MODE) && DEBUG_MODE == 1
list_t container_getAllVerbs() {
    container_freeResults();
    list_init(current_results);
    m_sqlite_get_all(current_results);
    return current_results;
}
#endif

list_t container_getRandomVerb() {
    container_freeResults();
    list_init(current_results);
    int index_to_get = get_random_int(0, (int)container_getCount());
    m_sqlite_get_by_id(index_to_get, current_results);
    return current_results;
}

size_t container_getCount() {
    if (!cache_count_of_verbs) {
        cache_count_of_verbs = m_sqlite_get_count();
    }
    return cache_count_of_verbs;
}

void container_freeResults() {
    list_node* current_node;
    void* head;
    while ((current_node = list_head(current_results)) != NULL) {
        freeVerb(current_node->verb);
         head = list_head(current_results);
        list_pop(current_results);
        free(head);
    }
}

bool container_start_up() {
    if (!running) {
        return running = m_sqlite_start_up();
    } else {
        return false;
    }
}

void container_shut_down() {
    container_freeResults();
    if (running) {
        running = false;
        m_sqlite_shut_down();
    } else {
        false;
    }
}

#if defined(DEBUG_MODE) && DEBUG_MODE == 1
STRING container_get_last_error() {
    return m_sqlite_get_last_error_message();
}
#endif

bool container_is_running() {
    return running;
}
