#ifndef GRAPHICSEDITOR_H
#define GRAPHICSEDITOR_H

#include <QMainWindow>

namespace Ui {
class GraphicsEditor;
}

class GraphicsEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphicsEditor(QWidget *parent = nullptr);
    ~GraphicsEditor();

private:
    Ui::GraphicsEditor *ui;
};

#endif // GRAPHICSEDITOR_H
