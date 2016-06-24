#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "qextserial/qextserialport.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    
private slots:
    void on_pushButton_clicked();
    void readMyCom();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    QextSerialPort *myCom;
    QString s;
    QString Str_GPGGA;
    QString Str_GPRMC;
    QString Str_GPGSA;
    int i;

};

#endif // DIALOG_H
