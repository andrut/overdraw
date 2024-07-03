#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include <QScreen>
#include <QWidget>

class CanvasView : public QWidget
{
    Q_OBJECT
public:    
    QImage *im = nullptr;
    explicit CanvasView(QScreen *screen, float scale, QWidget *parent = nullptr);
private:
    void paintEvent(QPaintEvent *) override;
signals:

};

#endif // CANVASVIEW_H
