
//
// Created by Naren Sadhwani on 03.04.24.
//

#ifndef OCR_SCREENCAPTURE_H
#define OCR_SCREENCAPTURE_H

#include <QWidget>
#include "../MainWindow.h"

class MainWindow; // Forward declaration of MainWindow

class ScreenCapture: public QWidget {
    Q_OBJECT
public:
    explicit ScreenCapture(MainWindow *w);
    ~ScreenCapture() override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void closeWindow();
    void confirmCapture();

private:
    void initShortcuts();
    QPixmap captureDesktop();

    MainWindow *window;
    QPixmap screen;
    QPoint p1, p2;
    bool mouseDown;



};


#endif //OCR_SCREENCAPTURE_H
