#include "canvasview.h"

#include <QApplication>
#include <QPainter>
#include <QScreen>

CanvasView::CanvasView(QScreen *screen, float scale, QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    auto flags = Qt::WindowStaysOnTopHint
            | Qt::WindowTransparentForInput
            | Qt::WindowDoesNotAcceptFocus
            | Qt::FramelessWindowHint;
#ifdef Q_OS_LINUX
    flags |= Qt::X11BypassWindowManagerHint;
#endif
    setWindowFlags(flags);

    QRect scrGeom = screen->geometry();
    setGeometry(scrGeom);
}

void CanvasView::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if (im) {
        p.drawImage(0, 0, *im);
    }
}
