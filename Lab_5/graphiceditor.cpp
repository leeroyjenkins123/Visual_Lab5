#include "graphiceditor.h"
#include "ui_graphiceditor.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QScrollBar>

graphiceditor::graphiceditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::graphiceditor),
    image_(new QPixmap(800, 600)),  // Начальный размер изображения
    scrollArea(new QScrollArea(this)),
    currentPen(Qt::black, 2)
{
    ui->setupUi(this);
    setWindowTitle("Graphic Editor");

    image_->fill(Qt::white);  // Заполняем белым цветом

        // Настраиваем QLabel для отображения изображения
    imageLabel->setPixmap(*image_);
    imageLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

        // Настраиваем QScrollArea для прокрутки изображения
        scrollArea->setWidget(imageLabel);
        scrollArea->setWidgetResizable(true);

        // Создаем центральный виджет и устанавливаем его в QMainWindow
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        // Настраиваем QVBoxLayout
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);
        layout->addWidget(scrollArea);

        // Установите дополнительные элементы интерфейса, если нужно
        // Например, добавьте кнопки или другие виджеты

        // Устанавливаем QVBoxLayout как главный компоновщик для центрального виджета
        centralWidget->setLayout(layout);
}

graphiceditor::~graphiceditor()
{
    delete ui;
    delete image_;
}

void graphiceditor::closeEvent(QCloseEvent *event)
{
    emit editorClosed();
    QMainWindow::closeEvent(event);
}

void graphiceditor::resizeEvent(QResizeEvent *event)
{
    if (event->size().width() > image_->width() || event->size().height() > image_->height()) {
        QPixmap newImage(event->size().width(), event->size().height());
        newImage.fill(Qt::white);

        QPainter painter(&newImage);
        painter.drawPixmap(0, 0, *image_);

        *image_ = newImage;
        imageLabel->setPixmap(*image_);
        imageLabel->resize(image_->size());
    }

    QMainWindow::resizeEvent(event);
}

void graphiceditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, *image_);
}

void graphiceditor::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDrawing_ = true;

        // Учитываем текущие значения прокрутки
        int xOffset = scrollArea->horizontalScrollBar()->value();
        int yOffset = scrollArea->verticalScrollBar()->value();

        lastPoint_ = event->pos() + QPoint(xOffset, yOffset);
    }
}

void graphiceditor::mouseMoveEvent(QMouseEvent *event)
{
    if (isDrawing_)
    {
        int xOffset = scrollArea->horizontalScrollBar()->value();
        int yOffset = scrollArea->verticalScrollBar()->value();

        QPoint currentPoint = event->pos() + QPoint(xOffset, yOffset);

        QPainter painter(image_);
        painter.setPen(currentPen);
        painter.drawLine(lastPoint_, currentPoint);

        lastPoint_ = currentPoint;
        imageLabel->setPixmap(*image_);
        update();
    }
}

void graphiceditor::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDrawing_ = false;
    }
}

void graphiceditor::on_SetPen_triggered()
{
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Настройка пера"));

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QFormLayout *formLayout = new QFormLayout();

    // Выбор стиля пера
    QComboBox *styleComboBox = new QComboBox();
    styleComboBox->addItem("Solid", QVariant::fromValue(Qt::SolidLine));
    styleComboBox->addItem("Dash", QVariant::fromValue(Qt::DashLine));
    styleComboBox->addItem("Dot", QVariant::fromValue(Qt::DotLine));
    styleComboBox->addItem("Dash Dot", QVariant::fromValue(Qt::DashDotLine));
    styleComboBox->addItem("Dash Dot Dot", QVariant::fromValue(Qt::DashDotDotLine));
    formLayout->addRow(tr("Стиль:"), styleComboBox);

    // Выбор ширины пера
    QSpinBox *widthSpinBox = new QSpinBox();
    widthSpinBox->setRange(1, 20);
    widthSpinBox->setValue(1); // начальное значение
    formLayout->addRow(tr("Ширина:"), widthSpinBox);

    // Выбор цвета
    QPushButton *colorButton = new QPushButton(tr("Выбрать цвет"));
    QColor penColor = Qt::black; // Начальный цвет
    connect(colorButton, &QPushButton::clicked, [&]() {
        QColor color = QColorDialog::getColor(penColor, this, tr("Выберите цвет пера"));
        if (color.isValid()) {
            penColor = color;
            colorButton->setStyleSheet(QString("background-color: %1").arg(color.name())); // Изменение цвета кнопки
        }
    });
    formLayout->addRow(tr("Цвет:"), colorButton);

    // Выбор стиля конца
    QComboBox *capStyleComboBox = new QComboBox();
    capStyleComboBox->addItem("Flat", QVariant::fromValue(Qt::FlatCap));
    capStyleComboBox->addItem("Round", QVariant::fromValue(Qt::RoundCap));
    capStyleComboBox->addItem("Square", QVariant::fromValue(Qt::SquareCap));
    formLayout->addRow(tr("Стиль конца:"), capStyleComboBox);

    // Выбор стиля соединения
    QComboBox *joinStyleComboBox = new QComboBox();
    joinStyleComboBox->addItem("Miter", QVariant::fromValue(Qt::MiterJoin));
    joinStyleComboBox->addItem("Bevel", QVariant::fromValue(Qt::BevelJoin));
    joinStyleComboBox->addItem("Round", QVariant::fromValue(Qt::RoundJoin));
    formLayout->addRow(tr("Стиль соединения:"), joinStyleComboBox);

    layout->addLayout(formLayout);

    // Кнопка ОК
    QPushButton *okButton = new QPushButton(tr("ОК"));
    layout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, [&]() {
            // Создаем QPen с выбранными параметрами
            currentPen.setStyle(static_cast<Qt::PenStyle>(styleComboBox->currentData().value<int>()));
            currentPen.setWidth(widthSpinBox->value());
            currentPen.setBrush(penColor);
            currentPen.setCapStyle(static_cast<Qt::PenCapStyle>(capStyleComboBox->currentData().value<int>()));
            currentPen.setJoinStyle(static_cast<Qt::PenJoinStyle>(joinStyleComboBox->currentData().value<int>()));

            dialog.accept(); // Закрыть диалог
        });

    dialog.exec(); // Показать диалог
}
