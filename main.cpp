#include <QApplication>
#include "tubesimple.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    tubesimple tubeWidget;
    tubeWidget.setWindowTitle("Tube Simple");
    tubeWidget.show();

    return app.exec();
}
