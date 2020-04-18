//
// Created by Martin on 22/02/2020.
//

#include <locale.h>
#include "Utils.h"
#include "View/IncludeCurses.h"
#include "ViewInternals.h"

void view_start_up() {
    setlocale(LC_ALL, ""); // for wide characters support (it failed!)
    if (initscr() == NULL) {
        exit(EXIT_BECAUSE_CURSES_ISSUE);
    }
    wclear(stdscr);
    curs_set(0);

    // initialize the colors
    // I do not check has_colors neither can_change_colors because using color functions cannot be harmful
    start_color();
    init_pair(COLOR_DEFAULT, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_PAIR_ONE, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_PAIR_TWO, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_PAIR_THREE, COLOR_RED, COLOR_BLACK);

    // initialize the windows
    int screen_x, screen_y;
    getmaxyx(stdscr, screen_y, screen_x);
    title_win = newwin(3, 0, 0, 0);
    contents_win = newwin(screen_y - 3, 0, 3, 0);
    title_text_win = derwin(title_win, 1, screen_x - 4, 1, 2);

    // fill the title window
    wborder(title_win, '#', '#', '#', '#', '#', '#', '#', '#');
}

void view_refresh_screen() {
    touchwin(title_win);
    wrefresh(title_text_win);
    wrefresh(title_win);
    wrefresh(contents_win);
}

void view_clear_contents() {
    werase(contents_win);
}

void view_shut_down() {
    if (!isendwin()) {
        delwin(title_text_win);
        delwin(contents_win);
        delwin(title_win);
        endwin();
    }
}
