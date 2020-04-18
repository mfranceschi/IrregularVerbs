//
// Created by Martin on 17/01/2020.
//

#include "View/IncludeCurses.h"
#include "Interface_Texts.h"
#include "View/NCurses_Outputs_Helpers.h"
#include "View.h"
#include "ViewInternals.h"
#include "View/NCurses_Inputs_Driver.h"

WINDOW* title_win = NULL;
WINDOW* title_text_win = NULL;
WINDOW* contents_win = NULL;

void view_set_title(STRING t, bool centered) {
    if (centered) {
        ncurses_print_at_center(title_text_win, 0, 0, getmaxx(title_text_win), t);
    } else {
        wclear(title_text_win);
        mvwaddstr(title_text_win, 0, 0, t);
    }
}

void view_show_welcome_screen() {
    noecho();
    view_set_title(welcome_screen_title, true);
    wclear(contents_win);
    ncurses_print_at_center(title_win, 1, 0, getmaxx(title_win), welcome_screen_central_text);
    view_refresh_screen();
}

void view_show_main_menu() {
    view_set_title(main_menu_title, true);
    wclear(contents_win);
    mvwaddstr(contents_win, 0, 0, main_menu_header);
    mvwprintw(
            contents_win, 2, 0,
            "[L] - %s. \n[S] - %s. \n[E] - %s. \n[Q] - %s. ",
            main_menu_choices_verbose[0],
            main_menu_choices_verbose[1],
            main_menu_choices_verbose[2],
            main_menu_choices_verbose[3]);
    view_refresh_screen();
}

Command view_ask_user_choice(bool can_go_back) {
    return ncurses_input_user_choice(contents_win, can_go_back);
}

CHARACTER view_ask_user_letter(bool can_escape, bool can_arrows, bool can_backspace) {
    wmove(title_text_win, 0, 0);
    return ncurses_input_user_letter(title_text_win, can_escape, can_arrows, can_backspace);
}

void view_show_verbs_list(void *verbs) {
    struct x * pointed_struct;
    int current_row = ROW_OF_HEADER + 2;
    int current_color_index = COLOR_PAIR_ONE;
    while (verbs != NULL && current_row < getmaxy(contents_win)) {
        pointed_struct = verbs;

        wattron(contents_win, COLOR_PAIR(current_color_index));
        current_row = ncurses_table_print_one_verb(contents_win, current_row, 0, len_cols, false, getmaxx(contents_win) - current_row, pointed_struct->verb);
        wattroff(contents_win, COLOR_PAIR(current_color_index));

        COLOR_VERB_LOOP(current_color_index);
        verbs = pointed_struct->next;
        ++current_row;
    }
    wmove(contents_win, current_row, 0);
    wclrtobot(contents_win);
}

void view_show_table_headers() {
    ncurses_table_print_one_row(contents_win, ROW_OF_HEADER, 0, len_cols, true, verb_column_headers);
    wmove(contents_win, ROW_OF_HEADER + 1, 0);
    for(int i=0; i<getmaxx(contents_win); i++) {
        waddch(contents_win, '=');
    }
}

STRING view_get_search_string() {
    ncurses_input_buffer_reset();
    wmove(title_text_win, 0, 0);
    view_set_title(search_title_beginning, false);
    waddstr(title_text_win, " - ");
    ncurses_input_buffer_handle_user_input(title_text_win);
    return ncurses_input_buffer_get();
}

Buffer_Command view_get_search_command() {
    wmove(title_text_win, 0, 0);
    return ncurses_input_buffer_get_command(title_text_win);
}

#undef ROW_OF_HEADER
