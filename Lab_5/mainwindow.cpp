#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeTab(int index)
{
    QWidget *widget = ui->tabWidget->widget(index);

    if (widget) {
        QTextEdit* editor = qobject_cast<QTextEdit*>(widget);
        QTableWidget* table = qobject_cast<QTableWidget*>(widget);
        QString filePath = ui->tabWidget->tabToolTip(index);

        if (editor && !editor->document()->isModified()) {
            ui->tabWidget->removeTab(index);
            editor->deleteLater(); 
        }

        else if (table && !tableModified) {
            ui->tabWidget->removeTab(index);
            table->deleteLater(); 
        }
        else {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Закрыть вкладку",
                    "Этот файл содержит несохранённые изменения. Сохранить перед закрытием?",
                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

            if (reply == QMessageBox::Yes) {
                
                on_SaveFile_triggered();
                ui->tabWidget->removeTab(index);
                widget->deleteLater(); 
            } else if (reply == QMessageBox::No) {
                ui->tabWidget->removeTab(index);
                widget->deleteLater(); 
            }

        }
    }
}