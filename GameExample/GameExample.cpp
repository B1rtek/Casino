#include <iostream>

#include "Gambler.h"
#include "TexasBot.h"
#include "TexasHoldem.h"

using namespace std;

void displayCurrentGameState(TexasHoldem *game, const string& what) {
    cout << what << endl;
    cout << "Cards: " << endl;
    for(auto &gambler: game->getPlayers()) {
        cout << gambler->getName() << ": ";
        vector<Card*> cards = game->getGamblersCards()[gambler];
        for(auto &card:cards) {
            cout << *card << ", ";
        }
        cout << endl;
    }
    cout << "Dealt cards: " << endl;
    for(auto &card:game->getCurrentDealtCards()) {
        cout << *card << ", ";
    }
    cout << endl << "Player bets: ";
    map<Gambler*, int> bets = game->getCurrentBets();
    for(auto &gambler: game->getPlayers()) {
        cout << gambler->getName() << ": " << bets[gambler] << endl;
    }
    cout << "---------------------------------------------------" << endl;
}

int main() {
    // game copied from TexasHoldemTest.GameEndInRiver without rigged shuffling
    auto *gambler1 = new Gambler(1337, "Gambler 1");
    auto *bot1 = new TexasBot(1338, "Bot 1"), *bot2 = new TexasBot(1339, "Bot 2");
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new TexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    displayCurrentGameState(texasHoldem, "Game starts");
    texasHoldem->advanceGame(30001); // bot1's small blind
    displayCurrentGameState(texasHoldem, "Bot 1's small blind");
    texasHoldem->advanceGame(30004); // bot2's big blind
    displayCurrentGameState(texasHoldem, "Bot 2's big blind");
    texasHoldem->call(gambler1); // gambler1 calls
    displayCurrentGameState(texasHoldem, "Gambler 1 calls");
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    displayCurrentGameState(texasHoldem, "Bot 1 calls, game goes into flop");
    texasHoldem->advanceGame(30010); // bot2 checks
    displayCurrentGameState(texasHoldem, "Bot 2 checks");
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    displayCurrentGameState(texasHoldem, "Gambler 1 raises");
    texasHoldem->advanceGame(30013); // bot1 calls
    displayCurrentGameState(texasHoldem, "Bot 1 calls");
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    displayCurrentGameState(texasHoldem, "Bot 2 calls, turn starts");
    texasHoldem->call(gambler1); // gambler1 checks
    displayCurrentGameState(texasHoldem, "Gambler 1 checks");
    texasHoldem->advanceGame(30016); // bot1 checks
    displayCurrentGameState(texasHoldem, "Bot 1 checks");
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    displayCurrentGameState(texasHoldem, "Bot 2 raises by 2");
    texasHoldem->call(gambler1); // gambler1 calls
    displayCurrentGameState(texasHoldem, "Gambler 1 calls");
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    displayCurrentGameState(texasHoldem, "Bot 1 calls, river starts");
    texasHoldem->advanceGame(30020); // bot 2 raises
    displayCurrentGameState(texasHoldem, "Bot 2 raises by 2");
    texasHoldem->call(gambler1); // gambler1 calls
    displayCurrentGameState(texasHoldem, "Gambler 1 calls");
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    displayCurrentGameState(texasHoldem, "Bot 1 calls, game ends");
    cout << texasHoldem->getLastGameWinners()[0]->getName() << " wins!";
    delete texasHoldem;
    delete bot1;
    delete bot2;
    delete gambler1;
    return 0;
}