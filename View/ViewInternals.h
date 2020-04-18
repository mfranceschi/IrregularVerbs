//
// Created by Martin on 22/02/2020.
//

#ifndef IRREGULARVERBS_VIEWINTERNALS_H
#define IRREGULARVERBS_VIEWINTERNALS_H

#include "IncludeCurses.h"
#include "Verb.h"

struct x{struct x* next; Verb* verb;};
#define ROW_OF_HEADER 1
#define len_cols ((getmaxx(contents_win) / 4) - 2)

extern WINDOW* title_win;
extern WINDOW* title_text_win;
extern WINDOW* contents_win;

#define COLOR_DEFAULT 1
#define COLOR_PAIR_ONE 2
#define COLOR_PAIR_TWO 3
#define COLOR_PAIR_THREE 4
#define COLOR_VERB_LOOP(cur) cur = (\
    (cur == COLOR_PAIR_ONE) ? COLOR_PAIR_TWO : \
    (cur == COLOR_PAIR_TWO) ? COLOR_PAIR_THREE : \
    COLOR_PAIR_ONE)

#endif //IRREGULARVERBS_VIEWINTERNALS_H
