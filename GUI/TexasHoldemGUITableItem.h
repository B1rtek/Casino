#ifndef CASINOGAME_TEXASHOLDEMGUITABLEITEM_H
#define CASINOGAME_TEXASHOLDEMGUITABLEITEM_H

#include <QtWidgets/QLabel>

#include "TexasHoldem.h"

class TexasHoldemGUITableItem {
    QLabel *labelName, *labelBalance, *labelBet, *labelCard1, *labelCard2;

public:
    TexasHoldemGUITableItem(QLabel*labelName, QLabel *labelBalance, QLabel *labelBet, QLabel *labelCard1, QLabel *labelCard2);

    void updateItem(TexasHoldem *game = nullptr, Gambler *gambler = nullptr, Gambler *player = nullptr);
};


#endif //CASINOGAME_TEXASHOLDEMGUITABLEITEM_H
