#ifndef GRAPHICEDITOR_H
#define GRAPHICEDITOR_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>
#include <QLabel>
#include <QScrollArea>

namespace Ui {
class graphiceditor;
}

class graphiceditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit graphiceditor(QWidget *parent = nullptr);
    ~graphiceditor() override;

signals:
    void editorClosed();

protected:
    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::graphiceditor *ui;
    QLabel *imageLabel;     // QLabel для отображения изображения
    QPixmap *image_;        // QPixmap для рисования
    QScrollArea *scrollArea; // QScrollArea для прокрутки изображения
    QPoint lastPoint_;      // Последняя точка для рисования линии
    bool isDrawing_ = false; // Флаг для отслеживания рисования
};

#endif // GRAPHICEDITOR_H
