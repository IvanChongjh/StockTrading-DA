#include "tradestatistics.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TradeStatistics w;
    w.show();
    return a.exec();
}
