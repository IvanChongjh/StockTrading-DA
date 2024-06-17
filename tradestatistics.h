#ifndef TRADESTATISTICS_H
#define TRADESTATISTICS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class TradeStatistics;
}
QT_END_NAMESPACE

class TradeStatistics : public QMainWindow
{
    Q_OBJECT

public:
    TradeStatistics(QWidget *parent = nullptr);
    ~TradeStatistics();

private slots:
    void on_pushButton_clicked();

    void add_database(double &profitloss,int &index);

    double calculate_Percentage(double &winloss, int &totalentry);


    void on_calculateBtn_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_RemoveBtn_clicked();

    void overrisktradecheck();
    void clearForm();
    void on_clearAllBtn_clicked();

private:
    Ui::TradeStatistics *ui;

    double database[200];
    double profitlossentry=0;
    int dataindex=0;
    int itemcount=1;
    double win = 0 ;
    double loss = 0 ;
    double highestwin = 0;
    double highestloss =0;
    int selected = 0;
    int removedtrack =0;
    double balance =0 ;

    double sum = 0 ;
    int totalinput = 0;
    double winpercent = 0;
    double losspercent = 0;
};
#endif // TRADESTATISTICS_H
