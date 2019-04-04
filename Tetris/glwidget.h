#ifndef GLWIDGET_H
#define GLWIDGET_H


#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>
#include <GL/glu.h>
#include "tetrixpiece.h"

// Classe dediee a l'affichage d'une scene OpenGL
class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    // Constructeur
    GLWidget(QWidget * parent = nullptr);

    void cubeGame(int r);
public slots:
    void addCubes(int x, int y, TetrixShape shape);
    void createCube(double x, double z, TetrixShape shape);
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
