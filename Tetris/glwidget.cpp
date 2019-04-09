#define _USE_MATH_DEFINES
#include <QtWidgets>

#include "glwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <cmath>
#include <random>


// Declarations des constantes
const unsigned int WIN_WIDTH  = 750;
const unsigned int WIN_HEIGHT = 700;
const float MAX_DIMENSION     = 50.0f;


// Constructeur
GLWidget::GLWidget(QWidget * parent) : QGLWidget(parent)
{
    // Reglage de la taille/position
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    isStarted = false;
    isPaused = false;
    clearBoard();

    nextPiece.setRandomShape();
}




//! [1]
void GLWidget::setNextPieceLabel(QLabel *label)
{
    nextPieceLabel = label;
}
//! [1]


//! [4]
void GLWidget::start()
{
    if (isPaused)
        return;

    isStarted = true;
    isWaitingAfterLine = false;
    numLinesRemoved = 0;
    numPiecesDropped = 0;
    score = 0;
    level = 1;
    clearBoard();

    emit linesRemovedChanged(numLinesRemoved);
    emit scoreChanged(score);
    emit levelChanged(level);

    newPiece();
    timer.start(timeoutTime(), this);
}
//! [4]

//! [5]
void GLWidget::pause()
{
    if (!isStarted)
        return;

    isPaused = !isPaused;
    if (isPaused) {
        timer.stop();
    } else {
        timer.start(timeoutTime(), this);
    }
    updateGL();
    //! [5] //! [6]
}
//! [6]

//! [7]
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
    gluLookAt(width()*5,height()/3,700,width()*5,height()/2,0,0,1,0);

    //Création du plateau
    glEnable(GL_DEPTH_TEST);
    glColor3ub(255,255,255);

    if (!isStarted) {
        renderText(width()/2-10, height()/2, tr("Appuyez sur start"));
        return;
    }
    if (isPaused) {
        renderText(100, 100, tr("Pause"));
        return;
    }


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80,width()/height()*20,0.1,-20);
    glColor3ub(255,255,255);
    glBegin(GL_LINES);
    paintLines();
    glEnd();
    for (int i = 0; i < 22; ++i) {
        for (int j = 0; j < 10; ++j) {
            TetrixShape shape = shapeAt(j, i);
            if (shape != NoShape)
                createCube(j,i ,shape);
        }
        if (curPiece.shape() != NoShape && isStarted==true) {
            for (int i = 0; i < 4; ++i) {
                int x = curX + curPiece.x(i);
                int y = curY - curPiece.y(i);
                createCube(x,y,curPiece.shape());
            }
        }
    }



    //! [12]
}

void GLWidget::createCube(double x, double z, TetrixShape shape){
    static const QRgb colorTable[8] = {
            0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
            0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
    };

    QColor color = colorTable[int(shape)];
    glColor3ub(color.red(),color.green(),color.blue());
    z=(z+1)*height()/23;
    x=(x+1)*width();
    glBegin(GL_QUADS);
    glVertex3d(x,z,0);
    glVertex3d(x+width(),z,0);
    glVertex3d(x+width(),z+height()/23,0);
    glVertex3d(x,z+height()/23,0);

    glVertex3d(x,z,0);
    glVertex3d(x+width(),z,0);
    glVertex3d(x+width(),z,-20);
    glVertex3d(x,z,-20);

    glVertex3d(x,z+height()/23,0);
    glVertex3d(x+width(),z+height()/23,0);
    glVertex3d(x+width(),z+height()/23,-20);
    glVertex3d(x,z+height()/23,-20);

    glVertex3d(x,z,-20);
    glVertex3d(x+width(),z,-20);
    glVertex3d(x+width(),z+height()/23,-20);
    glVertex3d(x,z+height()/23,-20);

    glVertex3d(x,z,0);
    glVertex3d(x,z,-20);
    glVertex3d(x,z+height()/23,-20);
    glVertex3d(x,z+height()/23,0);

    glVertex3d(x+width(),z,0);
    glVertex3d(x+width(),z,-20);
    glVertex3d(x+width(),z+height()/23,-20);
    glVertex3d(x+width(),z+height()/12,0);

    glEnd();
}

//! [12]

//! [13]
void GLWidget::kPressEvent(QKeyEvent *event)
{
    if (!isStarted || isPaused || curPiece.shape() == NoShape) {
        //keyPressEvent(event);
        return;
    }
    //! [13]

    //! [14]
    switch (event->key()) {
    case Qt::Key_Left:
        tryMove(curPiece, curX - 1, curY);
        break;
    case Qt::Key_Right:
        tryMove(curPiece, curX + 1, curY);
        break;
    case Qt::Key_Down:
        tryMove(curPiece.rotatedRight(), curX, curY);
        break;
    case Qt::Key_Up:
        tryMove(curPiece.rotatedLeft(), curX, curY);
        break;
    case Qt::Key_Space:
        dropDown();
        break;
    case Qt::Key_D:
        oneLineDown();
        break;
    default:
        //keyPressEvent(event);
        //event->ignore();
        break;
    }
    //! [14]
    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    updateGL();

}

void GLWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        if (isWaitingAfterLine) {
            isWaitingAfterLine = false;
            newPiece();
            timer.start(timeoutTime(), this);
        } else {
            oneLineDown();
        }
    } else {
        timerEvent(event);
        //! [15] //! [16]
    }
    //! [16] //! [17]
}
//! [17]

//! [18]

void GLWidget::clearBoard()
{
    for (int i = 0; i < BoardHeight * BoardWidth; ++i)
        board[i] = NoShape;
}
//! [18]

//! [19]
void GLWidget::dropDown()
{
    int dropHeight = 0;
    int newY = curY;
    while (newY > 0) {
        if (!tryMove(curPiece, curX, newY - 1))
            break;
        --newY;
        ++dropHeight;
    }
    pieceDropped(dropHeight);
    //! [19] //! [20]
}
//! [20]

//! [21]
void GLWidget::oneLineDown()
{
    if (!tryMove(curPiece, curX, curY - 1))
        pieceDropped(0);
}
//! [21]

//! [22]
void GLWidget::pieceDropped(int dropHeight)
{
    for (int i = 0; i < 4; ++i) {
        int x = curX + curPiece.x(i);
        int y = curY - curPiece.y(i);
        // setShapeAt(curPiece.shape(), x, y);
        shapeAt(x, y) = curPiece.shape();
    }

    ++numPiecesDropped;
    if (numPiecesDropped % 25 == 0) {
        ++level;
        timer.start(timeoutTime(), this);
        emit levelChanged(level);
    }

    score += dropHeight + 7;
    emit scoreChanged(score);
    removeFullLines();

    if (!isWaitingAfterLine)
        newPiece();
    //! [22] //! [23]
}
//! [23]

//! [24]
void GLWidget::removeFullLines()
{
    int numFullLines = 0;

    for (int i = BoardHeight - 1; i >= 0; --i) {
        bool lineIsFull = true;

        for (int j = 0; j < BoardWidth; ++j) {
            if (shapeAt(j, i) == NoShape) {
                lineIsFull = false;
                break;
            }
        }

        if (lineIsFull) {
            //! [24] //! [25]
            ++numFullLines;
            for (int k = i; k < BoardHeight - 1; ++k) {
                for (int j = 0; j < BoardWidth; ++j){
                    // setShapeAt(shapeAt(j, k + 1), j, k);
                    shapeAt(j, k) = shapeAt(j, k + 1);
                }
            }
            //! [25] //! [26]
            for (int j = 0; j < BoardWidth; ++j){
                // setShapeAt(NoShape, j, BoardHeight - 1);
                shapeAt(j, BoardHeight - 1) = NoShape;
            }
        }
        //! [26] //! [27]
    }
    //! [27]

    //! [28]
    if (numFullLines > 0) {
        numLinesRemoved += numFullLines;
        score += 10 * numFullLines;
        emit linesRemovedChanged(numLinesRemoved);
        emit scoreChanged(score);

        timer.start(500, this);
        isWaitingAfterLine = true;
        curPiece.setShape(NoShape);
        update();
    }
    //! [28] //! [29]
}
//! [29]

//! [30]

void GLWidget::newPiece()
{
    curPiece = nextPiece;
    nextPiece.setRandomShape();
    showNextPiece();
    curX = BoardWidth / 2 + 1;
    curY = BoardHeight - 1 + curPiece.minY();

    if (!tryMove(curPiece, curX, curY)) {
        curPiece.setShape(NoShape);
        timer.stop();
        isStarted = false;
    }
    //! [30] //! [31]
}
void GLWidget::showNextPiece()
{
    if (!nextPieceLabel)
        return;

    int dx = nextPiece.maxX() - nextPiece.minX() + 1;
    int dy = nextPiece.maxY() - nextPiece.minY() + 1;

    QPixmap pixmap(dx * contentsRect().width() /10, dy * contentsRect().height()/22);
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), nextPieceLabel->palette().background());

    for (int i = 0; i < 4; ++i) {
        int x = nextPiece.x(i) - nextPiece.minX();
        int y = nextPiece.y(i) - nextPiece.minY();
        drawSquare(painter, x * contentsRect().width() /10, y * contentsRect().height()/22,
                   nextPiece.shape());
    }
    nextPieceLabel->setPixmap(pixmap);
//! [32] //! [33]
}
void GLWidget::drawSquare(QPainter &painter, int x, int y, TetrixShape shape)
{
    static const QRgb colorTable[8] = {
        0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
        0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
    };

    QColor color = colorTable[int(shape)];
    painter.fillRect(x + 1, y + 1, contentsRect().width() /10 - 2, contentsRect().height()/22 - 2,
                     color);

    painter.setPen(color.light());
    painter.drawLine(x, y + contentsRect().height()/22 - 1, x, y);
    painter.drawLine(x, y, x + contentsRect().width() /10 - 1, y);

    painter.setPen(color.dark());
    painter.drawLine(x + 1, y + contentsRect().height()/22 - 1,
                     x + contentsRect().width() /10 - 1, y + contentsRect().height()/22 - 1);
    painter.drawLine(x + contentsRect().width() /10 - 1, y + contentsRect().height()/22 - 1,
                     x + contentsRect().width() /10 - 1, y + 1);
}
bool GLWidget::tryMove(const TetrixPiece &newPiece, int newX, int newY)
{
    for (int i = 0; i < 4; ++i) {
        int x = newX + newPiece.x(i);
        int y = newY - newPiece.y(i);
        if (x < 0 || x >= 10 || y < 0 || y >= 22)
            return false;
        if (shapeAt(x, y) != NoShape)
            return false;
    }
    //! [34]

    //! [35]
    curPiece = newPiece;
    curX = newX;
    curY = newY;
    update();
    return true;
}
//! [35]

//! [36]
//!
void GLWidget::tryMoveCam(Movment mvm)
{
    switch (mvm) {
    case Movment::mLeft:
        tryMove(curPiece, curX - 1, curY);
        break;
    case Movment::mRight:
        tryMove(curPiece, curX + 1, curY);
        break;
    case Movment::rRight:
        if (lastMvmTime.isNull()){
            lastMvmTime = QTime::currentTime();
            tryMove(curPiece.rotatedRight(), curX, curY);
            break;
        }
        if (QTime::currentTime().msecsTo(lastMvmTime)<-150){
            lastMvmTime = QTime::currentTime();
            tryMove(curPiece.rotatedRight(), curX, curY);
        }
        break;
    case Movment::rLeft:
        tryMove(curPiece.rotatedLeft(), curX, curY);
        break;
    case Movment::kNone:
        break;
    }
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
    glViewport(0, 0, width, height);


    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0f, width/height, 0.1f, 12.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}




void GLWidget::paintLines(){
    for (int i= 1;i<24;i++){
        glVertex3d(width(),i*height()/23,-20);
        glVertex3d(width()*11,i*height()/23,-20);



    }

    for(int i =1; i<12;i++){
        glVertex3d(i*width(),height()/23,-20);
        glVertex3d(i*width(),height()/23*23,-20);
    }
}




