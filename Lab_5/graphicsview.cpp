#include "graphicsview.h"

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent),
                                                                     currentColor(Qt::black),
                                                                     isDrawing(false), // Цвет по умолчанию
                                                                     isMovingShape(false)
{
    setRenderHint(QPainter::Antialiasing); // Включение сглаживания
    setRenderHint(QPainter::SmoothPixmapTransform);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn); // Включаем прокрутку
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);   // Включаем прокрутку
    setDragMode(QGraphicsView::NoDrag);                  // Отключаем следование за курсором

}

GraphicsView::~GraphicsView()
{
}

void GraphicsView::setPen(const QPen &pen)
{
    currentPen = pen;
}

void GraphicsView::scrollContentsBy(int dx, int dy)
{
    QGraphicsView::scrollContentsBy(dx, dy);
    emit viewportChanged();
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{

        // Проверяем, находится ли точка в пределах окна
        // viewport()->rect().contains(event->pos())
        QGraphicsItem *selectedItem = scene()->itemAt(mapToScene(event->pos()), QTransform());
        if (selectedItem && selectedItem->flags().testFlag(QGraphicsItem::ItemIsMovable)) {
                isMovingShape = true;  // Устанавливаем флаг перемещения
                selectedItem->setZValue(1);
            }
        else if (event->button() == Qt::LeftButton && viewport()->rect().adjusted(
                    10, 10,
                    -10, -10).contains(event->pos()))
        {
            isDrawing = true;
            isMovingShape = false;
            lastPoint = mapToScene(event->pos()).toPoint(); // Запоминаем точку нажатия
        }

    QGraphicsView::mousePressEvent(event); // Не забываем вызвать базовый метод
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (isDrawing && !isMovingShape)
    {
        // Если точка находится за пределами окна, прекращаем рисование
        if (!viewport()->rect().adjusted(
                    10, 10,
                    -10, -10).contains(event->pos()))
        {
            isDrawing = false;
            return;
        }

        QPoint currentPoint = mapToScene(event->pos()).toPoint(); // Получаем текущую точку
        QPainterPath path;
        path.moveTo(lastPoint);
        path.lineTo(currentPoint);

        // Добавляем линию на сцену
        QGraphicsPathItem *line = scene()->addPath(path, currentPen);
        line->setZValue(-1);

        lastPoint = currentPoint; // Обновляем последнюю точку
    }
    QGraphicsView::mouseMoveEvent(event); // Не забываем вызвать базовый метод
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDrawing = false;
    }
    QGraphicsView::mouseReleaseEvent(event); // Не забываем вызвать базовый метод
}
