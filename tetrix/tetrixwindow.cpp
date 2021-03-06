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

#include "tetrixboard.h"
#include "tetrixwindow.h"
#include "camera.h"

//! [0]
TetrixWindow::TetrixWindow()
{
    QFont fontbutton;
    fontbutton.setPointSize(14);
    fontbutton.setBold(true);

    board = new TetrixBoard;
    cameraWidget = new camera(); // widget camera

    nextPieceLabel = new QLabel;
    nextPieceLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    nextPieceLabel->setAlignment(Qt::AlignCenter);
    //nextPieceLabel->setMinimumHeight(200);
    board->setNextPieceLabel(nextPieceLabel);

    scoreLcd = new QLCDNumber(5);
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    scoreLcd->setMinimumHeight(50);
    scoreLcd->setMaximumHeight(100);
    levelLcd = new QLCDNumber(2);
    levelLcd->setSegmentStyle(QLCDNumber::Filled);
    levelLcd->setMinimumHeight(50);
    levelLcd->setMaximumHeight(100);
    linesLcd = new QLCDNumber(5);
    linesLcd->setSegmentStyle(QLCDNumber::Filled);
    linesLcd->setMinimumHeight(50);
    linesLcd->setMaximumHeight(100);

    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);
    startButton->setFont(fontbutton);
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    quitButton->setFont(fontbutton);
    pauseButton = new QPushButton(tr("&Pause"));
    pauseButton->setFocusPolicy(Qt::NoFocus);
    pauseButton->setFont(fontbutton);

    connect(startButton, &QPushButton::clicked, board, &TetrixBoard::start);
    connect(quitButton , &QPushButton::clicked, qApp, &QApplication::quit);
    connect(pauseButton, &QPushButton::clicked, board, &TetrixBoard::pause);

    connect(board, &TetrixBoard::scoreChanged,
            scoreLcd, qOverload<int>(&QLCDNumber::display));
    connect(board, &TetrixBoard::levelChanged,
            levelLcd, qOverload<int>(&QLCDNumber::display));
    connect(board, &TetrixBoard::linesRemovedChanged,
            linesLcd, qOverload<int>(&QLCDNumber::display));

    connect(cameraWidget,SIGNAL(tourneCam()),board,SLOT(touche()));                    // faire les fonctions dans board
    connect(cameraWidget,SIGNAL(droiteCam()),board,SLOT(droite()));
    connect(cameraWidget,SIGNAL(gaucheCam()),board,SLOT(gauche()));
    connect(cameraWidget,SIGNAL(descendreCam()),board,SLOT(descendre()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createLabel(tr("NEXT PIECE")), 0, 0);
    layout->addWidget(nextPieceLabel, 1, 0);
    layout->addWidget(createLabel(tr("CAMERA")), 2, 0);
    layout->addWidget(cameraWidget, 3, 0); // Camera
    layout->addWidget(board, 0, 1, 7, 1);
    layout->addWidget(createLabel(tr("SCORE")), 0, 2);
    layout->addWidget(scoreLcd, 1, 2);
    layout->addWidget(createLabel(tr("LEVEL")), 2, 2);
    layout->addWidget(levelLcd, 3, 2);
    layout->addWidget(createLabel(tr("LINES REMOVED")), 4, 2);
    layout->addWidget(linesLcd, 5, 2);
    layout->addWidget(startButton, 6, 2);
    layout->addWidget(quitButton, 7, 2);
    layout->addWidget(pauseButton, 8, 2);
    setLayout(layout);

    setWindowTitle(tr("Tetrax"));
    resize(1550, 875);
}

QLabel *TetrixWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);

    QFont font;
    font.setPointSize(22);
    font.setBold(true);

    label->setFont(font);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}


