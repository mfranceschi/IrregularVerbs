//
// Created by Martin on 01/02/2020.
//

#ifndef IRREGULARVERBS_NCURSES_INPUTS_DRIVER_H
#define IRREGULARVERBS_NCURSES_INPUTS_DRIVER_H

#include "IncludeCurses.h"
#include "Utils.h"
#include "View.h"

Command ncurses_input_user_choice(WINDOW* window, bool can_go_back);
CHARACTER ncurses_input_user_letter(WINDOW* window, bool can_escape, bool can_arrows, bool can_backspace);

STRING ncurses_input_buffer_get();
void ncurses_input_buffer_reset();
void ncurses_input_buffer_handle_user_input(WINDOW* window);
Buffer_Command ncurses_input_buffer_get_command(WINDOW* window);

#endif //IRREGULARVERBS_NCURSES_INPUTS_DRIVER_H
