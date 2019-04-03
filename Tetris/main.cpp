#include "game.h"
#include <QApplication>
#include "glwidget.h"
int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    game w;
//    w.show();

//    return a.exec();

    // Initialisation du generateur de nombres aleatoires
    srand(time(nullptr));

    // Creation de l'application QT
    QApplication app(argc, argv);

    // Creation du widget opengl
    GLWidget glWidget;
    glWidget.show();

    // Execution de l'application QT
    return app.exec();
}
