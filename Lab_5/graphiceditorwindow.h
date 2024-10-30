// graphiceditorwindow.h
#ifndef GRAPHICEDITORWINDOW_H
#define GRAPHICEDITORWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>

class GraphicEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    GraphicEditorWindow(QWidget *parent = nullptr);
    void on_brushSizeChanged();
    void on_eraserSizeChanged(int size);
    void on_backgroundColorChanged();
    void on_addFigure();
    void on_deleteFigure();
    ~GraphicEditorWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPixmap *image_;
    QPoint lastPoint_;
    bool isDrawing_;
    QPainter painter;
    int eraserSize_;
    QList<QPointF> points_;

};

#endif // GRAPHICEDITORWINDOW_H
