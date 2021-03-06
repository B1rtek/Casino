/**
 * Test program that was used to check if GameManager and its objects don't cause a crash
 * after running for a long time, it was also used to check if the whole concept of many games
 * being played simultaneously by bots works or not
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <random>

#include "GameManager.h"

using namespace std;

int main() {
    srand(time(nullptr));
    auto start = chrono::steady_clock::now();
    GameManager gameManager = GameManager();
    gameManager.start();
    for(;;) {
        auto now = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - start);
        int millisecondsPassed = elapsed.count();
        cout << millisecondsPassed << endl;
        gameManager.advanceCasino(millisecondsPassed);
        this_thread::sleep_for(100ms);
    }
    return 0;
}