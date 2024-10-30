// graphiceditorwindow.cpp
#include "graphiceditorwindow.h"
#include <qcolordialog.h>
#include <qinputdialog.h>

GraphicEditorWindow::GraphicEditorWindow(QWidget *parent) : QMainWindow(parent),
                                                            image_(new QPixmap(800, 600))
{
    setWindowTitle("Graphic Editor");
    setCentralWidget(new QWidget);
    QPainter painter(image_);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawRect(0, 0, 800, 600);
}

GraphicEditorWindow::~GraphicEditorWindow()
{
    delete image_;
}



void GraphicEditorWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, *image_);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawRect(0, 0, image_->width(), image_->height());
}

void GraphicEditorWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDrawing_ = true;
        lastPoint_ = event->pos();
    }
}

void GraphicEditorWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isDrawing_)
    {
        QPainter painter(image_);
        painter.setPen(QPen(Qt::black, 2));
        painter.drawLine(lastPoint_, event->pos());
        lastPoint_ = event->pos();
        update();
    }
}

void GraphicEditorWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDrawing_ = false;
    }
}


void GraphicEditorWindow::on_brushSizeChanged()
{
}


void GraphicEditorWindow::on_eraserSizeChanged(int size)
{
    eraserSize_ = size;
    painter.setPen(QPen(Qt::white, size));
}

void GraphicEditorWindow::on_backgroundColorChanged()
{
    QColor newColor = QColorDialog::getColor(Qt::white, this);
    if (newColor.isValid()) {
        image_->fill(newColor);
        update();
    }
}

void GraphicEditorWindow::on_addFigure()
{
    QPainter painter(image_);
    painter.setPen(QPen(Qt::red, 2));
    int x = QInputDialog::getInt(this, "Graphic Editor", "Enter x coordinate:", 0, 800, 1);
    int y = QInputDialog::getInt(this, "Graphic Editor", "Enter y coordinate:", 0, 600, 1);
    int width = QInputDialog::getInt(this, "Graphic Editor", "Enter width:", 10, 800, 1);
    int height = QInputDialog::getInt(this, "Graphic Editor", "Enter height:", 10, 600, 1);
    painter.drawRect(x, y, width, height);
    update();
    // Store the points in a member variable
    points_.append(QPointF(x, y));
    points_.append(QPointF(x + width, y + height));
}

void GraphicEditorWindow::on_deleteFigure()
{
    if (!image_ || points_.isEmpty()) {
        return;
    }
    
    // Remove the last point
    points_.pop_back();
    // Draw the polyline
    QPainter painter(image_);
    painter.setPen(QPen(Qt::red, 2));
    painter.drawPolyline(points_.toVector().data(), points_.size());
    update();
}
