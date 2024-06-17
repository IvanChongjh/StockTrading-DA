#include "tradestatistics.h"
#include "./ui_tradestatistics.h"

TradeStatistics::TradeStatistics(QWidget *parent) // constructor taking in Qmain parameter and ui
    : QMainWindow(parent)
    , ui(new Ui::TradeStatistics)
{
    ui->setupUi(this);

    ui->winTxt->setText("");
    ui->lossTxt->setText("");
    ui->BiglossTxt->setText("");
    ui->BiglossTxt->setText("");
    ui->totalTradeTxt->setText("");
    ui->BigwinnerTxt->setText("");
    ui->profitlosstxt->setText("");
    ui->plTxt->setText("");
    ui->balanceTxt->setText("");
    ui->messageTxt->setText("");
    ui->initialBalanceTxt->setText("");
    ui->listWidget->setBackgroundRole(QPalette::Highlight);
}

TradeStatistics::~TradeStatistics() // destructor
{
    delete ui;
}
double TradeStatistics::calculate_Percentage(double &winloss, int &totalentry)
{
    double percent = (winloss/totalentry)*100;
    return percent;
}
void TradeStatistics::add_database(double &profitloss,int &index)
{
    database[index] = profitloss;
}
void TradeStatistics::on_pushButton_clicked()
{
    QString plinput = ui->profitlosstxt->text();
    profitlossentry = plinput.toDouble();
    add_database(profitlossentry,dataindex);
    ui->listWidget->addItem(QString::number(itemcount) + ")" + "=  $ " + QString::number(profitlossentry));
    ui->profitlosstxt->setText("");

    itemcount++;
    dataindex++;


}
void TradeStatistics:: overrisktradecheck()
{
    int check = 0; // return 0 if safe trade return 1 if overrisk trade
    int error = 0 ;

    // ui->messageTxt->setText("Your Risk Per Trade :" + QString::number(balance*0.01));
    for (int i = 0 ; i < dataindex ; i ++ )
    {
        // qDebug() << "HERE "<< i;
        // qDebug()<<" Number of data : " << QString::number(dataindex);
        if (database[i] < 0 && database[i] < -(balance*0.01)){ // 0.01 1 % risk
            ui->messageTxt->setAlignment(Qt::AlignCenter);
            ui->messageTxt->setText("Your Risk Per Trade At 1 % :  " + QString::number(balance*0.01)+ " \nYou Are Over Exposed On Trade Entry : "
                                    + QString::number(i+1) + " = " + QString::number(database[i]) +
                                   "\nYour Risk Per Trade Should Not Exceed  " + QString::number(balance*0.01));
            error ++;
        }

    }
    if (error ==0)
        ui->messageTxt->setText("Congratulations, No Risky Trades Detected ! Good Job !");
}
void TradeStatistics::on_calculateBtn_clicked()
{
    QString capitalbalance = ui->balancevalue->text();
    balance = capitalbalance.toDouble();

     ui->initialBalanceTxt->setText("$" + QString::number(balance));


    if ((itemcount-removedtrack) > 0){  // if it is not empty


            for(int i = 0 ; i < dataindex ; i ++)
            {
                qDebug() << database[i];
                sum += database[i];
                if(database[i] > 0 ) // above 0 = positive
                {
                    win++;

                    if(database[i] > highestwin){

                        highestwin = database[i];

                    }
                }
                else if(database[i] < 0 ) // below 0 = negative
                {

                    loss++;

                    if(database[i] < highestloss){
                        highestloss = database[i];

                    }
                }
                else
                {
                    qDebug() << "No Data Entry";
                }

            }



    }

    int totalinput = dataindex - removedtrack;
    double winpercent = calculate_Percentage(win,totalinput);
    double losspercent = calculate_Percentage(loss,totalinput);
    overrisktradecheck();

    balance += sum;


    ui->BiglossTxt->setText(" $ " + QString::number(highestloss));
    ui->BigwinnerTxt->setText(" $  +" + QString::number(highestwin));
    ui->winTxt->setText( QString::number(winpercent) );
    ui->lossTxt->setText( QString::number(losspercent) );
    ui->totalTradeTxt->setText(QString::number(dataindex-removedtrack));
    ui->plTxt->setText(" $ " + QString::number(sum));
    ui->balanceTxt->setText("$" + QString::number(balance));
    ui->balancevalue->setText("");
    ui->calculateBtn->setDisabled(true);
    ui->pushButton->setDisabled(true);
    ui->RemoveBtn->setDisabled(true);

}


void TradeStatistics::on_listWidget_currentRowChanged(int currentRow)
{
    selected = currentRow; // the way widget works is like an array first listed is 0 index


}
void TradeStatistics::on_RemoveBtn_clicked()
{
    int holdvalue = selected;
    QListWidgetItem * ptr = ui->listWidget->takeItem(selected);
    qDebug() << holdvalue << " Database data : " << QString::number(database[holdvalue]);

    database[holdvalue] = 0 ;
    delete ptr;

    removedtrack ++;

}

void TradeStatistics:: clearForm()
{
    ui->winTxt->setText("");
    ui->lossTxt->setText("");
    ui->BiglossTxt->setText("");
    ui->BiglossTxt->setText("");
    ui->totalTradeTxt->setText("");
    ui->BigwinnerTxt->setText("");
    ui->profitlosstxt->setText("");
    ui->plTxt->setText("");
    ui->balanceTxt->setText("");
    ui->messageTxt->setText("");
    profitlossentry=0;
    dataindex=0;
    itemcount=1;
    win = 0 ;
    loss = 0 ;
    highestwin = 0;
    highestloss =0;
    selected = 0;
    removedtrack =0;
    balance =0 ;
    sum = 0 ;
    totalinput = 0;
     winpercent = 0;
    losspercent = 0;

    for(int i = 0 ; i < 200 ; i ++ ) // erase all data point to null
    {
        database[i] = NULL;
    }
    ui->calculateBtn->setDisabled(false);
    ui->pushButton->setDisabled(false);
    ui->RemoveBtn->setDisabled(false);

}


void TradeStatistics::on_clearAllBtn_clicked()
{
    int loop = 0;

    while(ui->listWidget->takeItem(loop) != NULL)
    {
        QListWidgetItem*ptr;
        ptr = ui->listWidget->takeItem(loop);
        delete ptr;
    }
    clearForm();

}

