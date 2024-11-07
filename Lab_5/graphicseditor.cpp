#include "graphicseditor.h"
#include "ui_graphicseditor.h"

GraphicsEditor::GraphicsEditor(QWidget *parent) : QMainWindow(parent),
                                                  ui(new Ui::GraphicsEditor),
                                                  currentColor(Qt::white),
                                                  currentPen(Qt::black),
                                                  topWall(nullptr), bottomWall(nullptr), leftWall(nullptr), rightWall(nullptr)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    view = new GraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setRenderHint(QPainter::SmoothPixmapTransform);
    view->setAlignment(Qt::AlignTop | Qt::AlignLeft);                         // Выравнивание области просмотра
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);                // Включаем горизонтальную полосу прокрутки
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);                  // Включаем вертикальную полосу прокрутки
    setCentralWidget(view);                                                   // Устанавливаем наш view как центральный виджет

    connect(view, &GraphicsView::viewportChanged, this, &GraphicsEditor::updateWallPositions);
    connect(view, &GraphicsView::resized, this, &GraphicsEditor::setupWalls); // Подключение сигнала resized к setupWalls
    setupWalls();
}

GraphicsEditor::~GraphicsEditor()
{
    delete ui;
}

void GraphicsEditor::closeEvent(QCloseEvent *event)
{
    emit editorClosed();
    QMainWindow::closeEvent(event);
}

void GraphicsEditor::on_BackColor_triggered()
{
    QColor color = QColorDialog::getColor(currentColor, this, "Choose Background Color");

    if (color.isValid())
    {
        scene->setBackgroundBrush(color);
        currentColor = color;
    }
}

void GraphicsEditor::on_SetPen_triggered()
{
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Настройка пера"));

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QFormLayout *formLayout = new QFormLayout();

    // Выбор стиля пера
    QComboBox *styleComboBox = new QComboBox();
    styleComboBox->setIconSize(QSize(64, 64)); // Например, 32x32 пикселя
    styleComboBox->addItem(QIcon(":/res/images/penIcons/Solid"), "Solid", QVariant::fromValue(Qt::SolidLine));
    styleComboBox->addItem(QIcon(":/res/images/penIcons/Dash"), "Dash", QVariant::fromValue(Qt::DashLine));
    styleComboBox->addItem(QIcon(":/res/images/penIcons/DotLine"), "Dot", QVariant::fromValue(Qt::DotLine));
    styleComboBox->addItem(QIcon(":/res/images/penIcons/DashDotLine"), "Dash Dot", QVariant::fromValue(Qt::DashDotLine));
    styleComboBox->addItem(QIcon(":/res/images/penIcons/DashDotDotLine"), "Dash Dot Dot", QVariant::fromValue(Qt::DashDotDotLine));
    styleComboBox->setCurrentIndex(styleComboBox->findData(static_cast<int>(currentPen.style())));
    formLayout->addRow(tr("Стиль:"), styleComboBox);

    // Выбор ширины пера
    QSpinBox *widthSpinBox = new QSpinBox();
    widthSpinBox->setRange(1, 20);
    widthSpinBox->setValue(currentPen.width()); // начальное значение
    formLayout->addRow(tr("Ширина:"), widthSpinBox);

    // Выбор цвета
    QPushButton *colorButton = new QPushButton(tr("Выбрать цвет"));
    QColor penColor = currentPen.color(); // Начальный цвет
    colorButton->setStyleSheet(QString("background-color: %1").arg(penColor.name()));
    connect(colorButton, &QPushButton::clicked, [&]()
            {
        QColor color = QColorDialog::getColor(penColor, this, tr("Выберите цвет пера"));
        if (color.isValid()) {
            penColor = color;
            colorButton->setStyleSheet(QString("background-color: %1").arg(color.name())); // Изменение цвета кнопки
        } });
    formLayout->addRow(tr("Цвет:"), colorButton);

    // Выбор стиля конца
    QComboBox *capStyleComboBox = new QComboBox();
    capStyleComboBox->setIconSize(QSize(64, 64));
    capStyleComboBox->addItem(QIcon(":/res/images/penIcons/FlatCap"), "Flat", QVariant::fromValue(Qt::FlatCap));
    capStyleComboBox->addItem(QIcon(":/res/images/penIcons/RoundCap"), "Round", QVariant::fromValue(Qt::RoundCap));
    capStyleComboBox->addItem(QIcon(":/res/images/penIcons/SquareCap"), "Square", QVariant::fromValue(Qt::SquareCap));
    capStyleComboBox->setCurrentIndex(capStyleComboBox->findData(static_cast<int>(currentPen.capStyle())));
    formLayout->addRow(tr("Стиль конца:"), capStyleComboBox);

    // Выбор стиля соединения
    QComboBox *joinStyleComboBox = new QComboBox();
    joinStyleComboBox->setIconSize(QSize(64, 64));
    joinStyleComboBox->addItem(QIcon(":/res/images/penIcons/MilterJoin"), "Miter", QVariant::fromValue(Qt::MiterJoin));
    joinStyleComboBox->addItem(QIcon(":/res/images/penIcons/BevelJoin"), "Bevel", QVariant::fromValue(Qt::BevelJoin));
    joinStyleComboBox->addItem(QIcon(":/res/images/penIcons/RoundJoin"), "Round", QVariant::fromValue(Qt::RoundJoin));
    joinStyleComboBox->setCurrentIndex(joinStyleComboBox->findData(static_cast<int>(currentPen.joinStyle())));
    formLayout->addRow(tr("Стиль соединения:"), joinStyleComboBox);

    layout->addLayout(formLayout);

    // Кнопка ОК
    QPushButton *okButton = new QPushButton(tr("ОК"));
    layout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, [&]()
            {
                // Установка пера с выбранными параметрами
                currentPen.setStyle(static_cast<Qt::PenStyle>(styleComboBox->currentData().value<int>()));
                currentPen.setWidth(widthSpinBox->value());
                currentPen.setColor(penColor);
                currentPen.setCapStyle(static_cast<Qt::PenCapStyle>(capStyleComboBox->currentData().value<int>()));
                currentPen.setJoinStyle(static_cast<Qt::PenJoinStyle>(joinStyleComboBox->currentData().value<int>()));

                view->setPen(currentPen); // Передаем перо в GraphicsView
                dialog.accept();          // Закрыть диалог
            });

    dialog.exec(); // Показать диалог
}

void GraphicsEditor::on_Clear_triggered()
{
    scene->clear();
    scene->setBackgroundBrush(Qt::white);
}

void GraphicsEditor::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    setupWalls(); // Перестраиваем стены при каждом изменении размера окна
}

void GraphicsEditor::setupWalls()
{
    int viewWidth = view->viewport()->width();
    int viewHeight = view->viewport()->height();
    int wallThickness = 10;

    QPixmap wallImage(":/res/images/wall.jpg");

    QPixmap scaledTopBottom = wallImage.scaled(viewWidth, wallThickness);
        QPixmap scaledLeftRight = wallImage.scaled(wallThickness, viewHeight);

    // Если стены ещё не были созданы, создаём их, иначе просто изменяем размеры
    if (!topWall)
    {
        topWall = scene->addPixmap(scaledTopBottom);
                bottomWall = scene->addPixmap(scaledTopBottom);
                leftWall = scene->addPixmap(scaledLeftRight);
                rightWall = scene->addPixmap(scaledLeftRight);

        topWall->setFlag(QGraphicsItem::ItemIsMovable, false);
        bottomWall->setFlag(QGraphicsItem::ItemIsMovable, false);
        leftWall->setFlag(QGraphicsItem::ItemIsMovable, false);
        rightWall->setFlag(QGraphicsItem::ItemIsMovable, false);
    }
    else
    {
        topWall->setPixmap(scaledTopBottom);
                bottomWall->setPixmap(scaledTopBottom);
                leftWall->setPixmap(scaledLeftRight);
                rightWall->setPixmap(scaledLeftRight);
    }

    updateWallPositions();
}

void GraphicsEditor::updateWallPositions()
{
    int wallThickness = 10;

    int horizontalOffset = view->horizontalScrollBar()->value();
    int verticalOffset = view->verticalScrollBar()->value();

    if (topWall)
        topWall->setPos(horizontalOffset, verticalOffset);
    if (bottomWall)
        bottomWall->setPos(horizontalOffset, view->viewport()->height() - wallThickness + verticalOffset);
    if (leftWall)
        leftWall->setPos(horizontalOffset, verticalOffset);
    if (rightWall)
        rightWall->setPos(view->viewport()->width() - wallThickness + horizontalOffset, verticalOffset);
}

void GraphicsEditor::on_AddFigure_triggered()
{
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Добавить фигуру"));

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QFormLayout *formLayout = new QFormLayout();

    // Выбор типа фигуры
    QComboBox *shapeComboBox = new QComboBox();
    shapeComboBox->addItem("Квадрат", "Square");
    shapeComboBox->addItem("Прямоугольник", "Rectangle");
    shapeComboBox->addItem("Треугольник", "Triangle");
    shapeComboBox->addItem("Круг", "Circle");
    shapeComboBox->addItem("Эллипс", "Ellipse");
    formLayout->addRow(tr("Тип фигуры:"), shapeComboBox);

    // Ввод размеров (ширина и высота)
    QSpinBox *widthSpinBox = new QSpinBox();
    widthSpinBox->setRange(1, 1000);
    widthSpinBox->setValue(100);
    formLayout->addRow(tr("Ширина:"), widthSpinBox);

    QSpinBox *heightSpinBox = new QSpinBox();
    heightSpinBox->setRange(1, 1000);
    heightSpinBox->setValue(100);
    formLayout->addRow(tr("Высота:"), heightSpinBox);

    // Выбор цвета заливки
    QPushButton *fillColorButton = new QPushButton(tr("Цвет заливки"));
    QColor fillColor = Qt::yellow;
    fillColorButton->setStyleSheet(QString("background-color: %1").arg(fillColor.name()));
    connect(fillColorButton, &QPushButton::clicked, [&]() {
        QColor color = QColorDialog::getColor(fillColor, this, tr("Выберите цвет заливки"));
        if (color.isValid()) {
            fillColor = color;
            fillColorButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
        }
    });
    formLayout->addRow(tr("Цвет заливки:"), fillColorButton);

    // Выбор цвета обводки
    QPushButton *strokeColorButton = new QPushButton(tr("Цвет обводки"));
    QColor strokeColor = Qt::black;
    strokeColorButton->setStyleSheet(QString("background-color: %1").arg(strokeColor.name()));
    connect(strokeColorButton, &QPushButton::clicked, [&]() {
        QColor color = QColorDialog::getColor(strokeColor, this, tr("Выберите цвет обводки"));
        if (color.isValid()) {
            strokeColor = color;
            strokeColorButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
        }
    });
    formLayout->addRow(tr("Цвет обводки:"), strokeColorButton);

    // Выбор ширины обводки
    QSpinBox *strokeWidthSpinBox = new QSpinBox();
    strokeWidthSpinBox->setRange(1, 20);
    strokeWidthSpinBox->setValue(2);
    formLayout->addRow(tr("Ширина обводки:"), strokeWidthSpinBox);

    layout->addLayout(formLayout);

    // Кнопка ОК
    QPushButton *okButton = new QPushButton(tr("ОК"));
    layout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, [&]() {
        // Получаем значения из формы
        QString shapeType = shapeComboBox->currentData().toString();
        int width = widthSpinBox->value();
        int height = heightSpinBox->value();
        int x = (view->viewport()->width() - width) / 2;  // Центрируем фигуру
        int y = (view->viewport()->height() - height) / 2;

        // Добавляем фигуру
        addShape(shapeType, QRectF(x, y, width, height), fillColor, strokeColor, strokeWidthSpinBox->value());

        dialog.accept(); // Закрыть диалог
    });

    dialog.exec(); // Показать диалог
}

void GraphicsEditor::addShape(QString shapeType, QRectF rect, QColor fillColor, QColor strokeColor, int strokeWidth)
{
    QGraphicsItem *shape = nullptr;
    QPen pen(strokeColor, strokeWidth);
    QBrush brush(fillColor);

    if (shapeType == "Square") {
        // Квадрат (равные ширина и высота)
        shape = scene->addRect(rect, pen, brush);
    } else if (shapeType == "Rectangle") {
        // Прямоугольник
        shape = scene->addRect(rect, pen, brush);
    } else if (shapeType == "Circle") {
        // Круг
        shape = scene->addEllipse(rect, pen, brush);
    } else if (shapeType == "Ellipse") {
        // Эллипс
        shape = scene->addEllipse(rect, pen, brush);
    } else if (shapeType == "Triangle") {
        // Треугольник
        QPolygonF triangle;
        triangle << QPointF(rect.left() + rect.width() / 2, rect.top())
                 << QPointF(rect.bottomLeft())
                 << QPointF(rect.bottomRight());
        shape = scene->addPolygon(triangle, pen, brush);
    }

    if (shape) {
        shape->setFlag(QGraphicsItem::ItemIsMovable, true); // Фигуры можно перемещать
        shape->setFlag(QGraphicsItem::ItemIsSelectable, true); // Фигуры можно выделять
        shape->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    }
}
