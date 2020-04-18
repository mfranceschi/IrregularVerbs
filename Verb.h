//
// Created by mfran on 15/01/2020.
//

#ifndef IRREGULARVERBS_VERB_H
#define IRREGULARVERBS_VERB_H

#include <stdbool.h>
#include "Strings.h"

typedef struct Verb_s {
    MultiStrings* infinitive;
    MultiStrings* translation;
    MultiStrings* time1;
    MultiStrings* time2;
} Verb;

bool matchesInfinitive(STRING, const Verb*, bool strictly);
bool matchesTranslation(STRING, const Verb*, bool strictly);
bool matchesTime1(STRING, const Verb*, bool strictly);
bool matchesTime2(STRING, const Verb*, bool strictly);

Verb* makeVerbFromStrings(STRING infinitive, STRING translation, STRING time1, STRING time2);
Verb* makeVerbFromMultiStrings(MultiStrings* infinitive, MultiStrings* translation, MultiStrings* time1, MultiStrings* time2);
Verb* copyVerb(const Verb*);
void freeVerb(Verb*);

#endif //IRREGULARVERBS_VERB_H
