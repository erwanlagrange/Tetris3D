#ifndef WIDGETTETRIS_H
#define WIDGETTETRIS_H

#include "tetrixpiece.h"

#include <QWidget>
#include <QOpenGLWidget>
#include <QLabel>
#include <QBasicTimer>
#include <QPointer>

namespace Ui {
class WidgetTetris;
}

class WidgetTetris : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit WidgetTetris(QWidget *parent = nullptr);
    ~WidgetTetris();

private:
    Ui::WidgetTetris *ui;
    void DrawGrille();
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

//***************************************************

public:
    void setNextPieceLabel(QLabel *label);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

public slots:
    void start();
    void pause();

signals:
    void scoreChanged(int score);
    void levelChanged(int level);
    void linesRemovedChanged(int numLines);

protected:
    void paintEvent(QPaintEvent *event) override;
    //void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    enum { BoardWidth = 10, BoardHeight = 20 };

    TetrixShape &shapeAt(int x, int y) { return board[(y * BoardWidth) + x]; }
    int timeoutTime() { return 1000 / (1 + level); }
    int squareWidth() { return contentsRect().width() / BoardWidth; }
    int squareHeight() { return contentsRect().height() / BoardHeight; }
    void clearBoard();
    void dropDown();
    void oneLineDown();
    void pieceDropped(int dropHeight);
    void removeFullLines();
    void newPiece();
    void showNextPiece();
    bool tryMove(const TetrixPiece &newPiece, int newX, int newY);
    void drawCube(QPainter &painter, int x, int y, TetrixShape shape);

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

};

#endif // WIDGETTETRIS_H
