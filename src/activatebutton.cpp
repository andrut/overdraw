#include "activatebutton.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QMouseEvent>
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
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addSpacing(10*scale);
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
    if (!dragged) {
        setGeometry(scrGeom.x() + scrGeom.width() - width(), scrGeom.y() + scrGeom.height() - height(), width(), height());
    }
}

void ActivateButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        dragged = true;
        dragOffset = e->globalPos() - frameGeometry().topLeft();
        e->accept();
    }
}

void ActivateButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        dragged = false;
        e->accept();
    }
}

void ActivateButton::mouseMoveEvent(QMouseEvent *e)
{
    if (dragged && (e->buttons() & Qt::LeftButton)) {
        move(e->globalPos() - dragOffset);
        e->accept();
    }
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
