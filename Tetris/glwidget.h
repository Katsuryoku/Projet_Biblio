#ifndef GLWIDGET_H
#define GLWIDGET_H


#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>
#include <GL/glu.h>


// Classe dediee a l'affichage d'une scene OpenGL
class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    // Constructeur
    GLWidget(QWidget * parent = nullptr);

    void createCube(double x,double y);

    void cubeGame(int r);

protected:
    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent * event);

private:
};


#endif // GLWIDGET_H
