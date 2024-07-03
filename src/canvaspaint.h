#ifndef CANVASPAINT_H
#define CANVASPAINT_H

#include <QEvent>
#include <QPen>
#include <QWidget>

class CanvasPaint : public QWidget
{
    Q_OBJECT
public:
    QWidget *view = nullptr;
    QWidget *viewButton = nullptr;
    QImage im;
    explicit CanvasPaint(QScreen *screen, float scale, QWidget *parent = nullptr);
signals:

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);
private:
    float scale;
    QPen pen;
    QPen eraserPen;
    QPoint lastPos;
    bool drawing = false;
    bool eraser = false;
private slots:
    void showView();
};

#endif // MAINCANVAS_H
