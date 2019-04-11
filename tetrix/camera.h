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
    // affichage de la caméra
    VideoCapture * webCam_;
    QTimer * timer;
    VideoCapture cap;
    // classe qui va identifier les poings
    CascadeClassifier face_cascade;
    // vecteur qui contiendra des rectangles avec la position des poing
    vector<Rect> fist;
    // variable qui sert a cadencer la vitesse des mouvements
    int i;

public slots:
    // mets a jour l'image en continu
    void updatePicture();
    // calcule la position des mains et emmet un signal en fonction de celle ci
    void positionMain();

signals:
    // singaux qui vont faire bouger les pieces
    void tourneCam();
    void droiteCam();
    void gaucheCam();
    void descendreCam();

};

#endif // CAMERA_H
