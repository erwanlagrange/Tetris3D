#ifndef CAMERA_H
#define CAMERA_H

#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

class camera : public QLabel
{
    Q_OBJECT

public:
    explicit camera(QWidget *parent = nullptr);
    ~camera();

private:
    VideoCapture * webCam_;
    QTimer * timer;
    VideoCapture cap;
    CascadeClassifier face_cascade;
    vector<Rect> fist;

public slots:
    void updatePicture();
    char positionMain();

signals:
    // These signals move the tetriminos when the fists are in a certain shape
    void tourneCam();
    void droiteCam();
    void gaucheCam();

};

#endif // CAMERA_H
