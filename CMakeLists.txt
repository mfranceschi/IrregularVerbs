cmake_minimum_required(VERSION 3.0) # I do not know what to put here ^v^
project(IrregularVerbs LANGUAGES C) # C program
set(CMAKE_C_STANDARD 11)            # C11 standard
add_executable(${PROJECT_NAME})

# Directories settings
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
include_directories(utils Texts .)

# Find the Curses library.
# It might well be Curses, NCurses or PDCurses. Who knows?
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_compile_definitions(
        CURSES_HAVE_CURSES_H=$<BOOL:${CURSES_HAVE_CURSES_H}>
        CURSES_HAVE_NCURSES_H=$<BOOL:${CURSES_HAVE_NCURSES_H}>
        CURSES_HAVE_NCURSES_NCURSES_H=$<BOOL:${CURSES_HAVE_NCURSES_NCURSES_H}>
        CURSES_HAVE_NCURSES_CURSES_H=$<BOOL:${CURSES_HAVE_NCURSES_CURSES_H}>
)

# Preprocessor macro: 1 if we are in debug mode, 0 otherwise.
set(DEBUG_MODE 1)
add_compile_definitions(DEBUG_MODE=${DEBUG_MODE})

# Tell SQLite not to add thread-safety policy.
add_compile_definitions(SQLITE_THREADSAFE=0)

# Add sources.
file(GLOB SOURCE_FILES ./*.c utils/*.c Texts/*.c View/*.c)
add_subdirectory(extlibs)

# Declare the executable.
target_sources(${PROJECT_NAME}
        PUBLIC ${SOURCE_FILES})

# Link Curses.
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})

# Link math and Dynamic Linking libraries.
if (NOT MSVC)
    target_link_libraries(${PROJECT_NAME} m ${CMAKE_DL_LIBS})
endif()

# Add warnings
set(WarningsAsErrors FALSE)
if(MSVC)
    add_compile_options(/W4)
    if (${WarningsAsErrors})
        add_compile_options(/WX)
    endif()
else()
    add_compile_options(-Wall -Wextra -pedantic)
    if (${WarningsAsErrors})
        add_compile_options(-Werror)
    endif()
endif()
