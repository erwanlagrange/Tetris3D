#include "camera.h"
#include "ui_camera.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>

#include "ui_widget.h"
#include <QString>
#include <QTimer>
#include <cstdio>
#include <iostream>
#include <QDebug>

using namespace cv;
using namespace std;

Camera::Camera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Camera)
{
    ui->setupUi(this);

    cap = VideoCapture(0);

    int frameWidth = 600;
    int frameHeight = 300;

    cap.set(CV_CAP_PROP_FRAME_WIDTH,frameWidth);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,frameHeight);

    if(!cap.isOpened())  // check if we succeeded
    {
        cerr<<"Error openning the default camera"<<endl;
    }

    if( !face_cascade.load( "../TestWebCamQt/fist_v3.xml" ) )
    {
        cerr<<"Error loading haarcascade"<<endl;
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePicture()));
    timer->start(16);
}

Camera::~Camera()
{
    delete ui;
    delete webCam_;
}

void Camera::updatePicture()
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

            ui->label->setPixmap(QPixmap::fromImage(image1));
            ui->label->show();
            char res = positionMain();
    }

char Camera::positionMain()
    {

    //qDebug()<<fist.size();
    ui->label_direction->setText("");

    if(fist.size() == 2)  {
        int centreX1 = (fist[0].br().x + fist[0].tl().x)/2;
        int centreY1 = (fist[0].br().y + fist[0].tl().y)/2;
        int centreX2 = (fist[1].br().x + fist[1].tl().x)/2;
        int centreY2 = (fist[1].br().y + fist[1].tl().y)/2;

        if (abs(centreX1 - centreX2) < 100 && abs(centreY1 - centreY2) < 30)
        {
           qDebug()<<"touche";
           ui->label_direction->setText("touche");
           return  'c';
        }

        if (centreY1 > 175 && centreY2 < 125)
        {
           qDebug()<<"gauche";
           ui->label_direction->setText("gauche");
           return  'g';
        }

        if (centreY1 < 125 && centreY2 > 175)
        {
           qDebug()<<"droite";
           ui->label_direction->setText("droite");
           return  'droite';
        }
    }

}
