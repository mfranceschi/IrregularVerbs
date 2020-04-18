//
// Created by Martin on 16/01/2020.
//

#include <ctype.h>
#include <string.h>
#include "Strings.h"
#include "Utils.h"

const STRING SEPARATOR = ",";
const size_t LEN_SEPARATOR = 1; // length of SEPARATOR

MultiStrings* makeMultiStrings(STRING input) {
    // Algorithm:
    // 1 - Allocate (number of separators + 1) pointers of strings = initial_length
    // 2 - Run through the string and allocate a string only if necessary (non-empty string)

    MultiStrings* output = malloc(sizeof(MultiStrings)); // to be returned
    size_t initial_length = count_occurrences_of_substring(SEPARATOR, input) + 1; // maximum number of arrays allocated
    WRITEABLE_STRING* array = calloc(initial_length * sizeof(STRING), 1); // c-alloc so that a free on NULL is not harmful
    STRING end_of_current_substring;
    size_t length_of_current_substring;
    STRING beginning_of_current_substring = input;
    size_t real_length = 0;

    for (size_t i = 0; i < initial_length; i++) {
        // skip trailing spaces at the beginning
        while(isspace(*beginning_of_current_substring)) {
            beginning_of_current_substring++;
        }

        // get end of current substring
        if ((end_of_current_substring = strstr(beginning_of_current_substring, SEPARATOR)) == NULL) {
            end_of_current_substring = beginning_of_current_substring + strlen(beginning_of_current_substring);
        }

        // allocate and copy if necessary
        length_of_current_substring = end_of_current_substring - beginning_of_current_substring;
        if (length_of_current_substring > 0) {
            array[real_length] = malloc(length_of_current_substring + 1);
            strncpy(array[real_length], beginning_of_current_substring, length_of_current_substring);
            array[real_length][length_of_current_substring] = '\0';
            real_length++;
        }
        beginning_of_current_substring = end_of_current_substring + 1;
    }

    output->length = real_length;
    output->array = (STRING *) array;
    return output;
}

MultiStrings* copyMultiStrings(const MultiStrings* input) {
    size_t length = input->length;
    WRITEABLE_STRING* array = malloc(sizeof(STRING) * length);

    for (size_t i = 0; i < length; ++i) {
        size_t str_len = strlen(input->array[i]);
        array[i] = malloc(str_len + 1);
        strcpy(array[i], input->array[i]);
    }

    MultiStrings* output = malloc(sizeof(MultiStrings));
    *output = (MultiStrings) {
            .length = length,
            .array = malloc(sizeof(STRING) * length)
    };

    return output;
}

void freeMultiStrings(MultiStrings* ms) {
    for (size_t i = 0; i < ms->length; i++) {
        free((void *) ms->array[i]);
    }
    free(ms->array);
    free(ms);
}

bool isSubstringOfString(STRING potential, STRING toCompareTo) {
    char* result = strstr(toCompareTo, potential);
    return result && result != toCompareTo;
}

bool isSubstringOfMultiStrings(STRING potential, const MultiStrings* toCompareTo) {
    for (size_t i = 0; i < toCompareTo->length; i++) {
        if (isSubstringOfString(potential, toCompareTo->array[i])) {
            return true;
        }
    }
    return false;
}

bool matchesString(STRING potential, STRING toCompareTo) {
    return !strcmp(potential, toCompareTo);
}

bool matchesMultiStrings(STRING potential, const MultiStrings* toCompareTo) {
    for (size_t i = 0; i < toCompareTo->length; i++) {
        if (matchesString(potential, toCompareTo->array[i])) {
            return true;
        }
    }
    return false;
}

STRING makeStringFromMultiStrings(MultiStrings *input) {
    // get total size of string = size of all strings + (n-1) * separator + 1
    // allocate
    // copy all strings up to (n-1) followed by separator
    // copy last string without separator

    size_t ms_len = input->length;

    size_t total_length = ((ms_len - 1) * strlen(SEPARATOR)) + 1;
    for (size_t i = 0; i < ms_len; i++) {
        total_length += strlen(input->array[i]);
    }

    WRITEABLE_STRING output = malloc(total_length);
    WRITEABLE_STRING output_ptr = output;

    for (size_t i = 0; i < ms_len; i++) {
        strcpy(output_ptr, input->array[i]);
        output_ptr += strlen(input->array[i]);

        if (i != ms_len - 1) {
            strcpy(output_ptr, SEPARATOR);
            output_ptr += LEN_SEPARATOR;
        }
    }
    output_ptr[0] = '\0';

    return (STRING) output;
}

void freeStringFromMultiStrings(STRING str) {
    free((void*)str);
}

STRING ensure_ascii(STRING str) {
    bool need_new_string = false;

    for (int i=0; str[i] != '\0'; i++) {
        if (!isprint(str[i])) {
            need_new_string = true;
        }
    }

    if (need_new_string) {
        strlen(str);
        WRITEABLE_STRING output = calloc(strlen(str), 1);
        unsigned int i_input = 0;
        unsigned int i_output = 0;

        for (; str[i_input] != '\0'; i_input++) {
            if (isprint(str[i_input])) {
                output[i_output++] = str[i_input];
            } else {
                switch (str[i_input]) {
                    case '\xC3':
                        switch (str[++i_input]) {
                            case '\x9f':
                                output[i_output++] = 's';
                                output[i_output++] = 's';
                                break;

                            case '\xa0':
                            case '\xa2':
                            case '\xa4':
                                output[i_output++] = 'a';
                                break;

                            case '\xa7':
                                output[i_output++] = 'c';
                                break;

                            case '\xa8':
                            case '\xa9':
                            case '\xaa':
                            case '\xab':
                                output[i_output++] = 'e';
                                break;

                            case '\xac':
                            case '\xad':
                            case '\xae':
                            case '\xaf':
                                output[i_output++] = 'i';
                                break;

                            case '\xb1':
                                output[i_output++] = 'n';
                                break;

                            case '\xb0':
                            case '\xb2':
                            case '\xb3':
                            case '\xb4':
                            case '\xb5':
                            case '\xb6':
                            case '\xb8':
                                output[i_output++] = 'o';
                                break;

                            case '\xb9':
                            case '\xba':
                            case '\xbb':
                            case '\xbc':
                                output[i_output++] = 'u';
                                break;
                        }
                        break;

                }
            }
        }
        free((void *)str);
        return output;
    } else {
        return str;
    }
}
