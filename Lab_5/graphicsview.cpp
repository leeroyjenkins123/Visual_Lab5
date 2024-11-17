#include "graphicsview.h"
#include "graphicseditor.h"

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

void GraphicsView::setEraserMode(bool mode)
{
    isEraserMode = mode;
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

        if(selectedItem){
            QGraphicsItemGroup *itemGroup = dynamic_cast<QGraphicsItemGroup *>(selectedItem->topLevelItem());
                    if (selectedItem->flags().testFlag(QGraphicsItem::ItemIsMovable) || (itemGroup && itemGroup->flags().testFlag(QGraphicsItem::ItemIsMovable))) {
                        isMovingShape = true;  // Устанавливаем флаг перемещения
                        selectedItem->setZValue(1);
                        lastMousePos = event->pos();
                    }
        }
        else if (event->button() == Qt::LeftButton && viewport()->rect().adjusted(
                    10, 10,
                    -10, -10).contains(event->pos()))
        {
            isDrawing = true;
            isMovingShape = false;
            lastPoint = mapToScene(event->pos()).toPoint(); // Запоминаем точку нажатия
        }
        else if (isEraserMode && event->button() == Qt::LeftButton)
                {
                    // Start erasing on left mouse button press
                    isDrawing = true;
                    lastPoint = mapToScene(event->pos()).toPoint(); // Capture initial point for eraser
                }

    QGraphicsView::mousePressEvent(event); // Не забываем вызвать базовый метод
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (isEraserMode && isDrawing) {
        QPoint currentPoint = mapToScene(event->pos()).toPoint();
            QPainterPath eraserPath;
            eraserPath.addEllipse(currentPoint, currentPen.width() / 2, currentPen.width() / 2); // Задаем область ластика

            QList<QGraphicsItem*> itemsToErase = scene()->items(eraserPath); // Находим объекты в области ластика

            for (QGraphicsItem* item : itemsToErase) {
                bool isUserCreated = item->data(0) == "user"; // Проверяем метку элемента

                if (isUserCreated) {
                    // Удаляем только нарисованные элементы
                    scene()->removeItem(item);
                    delete item;
                }
            }

            lastPoint = currentPoint; // Обновляем точку для плавного стирания
        }
    else if (isDrawing && !isMovingShape)
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
        line->setZValue(1);
        line->setData(0, "user");

        lastPoint = currentPoint; // Обновляем последнюю точку
    }
    else if (isMovingShape) {
           QGraphicsItem *selectedItem = scene()->itemAt(mapToScene(event->pos()), QTransform());

                   if (selectedItem) {

                       // Проверяем, является ли элемент частью группы
                       QGraphicsItemGroup *itemGroup = dynamic_cast<QGraphicsItemGroup *>(selectedItem->topLevelItem());
                       if (itemGroup) {
                           // Перемещаем всю группу
                           QPointF currentPos = itemGroup->pos();
                           QPointF delta = mapToScene(event->pos()) - mapToScene(lastMousePos);  // Смещение от предыдущей позиции

                           // Проверка на столкновение с границами
                           GraphicsEditor* editor = qobject_cast<GraphicsEditor*>(parent());
                           if (editor) {
                               if (itemGroup->collidesWithItem(editor->getTopWall()) ||
                                   itemGroup->collidesWithItem(editor->getBottomWall()) ||
                                   itemGroup->collidesWithItem(editor->getLeftWall()) ||
                                   itemGroup->collidesWithItem(editor->getRightWall())) {
                                   return;  // Прекращаем перемещение при столкновении с границей
                               }
                           }

                           // Применяем смещение к группе
                           itemGroup->setPos(currentPos + delta);
                       } else {
                           // Для обычных объектов
                           QPointF currentPos = selectedItem->pos();
                           QPointF delta = mapToScene(event->pos()) - mapToScene(lastMousePos);  // Смещение от предыдущей позиции

                           // Проверка на столкновение с границами
                           GraphicsEditor* editor = qobject_cast<GraphicsEditor*>(parent());
                           if (editor) {
                               if (selectedItem->collidesWithItem(editor->getTopWall()) ||
                                   selectedItem->collidesWithItem(editor->getBottomWall()) ||
                                   selectedItem->collidesWithItem(editor->getLeftWall()) ||
                                   selectedItem->collidesWithItem(editor->getRightWall())) {
                                   return;  // Прекращаем перемещение при столкновении с границей
                               }
                           }

                           // Применяем смещение к объекту
                           selectedItem->setPos(currentPos + delta);
                       }
                   }
               }

               lastMousePos = event->pos();
    QGraphicsView::mouseMoveEvent(event); // Не забываем вызвать базовый метод
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{

        isDrawing = false;
    isMovingShape = false;
    QGraphicsView::mouseReleaseEvent(event); // Не забываем вызвать базовый метод
}

