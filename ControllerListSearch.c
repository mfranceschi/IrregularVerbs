//
// Created by Martin on 14/02/2020.
//

#include <ctype.h>
#include <stdio.h>
#include "Interface_Texts.h"
#include "VerbsContainer.h"
#include "View.h"
#include "Utils.h"

#define LIST_OFFSET_DECREASE(o) if (o) {o--;} (void)0
#define LIST_OFFSET_INCREASE(o,len) if (o < len - 1) {o++;} (void)0

void controller_handle_list() {
    size_t len_of_title = strlen(list_title_beginning) + strlen(" - ") + 1;
    WRITEABLE_STRING title = calloc(len_of_title + 1, 1);
    char input = get_random_letter();
    list_t results_as_list = NULL;
    list_node* current_results;
    int offset = 0;

    view_clear_contents();
    view_show_table_headers();

    while(input != KB_KEY_ESC) {
        switch (input) {
            case KB_KEY_UP:
              LIST_OFFSET_DECREASE(offset);
                break;
            case KB_KEY_DOWN:
                LIST_OFFSET_INCREASE(offset, list_length((results_as_list)));
                break;
            default:
                if (isalpha(input)) { // i cannot find why it is necessary (^D sometimes when lateral arrow keys)
                    snprintf(title, len_of_title + 1, "%s - %c", list_title_beginning, input);
                    view_set_title(title, true);

                    results_as_list = container_getVerbsByFirstLetter(input);
                    offset = 0;
                }
                break;
        }
        current_results = list_head(results_as_list);
        for (int i=0; i<offset; i++) {
            current_results = current_results->next;
        }
        view_show_verbs_list(current_results);
        view_refresh_screen();
        input = view_ask_user_letter(true, true, false);
    }
    free(title);
}

void controller_handle_search() {
    list_t results_as_list = NULL;
    list_node* current_results;
    int offset = 0;
    Buffer_Command cmd = BUFFER_RESET;
    STRING input_string;

    view_clear_contents();
    view_show_table_headers();

    while (1) {
        switch(cmd) {
            case BUFFER_RESET:
                input_string = view_get_search_string();
                results_as_list = container_getVerbsBySubstring(input_string);
                offset = 0;
                break;
            case BUFFER_BACK_HOME:
                return;
            case BUFFER_KEY_UP:
                LIST_OFFSET_DECREASE(offset);
                break;
            case BUFFER_KEY_DOWN:
                LIST_OFFSET_INCREASE(offset, list_length(results_as_list));
                break;
            default:
                exit(EXIT_BECAUSE_UNEXPECTED);
        }
        current_results = list_head(results_as_list);
        for (int i=0; i<offset; i++) {
            current_results = current_results->next;
        }
        view_show_verbs_list(current_results);
        view_refresh_screen();
        cmd = view_get_search_command();
    }
}
