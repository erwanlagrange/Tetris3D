#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

namespace Ui {
class Camera;
}

class Camera : public QWidget
{
    Q_OBJECT

public:
    explicit Camera(QWidget *parent = nullptr);
    ~Camera();

private:
    Ui::Camera *ui;
    VideoCapture * webCam_;
    QTimer * timer;
    VideoCapture cap;
    CascadeClassifier face_cascade;
    vector<Rect> fist;

public slots:
    void updatePicture();
    char positionMain();

};

#endif // CAMERA_H
