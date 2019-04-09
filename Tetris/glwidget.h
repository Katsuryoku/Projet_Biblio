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
/* Autor : Hugo Nicolle */
class QLabel;

// Classe dediee a l'affichage d'une scene OpenGL et au déroulement du jeu
class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    // Constructeur
    GLWidget(QWidget * parent = nullptr);

    //Draw a cube in the coordinate system of the GL scene
    void createCube(double x, double z, TetrixShape shape);

    void setNextPieceLabel(QLabel *label);
public slots:

    //Initialize a game
    void start();

    //Put the game
    void pause();

    //Move a piece according to the argument movement
    void tryMoveCam(Movment mvm);

    //Interactions with the keyboard
    void kPressEvent(QKeyEvent *event);

signals:

    //Indicates the score changed
    void scoreChanged(int score);

    //Indicates a level change
    void levelChanged(int level);

    //Indicates lines were removed from the board
    void linesRemovedChanged(int numLines);



protected:
    // Fonction d'initialisation
    void initializeGL();
    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    // Timer gestion
    void timerEvent(QTimerEvent *event) ;

private:
    enum { BoardWidth = 10, BoardHeight = 22 };

    // Find a shape in the board
    TetrixShape &shapeAt(int x, int y) { return board[(y * BoardWidth) + x]; }

    // Returns a timeout time for the timer
    int timeoutTime() { return 1000 / (1 + level); }

    // Completely clears the board for a new game
    void clearBoard();

    // Drops the current piece at the bottom
    void dropDown();

    // Moves a piece one line down
    void oneLineDown();

    // Changes game variables when a piece reaches the bottom of the board
    void pieceDropped(int dropHeight);

    // Removes lines that are full
    void removeFullLines();

    // Changes the current piece
    void newPiece();


    void showNextPiece();

    // Tells if a piece can move to a location and move it if it's possible
    bool tryMove(const TetrixPiece &newPiece, int newX, int newY);
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
