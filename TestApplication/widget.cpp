#include "widget.h"
#include <QtGui>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
       setMinimumSize(500, 200);
       setStyleSheet("background: rgb(211, 211, 211)");

       ClearButton = new QPushButton(tr(""),this);
       CloseButton = new QPushButton();
       CopyButton = new QPushButton();
       lineEdit = new QLineEdit(tr("Тут можно что-то написать"), this);  

       ClearButton->setStyleSheet("min-width: 50px; min-height: 50px; background: rgb(192, 192, 192)");
       CloseButton->setStyleSheet("min-width: 50px; min-height: 50px; background: rgb(192, 192, 192)");
       CopyButton->setStyleSheet("min-width: 50px; min-height: 50px; background: rgb(192, 192, 192)");
       lineEdit->setStyleSheet("min-width: 50px; min-height: 50px; background: white");

       TextLabel = new QLabel(tr(""), this);
       CounterLabel = new QLabel(tr("0"), this);

       hlayout = new QHBoxLayout;
       hlayout->addWidget(CopyButton);
       hlayout->addWidget(lineEdit);
       hlayout->addWidget(ClearButton);
       hlayout->addWidget(CloseButton);

       vlayout = new QVBoxLayout;
       vlayout->addLayout(hlayout);
       vlayout->addWidget(TextLabel);
       vlayout->addWidget(CounterLabel);

       QWidget::setLayout(vlayout);

       TextLabel->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
       CounterLabel->setAlignment(Qt::AlignCenter | Qt::AlignCenter);

       connect(CloseButton, QPushButton::clicked, this, on_Close_Button_clicked);
       connect(ClearButton, QPushButton::clicked, this, on_ClearButton_clicked);

       CopyButton->setVisible(false);
       ClearButton->setVisible(true);
       init();
}

void Widget::init(){
     QThread *thread = new QThread;
     handler = new ThreadHandler();
     handler->moveToThread(thread);
     lineEdit->installEventFilter(this);

     connect(thread, &QThread::started, handler, &ThreadHandler::process);
     connect(handler, &ThreadHandler::finished, thread, &QThread::quit);
     connect(handler, &ThreadHandler::finished, handler, &ThreadHandler::deleteLater);
     connect(thread, &QThread::finished, thread, &QThread::deleteLater);
     connect(this, &Widget::closing, handler, &ThreadHandler::stopThread);
     connect(handler, &ThreadHandler::rounding, this, &Widget::takeCounter);

     thread->start();
}

bool Widget::eventFilter(QObject *obj, QEvent *ev){
    if (obj == lineEdit){
        if(ev->type() == QEvent::FocusIn){
            CopyButton->setVisible(true);
            ClearButton->setVisible(false);
            lineEdit->setText("");
            ClearButton->setFocus();
            return true;
        }
        else if (ev->type() == QEvent::FocusOut){
            on_CopyButton_clicked();
            CopyButton->setVisible(false);
            ClearButton->setVisible(true);
            lineEdit->setEnabled(true);
            return true;
        }
    }
    else{
        return QWidget::eventFilter(obj, ev);
    }
}


void Widget::on_CopyButton_clicked() {
    QString text = lineEdit->text();
    long long int value = ThreadHandler::getValue();
    TextLabel->setText(QString("%1 %2").arg(text).arg(value));
    lineEdit->setText("Тут можно что-то написать");
    CopyButton->setVisible(false);
}

void Widget::on_ClearButton_clicked(){
    TextLabel->setText("");
}

void Widget::on_Close_Button_clicked(){
    emit closing();
    this -> close();
}

void Widget::takeCounter(){
    CounterLabel->setText(QString::number(ThreadHandler::getCounter()));
}

Widget::~Widget()
{
}
