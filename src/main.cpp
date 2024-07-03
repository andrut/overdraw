#include <QApplication>
#include "canvasview.h"
#include "canvaspaint.h"
#include "activatebutton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QScreen *screen = QApplication::primaryScreen();
    QList<QScreen *> screens = QApplication::screens();
    if (!screen || screens.size() < 1) {
        qDebug("No screen detected.");
        return -1;
    }
    if (screens.size() > 1) {
        // TODO: display screen chooser
    }
    float scale = screen->logicalDotsPerInch()/96.0f;

    CanvasView v(screen, scale);
    CanvasPaint p(screen, scale);
    ActivateButton ab(screen, scale);
    v.im = &p.im;
    p.view = &v;
    p.viewButton = &ab;
    ab.view = &v;
    ab.paint = &p;
    ab.show();
    ab.raise();
    v.show();
    return a.exec();
}
