//
// Created by Martin on 16/01/2020.
//

#include "Verb.h"

static bool _matchesField(STRING potential, MultiStrings* fieldFromVerb, bool strictly) {
    return strictly ?
        matchesMultiStrings(potential, fieldFromVerb) :
        isSubstringOfMultiStrings(potential, fieldFromVerb);
}

bool matchesInfinitive(STRING potential, const Verb* verb, bool strictly) {
    return _matchesField(potential, verb->infinitive, strictly);
}

bool matchesTranslation(STRING potential, const Verb* verb, bool strictly) {
    return _matchesField(potential, verb->translation, strictly);
}

bool matchesTime1(STRING potential, const Verb* verb, bool strictly) {
    return _matchesField(potential, verb->time1, strictly);
}

bool matchesTime2(STRING potential, const Verb* verb, bool strictly) {
    return _matchesField(potential, verb->time2, strictly);
}

Verb* makeVerbFromStrings(STRING infinitive, STRING translation, STRING time1, STRING time2) {
    MultiStrings* inf = makeMultiStrings(infinitive);
    MultiStrings* tra = makeMultiStrings(translation);
    MultiStrings* ti1 = makeMultiStrings(time1);
    MultiStrings* ti2 = makeMultiStrings(time2);

    return makeVerbFromMultiStrings(inf, tra, ti1, ti2);
}

Verb* makeVerbFromMultiStrings(MultiStrings* infinitive, MultiStrings* translation, MultiStrings* time1, MultiStrings* time2) {
    Verb* output = malloc(sizeof(Verb));
    output->infinitive = infinitive;
    output->translation = translation;
    output->time1 = time1;
    output->time2 = time2;
    return output;
}

Verb* copyVerb(const Verb* input) {
    Verb* output = malloc(sizeof(Verb));
    *output = (Verb) {
        .infinitive = copyMultiStrings(input->infinitive),
        .translation = copyMultiStrings(input->translation),
        .time1 = copyMultiStrings(input->time1),
        .time2 = copyMultiStrings(input->time2)
    };
    return output;
}

void freeVerb(Verb* v) {
    freeMultiStrings(v->infinitive);
    freeMultiStrings(v->translation);
    freeMultiStrings(v->time1);
    freeMultiStrings(v->time2);
    free(v);
}
