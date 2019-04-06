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

//const unsigned int WIN_WIDTH  = 900;
//const unsigned int WIN_HEIGHT = 1600;


TetrixBoard::TetrixBoard(QGLWidget *parent)
    : QGLWidget (parent)
{
    setFocusPolicy(Qt::StrongFocus);
    isStarted = false;
    isPaused = false;
    clearBoard();

    nextPiece.setRandomShape();

    // camera

    cap = VideoCapture(0);

    /*int frameWidth = 200;
    int frameHeight = 100;

    cap.set(CV_CAP_PROP_FRAME_WIDTH,frameWidth);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,frameHeight);*/

    if(!cap.isOpened())  // check if we succeeded
    {
        cerr<<"Error openning the default camera"<<endl;
    }

    if(!face_cascade.load( "../tetrix/fist_v3.xml" ))
    {
        cerr<<"Error loading haarcascade"<<endl;
    }

    timerCamera = new QTimer(this);
    connect(timerCamera, SIGNAL(timeout()), this, SLOT(updatePicture()));
    timerCamera->start(16);
}

void TetrixBoard::setNextPieceLabel(QLabel *label)
{
    nextPieceLabel = label;
}


void TetrixBoard::setCameraLabel(QLabel *label)
{
    cameraLabel = label;
}

/*QSize TetrixBoard::sizeHint() const
{
    return QSize(BoardWidth * 15 + frameWidth() * 2,
                 BoardHeight * 15 + frameWidth() * 2);
}

QSize TetrixBoard::minimumSizeHint() const
//! [2] //! [3]
{
    return QSize(BoardWidth * 5 + frameWidth() * 2,
                 BoardHeight * 5 + frameWidth() * 2);
}*/


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
//! [4]

//! [5]
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
//! [5] //! [6]
}
//! [6]

//! [7]
void TetrixBoard::paintEvent(QPaintEvent *event)
{
    QGLWidget::paintEvent(event);

   /* QPainter painter(this);
    QRect rect = contentsRect();
//! [7]

    if (isPaused) {
        painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
        return;
    }

//! [8]
    int boardTop = rect.bottom() - BoardHeight*squareHeight();

    for (int i = 0; i < BoardHeight; ++i) {
        for (int j = 0; j < BoardWidth; ++j) {
            TetrixShape shape = shapeAt(j, BoardHeight - i - 1);
            if (shape != NoShape)
                drawSquare(painter, rect.left() + j * squareWidth(),
                           boardTop + i * squareHeight(), shape);
        }
//! [8] //! [9]
    }
//! [9]

//! [10]
    if (curPiece.shape() != NoShape) {
        for (int i = 0; i < 4; ++i) {
            int x = curX + curPiece.x(i);
            int y = curY - curPiece.y(i);
            drawSquare(painter, rect.left() + x * squareWidth(),
                       boardTop + (BoardHeight - y - 1) * squareHeight(),
                       curPiece.shape());
        }
//! [10] //! [11]
    }
//! [11] //! [12]*/
}
//! [12]

//! [13]
void TetrixBoard::keyPressEvent(QKeyEvent *event)
{
    if (!isStarted || isPaused || curPiece.shape() == NoShape) {
        QGLWidget::keyPressEvent(event);
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
        QGLWidget::keyPressEvent(event);
    }
//! [14]
}

//! [15]
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
        QGLWidget::timerEvent(event);
//! [15] //! [16]
    }
//! [16] //! [17]
}
//! [17]

//! [18]
void TetrixBoard::clearBoard()
{
    for (int i = 0; i < BoardHeight * BoardWidth; ++i)
        board[i] = NoShape;
}
//! [18]

//! [19]
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
//! [19] //! [20]
}
//! [20]

//! [21]
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
//! [22] //! [23]
}
//! [23]

//! [24]
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
//! [24] //! [25]
            ++numFullLines;
            for (int k = i; k < BoardHeight - 1; ++k) {
                for (int j = 0; j < BoardWidth; ++j)
                    shapeAt(j, k) = shapeAt(j, k + 1);
            }
//! [25] //! [26]
            for (int j = 0; j < BoardWidth; ++j)
                shapeAt(j, BoardHeight - 1) = NoShape;
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
//! [30] //! [31]
}
//! [31]

//! [32]
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
//! [32] //! [33]
}
//! [33]

//! [34]
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

void TetrixBoard::setBackGroundColor(){
    glClearColor(1.0, 0.0, 0.0, 1.0);
}

void TetrixBoard::initializeGL()
{
    // Reglage de la couleur de fond
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Activation du zbuffer
    glEnable(GL_DEPTH_TEST);
}

void TetrixBoard::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);
    qInfo() << width;
    qInfo() << height;
    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0f, static_cast <float>(width)/height, 0.1f, 300.0f);
}

void TetrixBoard::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluPerspective(80.0f, width()/height(), 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(50, 25, 200, // position de la caméra
                50, 100, 0, // position du point que fixe la caméra
                0, 1, 0); // vecteur vertical

    //gluLookAt(50, 100, 30, 105, 105, 5, 0, 1, 1);


    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f,0.0f);
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

}

void TetrixBoard::updatePicture()
{
    Mat frame,frame_gray;
    // Get frame
    cap >> frame;

    // Mirror effect
    cv::flip(frame,frame,1);
    // Convert to gray
    cv::cvtColor(frame,frame_gray,COLOR_BGR2GRAY);
    //-- Detect fist
    face_cascade.detectMultiScale( frame_gray, fist, 1.1, 4, 0|CV_HAAR_SCALE_IMAGE, Size(60, 60) );

    if (fist.size()>0)
    {
        // Draw green rectangle
        for (int i=0;i<(int)fist.size();i++)
            rectangle(frame,fist[i],Scalar(0,255,0),2);
    }

    cvtColor(frame, frame_gray,CV_BGR2RGB);
    QImage image1= QImage((uchar*) frame_gray.data, frame_gray.cols, frame_gray.rows, frame_gray.step, QImage::Format_RGB888);

    //show Qimage using QLabel
    //cameraLabel->resize(200,100);
    cameraLabel->setPixmap(QPixmap::fromImage(image1));
    cameraLabel->show();
    positionMain();
}

void TetrixBoard::positionMain()
{
    if(fist.size() == 2)  {
        int centreX1 = (fist[0].br().x + fist[0].tl().x)/2;
        int centreY1 = (fist[0].br().y + fist[0].tl().y)/2;
        int centreX2 = (fist[1].br().x + fist[1].tl().x)/2;
        int centreY2 = (fist[1].br().y + fist[1].tl().y)/2;

        if (abs(centreX1 - centreX2) < 100 && abs(centreY1 - centreY2) < 30)
        {
           qDebug()<<"touche";
           direction = "touche";
        }

        else {
            if (centreY1 > 175 && centreY2 < 125)
                    {
                       direction = "gauche";
                       qDebug()<<"gauche";
                    }
            else{
                if (centreY1 < 125 && centreY2 > 175)
                {
                   direction = "droite";
                   qDebug()<<"droite";
                }
                else{
                    direction = "";
                    qDebug()<<"rien";
                }
            }
        }
    }
}
