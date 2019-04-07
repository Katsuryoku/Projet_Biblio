#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QBasicTimer>
#include <QFrame>
#include <QPointer>
#include <QTime>
#include "tetrixpiece.h"
#include "fistdetection.h"
#include <QDebug>
#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>
#include <GL/glu.h>

class QLabel;

// Classe dediee a l'affichage d'une scene OpenGL
class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    // Constructeur
    GLWidget(QWidget * parent = nullptr);

    void cubeGame(int x, int y);


    void setNextPieceLabel(QLabel *label);
public slots:

    void addCubes(int x, int y, TetrixShape shape);
    void createCube(double x, double z, TetrixShape shape);
    void start();
    void pause();
    void tryMoveCam(Movment mvm);

signals:
    void scoreChanged(int score);
    void levelChanged(int level);
    void linesRemovedChanged(int numLines);
    void Cube(double x, double z,TetrixShape shape);

protected:
    // Fonction d'initialisation
    void initializeGL();
    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    // Fonction de gestion d'interactions clavier

    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event) ;

private:
    enum { BoardWidth = 10, BoardHeight = 22 };

    TetrixShape &shapeAt(int x, int y) { return board[(y * BoardWidth) + x]; }
    int timeoutTime() { return 1000 / (1 + level); }

    void clearBoard();
    void dropDown();
    void oneLineDown();
    void pieceDropped(int dropHeight);
    void removeFullLines();
    void newPiece();
    void showNextPiece();
    bool tryMove(const TetrixPiece &newPiece, int newX, int newY);
    void drawSquare(QPainter &painter, int x, int y, TetrixShape shape);
    QTime lastMvmTime;
    QBasicTimer timer;
    QPointer<QLabel> nextPieceLabel;
    bool isStarted;
    bool isPaused;
    bool isWaitingAfterLine;
    TetrixPiece curPiece;
    TetrixPiece nextPiece;
    int curX;
    int curY;
    int numLinesRemoved;
    int numPiecesDropped;
    int score;
    int level;
    TetrixShape board[BoardWidth * BoardHeight];
    void paintLines();
};


#endif // GLWIDGET_H
