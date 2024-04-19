//
// Created by Naren Sadhwani on 03.04.24.
//

#include <QApplication>
#include "ScreenCapture.h"
#include <QScreen>
#include <QDesktopWidget>
#include <QRect>
#include <QPainter>
#include <QColor>
#include <QRegion>
#include <QShortcut>
#include <QMouseEvent>

ScreenCapture::ScreenCapture(MainWindow *w) :
QWidget(nullptr), window(w) {
    setWindowFlags(
            Qt::BypassWindowManagerHint
            | Qt::WindowStaysOnTopHint
            | Qt::FramelessWindowHint
            | Qt::Tool
            );

    setAttribute(Qt::WA_DeleteOnClose);
    screen = captureDesktop();
    resize(screen.size());
    initShortcuts();
}

ScreenCapture::~ScreenCapture() {

}

void ScreenCapture::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0,0, screen);
    QRegion grey(rect());

    if(p1.x()!=p2.x() && p1.y() != p2.y()){
        painter.setPen(QColor(200,100,50,255));
        painter.drawRect(QRect(p1,p2));
        grey = grey.subtracted(QRect(p1,p1));
    }



    painter.setClipRegion(grey);
    QColor overlayColor(20,20,20,50);
    painter.fillRect(rect(), overlayColor);
    painter.setClipRect(rect());
}

void ScreenCapture::mouseMoveEvent(QMouseEvent *event) {
    if(!mouseDown) return;
    p2 = event->pos();
    update();
}

void ScreenCapture::mousePressEvent(QMouseEvent *event) {
    mouseDown = true;
    p1 = event->pos();
    p2 = event->pos();
    update();


}

void ScreenCapture::mouseReleaseEvent(QMouseEvent *event) {
    mouseDown = false;
    p2 = event->pos();
    update();
}

void ScreenCapture::closeWindow() {
    this->close();
    window->showNormal();
    window->activateWindow();
}

void ScreenCapture::confirmCapture() {
    QRect region = QRect(p1, p2).normalized();
    QPixmap image = screen.copy(region);
    window->showImage(image);
    closeWindow();
}

void ScreenCapture::initShortcuts() {
    new QShortcut(Qt::Key_Escape, this, SLOT(closeWindow()));
    new QShortcut(Qt::Key_Return, this, SLOT(confirmCapture()));
}

QPixmap ScreenCapture::captureDesktop() {
    QRect geometry;
    for (QScreen *const screen : QGuiApplication::screens()) {
        geometry = geometry.united(screen->geometry());
    }

    QPixmap pixmap(QApplication::primaryScreen()->grabWindow(
            QApplication::desktop()->winId(),
            geometry.x(),
            geometry.y(),
            geometry.width(),
            geometry.height()
    ));
    pixmap.setDevicePixelRatio(QApplication::desktop()->devicePixelRatio());
    return pixmap;
}






