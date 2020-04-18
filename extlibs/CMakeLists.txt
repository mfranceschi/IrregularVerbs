# This file just sets the files to compile for the extlibs in a variable "EXTLIBS_SOURCE_FILES"
# which is available at parent directory level.

# Ensure that they are well included.
# The SYSTEM parameter makes the potential warnings disappear.
include_directories(Contiki_2.6 SQLite)

# Set the variable's contents and make it available (and usable) at parent level.
target_sources(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Contiki_2.6/list.c
        ${CMAKE_CURRENT_SOURCE_DIR}/SQLite/sqlite3.c
)
