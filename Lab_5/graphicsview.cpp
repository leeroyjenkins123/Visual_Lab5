#include "GraphicsView.h"

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent) :
    QGraphicsView(scene, parent),
    currentColor(Qt::black),
    isDrawing(false)// Цвет по умолчанию
{
    setRenderHint(QPainter::Antialiasing);  // Включение сглаживания
    setRenderHint(QPainter::SmoothPixmapTransform);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);  // Включаем прокрутку
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);    // Включаем прокрутку
    setDragMode(QGraphicsView::NoDrag);  // Отключаем следование за курсором
}

GraphicsView::~GraphicsView()
{
}

void GraphicsView::setPen(const QPen &pen)
{
    currentPen = pen;
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
            // Проверяем, находится ли точка в пределах окна
            if (this->rect().contains(event->pos())) {
                isDrawing = true;
                lastPoint = mapToScene(event->pos()).toPoint();  // Запоминаем точку нажатия
            }
        }
        QGraphicsView::mousePressEvent(event);  // Не забываем вызвать базовый метод
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (isDrawing) {
            // Если точка находится за пределами окна, прекращаем рисование
            if (!this->rect().contains(event->pos())) {
                isDrawing = false;
                return;
            }

            QPoint currentPoint = mapToScene(event->pos()).toPoint();  // Получаем текущую точку
            QPainterPath path;
            path.moveTo(lastPoint);
            path.lineTo(currentPoint);

            // Добавляем линию на сцену
            scene()->addPath(path, currentPen);

            lastPoint = currentPoint;  // Обновляем последнюю точку
        }
        QGraphicsView::mouseMoveEvent(event);  // Не забываем вызвать базовый метод
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isDrawing = false;
    }
    QGraphicsView::mouseReleaseEvent(event);  // Не забываем вызвать базовый метод
}
