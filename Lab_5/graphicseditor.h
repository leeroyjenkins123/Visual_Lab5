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
#include <QDebug>
#include <QTimer>
#include <QSound>
#include <QRandomGenerator>
#include <QtMath>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>

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
    QGraphicsPixmapItem* getTopWall() const { return topWall; }
        QGraphicsPixmapItem* getBottomWall() const { return bottomWall; }
        QGraphicsPixmapItem* getLeftWall() const { return leftWall; }
        QGraphicsPixmapItem* getRightWall() const { return rightWall; }
        QList<QGraphicsItemGroup*> getMovingItemGroups() const { return movingItemGroups; }

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
    void addShape(QString shapeType, QRectF rect, QColor fillColor, Qt::BrushStyle brushStyle, QColor strokeColor, int strokeWidth);
    void on_DeleteFigure_triggered();
    void drawKapustin();
    void drawFrolova();
    void drawNazarov();
    void groupSetFlags(QGraphicsItemGroup *group);
    void textSetFlags(QGraphicsTextItem *item);
    Qt::BrushStyle stringToBrushStyle(const QString &styleStr);
    void createMovingObject_1();
    void createMovingObject_2();
    void createMovingObject_3();
    void moveObject();
    void on_Eraser_triggered();
    void on_actionSaveScene_triggered();
    void on_ActionAddImage_triggered();
    void resumeMovingObjects();
    void stopMovingObjects();

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

    QTimer *moveTimer;

    QList<QGraphicsItemGroup*> movingItemGroups;  // Список движущихся объектов
    QList<QPointF> velocities;
    QSound collisionSound;
    QList<bool> movingStates;

};

#endif // GRAPHICSEDITOR_H
