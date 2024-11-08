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

    drawKapustin();
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

        // Получаем список всех объектов на сцене
        QList<QGraphicsItem *> items = scene->items();

        // Удаляем все объекты, кроме стен
        foreach (QGraphicsItem *item, items) {
            // Проверяем, что это не стена
            if (item != topWall && item != bottomWall && item != leftWall && item != rightWall) {
                scene->removeItem(item);  // Убираем из сцены
                delete item;              // Удаляем объект
            }
        }

        // Опционально можно перерисовать стены, чтобы они точно остались на месте
        setupWalls();


    scene->setBackgroundBrush(Qt::white);  // Reset background color if necessary
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

    // Ввод размера (ширина и высота)
    QSpinBox *widthSpinBox = new QSpinBox();
    widthSpinBox->setRange(1, 1000);
    widthSpinBox->setValue(100);
    formLayout->addRow(tr("Ширина:"), widthSpinBox);

    QSpinBox *heightSpinBox = new QSpinBox();
    heightSpinBox->setRange(1, 1000);
    heightSpinBox->setValue(100);
    formLayout->addRow(tr("Высота:"), heightSpinBox);

    // Функция, которая будет изменять поля в зависимости от выбранной фигуры
    auto updateShapeInputs = [&]() {
        QString shapeType = shapeComboBox->currentData().toString();

        if (shapeType == "Square") {
            heightSpinBox->setValue(widthSpinBox->value());  // Устанавливаем высоту равной ширине
            heightSpinBox->setEnabled(false);  // Выключаем поле высоты
        } else if (shapeType == "Circle") {
            heightSpinBox->setValue(widthSpinBox->value());  // Устанавливаем высоту равной ширине для радиуса
            heightSpinBox->setEnabled(false);  // Выключаем поле высоты
        } else {
            heightSpinBox->setEnabled(true);  // Включаем поле высоты для других фигур
        }
    };

    // Обновление полей при изменении типа фигуры
    connect(shapeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), updateShapeInputs);


    // Изначально вызываем функцию для корректного отображения полей
    updateShapeInputs();

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

    QComboBox *brushComboBox = new QComboBox();
    brushComboBox->addItem("Кисть не задана", "NoBrush");
    brushComboBox->addItem("Однородный цвет", "SolidPattern");
    brushComboBox->addItem("Чрезвычайно плотная кисть", "Dense1Pattern");
    brushComboBox->addItem("Очень плотная кисть", "Dense2Pattern");
    brushComboBox->addItem("Довольно плотная кисть", "Dense3Pattern");
    brushComboBox->addItem("Наполовину плотная кисть", "Dense4Pattern");
    brushComboBox->addItem("Довольно редкая кисть", "Dense5Pattern");
    brushComboBox->addItem("Очень редкая кисть", "Dense6Pattern");
    brushComboBox->addItem("Чрезвычайно редкая кисть", "Dense7Pattern");
    brushComboBox->addItem("Горизонтальные линии", "HorPattern");
    brushComboBox->addItem("Вертикальные линии", "VerPattern");
    brushComboBox->addItem("Пересекающиеся вертикальные и горизонтальные линии", "CrossPattern");
    brushComboBox->addItem("Обратные диагональные линии", "BDiagPattern");
    brushComboBox->addItem("Прямые диагональные линии", "FDiagPattern");
    brushComboBox->addItem("Пересекающиеся диагональные линии", "DiagCrossPattern");
    formLayout->addRow(tr("Тип заливки:"), brushComboBox);

    layout->addLayout(formLayout);

    // Кнопка ОК
    QPushButton *okButton = new QPushButton(tr("ОК"));
    layout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, [&]() {
        // Получаем значения из формы
        QString shapeType = shapeComboBox->currentData().toString();
        int width = widthSpinBox->value();
        int height = (shapeType == "Square" || shapeType == "Circle") ? width : heightSpinBox->value();
        int x = (view->viewport()->width() - width) / 2;  // Центрируем фигуру
        int y = (view->viewport()->height() - height) / 2;

        QString brushStyleStr = brushComboBox->currentData().toString();
        Qt::BrushStyle brushStyle = stringToBrushStyle(brushStyleStr);

        // Добавляем фигуру
        addShape(shapeType, QRectF(x, y, width, height), fillColor, brushStyle, strokeColor, strokeWidthSpinBox->value());

        dialog.accept(); // Закрыть диалог
    });

    dialog.exec(); // Показать диалог
}


void GraphicsEditor::addShape(QString shapeType, QRectF rect, QColor fillColor, Qt::BrushStyle brushStyle, QColor strokeColor, int strokeWidth)
{
    QGraphicsItem *shape = nullptr;
    QPen pen(strokeColor, strokeWidth);
    QBrush brush(fillColor, brushStyle);

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

        shape->setFlag(QGraphicsItem::ItemIsMovable, true); // Фигуры можно перемещать
        shape->setFlag(QGraphicsItem::ItemIsSelectable, true); // Фигуры можно выделять
        shape->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

}

void GraphicsEditor::on_DeleteFigure_triggered()
{
    // Получаем список всех выбранных объектов на сцене
    QList<QGraphicsItem *> selectedItems = scene->selectedItems();

    // Проверка, есть ли вообще выбранные элементы
    if (selectedItems.isEmpty()) {
        qDebug() << "No items selected for deletion.";
        return;
    }

    // Выводим количество выбранных объектов
    qDebug() << "Selected items count:" << selectedItems.count();

    foreach (QGraphicsItem *item, selectedItems) {
        qDebug() << "Item type:" << item->type();

        if (QGraphicsItemGroup *group = qgraphicsitem_cast<QGraphicsItemGroup *>(item)) {
            // Если это группа, выводим информацию и удаляем её элементы
            qDebug() << "Removing group with child items.";

            QList<QGraphicsItem *> children = group->childItems();
            for (QGraphicsItem *child : children) {
                qDebug() << "Removing child item:" << child;
                scene->removeItem(child);  // Убираем элемент из сцены
                delete child;              // Удаляем элемент
            }

            scene->removeItem(group);  // Убираем саму группу из сцены
            delete group;              // Удаляем саму группу
        } else {
            // Если это не группа, удаляем только объект
            qDebug() << "Removing single item:" << item;
            scene->removeItem(item);  // Убираем объект из сцены
            delete item;              // Удаляем объект
        }
    }

    // Обновляем сцену и выводим сообщение
    scene->update();
    qDebug() << "Scene updated after deletion.";
}





void GraphicsEditor::drawKapustin() {
    //  K
    QGraphicsItemGroup *group_K = new QGraphicsItemGroup();
    QGraphicsItem *K_1 = scene->addRect(QRectF(15,15,10,50), QPen(Qt::green, 2), QBrush(Qt::black, Qt::SolidPattern));
    group_K->addToGroup(K_1);
    QGraphicsItem *K_2 = scene->addRect(QRectF(15,15,30,10), QPen(Qt::green, 2), QBrush(Qt::black, Qt::SolidPattern));
    K_2->setTransformOriginPoint(15, 15);
    K_2->setRotation(-45);
    K_2->setPos(5, 20);
    group_K->addToGroup(K_2);
    QGraphicsItem *K_3 = scene->addRect(QRectF(15,15,30,10), QPen(Qt::green, 2), QBrush(Qt::black, Qt::SolidPattern));
    K_3->setTransformOriginPoint(15, 15);
    K_3->setRotation(45);
    K_3->setPos(15, 20);
    group_K->addToGroup(K_3);
    groupSetFlags(group_K);
    scene->addItem(group_K);

    //  A
    QGraphicsItemGroup *group_A = new QGraphicsItemGroup();
    QGraphicsItem *A_1 = scene->addLine(QLineF(70, 60, 85, 15), QPen(Qt::red, 6));
    group_A->addToGroup(A_1);
    QGraphicsItem *A_2 = scene->addLine(QLineF(85, 15, 100, 60), QPen(Qt::red, 6));
    group_A->addToGroup(A_2);
    QGraphicsItem *A_3 = scene->addLine(QLineF(75, 50, 95, 50), QPen(Qt::red, 6));
    group_A->addToGroup(A_3);
    groupSetFlags(group_A);

    scene->addItem(group_A);

    //  П
    QGraphicsItemGroup *group_P = new QGraphicsItemGroup();
    QGraphicsItem *P_1 = scene->addLine(QLineF(110, 60, 110, 15), QPen(Qt::blue, 6));
    group_P->addToGroup(P_1);
    QGraphicsItem *P_2 = scene->addRect(QRectF(110,15,30,10), QPen(Qt::blue, 2), QBrush(Qt::yellow, Qt::SolidPattern));
    group_P->addToGroup(P_2);
    QGraphicsItem *P_3 = scene->addLine(QLineF(140, 15, 140, 60), QPen(Qt::blue, 6));
    group_P->addToGroup(P_3);
    groupSetFlags(group_P);

    scene->addItem(group_P);

    //  У
    QGraphicsItemGroup *group_U = new QGraphicsItemGroup();
    QGraphicsItem *U_1 = scene->addLine(QLineF(150, 15, 160, 30), QPen(Qt::red, 6));
    group_U->addToGroup(U_1);
    QGraphicsItem *U_2 = scene->addLine(QLineF(150, 60, 170, 15), QPen(Qt::red, 6));
    group_U->addToGroup(U_2);
    groupSetFlags(group_U);

    scene->addItem(group_U);

    //  С
    QGraphicsItemGroup *group_C = new QGraphicsItemGroup();
    QGraphicsLineItem *C_1 = scene->addLine(QLineF(180, 15, 210, 15), QPen(Qt::yellow, 6));
    group_C->addToGroup(C_1);
    QGraphicsLineItem *C_2 = scene->addLine(QLineF(180, 15, 180, 60), QPen(Qt::yellow, 6));
    group_C->addToGroup(C_2);
    QGraphicsLineItem *C_3 = scene->addLine(QLineF(180, 60, 210, 60), QPen(Qt::yellow, 6));
    group_C->addToGroup(C_3);;
    groupSetFlags(group_C);

    scene->addItem(group_C);

    //  остальные буквы при помощи шрифта
    QFont font("Arial", 50, QFont::Bold);
    QGraphicsTextItem *textT1 = new QGraphicsTextItem("Т");
    textT1->setFont(font);
    textT1->setDefaultTextColor(Qt::green);
    textT1->setPos(220, 15);
    textSetFlags(textT1);
    scene->addItem(textT1);

    QGraphicsTextItem *textI1 = new QGraphicsTextItem("И");
    textI1->setFont(font);
    textI1->setDefaultTextColor(Qt::green);
    textI1->setPos(270, 15);
    textSetFlags(textI1);
    scene->addItem(textI1);

    QGraphicsTextItem *textN = new QGraphicsTextItem("Н");
    textN->setFont(font);
    textN->setDefaultTextColor(Qt::green);
    textN->setPos(320, 15);
    textSetFlags(textN);
    scene->addItem(textN);

    QGraphicsTextItem *textT2 = new QGraphicsTextItem("Т");
    textT2->setFont(font);
    textT2->setDefaultTextColor(Qt::green);
    textT2->setPos(370, 15);
    textSetFlags(textT2);
    scene->addItem(textT2);

    QGraphicsTextItem *textI2 = new QGraphicsTextItem("И");
    textI2->setFont(font);
    textI2->setDefaultTextColor(Qt::green);
    textI2->setPos(420, 15);
    textSetFlags(textI2);
    scene->addItem(textI2);

    QGraphicsTextItem *textM = new QGraphicsTextItem("М");
    textM->setFont(font);
    textM->setDefaultTextColor(Qt::green);
    textM->setPos(470, 15);
    textSetFlags(textM);
    scene->addItem(textM);

    QGraphicsTextItem *textO = new QGraphicsTextItem("О");
    textO->setFont(font);
    textO->setDefaultTextColor(Qt::green);
    textO->setPos(520, 15);
    textSetFlags(textO);
    scene->addItem(textO);

    QGraphicsTextItem *textF = new QGraphicsTextItem("Ф");
    textF->setFont(font);
    textF->setDefaultTextColor(Qt::green);
    textF->setPos(570, 15);
    textSetFlags(textF);
    scene->addItem(textF);

    QGraphicsTextItem *textE = new QGraphicsTextItem("Е");
    textE->setFont(font);
    textE->setDefaultTextColor(Qt::green);
    textE->setPos(620, 15);
    textSetFlags(textE);
    scene->addItem(textE);

    QGraphicsTextItem *textY = new QGraphicsTextItem("Й");
    textY->setFont(font);
    textY->setDefaultTextColor(Qt::green);
    textY->setPos(670, 15);
    textSetFlags(textY);
    scene->addItem(textY);



}

void GraphicsEditor::groupSetFlags(QGraphicsItemGroup *group){
    group->setFlag(QGraphicsItem::ItemIsMovable, true);
    group->setFlag(QGraphicsItem::ItemIsSelectable, true);
    group->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void GraphicsEditor::textSetFlags(QGraphicsTextItem *item){
        item->setFlag(QGraphicsItem::ItemIsMovable, true);
        item->setFlag(QGraphicsItem::ItemIsSelectable, true);
        item->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

Qt::BrushStyle GraphicsEditor::stringToBrushStyle(const QString &styleStr) {
    if (styleStr == "SolidPattern") {
        return Qt::SolidPattern;
    } else if (styleStr == "Dense1Pattern") {
        return Qt::Dense1Pattern;
    } else if (styleStr == "Dense2Pattern") {
        return Qt::Dense2Pattern;
    } else if (styleStr == "Dense3Pattern") {
        return Qt::Dense3Pattern;
    } else if (styleStr == "Dense4Pattern") {
        return Qt::Dense4Pattern;
    } else if (styleStr == "Dense5Pattern") {
        return Qt::Dense5Pattern;
    } else if (styleStr == "Dense6Pattern") {
        return Qt::Dense6Pattern;
    } else if (styleStr == "Dense7Pattern") {
        return Qt::Dense7Pattern;
    } else if (styleStr == "HorPattern") {
        return Qt::HorPattern;
    } else if (styleStr == "VerPattern") {
        return Qt::VerPattern;
    } else if (styleStr == "CrossPattern") {
        return Qt::CrossPattern;
    } else if (styleStr == "BDiagPattern") {
        return Qt::BDiagPattern;
    } else if (styleStr == "FDiagPattern") {
        return Qt::FDiagPattern;
    } else if (styleStr == "DiagCrossPattern") {
        return Qt::DiagCrossPattern;
    } else {
        return Qt::NoBrush;  // Default if no match
    }
}
