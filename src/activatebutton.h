#ifndef ACTIVATEBUTTON_H
#define ACTIVATEBUTTON_H

#include <QWidget>
#include "canvaspaint.h"
#include "canvasview.h"

class ActivateButton : public QWidget
{
    Q_OBJECT
public:
    CanvasPaint *paint = nullptr;
    CanvasView *view = nullptr;
    explicit ActivateButton(QScreen *screen, float scale, QWidget *parent = nullptr);
protected:
    void closeEvent(QCloseEvent *);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
private:
    enum Mode { Paint, View };
    Mode mode = Mode::View;
    QRect scrGeom;

    bool dragged = false;
    QPoint dragOffset;

private slots:
    void activateClicked();    
    void clearClicked();
signals:

};

#endif // ACTIVATEBUTTON_H
