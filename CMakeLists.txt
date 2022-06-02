cmake_minimum_required(VERSION 3.11)
project(CasinoGame)

set(CMAKE_CXX_STANDARD 14)

set(PATH_TO_QT5 "D:\\Kody\\Qt5\\5.15.2\\msvc2019_64;C:\\Qt\\5.15.2\\msvc2019_64") # path to your Qt5 directory goes here
if (WIN32)
    set(CMAKE_PREFIX_PATH ${PATH_TO_QT5})
endif (WIN32)
find_package(Qt5Widgets REQUIRED)

include_directories(Casino GameLib GamblerLib GUI)

add_library(GameLib GameLib/Game.cpp GameLib/Game.h GameLib/CardGame.cpp GameLib/CardGame.h GameLib/Card.cpp GameLib/Card.h GameLib/TexasHoldem.cpp GameLib/TexasHoldem.h GameLib/Jackpot.cpp GameLib/Jackpot.h GameLib/Roulette.cpp GameLib/Roulette.h GameLib/GameManager.h GameLib/GameManager.cpp)
add_library(GamblerLib GamblerLib/Gambler.cpp GamblerLib/Gambler.h GamblerLib/JackpotBot.cpp GamblerLib/JackpotBot.h GamblerLib/GamblerBot.cpp GamblerLib/GamblerBot.h GamblerLib/TexasBot.cpp GamblerLib/TexasBot.h GamblerLib/Shop.cpp GamblerLib/Shop.h GamblerLib/RouletteBot.cpp GamblerLib/RouletteBot.h)
set(GUI_SOURCE_FILES GUI/CasinoWindow.h GUI/CasinoWindow.cpp GUI/TexasHoldemGUITableItem.cpp GUI/TexasHoldemGUITableItem.h)
add_executable(GameExample GameExample/TestTexasSimulation.cpp)
target_link_libraries(GameExample PUBLIC GameLib GamblerLib)

add_executable(GameManagerTest GameExample/GameManagerTest.cpp)
target_link_libraries(GameManagerTest PUBLIC GameLib GamblerLib)

set(GUI_TARGETS TexasHoldemUITest JackpotUITest RouletteUITest)
foreach(GUI_TARGET IN LISTS GUI_TARGETS)
    add_executable(${GUI_TARGET} GameExample/${GUI_TARGET}.cpp)
    target_link_libraries(${GUI_TARGET} PRIVATE GameLib GamblerLib Qt5::Widgets)
    if(WIN32)
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            add_custom_command(TARGET ${GUI_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/WindowsQt5files/Debug ${CMAKE_CURRENT_BINARY_DIR})
        else()
            add_custom_command(TARGET ${GUI_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/WindowsQt5files/Release ${CMAKE_CURRENT_BINARY_DIR})
        endif()
        set(WIN_CPP_FILES libgcc_s_seh-1.dll libstdc++-6.dll libwinpthread-1.dll)
        foreach(FILE IN LISTS WIN_CPP_FILES)
            add_custom_command(TARGET ${GUI_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/WindowsQt5files/${FILE} ${CMAKE_CURRENT_BINARY_DIR})
        endforeach()
    endif()
endforeach()

add_executable(Casino Casino.cpp ${GUI_SOURCE_FILES})
target_link_libraries(Casino PRIVATE GameLib GamblerLib Qt5::Widgets)
if(WIN32)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_custom_command(TARGET Casino POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/WindowsQt5files/Debug ${CMAKE_CURRENT_BINARY_DIR})
    else()
        add_custom_command(TARGET Casino POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/WindowsQt5files/Release ${CMAKE_CURRENT_BINARY_DIR})
    endif()
    set(WIN_CPP_FILES libgcc_s_seh-1.dll libstdc++-6.dll libwinpthread-1.dll)
    foreach(FILE IN LISTS WIN_CPP_FILES)
        add_custom_command(TARGET Casino POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/WindowsQt5files/${FILE} ${CMAKE_CURRENT_BINARY_DIR})
    endforeach()
endif()

message("CLion > Visual Studio")

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
if(WIN32)
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif(WIN32)
FetchContent_MakeAvailable(googletest)
enable_testing()

# game tests
add_executable(GameTest GameTest/GameTest.cpp)
add_executable(CardGameTest GameTest/CardGameTest.cpp)
add_executable(CardTest GameTest/CardTest.cpp)
add_executable(TexasHoldemTest GameTest/TexasHoldemTest.cpp)
add_executable(JackpotTest GameTest/JackpotTest.cpp)
add_executable(RouletteTest GameTest/RouletteTest.cpp)
target_link_libraries(GameTest PUBLIC gtest_main GameLib GamblerLib)
target_link_libraries(CardGameTest PUBLIC gtest_main GameLib GamblerLib)
target_link_libraries(CardTest PUBLIC gtest_main GameLib)
target_link_libraries(TexasHoldemTest PUBLIC gtest_main GameLib GamblerLib)
target_link_libraries(JackpotTest PUBLIC gtest_main gmock_main GameLib GamblerLib)
target_link_libraries(RouletteTest PUBLIC gtest_main GameLib GamblerLib)

# gambler tests
add_executable(GamblerTest GamblerTest/GamblerTest.cpp)
add_executable(GamblerBotTest GamblerTest/GamblerBotTest.cpp)
add_executable(JackpotBotTest GamblerTest/JackpotBotTest.cpp)
add_executable(TexasBotTest GamblerTest/TexasBotTest.cpp)
target_link_libraries(GamblerTest PUBLIC gtest_main GamblerLib GameLib)
target_link_libraries(GamblerBotTest PUBLIC gtest_main GamblerLib GameLib)
target_link_libraries(JackpotBotTest PUBLIC gtest_main GameLib GamblerLib)
target_link_libraries(TexasBotTest PUBLIC gtest_main GameLib GamblerLib)

include(GoogleTest)
gtest_discover_tests(GameTest)
gtest_discover_tests(CardGameTest)
gtest_discover_tests(CardTest)
gtest_discover_tests(TexasHoldemTest)
gtest_discover_tests(JackpotTest)
gtest_discover_tests(GamblerTest)
gtest_discover_tests(GamblerBotTest)
gtest_discover_tests(JackpotBotTest)
gtest_discover_tests(TexasBotTest)
gtest_discover_tests(RouletteTest)

