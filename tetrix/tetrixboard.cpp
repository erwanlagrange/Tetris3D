/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include<GL/glu.h>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>

#include <QString>
#include <QTimer>
#include <cstdio>
#include <iostream>
#include <QDebug>

#include "tetrixboard.h"


using namespace cv;
using namespace std;

TetrixBoard::TetrixBoard(QGLWidget *parent)
    : QGLWidget (parent)
{
    setFocusPolicy(Qt::StrongFocus);
    isStarted = false;
    isPaused = false;
    clearBoard();

    nextPiece.setRandomShape();
    // initialisation position caméra
    xcam =50;
    ycam =20;
}

void TetrixBoard::setNextPieceLabel(QLabel *label)
{
    nextPieceLabel = label;
}

void TetrixBoard::start()
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

void TetrixBoard::pause()
{
    if (!isStarted)
        return;

    isPaused = !isPaused;
    if (isPaused) {
        timer.stop();
    } else {
        timer.start(timeoutTime(), this);
    }
    update();
}

void TetrixBoard::keyPressEvent(QKeyEvent *event)
{
    if (!isStarted || isPaused || curPiece.shape() == NoShape) {
        QGLWidget::keyPressEvent(event);
        return;
    }

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
    case Qt::Key_W:
        oneLineDown();
        break;
    case Qt::Key_Escape:
        QApplication::quit();
        break;
    case Qt::Key_Z:
        ycam++;
        break;
    case Qt::Key_Q:
        xcam--;
        break;
    case Qt::Key_S:
        ycam--;
        break;
    case Qt::Key_D:
        xcam++;
        break;
    default:
        keyPressEvent(event);
    }
    updateGL();
}

void TetrixBoard::timerEvent(QTimerEvent *event)
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
    }
}

void TetrixBoard::clearBoard()
{
    for (int i = 0; i < BoardHeight * BoardWidth; ++i)
        board[i] = NoShape;
}

void TetrixBoard::dropDown()
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
}

void TetrixBoard::oneLineDown()
{
    if (!tryMove(curPiece, curX, curY - 1))
        pieceDropped(0);
}
//! [21]

//! [22]
void TetrixBoard::pieceDropped(int dropHeight)
{
    for (int i = 0; i < 4; ++i) {
        int x = curX + curPiece.x(i);
        int y = curY - curPiece.y(i);
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
}

void TetrixBoard::removeFullLines()
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
            ++numFullLines;
            for (int k = i; k < BoardHeight - 1; ++k) {
                for (int j = 0; j < BoardWidth; ++j)
                    shapeAt(j, k) = shapeAt(j, k + 1);
            }
            for (int j = 0; j < BoardWidth; ++j)
                shapeAt(j, BoardHeight - 1) = NoShape;
        }
    }
    if (numFullLines > 0) {
        numLinesRemoved += numFullLines;
        score += 10 * numFullLines;
        emit linesRemovedChanged(numLinesRemoved);
        emit scoreChanged(score);

        timer.start(500, this);
        isWaitingAfterLine = true;
        curPiece.setShape(NoShape);
        //update();
        updateGL();
    }
}

void TetrixBoard::newPiece()
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
}

bool TetrixBoard::tryMove(const TetrixPiece &newPiece, int newX, int newY)
{
    for (int i = 0; i < 4; ++i) {
        int x = newX + newPiece.x(i);
        int y = newY - newPiece.y(i);
        if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
            return false;
        if (shapeAt(x, y) != NoShape)
            return false;
    }

    curPiece = newPiece;
    curX = newX;
    curY = newY;
    //update();
    updateGL();
    return true;
}
//! [35]
void TetrixBoard::drawCube(int x, int y, TetrixShape shape)
{
    static const QRgb colorTable[8] = {
        0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
        0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
    };

    QColor color = colorTable[int(shape)];

    x=x*10;
    y=y*10;

    glBegin(GL_QUADS);
    // recupère couleur
    glColor3ub(color.red(), color.green(), color.blue());

    //cube
    glVertex3f(x,y,5);      //devant
    glVertex3f(x+10,y,5);
    glVertex3f(x+10,y+10,5);
    glVertex3f(x,y+10,5);

    glVertex3f(x,y,1);      //deriere
    glVertex3f(x+10,y,1);
    glVertex3f(x+10,y+10,1);
    glVertex3f(x,y+10,1);

    glVertex3f(x,y,5);      //gauche
    glVertex3f(x,y+10,5);
    glVertex3f(x,y+10,1);
    glVertex3f(x,y,1);

    glVertex3f(x+10,y,5);    //droite
    glVertex3f(x+10,y+10,5);
    glVertex3f(x+10,y+10,1);
    glVertex3f(x+10,y,1);

    glVertex3f(x,y,5);      //dessous
    glVertex3f(x+10,y,5);
    glVertex3f(x+10,y,1);
    glVertex3f(x,y,1);

    glVertex3f(x,y+10,5);    //dessus
    glVertex3f(x+10,y+10,5);
    glVertex3f(x+10,y+10,1);
    glVertex3f(x,y+10,1);

    glEnd();

    // ligne des cubes
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex3f(x,y,5.01f);
    glVertex3f(x+10,y,5.01f);

    glVertex3f(x+10,y,5.01f);
    glVertex3f(x+10,y+10,5.01f);

    glVertex3f(x+10,y+10,5.01f);
    glVertex3f(x,y+10,5.01f);

    glVertex3f(x,y+10,5.01f);
    glVertex3f(x,y,5.01f);

    //left
    glVertex3f(x+0.01f,y-0.01f,5.01f);
    glVertex3f(x+0.01f,y-0.01f,1.01f);

    glVertex3f(x+0.01f,y+10.01f,5.01f);
    glVertex3f(x+.01f,y+10.01f,1.01f);

    //Right

    glVertex3f(x+4.01f,y-0.01f,5.01f);
    glVertex3f(x+4.01f,y-0.01f,1.01f);

    glVertex3f(x+4.01f,y+10.01f,5.01f);
    glVertex3f(x+4.01f,y+10.01f,1.01f);

    glEnd();

}

void TetrixBoard::initializeGL()
{
    // Reglage de la couleur de fond
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Activation du zbuffer
    glEnable(GL_DEPTH_TEST);

    paintGL();
    newPiece();
}

void TetrixBoard::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);
    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -5.0, 150.0, -100.0, 300.0);
    //gluPerspective(80.0f, static_cast <float>(width)/height, 0.1f, 300.0f);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void TetrixBoard::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(90, 1, 0.1, 300);
    gluLookAt(xcam, ycam, 100, // position de la caméra
              50, 80, 0, // position du point que fixe la caméra
              0, 1, 0); // vecteur vertical

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // grille

    glBegin(GL_LINES);
    glColor3ub(255,255,255);

    for(int x = 0; x<11; x++)
    {
        glVertex3f(10*x, 0, 0 );
        glVertex3f(10*x, 200, 0 );
    }
    for(int y = 0; y<21; y++)
    {
        glVertex3f(0, 10*y, 0 );
        glVertex3f(100,10*y, 0 );
    }
    glEnd();

    // dessine les cubes
    for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 10; ++j) {
                TetrixShape shape = shapeAt(j, i);
                if (shape != NoShape)
                    drawCube(j,i,shape);
            }
        }
        if (curPiece.shape() != NoShape && isStarted==true) {
            for (int i = 0; i < 4; ++i) {
                int x = curX + curPiece.x(i);
                int y = curY - curPiece.y(i);
                drawCube(x,y, curPiece.shape());
            }
        }
    showNextPiece();
}

void TetrixBoard::touche()
{
    tryMove(curPiece.rotatedRight(), curX, curY);
}

void TetrixBoard::droite()
{
    tryMove(curPiece, curX + 1, curY);
}

void TetrixBoard::gauche()
{
    tryMove(curPiece, curX - 1, curY);
}

void TetrixBoard::showNextPiece()
{
    if (!nextPieceLabel)
        return;

    int dx = nextPiece.maxX() - nextPiece.minX() + 1;
    int dy = nextPiece.maxY() - nextPiece.minY() + 1;

    QPixmap pixmap(dx * squareWidth(), dy * squareHeight());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), nextPieceLabel->palette().background());

    for (int i = 0; i < 4; ++i) {
        int x = nextPiece.x(i) - nextPiece.minX();
        int y = nextPiece.y(i) - nextPiece.minY();
        drawSquare(painter, x * squareWidth(), y * squareHeight(),
                   nextPiece.shape());
    }
    nextPieceLabel->setPixmap(pixmap);
}

void TetrixBoard::drawSquare(QPainter &painter, int x, int y, TetrixShape shape)
{
    static const QRgb colorTable[8] = {
        0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
        0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
    };

    QColor color = colorTable[int(shape)];
    painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2,
                     color);

    painter.setPen(color.light());
    painter.drawLine(x, y + squareHeight() - 1, x, y);
    painter.drawLine(x, y, x + squareWidth() - 1, y);

    painter.setPen(color.dark());
    painter.drawLine(x + 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + squareHeight() - 1);
    painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + 1);
}
