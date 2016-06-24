#include "dialog.h"
#include "ui_dialog.h"
#include <QStringList>
#include <QByteArray>
#include <QTextCursor>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    myCom = NULL;
    i = 0;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString portName = "COM15";
    myCom = new QextSerialPort(portName);
    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
    myCom->setBaudRate(BAUD4800);
    myCom->setDataBits(DATA_8);
    myCom->setParity(PAR_NONE);
    myCom->setStopBits(STOP_1);
    myCom->setFlowControl(FLOW_OFF);

    if(myCom->open(QIODevice::ReadOnly))
    {
        //QMessageBox::information(this, tr("打开成功"), tr("已成功打开串口") + portName, QMessageBox::Ok);
    }
    else
    {
        //QMessageBox::critical(this, tr("打开失败"), tr("未能打开串口 ") + portName + tr("\n该串口设备不存在或已被占用"), QMessageBox::Ok);
        return;
    }
}

void Dialog::on_pushButton_2_clicked()
{
    if (myCom->isOpen())
    {
        myCom->close();
    }
}

void Dialog::readMyCom()
{
    QString GPGGA = "$GPGGA";
    QString GPRMC = "$GPRMC";
    QString GPGSA = "$GPGSA";
    QByteArray temp = myCom->readAll();
    for (int i=0;i<temp.size();i++)
    {
        if (temp.at(i)=='\n')
        {
            if (s.startsWith(GPGGA))
                Str_GPGGA = s;
            else if (s.startsWith(GPRMC))
                Str_GPRMC = s;
            else if (s.startsWith(GPGSA))
                Str_GPGSA = s;
            else
            {
                s.clear();
                return ;
            }
            s.clear();
        }
        else
        {
            s+=temp.at(i);
        }
    }

    if (!Str_GPRMC.isEmpty())
    {
        QStringList strList = Str_GPRMC.split(",");
        if (strList.at(2).startsWith("A"))
        {
            ui->Status->setText("Valid");
            QString UTCTime = strList.at(1);
            int hour = UTCTime.mid(0,2).toInt();
            int minute = UTCTime.mid(2,2).toInt();
            int second = UTCTime.mid(4,2).toInt();
            int bj_hour = (hour+8)%24;
            QString BjTime = QString::number(bj_hour)+QChar(':')+QString::number(minute)+QChar(':')+QString::number(second);
            ui->Time->setText(BjTime);
            QString Date = strList.at(9);
            int year = Date.mid(4,2).toInt()+2000;
            int month = Date.mid(2,2).toInt();
            int day = Date.mid(0,2).toInt();
            if (hour+8>=24)
                day++;
            QString BjDate = QString::number(year)+QChar('/')+QString::number(month)+QChar('/')+QString::number(day);
            ui->Date->setText(BjDate);
            qDebug()<<strList.at(3)<<strList.at(5);
            QString latitude = QString::number(strList.at(3).split(".").at(0).toInt()/100+strList.at(3).split(".").at(0).right(2).toDouble()/60+strList.at(3).split(".").at(1).toDouble()/600000,'f',6)+strList.at(4);
            QString longtitude = QString::number(strList.at(5).split(".").at(0).toInt()/100+strList.at(5).split(".").at(0).right(2).toDouble()/60+strList.at(5).split(".").at(1).toDouble()/600000,'f',6)+strList.at(6);
            ui->Longtitude->setText(longtitude);
            ui->Latitude->setText(latitude);
        }
        else
        {
            ui->Status->setText("Invalid");
            ui->Date->clear();
            ui->Time->clear();
            ui->Longtitude->clear();
            ui->Latitude->clear();
        }

    }


}
