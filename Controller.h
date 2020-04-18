//
// Created by mfran on 24/01/2020.
//

#ifndef IRREGULARVERBS_CONTROLLER_H
#define IRREGULARVERBS_CONTROLLER_H

/**
 * This function handles the proper execution of the whole application.
 *
 * @return One of the values EXIT_BECAUSE_* or EXIT_SUCCESS.
 */
int run();

void controller_handle_exercise();
void controller_handle_list();
void controller_handle_search();

#endif //IRREGULARVERBS_CONTROLLER_H
