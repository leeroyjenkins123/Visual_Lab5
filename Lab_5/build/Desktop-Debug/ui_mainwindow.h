/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *CreateNewFile;
    QAction *OpenFile;
    QAction *SaveFile;
    QAction *SaveFileAs;
    QAction *Search;
    QAction *Replace;
    QAction *Clear;
    QAction *Undo;
    QAction *Copy;
    QAction *Paste;
    QAction *Cut;
    QAction *Redo;
    QAction *Palette;
    QAction *FontAndSize;
    QAction *Table;
    QAction *AddRow;
    QAction *AddColumn;
    QAction *DeleteRow;
    QAction *DeleteColumn;
    QAction *Paddins;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QToolBar *mainToolBar;
    QToolBar *toolBar;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(641, 456);
        CreateNewFile = new QAction(MainWindow);
        CreateNewFile->setObjectName(QString::fromUtf8("CreateNewFile"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/images/icons/add-document _black.png"), QSize(), QIcon::Normal, QIcon::Off);
        CreateNewFile->setIcon(icon);
        OpenFile = new QAction(MainWindow);
        OpenFile->setObjectName(QString::fromUtf8("OpenFile"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/images/icons/folder-open_black.png"), QSize(), QIcon::Normal, QIcon::Off);
        OpenFile->setIcon(icon1);
        SaveFile = new QAction(MainWindow);
        SaveFile->setObjectName(QString::fromUtf8("SaveFile"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/res/images/icons/save_black.png"), QSize(), QIcon::Normal, QIcon::Off);
        SaveFile->setIcon(icon2);
        SaveFileAs = new QAction(MainWindow);
        SaveFileAs->setObjectName(QString::fromUtf8("SaveFileAs"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/res/images/icons/save_as_black.png"), QSize(), QIcon::Normal, QIcon::Off);
        SaveFileAs->setIcon(icon3);
        Search = new QAction(MainWindow);
        Search->setObjectName(QString::fromUtf8("Search"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/res/images/icons/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        Search->setIcon(icon4);
        Replace = new QAction(MainWindow);
        Replace->setObjectName(QString::fromUtf8("Replace"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/res/images/icons/replace.png"), QSize(), QIcon::Normal, QIcon::Off);
        Replace->setIcon(icon5);
        Clear = new QAction(MainWindow);
        Clear->setObjectName(QString::fromUtf8("Clear"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/res/images/icons/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        Clear->setIcon(icon6);
        Undo = new QAction(MainWindow);
        Undo->setObjectName(QString::fromUtf8("Undo"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/res/images/icons/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        Undo->setIcon(icon7);
        Copy = new QAction(MainWindow);
        Copy->setObjectName(QString::fromUtf8("Copy"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/res/images/icons/copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        Copy->setIcon(icon8);
        Paste = new QAction(MainWindow);
        Paste->setObjectName(QString::fromUtf8("Paste"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/res/images/icons/paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        Paste->setIcon(icon9);
        Cut = new QAction(MainWindow);
        Cut->setObjectName(QString::fromUtf8("Cut"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/res/images/icons/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        Cut->setIcon(icon10);
        Redo = new QAction(MainWindow);
        Redo->setObjectName(QString::fromUtf8("Redo"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/res/images/icons/un-undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        Redo->setIcon(icon11);
        Palette = new QAction(MainWindow);
        Palette->setObjectName(QString::fromUtf8("Palette"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/res/images/icons/palette.png"), QSize(), QIcon::Normal, QIcon::Off);
        Palette->setIcon(icon12);
        FontAndSize = new QAction(MainWindow);
        FontAndSize->setObjectName(QString::fromUtf8("FontAndSize"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/res/images/icons/text.png"), QSize(), QIcon::Normal, QIcon::Off);
        FontAndSize->setIcon(icon13);
        Table = new QAction(MainWindow);
        Table->setObjectName(QString::fromUtf8("Table"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/res/images/icons/table-list.png"), QSize(), QIcon::Normal, QIcon::Off);
        Table->setIcon(icon14);
        AddRow = new QAction(MainWindow);
        AddRow->setObjectName(QString::fromUtf8("AddRow"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/res/images/icons/row.png"), QSize(), QIcon::Normal, QIcon::Off);
        AddRow->setIcon(icon15);
        AddColumn = new QAction(MainWindow);
        AddColumn->setObjectName(QString::fromUtf8("AddColumn"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/res/images/icons/column.png"), QSize(), QIcon::Normal, QIcon::Off);
        AddColumn->setIcon(icon16);
        DeleteRow = new QAction(MainWindow);
        DeleteRow->setObjectName(QString::fromUtf8("DeleteRow"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/res/images/icons/delete row.png"), QSize(), QIcon::Normal, QIcon::Off);
        DeleteRow->setIcon(icon17);
        DeleteColumn = new QAction(MainWindow);
        DeleteColumn->setObjectName(QString::fromUtf8("DeleteColumn"));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/res/images/icons/delete column.png"), QSize(), QIcon::Normal, QIcon::Off);
        DeleteColumn->setIcon(icon18);
        Paddins = new QAction(MainWindow);
        Paddins->setObjectName(QString::fromUtf8("Paddins"));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/res/images/icons/indent.png"), QSize(), QIcon::Normal, QIcon::Off);
        Paddins->setIcon(icon19);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 641, 361));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 641, 20));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_2 = new QToolBar(MainWindow);
        toolBar_2->setObjectName(QString::fromUtf8("toolBar_2"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_2);
        MainWindow->insertToolBarBreak(toolBar_2);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menu->addAction(CreateNewFile);
        menu->addAction(OpenFile);
        menu->addAction(SaveFile);
        menu->addAction(SaveFileAs);
        menu_2->addAction(Search);
        menu_2->addAction(Replace);
        menu_2->addAction(Clear);
        menu_2->addAction(Undo);
        menu_2->addAction(Copy);
        menu_2->addAction(Paste);
        menu_2->addAction(Cut);
        menu_2->addAction(Redo);
        menu_3->addAction(Palette);
        menu_3->addAction(FontAndSize);
        menu_4->addAction(Table);
        menu_4->addAction(AddRow);
        menu_4->addAction(AddColumn);
        menu_4->addAction(DeleteRow);
        menu_4->addAction(DeleteColumn);
        menu_4->addAction(Paddins);
        mainToolBar->addAction(CreateNewFile);
        mainToolBar->addAction(OpenFile);
        mainToolBar->addAction(SaveFile);
        mainToolBar->addAction(SaveFileAs);
        mainToolBar->addAction(Table);
        toolBar->addAction(Search);
        toolBar->addAction(Replace);
        toolBar->addAction(Clear);
        toolBar->addAction(Undo);
        toolBar->addAction(Redo);
        toolBar->addAction(Copy);
        toolBar->addAction(Paste);
        toolBar->addAction(Cut);
        toolBar->addAction(Palette);
        toolBar->addAction(FontAndSize);
        toolBar_2->addAction(AddRow);
        toolBar_2->addAction(DeleteRow);
        toolBar_2->addAction(AddColumn);
        toolBar_2->addAction(DeleteColumn);
        toolBar_2->addAction(Paddins);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        CreateNewFile->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\275\320\276\320\262\321\213\320\271 \321\204\320\260\320\271\320\273", nullptr));
        OpenFile->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        SaveFile->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        SaveFileAs->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272", nullptr));
        Search->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        Replace->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\274\320\265\320\275\320\260", nullptr));
        Clear->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        Undo->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        Copy->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\277\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        Paste->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214", nullptr));
        Cut->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\200\320\265\320\267\320\260\321\202\321\214", nullptr));
        Redo->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\264\320\265\320\273\320\260\321\202\321\214", nullptr));
        Palette->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\320\273\320\270\321\202\321\200\320\260", nullptr));
        FontAndSize->setText(QCoreApplication::translate("MainWindow", "\320\250\321\200\320\270\321\204\321\202", nullptr));
        Table->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", nullptr));
        AddRow->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203", nullptr));
        AddColumn->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\321\202\320\276\320\273\320\261\320\265\321\206", nullptr));
        DeleteRow->setText(QCoreApplication::translate("MainWindow", "\320\243\320\261\321\200\320\260\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203", nullptr));
        DeleteColumn->setText(QCoreApplication::translate("MainWindow", "\320\243\320\261\321\200\320\260\321\202\321\214 \321\201\321\202\320\276\320\273\320\261\320\265\321\206", nullptr));
        Paddins->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\321\201\321\202\321\203\320\277\321\213", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\234\320\265\320\275\321\216", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\272\321\201\321\202", nullptr));
        menu_4->setTitle(QCoreApplication::translate("MainWindow", "\320\242\320\260\320\261\320\273\320\270\321\206\320\260", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
        toolBar_2->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar_2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
