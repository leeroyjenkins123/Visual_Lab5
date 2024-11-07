#ifndef GRAPHICSEDITOR_H
#define GRAPHICSEDITOR_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QPen>
#include <QDialog>
#include <QGraphicsPixmapItem>

#include "graphicsview.h" // Подключаем наш новый класс GraphicsView

namespace Ui
{
    class GraphicsEditor;
}

class GraphicsEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphicsEditor(QWidget *parent = nullptr);
    ~GraphicsEditor() override;

signals:
    void editorClosed();

protected:
    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_BackColor_triggered();
    void on_SetPen_triggered();
    void on_Clear_triggered();
    void setupWalls();
    void updateWallPositions();
    void on_AddFigure_triggered();
    void addShape(QString shapeType, QRectF rect, QColor fillColor, QColor strokeColor, int strokeWidth);

    void on_DeleteFigure_triggered();

private:
    Ui::GraphicsEditor *ui;
    QGraphicsScene *scene;
    QColor currentColor;
    QPen currentPen;
    GraphicsView *view;


    QGraphicsPixmapItem *topWall;
    QGraphicsPixmapItem *bottomWall;
    QGraphicsPixmapItem *leftWall;
    QGraphicsPixmapItem *rightWall;
};

#endif // GRAPHICSEDITOR_H
