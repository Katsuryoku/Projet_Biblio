#ifndef TETRIXWINDOW_H
#define TETRIXWINDOW_H

#include <QFrame>
#include <QWidget>
#include <CameraWidget.h>
#include <glwidget.h>

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE
class TetrixBoard;
/* Inspired by QtCreator, modified by Thomas Mion and Hugo Nicolle */

class TetrixWindow : public QWidget
{
    Q_OBJECT

public:
    // Constructor
    TetrixWindow();

private:
    // Create a label from a text
    QLabel *createLabel(const QString &text);
    // Widget for gl object
    GLWidget *glWidget;
    TetrixBoard *board;
    // Widget for method camera
    CameraWidget *Camera;
    // Qlabel for camera display
    QLabel *labelCamera;
    // QLabel for next Piece display
    QLabel *nextPieceLabel;
    // LCD for score
    QLCDNumber *scoreLcd;
    // LCD for level
    QLCDNumber *levelLcd;
    // LCD for lines destroyed
    QLCDNumber *linesLcd;
    // Button to start game
    QPushButton *startButton;
    // Button to quit application
    QPushButton *quitButton;
    // Button to pause game
    QPushButton *pauseButton;
private slots :
    // Slots that permit to destroy the cam when we quit application
    void destroyCam();
};

#endif
