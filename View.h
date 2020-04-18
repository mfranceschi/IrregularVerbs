//
// Created by Martin on 17/01/2020.
//

#ifndef IRREGULARVERBS_VIEW_H
#define IRREGULARVERBS_VIEW_H

#include "stdint.h"
#include "Strings.h"
#include "Verb.h"

#define KB_KEY_ESC        (char) 27
#define KB_KEY_UP         (char) 1
#define KB_KEY_DOWN       (char) 2
#define KB_KEY_BACKSPACE  (char) 3

typedef enum {
    LIST, SEARCH, EXERCISE, BACK_HOME, QUIT
} Command;

typedef enum {
    BUFFER_BACK_HOME,
    BUFFER_RESET,
    BUFFER_KEY_UP,
    BUFFER_KEY_DOWN
} Buffer_Command;

#define VERB_FIELD_INFINITIVE    0x1
#define VERB_FIELD_TRANSLATION   0x2
#define VERB_FIELD_TIME_1  0x3
#define VERB_FIELD_TIME_2        0x4

/**
 * This is used for the "exercises" functionality.
 * - Field "user_score" gives the current score of the user.
 * - Field "total_score" gives the upper bound of the user's score.
 * - Field "fields_to_display" indicates whether or not to display the fields from the verb. It should be filled
 *   using bitwise operators using the macros VERB_FIELD_X.
 */
typedef struct {
    union {
        struct {
            uint8_t user_score;
            uint8_t total_score;
        };
        uint16_t scores;
    };
    uint8_t fields_to_display;
} ExerciseParams;

/**
 * Starts, allocates and run every view initialization script.
 */
void view_start_up();

/**
 * Shows up a welcome screen without any menu.
 * May indicate that loading is in progress.
 *
 * @param title Title of that screen.
 * @param central_text The central text indicating that we are loading now.
 */
void view_show_welcome_screen();

/**
 * Shows the program's main menu. The user does not have control yet.
 *
 * @param title Title of that screen.
 * @param guideline The guideline below the title.
 * @param choices Explanation of each of the four options.
 */
void view_show_main_menu();

/**
 * Returns the user's input as a Command.
 *
 * @param can_go_back True if the "go back" option is allowed.
 * @return a Command corresponding to the user's input.
 */
Command view_ask_user_choice(bool can_go_back);

/**
 * Returns the user's input as a lowercase character, or ESC.
 *
 * @param can_escape True if the ESC char is allowed.
 * @param can_arrows True if UP and DOWN are allowed.
 * @param can_backspace True if BACKSPACE is allowed.
 * @return a char or ESC or UP or DOWN.
 */
CHARACTER view_ask_user_letter(bool can_escape, bool can_arrows, bool can_backspace);

/**
 * Sets the current view's Title.
 * If the string is too long then no-op.
 * It should not be explicitly called except for dev.
 *
 * @param t The new title.
 * @param centered If true then title is centered, if not it is left-aligned.
 */
void view_set_title(STRING t, bool centered);

/**
 * Show a list of verbs.
 * The `verbs` pointer shall point to a linked list of {.next: void*, .verb: Verb*} (declared in that order).
 *
 * @param verbs Linked list of verbs.
 */
void view_show_verbs_list(void *verbs);

/**
 * Displays the table headers.
 */
void view_show_table_headers();

/**
 * // todo define specs
 * @return
 */
STRING view_get_search_string();

/**
 * // todo define specs
 * @return
 */
Buffer_Command view_get_search_command();

WRITEABLE_STRING * view_exercise(const Verb* verb, ExerciseParams scores);

/**
 * If relevant, performs a screen refresh.
 */
void view_refresh_screen();

/**
 * Cleans the contents window but does not perform an explicit refresh.
 */
void view_clear_contents();

/**
 * Closes and releases any resource associated with the view.
 */
void view_shut_down();

#endif //IRREGULARVERBS_VIEW_H
