#include <QApplication>
#include <QtWidgets/QMainWindow>
#include "CasinoWindow.h"

using namespace std;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QApplication::setStyle("fusion");
    CasinoWindow window = CasinoWindow();
    srand(time(nullptr));
    window.show();
    return QApplication::exec();
}