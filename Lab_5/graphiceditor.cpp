#include "graphiceditor.h"
#include "ui_graphiceditor.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QScrollBar>

graphiceditor::graphiceditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::graphiceditor),
    imageLabel(new QLabel(this)),
    image_(new QPixmap(800, 600)),  // Начальный размер изображения
    scrollArea(new QScrollArea(this))
{
    ui->setupUi(this);
    setWindowTitle("Graphic Editor");

    image_->fill(Qt::white);  // Заполняем белым цветом

    // Настраиваем QLabel для отображения изображения
    imageLabel->setPixmap(*image_);
    imageLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // Настраиваем QScrollArea для прокрутки изображения
    scrollArea->setWidget(imageLabel);
    scrollArea->setWidgetResizable(true);

    // Устанавливаем QScrollArea как центральный виджет
    setCentralWidget(scrollArea);
}

graphiceditor::~graphiceditor()
{
    delete ui;
    delete image_;
}

void graphiceditor::closeEvent(QCloseEvent *event)
{
    emit editorClosed();
    QMainWindow::closeEvent(event);
}

void graphiceditor::resizeEvent(QResizeEvent *event)
{
    if (event->size().width() > image_->width() || event->size().height() > image_->height()) {
        QPixmap newImage(event->size().width(), event->size().height());
        newImage.fill(Qt::white);

        QPainter painter(&newImage);
        painter.drawPixmap(0, 0, *image_);

        *image_ = newImage;
        imageLabel->setPixmap(*image_);
        imageLabel->resize(image_->size());
    }

    QMainWindow::resizeEvent(event);
}

void graphiceditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, *image_);
}

void graphiceditor::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDrawing_ = true;

        // Учитываем текущие значения прокрутки
        int xOffset = scrollArea->horizontalScrollBar()->value();
        int yOffset = scrollArea->verticalScrollBar()->value();

        lastPoint_ = event->pos() + QPoint(xOffset, yOffset);
    }
}

void graphiceditor::mouseMoveEvent(QMouseEvent *event)
{
    if (isDrawing_)
    {
        int xOffset = scrollArea->horizontalScrollBar()->value();
        int yOffset = scrollArea->verticalScrollBar()->value();

        QPoint currentPoint = event->pos() + QPoint(xOffset, yOffset);

        QPainter painter(image_);
        painter.setPen(QPen(Qt::black, 2));
        painter.drawLine(lastPoint_, currentPoint);

        lastPoint_ = currentPoint;
        imageLabel->setPixmap(*image_);
        update();
    }
}

void graphiceditor::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDrawing_ = false;
    }
}
