#ifndef TETRIXBOARD_H
#define TETRIXBOARD_H

#include "tetrixpiece.h"

#include <QBasicTimer>
#include <QFrame>
#include <QGLWidget>
#include <QPointer>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <bits/stl_vector.h>
#include <bits/stl_vector.h>

using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class TetrixBoard : public QGLWidget
{
    Q_OBJECT

public:
    TetrixBoard(QGLWidget *parent = nullptr);

    void setNextPieceLabel(QLabel *label);
    void setCameraLabel(QLabel *label);
    void setBackGroundColor();
    //QSize sizeHint() const override;
    //QSize minimumSizeHint() const override;

public slots:
    void start();
    void pause();
    // Move the piece when the signal of rotation or translation is received
    void touche();
    void droite();
    void gauche();

signals:
    void scoreChanged(int score);
    void levelChanged(int level);
    void linesRemovedChanged(int numLines);

protected:
    // Fonction d'initialisation
    void initializeGL() override;

    // Fonction de redimensionnement
    void resizeGL(int width, int height) override;

    // Fonction d'affichage
    void paintGL() override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
//! [0]

//! [1]
private:
    enum { BoardWidth = 10, BoardHeight = 22 };

    TetrixShape &shapeAt(int x, int y) { return board[(y * BoardWidth) + x]; }
    int timeoutTime() { return 1000 / (1 + level); }
    int squareWidth() { return 100/ BoardWidth; }
    int squareHeight() { return 200 / BoardHeight; }
    void clearBoard();
    void dropDown();
    void oneLineDown();
    void pieceDropped(int dropHeight);
    void removeFullLines();
    void newPiece();
    void showNextPiece();
    bool tryMove(const TetrixPiece &newPiece, int newX, int newY);
    void drawSquare(QPainter &painter, int x, int y, TetrixShape shape);
    void drawCube(int x, int y, TetrixShape shape);

    QBasicTimer timer;
    QPointer<QLabel> nextPieceLabel;
    QPointer<QLabel> cameraLabel;
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
};

//! [1]

#endif
