#ifndef WIDGET_H
#define WIDGET_H

#include <threadhandler.h>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QThread>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
   explicit Widget(QWidget *parent = 0);
    ~Widget();
    QLineEdit * lineEdit;
    QLabel * TextLabel;
    QLabel * CounterLabel;
    QPushButton * ClearButton;
    QPushButton * CloseButton;
    QPushButton * CopyButton;
    QHBoxLayout * hlayout;
    QVBoxLayout * vlayout;
    bool eventFilter(QObject *obj, QEvent *ev);
    void init();

signals:
    void Copy_Button_Click();
    void Clear_Button_Click();
    void Close_Button_Click();
    void closing();

private slots:
   void on_CopyButton_clicked();
   void on_ClearButton_clicked();
   void takeCounter();
   void on_Close_Button_clicked();

private:
    ThreadHandler *handler;
};

#endif // WIDGET_H
