cmake_minimum_required(VERSION 3.11)
project(CasinoGame)

set(CMAKE_CXX_STANDARD 14)

include_directories(GameLib GamblerLib)

add_library(GameLib GameLib/Game.cpp GameLib/Game.h GameLib/CardGame.cpp GameLib/CardGame.h GameLib/Card.cpp GameLib/Card.h GameLib/TexasHoldem.cpp GameLib/TexasHoldem.h GameLib/Jackpot.cpp GameLib/Jackpot.h)
add_library(GamblerLib GamblerLib/Gambler.cpp GamblerLib/Gambler.h GamblerLib/JackpotBot.cpp GamblerLib/JackpotBot.h GamblerLib/GamblerBot.cpp GamblerLib/GamblerBot.h GamblerLib/TexasBot.cpp GamblerLib/TexasBot.h)

add_executable(GameExample GameExample/GameExample.cpp)
target_link_libraries(GameExample PUBLIC GameLib GamblerLib)

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
target_link_libraries(GameTest PUBLIC gtest_main GameLib GamblerLib)
target_link_libraries(CardGameTest PUBLIC gtest_main GameLib GamblerLib)
target_link_libraries(CardTest PUBLIC gtest_main GameLib)
target_link_libraries(TexasHoldemTest PUBLIC gtest_main GameLib GamblerLib)
target_link_libraries(JackpotTest PUBLIC gtest_main gmock_main GameLib GamblerLib)

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

