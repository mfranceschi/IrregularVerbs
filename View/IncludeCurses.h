//
// Created by Martin on 14/02/2020.
//

#ifndef IRREGULARVERBS_INCLUDECURSES_H
#define IRREGULARVERBS_INCLUDECURSES_H

/**
 * This module is only made to be included anywhere you need the Curses API.
 * It makes the right include directive for NCurses or PDCurses.
 */

#if   CURSES_HAVE_CURSES_H
#include         <curses.h>
#elif CURSES_HAVE_NCURSES_H
#include         <ncurses.h>
#elif CURSES_HAVE_NCURSES_NCURSES_H
#include         <ncurses/ncurses.h>
#elif CURSES_HAVE_NCURSES_CURSES_H
#include         <ncurses/curses.h>
#else
#error "Problem while including Curses."
#endif

#endif //IRREGULARVERBS_INCLUDECURSES_H
