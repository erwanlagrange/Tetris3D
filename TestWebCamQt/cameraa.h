#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include "opencv2/opencv.hpp"

using namespace cv;

class Camera : public QWidget
{
    Q_OBJECT

public:
    explicit Camera(QWidget *parent = nullptr);
    ~Camera();

private:
    VideoCapture * webCam_;
    QTimer * timer;
    VideoCapture cap;
    CascadeClassifier face_cascade;

public slots:
    void updatePicture();

};

#endif // CAMERA_H
