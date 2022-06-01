#ifndef CASINOGAME_TEXASHOLDEMGUITABLEITEM_H
#define CASINOGAME_TEXASHOLDEMGUITABLEITEM_H

#include <QtWidgets/QLabel>

class TexasHoldemGUITableItem {
    QLabel *labelName, *labelBalance, *labelBet, *labelCard1, *labelCard2;

public:
    TexasHoldemGUITableItem(QLabel*labelName, QLabel *labelBalance, QLabel *labelBet, QLabel *labelCard1, QLabel *labelCard2);
};


#endif //CASINOGAME_TEXASHOLDEMGUITABLEITEM_H
