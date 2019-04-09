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

#include "tetrixwindow.h"
#include "glwidget.h"

//! [0]
TetrixWindow::TetrixWindow()
{
//! [0]
    glWidget = new GLWidget();
    nextPieceLabel = new QLabel;
    nextPieceLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    nextPieceLabel->setAlignment(Qt::AlignCenter);
    glWidget->setNextPieceLabel(nextPieceLabel);

//! [1]
    scoreLcd = new QLCDNumber(5);
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);
//! [1]
    levelLcd = new QLCDNumber(2);
    levelLcd->setSegmentStyle(QLCDNumber::Filled);
    linesLcd = new QLCDNumber(5);
    linesLcd->setSegmentStyle(QLCDNumber::Filled);

//! [2]
    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton(tr("&Pause"));
//! [2] //! [3]
    pauseButton->setFocusPolicy(Qt::NoFocus);
//! [3] //! [4]
//! [Camera]
    labelCamera = new QLabel;
    labelCamera->setFrameStyle(QFrame::Box | QFrame::Raised);
    Camera = new CameraWidget(labelCamera);

    connect(startButton, &QPushButton::clicked, glWidget, &GLWidget::start);

    connect(startButton, &QPushButton::clicked, Camera, &CameraWidget::play);
//! [4] //! [5]
    connect(quitButton , &QPushButton::clicked, this, &TetrixWindow::destroyCam);
    connect(quitButton , &QPushButton::clicked, qApp, &QApplication::quit);
    connect(pauseButton, &QPushButton::clicked, glWidget, &GLWidget::pause);
    connect(pauseButton, &QPushButton::clicked, Camera, &CameraWidget::changePlay);
#if __cplusplus >= 201402L
    connect(glWidget, &GLWidget::scoreChanged,
           scoreLcd, qOverload<int>(&QLCDNumber::display));
    connect(glWidget, &GLWidget::levelChanged,
            levelLcd, qOverload<int>(&QLCDNumber::display));
    connect(glWidget, &GLWidget::linesRemovedChanged,
            linesLcd, qOverload<int>(&QLCDNumber::display));
#else
    connect(board, &TetrixBoard::scoreChanged,
            scoreLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(board, &TetrixBoard::levelChanged,
            levelLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(board, &TetrixBoard::linesRemovedChanged,
            linesLcd, QOverload<int>::of(&QLCDNumber::display));
#endif
    connect(Camera,&CameraWidget::tryMoveCam,glWidget,&GLWidget::tryMoveCam);
    connect(this,&TetrixWindow::kPressEvent, glWidget,&GLWidget::kPressEvent);
//! [5]

//! [6]
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createLabel(tr("NEXT")), 0, 0);
    layout->addWidget(nextPieceLabel, 1, 0);
    layout->addWidget(createLabel(tr("LEVEL")), 2, 0);
    layout->addWidget(levelLcd, 3, 0);
    layout->addWidget(createLabel(tr("LINES REMOVED")), 4, 0);
    layout->addWidget(linesLcd, 5, 0);
    layout->addWidget(startButton, 6, 0);
    layout->addWidget(quitButton, 7, 0);
    layout->addWidget(pauseButton, 8, 0);
    layout->addWidget(glWidget, 0, 1, 9, 1);
    layout->addWidget(createLabel(tr("SCORE")), 0, 2);
    layout->addWidget(scoreLcd, 1, 2);
    layout->addWidget(createLabel(tr("CAMERA")), 2, 2);
    layout->addWidget(labelCamera,3,2);
    setLayout(layout);

    setWindowTitle(tr("Tetrix"));
    QTimer::singleShot(0, this, SLOT(showFullScreen()));
}
//! [6]
void TetrixWindow::destroyCam(){
    Camera->~CameraWidget();
}
//! [7]
QLabel *TetrixWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}
//! [7]
void TetrixWindow::keyPressEvent(QKeyEvent *event){
    emit kPressEvent(event);
}

