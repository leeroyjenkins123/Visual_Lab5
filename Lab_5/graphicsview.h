#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPainter>
#include <QGraphicsScene>
#include <QPainterPath>
#include <QPen>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
    ~GraphicsView() override;
    void setPen(const QPen &pen);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPoint lastPoint;  // Текущая точка рисования
    QColor currentColor;  // Цвет кисти
    bool isDrawing;  // Флаг, рисуем ли мы
    QPen currentPen;

};

#endif // GRAPHICSVIEW_H
