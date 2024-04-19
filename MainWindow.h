
//
// Created by Naren Sadhwani on 03.04.24.
//

#ifndef OCR_MAINWINDOW_H
#define OCR_MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTextEdit>
#include <QLabel>
#include <tesseract/baseapi.h>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <QCheckBox>

#include "ScreenCaptureClass/ScreenCapture.h"
class MainWindow : public QMainWindow{
Q_OBJECT



public:
    explicit MainWindow(QWidget *parent= nullptr);
    ~MainWindow() override;
    void showImage(QPixmap image);
    

private:
    //Functions
    void initUI();
    void createActions();
    void setupShortcuts();

    void showImage(cv::Mat);
    void decode(const cv::Mat& scores, const cv::Mat& geometry, float threshold,
                std::vector<cv::RotatedRect>& detections, std::vector<float>& confidences);

    cv::Mat detectTextAreas(QImage &image, std::vector<cv::Rect>&);



    //Variables and placeholders
    // Menu and toolbar
    QMenu *fileMenu{};
    QToolBar *fileMenuToolBar{};

    //Graphics
    QGraphicsScene *imageScene{};
    QGraphicsView *imageView{};

    //Views
    QTextEdit *editor{};
    QStatusBar *mainStatusBar{};
    QLabel *mainStatusLabel{};

    //Actions
    QAction *openAction{};
    QAction *saveImageAction{};
    QAction *saveTextAsAction{};
    QAction *exitAction{};

    //Placeholders
    QString currentImagePath{};
    QGraphicsPixmapItem *currentImage{};

    //Text Actions
    QAction *ocrAction{};
    tesseract::TessBaseAPI *tesseractAPI;

    //DNN
    QCheckBox *detectAreaCheckBox{};
    cv::dnn::Net net;

    // Screen Capture
    QAction *captureAction{};

private slots:
    void openImage();
    void saveImageAs();
    void saveTextAs();
    void showImage(QString path);
    void extractText();

    //Screen Capture
    void captureScreen();
    void startCapture();




};


#endif //OCR_MAINWINDOW_H
