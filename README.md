# Irregular Verbs

This is a simple project I have led in solo during two weeks. It is a simple CLI program that allows the consultation of lists of irregular verbs in any language. Its final purpose is to be used to train and exercise towards the knowledge of these verbs. 

To run it you need to compile it by yourself:

* Microsoft Windows OS
* MinGW (a Windows C++ environment). I do not know everything that you might need, which packages are very required, apart from these ones:
  * CMake
  * GCC
  * `libncurses` (needed by the CLI)
  * It seems that `libpthread` is not required (neither of the libs I used do require threads). 
* Run CMake. I personally used the CLion IDE.
* Use Windows Explorer to locate the executable (possible path: `cmake-build-debug/IrregularVerbs.exe`) and run it from here. 
  * You can run it from CLion but ncurses does works with that IDE. 

## Current state

Unfortunately I have spent too much time on this project: I used a lot of low-level and time-consuming technologies, it was on purpose. Even though it is not finished I am stopping working on it (as of today, Feb. 8th, 2020). I may finish and/or polish it later. 

The current implementation is a French interface displaying German irregular verbs. The **list** menu works fine. The **search** menu works only once per execution (!). The **exercise** menu is not implemented yet.  

## Future?

What do I plan to do in the future (by order of priority):

* [DONE] Fix the **search** functionality (it works fine on the first try, but on the next attempts the results are not refreshed, we keep the original results).
* Implement the **exercise** functionality.
* [DONE] Polish the german verbs CSV. 
* [DONE] Randomize the first displayed letter when starting the **list**. 
* Put unused functions in conditional compilation.
  * [Update] Partially done. Some unused functions are removed.  
* Finish and polish the documentation of methods and modules. 
* Check if it might be possible to use CMake to allow some more flexible cross-platform implementation (as we do not need threads). 
  * [Update] Partially done. More code is cross-platform designed. Some testing will be required. 
* Make guides on how to extend it with other languages.
* [DONE] Change the behavior if the CSV file is not found: just exit. Perhaps display a specific error message.
* Examine workarounds against bad UTF-8 handling. 
* [DONE] Protect the **search** functionality against empty input strings.  
* Fix the **search** input weird behavior (too many backspaces = go out of writeable field). 
* Enhance the colors by not resetting them when we go up and down. 
* Do more checks on memory leaks. 
