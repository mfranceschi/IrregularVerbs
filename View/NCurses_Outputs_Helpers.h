//
// Created by Martin on 17/02/2020.
//

#ifndef IRREGULARVERBS_NCURSES_OUTPUTS_HELPERS_H
#define IRREGULARVERBS_NCURSES_OUTPUTS_HELPERS_H

#include "IncludeCurses.h"
#include "Verb.h"

/**
 * Prints some text at the center of the given space.
 * The unused space is filled with whitespaces.
 * No-op if string is too long. // TODO change
 *
 * @param win The window to print text in.
 * @param start_y Row of start in window.
 * @param start_x Column of start in window.
 * @param width Number of columns that we have.
 * @param text The text to print.
 */
void ncurses_print_at_center(WINDOW* win, int start_y, int start_x, int width, STRING text);

/**
 * Prints one row similarly to printf("%s | %s | %s | %s\n", texts[0], ...).
 *
 * @param win The window in which we will print.
 * @param row_i The index of the row.
 * @param col_i The index of the column [NOT ACTUALLY USED, WE CONSIDER THE WHOLE LINE].
 * @param col_width The width of each individual column (text space allowed).
 * @param centered If true then we print at the center of each column.
 * @param texts The four strings to print.
 */
void ncurses_table_print_one_row(WINDOW* win, int row_i, int col_i, int col_width, bool centered, const STRING texts[4]);

/**
 * Prints the given verb on one or several rows.
 *
 * @param win The window in which we will print.
 * @param row_i The index of the row.
 * @param col_i The index of the column [NOT ACTUALLY USED, WE CONSIDER THE WHOLE LINE].
 * @param col_width The width of each individual column (text space allowed).
 * @param centered If true then we print at the center of each column.
 * @param remaining The number or remaining allowed rows. We won't print more than remaining rows.
 * @param v The verb of course.
 * @return The current_row of the last printed row
 */
int ncurses_table_print_one_verb(WINDOW* win, int row_i, int col_i, int col_width, bool centered, int remaining, Verb* v);

#endif //IRREGULARVERBS_NCURSES_OUTPUTS_HELPERS_H
