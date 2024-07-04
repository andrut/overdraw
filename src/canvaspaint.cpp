#include "canvaspaint.h"

#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QScreen>
#include <QLayout>
#include <QLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QDebug>

CanvasPaint::CanvasPaint(QScreen *screen, float scale, QWidget *parent)
    : QWidget{parent},
      scale{scale},
      pen{QColor{255, 0, 40}},
      eraserPen{QColor{255, 255, 255, 0}}
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    setWindowFlags(Qt::WindowStaysOnTopHint
                   | Qt::FramelessWindowHint);

    QRect scrGeom = screen->geometry();
    setGeometry(scrGeom);
    im = QImage(scrGeom.width(), scrGeom.height(), QImage::Format_ARGB32);
    im.fill(QColor(255, 255, 255, 0));
    pen.setCapStyle(Qt::PenCapStyle::RoundCap);
    pen.setWidth(5*scale);
    eraserPen = QPen(QColor(255, 255, 255, 0));
    eraserPen.setCapStyle(Qt::PenCapStyle::RoundCap);
    eraserPen.setWidth(100*scale);
    setMouseTracking(true);

    QPushButton *but = new QPushButton(this);
    but->setText("<< View");
    int w = 100*scale;
    int h = 64*scale;
    but->setGeometry(scrGeom.x() + scrGeom.width() - w, scrGeom.y() + scrGeom.height() - h, w, h);
    connect(but, &QPushButton::clicked, this, &CanvasPaint::showView);
}

void CanvasPaint::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    #ifdef Q_OS_WINDOWS
    p.fillRect(geometry(), QColor(255, 255, 255, 1));
    #endif

    p.drawImage(0, 0, im);
    if (drawing) {
        if (eraser) {
            p.setBrush(QColor(255, 0, 0, 100));
            p.setPen(Qt::NoPen);
            p.drawEllipse(lastPos.x() - 50*scale, lastPos.y() - 50*scale, 100*scale, 100*scale);
        }
    } else {
        p.setRenderHint(QPainter::RenderHint::Antialiasing, true);
        p.setBrush(QColor(255, 255, 0, 128));
        p.setPen(Qt::NoPen);
        p.drawEllipse(lastPos.x() - 50*scale, lastPos.y() - 50*scale, 100*scale, 100*scale);
        p.setBrush(pen.color());
        p.drawEllipse(lastPos.x() - pen.width()/2, lastPos.y() - pen.width()/2, pen.width(), pen.width());
    }
}

void CanvasPaint::mousePressEvent(QMouseEvent *e)
{
    drawing = true;
    eraser = e->button() == Qt::RightButton;
    lastPos = e->pos();
    QPainter p(&im);
    p.setRenderHint(QPainter::RenderHint::Antialiasing, true);
    p.setPen(Qt::NoPen);
    p.setBrush(pen.color());
    if (eraser) {
        p.save();
        p.setCompositionMode(QPainter::CompositionMode_Clear);
        int r = eraserPen.width()/2;
        p.drawEllipse(lastPos.x() - r, lastPos.y() - r, 2*r+1, 2*r+1);
        p.restore();
    } else {
        p.drawEllipse(lastPos.x()-pen.width()/2, lastPos.y()-pen.width()/2, pen.width(), pen.width());
    }
    p.end();
    update();
    setCursor(QCursor(Qt::CursorShape::BlankCursor));
}

void CanvasPaint::mouseMoveEvent(QMouseEvent *e)
{
    if (drawing) {
        QPainter p(&im);
        p.setRenderHint(QPainter::RenderHint::Antialiasing, true);
        p.setPen(eraser ? eraserPen : pen);
        if (eraser) {
            p.save();
            p.setCompositionMode(QPainter::CompositionMode_Clear);
        }
        p.drawLine(lastPos.x(), lastPos.y(), e->pos().x(), e->pos().y());
        if (eraser){
            p.restore();
        }
        p.end();
    }
    lastPos = e->pos();
    update();
}

void CanvasPaint::mouseReleaseEvent(QMouseEvent *e)
{
    setCursor(QCursor(Qt::CursorShape::ArrowCursor));
    drawing = false;
    update();
}

void CanvasPaint::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Escape:
        showView();
        break;
    case Qt::Key_Delete:
        im.fill(QColor(255, 255, 255, 0));
        update();
        break;
    case Qt::Key_1:
        pen.setColor(QColor(255, 0, 40));
        break;
    case Qt::Key_2:
        pen.setColor(QColor(255, 192, 0));
        break;
    case Qt::Key_3:
        pen.setColor(QColor(50, 205, 50));
        break;
    case Qt::Key_4:
        pen.setColor(QColor(0, 80, 255));
        break;
    case Qt::Key_5:
        pen.setColor(QColor(0, 168, 255));
        break;
    case Qt::Key_6:
        pen.setColor(QColor(138, 43, 226));
        break;
    case Qt::Key_7:
        pen.setColor(Qt::black);
        break;
    case Qt::Key_Q:
        pen.setWidth(3*scale);
        break;
    case Qt::Key_W:
        pen.setWidth(5*scale);
        break;
    case Qt::Key_E:
        pen.setWidth(9*scale);
        break;
    case Qt::Key_R:
        pen.setWidth(15*scale);
        break;
    }
    update();
}

void CanvasPaint::showView()
{
    if (view) view->show();
    if (viewButton) viewButton->show();
    hide();
}
