﻿#include <QPainter>
#include <QWindow>
#include <QTime>

#include "ShapeMosaicLine.h"
#include "../Win/WinBox.h"

ShapeMosaicLine::ShapeMosaicLine(QObject* parent) : ShapeLineBase(parent)
{
    createMosaicImg();
}
ShapeMosaicLine::~ShapeMosaicLine()
{
}

void ShapeMosaicLine::paint(QPainter* painter)
{
    if (state == ShapeState::ready) {
        painter->drawImage(pathRect.topLeft(), imgPatch);
    }
    else {
        erasePath(winImg);
        painter->drawImage(QPoint(0, 0), *mosaicImg);//先画马赛克图
        painter->drawImage(QPoint(0, 0), *winImg); //再画擦除后的背景图,这样擦除部分就会显示马赛克图像了
    }
}

void ShapeMosaicLine::mouseRelease(QMouseEvent* event)
{
    if (state < ShapeState::sizing0) return;
    if (path.isEmpty()) {
        deleteLater();
        event->accept();
        return;
    }

    ShapeLineBase::mouseRelease(event);
    pathRect = path.boundingRect().adjusted(-strokeWidth, -strokeWidth, strokeWidth, strokeWidth);
    imgPatch = mosaicImg->copy(pathRect.toRect());
    QPainter painter(&imgPatch);
    painter.drawImage(QPoint(0, 0), winImg->copy(pathRect.toRect()));
    delete mosaicImg;
    delete winImg;

    if (state == ShapeState::sizing0) {
        QPainterPath tempPath;
        auto ele = pathStart.elementAt(pathStart.elementCount() - 1);
        tempPath.moveTo(ele.x, ele.y);
        for (int i = pathStart.elementCount() - 2; i >= 0; --i)
        {
            auto ele = pathStart.elementAt(i);
            tempPath.lineTo(ele.x, ele.y);
        }
        pathStart.clear();
        for (size_t i = 0; i < path.elementCount(); i++)
        {
            auto ele = path.elementAt(i);
            tempPath.lineTo(ele.x, ele.y);
        }
        path = tempPath;
    }
    auto startPos = path.elementAt(0);
    auto endPos = path.elementAt(path.elementCount() - 1);
    auto half{ draggerSize / 2 };
    draggers[0].setRect(startPos.x - half, startPos.y - half, draggerSize, draggerSize);
    draggers[1].setRect(endPos.x - half, endPos.y - half, draggerSize, draggerSize);
    showDragger();
    paintOnBoard();
    pathStroker = stroker.createStroke(path);
    event->accept();
}

void ShapeMosaicLine::mousePress(QMouseEvent* event)
{
    if (path.isEmpty() && hoverDraggerIndex >= 0) {
        imgPatch = QImage(0, 0);
        auto win = (WinBase*)parent();
        //win->repaint();
        createMosaicImg();
    }
    ShapeLineBase::mousePress(event);
}

void ShapeMosaicLine::erasePath(QImage* img)
{
    //擦除拍照得到的背景图
    QPainter painter(img);
    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    QPen pen(Qt::transparent);
    pen.setWidth(strokeWidth);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawPath(path);
}

void ShapeMosaicLine::createMosaicImg()
{
    auto win = (WinBox*)parent();
    //auto start = QTime::currentTime();
    HDC hScreen = GetDC(NULL);
    HDC hDC = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, win->w, win->h);
    DeleteObject(SelectObject(hDC, hBitmap));
    PrintWindow(win->hwnd, hDC, PW_RENDERFULLCONTENT); //给窗口拍照，注意是窗口，不是屏幕
    winImg = new QImage(win->w, win->h, QImage::Format_ARGB32);
    BITMAPINFO info = { sizeof(BITMAPINFOHEADER), (long)win->w, 0 - (long)win->h, 1, 32, BI_RGB, (DWORD)win->w * 4 * win->h, 0, 0, 0, 0 };
    GetDIBits(hDC, hBitmap, 0, win->h, winImg->bits(), &info, DIB_RGB_COLORS);
    DeleteDC(hDC);
    DeleteObject(hBitmap);
    ReleaseDC(NULL, hScreen);
    //auto ss = start.msecsTo(QTime::currentTime());
    {
        QPainter painter(winImg);
        for (int i = 0; i < win->shapes.size(); i++)
        {
            win->shapes[i]->paint(&painter);
        }
    }
    //ss = start.msecsTo(QTime::currentTime());
    //qDebug() << "\n create" << ss;
    QImage mosaicPixs = winImg->scaled(winImg->width() / mosaicRectSize,
        winImg->height() / mosaicRectSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    mosaicImg = new QImage(*winImg);
    QPainter painter(mosaicImg);
    painter.setPen(Qt::NoPen);
    for (quint32 x = 0; x < mosaicPixs.width(); x++)
    {
        auto xPos = x * mosaicRectSize;
        for (quint32 y = 0; y < mosaicPixs.height(); y++)
        {
            auto c = mosaicPixs.pixelColor(x, y);
            painter.setBrush(c);
            QRectF mRect(xPos, y * mosaicRectSize, mosaicRectSize, mosaicRectSize);
            painter.drawRect(mRect);
        }
    }
}

