//
// Created by Martin on 15/01/2020.
//

#include "Controller.h"
#include <stdio.h>
#include "Verb.h"
#include "VerbsContainer.h"

#define printf(...) (void)0 /* use this to forbid stdout display */

static void tests_make_verb() {
    bool should_shut_down_after = !container_is_running();
    if (should_shut_down_after) {
        container_start_up();
    }

    Verb* v = makeVerbFromStrings("infinitive", "translation", "time1", "time2");
    printf("Success de l'ajout: %i\n", container_addVerbs((const Verb **) &v, 1));
    freeVerb(v);
    printf("Count: %u\n", container_getCount());

    list_t list = container_getVerbsBySubstring("ti");
    list_node* node = (list_node *) list_head(list);
    printf("Result length: %d\n", list_length(list));
    while (node != NULL) {
        printf("Verbe infinitif: '%s'\n", node->verb->infinitive->array[0]);
        node = list_item_next(node);
    }
    printf("Last error: '%s'\n", container_get_last_error());
    container_freeResults();

    if (should_shut_down_after) {
        container_shut_down();
    }
}

int main(int nargs, char** args) {
    return run();
}
