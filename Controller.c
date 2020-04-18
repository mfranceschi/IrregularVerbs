//
// Created by Martin on 24/01/2020.
//

#include "Controller.h"
#include "Utils.h"
#include "VerbsContainer.h"
#include "View.h"

static void _controller_start_up(va_list list) {
    UNUSED(list);
    view_start_up();
    atexit(view_shut_down);
    view_show_welcome_screen();
    container_start_up();
    fill_verbs_container();
    atexit(container_shut_down);
}

static void _controller_shut_down(va_list list) {
    UNUSED(list);
    container_shut_down();
    view_shut_down();
}

int run() {
    Command input_command = BACK_HOME;
    run_and_wait(500000, _controller_start_up);

    while (input_command != QUIT) {
        view_show_main_menu();
        input_command = view_ask_user_choice(false);
        switch (input_command) {
            case LIST:
                controller_handle_list();
                break;

            case SEARCH:
                controller_handle_search();
                break;

            case EXERCISE:
                controller_handle_exercise();
                break;

            default:
                exit(EXIT_BECAUSE_UNEXPECTED);
        }
        container_freeResults();
    }
    _controller_shut_down(NULL);
    return EXIT_SUCCESS;
}
