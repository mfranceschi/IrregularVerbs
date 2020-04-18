//
// Created by Martin on 24/01/2020.
//

#ifndef IRREGULARVERBS_INTERFACE_TEXTS_H
#define IRREGULARVERBS_INTERFACE_TEXTS_H

#include "Strings.h"

#define LANG_INTERFACE French
#define LANG_VERBS German

/* WELCOME SCREEN */
extern const STRING welcome_screen_title;
extern const STRING welcome_screen_central_text;

/* MAIN MENU */
extern const STRING main_menu_title;
extern const STRING main_menu_header;
extern const STRING main_menu_choices_verbose[4];

/* LIST VERBS */
extern const STRING list_title_beginning;
extern const STRING verb_column_headers[4];

/* SEARCH VERBS */
extern const STRING search_title_beginning;

/* EXERCISES */
extern const STRING exercises_title;

extern const STRING csv_file_name;

// To define the CSV file name, please use this macro like this:
// const STRING csv_file_name = _MAKE_CSV_FILE_NAME("myFile.csv").
// It will generate it without you to care about build location.
#define MAKE_CSV_FILE_NAME(csv_file_name) ".." _SEP "rsc" _SEP csv_file_name
#ifdef _WIN32
    #define _SEP "\\"
#else
    #define _SEP "/"
#endif

#endif //IRREGULARVERBS_INTERFACE_TEXTS_H
