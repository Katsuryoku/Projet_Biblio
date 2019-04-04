

#define _USE_MATH_DEFINES

#include "glwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <cmath>
#include <random>


// Declarations des constantes
const unsigned int WIN_WIDTH  = 1600;
const unsigned int WIN_HEIGHT = 900;
const float MAX_DIMENSION     = 50.0f;


// Constructeur
GLWidget::GLWidget(QWidget * parent) : QGLWidget(parent)
{
    // Reglage de la taille/position
    //setFixedSize(WIN_WIDTH/3, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

}
// Fonction d'initialisation
void GLWidget::initializeGL()
{
    // Reglage de la couleur de fond
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

    // Activation du zbuffer
    // ...
    glEnable(GL_DEPTH_TEST);

    // Activation des textures
    glEnable(GL_TEXTURE_2D);

    // Reglage de la lampe
    // ...
//    glEnable(GL_LIGHTING);
//    GLfloat pos_tab[]={0,0,0,1};
//    GLfloat dif_tab[]={1,1,1,1};
//    glEnable(GL_LIGHT0);
//    glLightfv(GL_LIGHT0,GL_POSITION,pos_tab);
//    glLightfv(GL_LIGHT0,GL_AMBIENT_AND_DIFFUSE,dif_tab);





    // Activation de la lumiere
    // ...
}


// Fonction de redimensionnement
void GLWidget::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width/3, height);


    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0f, width/height, 0.1f, 12.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::createCube(double x, double z){
    glColor3ub(255,255,0);
    glBegin(GL_QUADS);
    glVertex3d(x,z,0);
    glVertex3d(x+width()/3,z,0);
    glVertex3d(x+width()/3,z+height()/23,0);
    glVertex3d(x,z+height()/23,0);

    glVertex3d(x,z,0);
    glVertex3d(x+width()/3,z,0);
    glVertex3d(x+width()/3,z,-20);
    glVertex3d(x,z,-20);

    glVertex3d(x,z+height()/23,0);
    glVertex3d(x+width()/3,z+height()/23,0);
    glVertex3d(x+width()/3,z+height()/23,-20);
    glVertex3d(x,z+height()/23,-20);

    glVertex3d(x,z,-20);
    glVertex3d(x+width()/3,z,-20);
    glVertex3d(x+width()/3,z+height()/23,-20);
    glVertex3d(x,z+height()/23,-20);

    glVertex3d(x,z,0);
    glVertex3d(x,z,-20);
    glVertex3d(x,z+height()/23,-20);
    glVertex3d(x,z+height()/23,0);

    glVertex3d(x+width()/3,z,0);
    glVertex3d(x+width()/3,z,-20);
    glVertex3d(x+width()/3,z+height()/23,-20);
    glVertex3d(x+width()/3,z+height()/12,0);

    glEnd();
}

void GLWidget::cubeGame(int r){
    int y= r/10;
    int x=r%10;
    y=(y+1)*height()/23;
    x=(x+1)*width()/3;
    createCube(x,y);
}

// Fonction d'affichage
void GLWidget::paintGL()
{
    // Reinitialisation des tampons
    // ...
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    // Definition de la position de la camera
    // ...


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(width()/3*5,height()/3,700,width()/3*5,height()/2,0,0,1,0);

    //Création du plateau
   glEnable(GL_DEPTH_TEST);
   glColor3ub(255,255,255);

   cubeGame(5);


   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(80,width()/height()*20,0.1,-20);
   glColor3ub(255,255,255);
   glBegin(GL_LINES);
   for (int i= 1;i<24;i++){
       glVertex3d(width()/3,i*height()/23,-20);
       glVertex3d(width()/3*11,i*height()/23,-20);



   }

   for(int i =1; i<12;i++){
       glVertex3d(i*width()/3,height()/23,-20);
       glVertex3d(i*width()/3,height()/23*23,-20);
   }
   glEnd();



}


// Fonction de gestion d'interactions clavier
void GLWidget::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
        // Activation/Arret de l'animation
        case Qt::Key_Space:
        {
            break;
        }

        // Sortie de l'application
        case Qt::Key_Escape:
        {
           break;
        }

        // Cas par defaut
        default:
        {
            // Ignorer l'evenement
            event->ignore();
            return;
        }
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    updateGL();
}
