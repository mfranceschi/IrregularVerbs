//
// Created by Martin on 17/02/2020.
//

#include <math.h>
#include "NCurses_Outputs_Helpers.h"
#include "Utils.h"

void ncurses_table_print_one_row(WINDOW* win, int row_i, int col_i, int col_width, bool centered, const STRING texts[4]) {
    UNUSED(col_i);
    int cur_pos = 0;
    static const STRING separator = " | ";
    static const int sep_len = 3;
    int i;

    /* 1 - CLEAR THE LINE */
    wmove(win, row_i, 0);
    for (int j=0; j<getmaxx(win); j++) {
        waddch(win, ' ');
    }

    /* 2 - DO THE DAMN JOB */
    for (i=0; i<4; i++) {
        if (centered) {
            ncurses_print_at_center(win, row_i, cur_pos, col_width, texts[i]);
        } else {
            mvwaddstr(win, row_i, cur_pos, texts[i]);
        }
        wmove(win, row_i, cur_pos + col_width);
        if (i != 4-1) {
            waddstr(win, separator);
            cur_pos += col_width + sep_len;
        }
    }
    wmove(win, row_i + 1, 0);
}

int ncurses_table_print_one_verb(WINDOW* win, int row_i, int col_i, int col_width, bool centered, int remaining, Verb* v) {
    MultiStrings decl[] = {
            *(v->infinitive),
            *(v->translation),
            *(v->time1),
            *(v->time2)
    };
    int max_iter = (int) fminl(
            remaining,
            fmaxl (decl[0].length,
                   fmaxl(decl[1].length,
                         fmaxl(decl[2].length, decl[3].length))));
    STRING texts[4];

    for (int i=0; i<max_iter; i++) {
        for(int j=0; j<4; j++) {
            texts[j] = (i < decl[j].length) ? decl[j].array[i] : "";
        }
        ncurses_table_print_one_row(win, row_i + i, col_i, col_width, centered, texts);
    }

    return row_i + max_iter - 1;
}

void ncurses_print_at_center(WINDOW* win, int start_y, int start_x, int width, STRING text) {
    int len = (int) strlen(text);
    if (len <= width) {
        mvwprintw(win, start_y, start_x, "%*s", width, "");
        mvwaddstr(win, start_y, start_x + ((width - len) / 2), text);
    }
}
