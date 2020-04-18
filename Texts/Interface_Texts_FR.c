//
// Created by mfran on 24/01/2020.
//

#include "Interface_Texts.h"
#if LANG_INTERFACE == French

/* WELCOME SCREEN */
const STRING welcome_screen_title = "Verbes irréguliers";
const STRING welcome_screen_central_text = "Merci de patienter...";

/* MAIN MENU */
const STRING main_menu_title = "Menu principal";
const STRING main_menu_header = "Tapez la lettre correspondante à votre choix";
const STRING main_menu_choices_verbose[4] = {
        "Liste alphabétique des verbes",
        "Recherche manuelle",
        "Exercices",
        "Quitter"
};

/* LIST VERBS */
const STRING list_title_beginning = "Liste";
const STRING verb_column_headers[4] = {
        "Infinitif", "Traduction",
#if LANG_VERBS == German
        "Prétérit", "Parfait"
#endif
};

/* SEARCH VERBS */
const STRING search_title_beginning = "Recherche";

/* EXERCISES */
const STRING exercises_title = "Exercice";

// just used during implementation, not for release
const STRING csv_file_name = MAKE_CSV_FILE_NAME("verbs.csv");

#endif
