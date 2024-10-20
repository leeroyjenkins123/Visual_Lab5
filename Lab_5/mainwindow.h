#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QFile>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QTextStream>
#include <QDebug>
#include <QPushButton>
#include <QCheckBox>
#include <QCloseEvent>
#include <QTemporaryFile>
#include <QFontDialog>
#include <QColorDialog>
#include <QSettings>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextBlock>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QSpinBox>
#include <QTextTableCell>
#include <QRadioButton>
#include <QTemporaryFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_CreateNewFile_triggered();

    void on_OpenFile_triggered();

    void on_SaveFile_triggered();

    void on_SaveFileAs_triggered();

    void on_Search_triggered();

    void on_Replace_triggered();

    void on_Table_triggered();

    void setupShortcuts();

    void onTableCellChanged(int row, int column);

    void on_AddRow_triggered();

    void on_AddColumn_triggered();

    void on_DeleteRow_triggered();

    void on_DeleteColumn_triggered();

private:
    Ui::MainWindow *ui;
    int pageIndex;
    QTextEdit *editor;
    QTableWidget *tableWidget;
    QFont currentFont;
    QColor textColor;
    QColor backgroundColor;
    QString appDir = "Laboratory_5";
    bool tableModified = true;
    static QTemporaryFile tempFile;
};

#endif // MAINWINDOW_H
