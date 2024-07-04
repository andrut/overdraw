#include "activatebutton.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScreen>
#include <QStyle>


ActivateButton::ActivateButton(QScreen *screen, float scale, QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::WindowStaysOnTopHint
                   | Qt::FramelessWindowHint);

    scrGeom = screen->geometry();
    setGeometry(scrGeom.x() + scrGeom.width() - 150*scale, scrGeom.y() + scrGeom.height() - 35*scale, 150*scale, 35*scale);
    QPushButton *butExit = new QPushButton("Exit", this);
    QPushButton *butClear = new QPushButton("Clear", this);
    QPushButton *but = new QPushButton("Draw", this);
    QSizePolicy sp = but->sizePolicy();
    sp.setVerticalPolicy(QSizePolicy::Expanding);
    but->setSizePolicy(sp);
    butClear->setSizePolicy(sp);
    butExit->setSizePolicy(sp);
    QHBoxLayout *layout = new QHBoxLayout(this);
    //layout->setMargin(0);
    layout->addWidget(butExit);
    layout->addWidget(butClear);
    layout->addWidget(but);
    connect(but, &QPushButton::clicked, this, &ActivateButton::activateClicked);
    connect(butClear, &QPushButton::clicked, this, &ActivateButton::clearClicked);
    connect(butExit, &QPushButton::clicked, this, &QWidget::close);
}

void ActivateButton::closeEvent(QCloseEvent *)
{
    qDebug("ActiveButton: Close - Exiting...");
    QApplication::exit(0);
}

void ActivateButton::resizeEvent(QResizeEvent *e)
{
    setGeometry(scrGeom.x() + scrGeom.width() - width(), scrGeom.y() + scrGeom.height() - height(), width(), height());
}

void ActivateButton::activateClicked()
{
    view->hide();
    paint->show();
    hide();
}

void ActivateButton::clearClicked()
{
    paint->im.fill(QColor(255, 255, 255, 0));
    view->update();
}
