# Irregular Verbs

## Summary

This simple program shall allow the user to visualize and test (or even train) its knowledge with irregular verbs in some language (originally German).

The verbs are dealt with like they are tuples of (infinitive form, translation, form at time 1, form at time 2), with every field being easily customizable. Even more: each field can hold several values for each verb (example: several translations for one verb).

At the beginning, it reads a CSV file and stores all the verbs in memory. Then the user is given a graphical interface that allows him/her to choose its next activity between:

* List verbs in alphabetical order and filtered by first letter.
* Search any verb by a substring.
* Test its knowledge by doing some exercise. One line is displayed, an incomplete line that the user shall fill the blanks in. The user can also ask for the solution.

## Implementation proposition

* Language: `C`
* Display: CLI with `curses`
* Verbs in-memory storage: SQLite
* Design patterns: MVC, ?
* No threads
* A Python script fetches the verbs from `https://www.allemandfacile.com/exercices/exercice-allemand-2/exercice-allemand-22677.php` (only once, if the `.CSV` file is missing).

### Directory organization

Current dir state, it was not something I planned. 

* `exlibs` folder: it contains the external, portable and lightweight libraries I used. The contents of the files are absolutely untouched.  
  * SQLite: the famous SQLite library. I removed the unnecessary files. One of the compilation parameters is to disable SQLite's multithreading security policies in order to enhance performances. 
  * Contiki_2.6: I only used the linked-list module. 
* `rsc` folder
  * `get_verbs.py`: a Python script I used to extract the German verbs from a website. I did not spend too much time on it! Normally a Python virtual environment comes with it...
  * `verbs.csv`: (to be renamed later) list of German irregular verbs in CSV format. 
* `Texts` folder: it contains the strings used by the C program for the user interface and the CSV file name.
  * `Interface_Texts.h`: lists the shared strings and also declares two variables (they can be easily changed) that specify the user interface language and the language of the irregular verbs. 
  * `Interface_Texts_FR.c`: implements the strings for French. 
  * This module is designed to be very modular and we can easily add a new language. 
* `utils` folder: various utilities in `.h` and `.c` pairs. 
  * `Utils`: bric-a-brac of utilities. The most important function here is the one that fills the container by reading the CSV.
  * `Strings`: provides type declarations and an exotic string type: the MultiStrings! Actually it is just an array of strings.  
  * `ftime`: I had to re-implement myself some functions of the famous header `sys/time.h` because MinGW says it is deprecated. I had to use the Windows API so it is very long to compile. 
  * `SQLiteDriver`: it contains all the SQLite-specific commands. 
  * `NCurses_Inputs_Driver`: it contains a few functions that only handle inputs from a NCurses window. 
* The **MVC design pattern** implemented here (in C, please do not laugh) involves the following modules: `Controller`, `View` and `Verb`. 
* The `VerbsContainer` module is an interface between the application and the SQLite driver. 

## Windows concepts (the final layout may have changed)

### Welcome screen
```
####################################
#          (some title)            #
####################################


          Now loading...


```

### Main menu screen
```
####################################
#          (some title)            #
####################################

(Some guideline)...

1 - (choice 1, list)
2 - (choice 2, search)
3 - (choice 3, exercise)
4 - (choice 4, quit)
```

### List screen

Each time the user presses an alphabetic key, the screen updates with the new results. 
The user may quit this screen using the ESCAPE key.

```
##################################################
#                      List - k                  # (For letter k)
##################################################

(infinitive) | (translation) | (time 1) | (time 2) (Headers)
==================================================
(infinitive) | (translation) | (time 1) | (time 2) (Instance 1)
(infinitive) | (translation) | (time 1) | (time 2) (Instance 2)
...
```

### Search screen

Each time the user presses an alphabetic key or BACKSPACE, the screen updates with the new results. An empty input (after several BACKSPACES) provides no results. The user may quit using the ESCAPE key. 

```
##################################################
#                  Search - xyz                  # (For input xyz)
##################################################

(infinitive) | (translation) | (time 1) | (time 2) (Headers)
==================================================
(infinitive) | (translation) | (time 1) | (time 2) (Instance 1)
(infinitive) | (translation) | (time 1) | (time 2) (Instance 2)
...
```

### Exercises screen

```
##################################################
#                 Exercise - 1/2                 # (User's score is 1 over 2)
##################################################

(infinitive):   .                                  (Not given, the user must fill the field)
(translation):  .                                  (Not given, the user must fill the field)
(time 1):       X                                  (Given, nothing to do)
(time 2):       Y                                  (Given, nothing to do)

```
