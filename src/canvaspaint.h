#ifndef CANVASPAINT_H
#define CANVASPAINT_H

#include <QEvent>
#include <QPen>
#include <QWidget>

struct ImageRegion {
    QPoint pos;
    QImage im;
};

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
    QImage imBeforeChange;
    QPoint regionMin, regionMax;
    QList<ImageRegion> undoStack;
    qsizetype undoRam = 0;
    qsizetype undoMaxRam = 256*1024*1024;
private slots:
    void showView();
};

#endif // MAINCANVAS_H
