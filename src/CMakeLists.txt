# src/CMakeLists.txt

SET(SOURCES
  main.cc
)

SET(MINESWEEPER_SOURCES
  minefield.cc
  minesweeper.cc
  utils.cc
)
SET (CMAKE_CXX_FLAGS "-lncurses -ltinfo")

add_library(minesweeperlib STATIC ${MINESWEEPER_SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} minesweeperlib)
add_dependencies(${PROJECT_NAME} minesweeperlib)

install(TARGETS ${PROJECT_NAME} DESTINATION ../bin)
