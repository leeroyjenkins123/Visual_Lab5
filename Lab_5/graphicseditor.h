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

#include "GraphicsView.h"// Подключаем наш новый класс GraphicsView

namespace Ui {
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

private slots:
    void on_BackColor_triggered();
    void on_SetPen_triggered();

    void on_Clear_triggered();

private:
    Ui::GraphicsEditor *ui;
    QGraphicsScene *scene;
    QColor currentColor;  // Цвет кисти
    QPen currentPen;
     GraphicsView *view;
};

#endif // GRAPHICSEDITOR_H
