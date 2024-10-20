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

void MainWindow::on_Search_triggered()
{
    // Получаем текущий виджет
    QWidget *currentWidget = ui->tabWidget->currentWidget();
    editor = qobject_cast<QTextEdit*>(currentWidget);

    if (!editor) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Текущая вкладка не поддерживает поиск. Создайте файл с текстом"));
        return;
    }
    editor->moveCursor(QTextCursor::Start);

    // Создаем диалоговое окно
    QDialog searchDialog(this);
    searchDialog.setWindowTitle("Поиск");

    // Элементы интерфейса
    QVBoxLayout *layout = new QVBoxLayout(&searchDialog);

    // Поле для текста поиска
    QLineEdit *searchLineEdit = new QLineEdit(&searchDialog);
    layout->addWidget(new QLabel("Введите текст для поиска:", &searchDialog));
    layout->addWidget(searchLineEdit);

    // Чекбоксы для учета регистра и полного слова
    QCheckBox *caseSensitiveCheckBox = new QCheckBox("Учитывать регистр", &searchDialog);
    layout->addWidget(caseSensitiveCheckBox);

    QCheckBox *wholeWordCheckBox = new QCheckBox("Искать только полные слова", &searchDialog);
    layout->addWidget(wholeWordCheckBox);

    // Добавляем кнопки "Следующее" и "Предыдущее"
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *nextButton = new QPushButton("Следующее", &searchDialog);
    QPushButton *prevButton = new QPushButton("Предыдущее", &searchDialog);
    buttonLayout->addWidget(prevButton);
    buttonLayout->addWidget(nextButton);
    layout->addLayout(buttonLayout);

    QPushButton *closeButton = new QPushButton("Закрыть", &searchDialog);
    layout->addWidget(closeButton);

    QRegularExpression cyrillicRegex("[\\p{Cyrillic}]");
    QRegularExpression latinRegex("[a-zA-Z]");

//     Лямбда-функция для поиска текста
    auto search = [&](bool forward) {
        QString searchText = searchLineEdit->text();

        if (searchText.isEmpty()) {
            QMessageBox::information(&searchDialog, "Поиск", "Введите текст для поиска.");
            return;
        }

        // Устанавливаем флаги поиска
        QTextDocument::FindFlags findFlags;
        if (caseSensitiveCheckBox->isChecked()) {
            findFlags |= QTextDocument::FindCaseSensitively;
        }

        // Если ищем назад, добавляем флаг FindBackward
        QTextCursor cursor = editor->textCursor();
        QTextDocument *document = editor->document();

        // Если ищем назад
        if (!forward) {
            findFlags |= QTextDocument::FindBackward;

            // Проверяем позицию курсора и сдвигаем его на один символ назад, чтобы избежать повторного поиска
            int currentPosition = cursor.position();
            if (currentPosition > 0) {
                cursor.movePosition(QTextCursor::PreviousCharacter);
                editor->setTextCursor(cursor);

            }
        }

        // Проверяем, установлен ли флажок "Искать только полные слова"
        if (wholeWordCheckBox->isChecked()) {
            // Используем регулярное выражение для поиска только целых слов
//            QRegularExpression regex("\\b" + QRegularExpression::escape(searchText) + "\\b");
            QRegularExpression regex;
            if(cyrillicRegex.match(searchText).hasMatch()){
                regex.setPattern("((?<![\\p{L}\\d_])" + QRegularExpression::escape(searchText) + "(?![\\p{L}\\d_]))");

//                regex.setPattern("(?<!\\w)" + QRegularExpression::escape(searchText) + "(?!\\w)");
            }
            else{
                regex.setPattern("\\b" + QRegularExpression::escape(searchText) + "\\b");
//                Метасимвол \b (граница слова) может работать корректно с латинскими символами, но при поиске по кириллице он может некорректно обрабатывать границы слов.
//                Это связано с тем, что \b ориентирован на латинские символы и цифры, и кириллические символы могут восприниматься неправиль
            }


            // Опции для учета регистра в регулярном выражении
            QRegularExpression::PatternOption caseOption = caseSensitiveCheckBox->isChecked()
                ? QRegularExpression::NoPatternOption
                : QRegularExpression::CaseInsensitiveOption;

            regex.setPatternOptions(caseOption);

            // Поиск с использованием регулярного выражения
            QTextCursor foundCursor = document->find(regex, cursor, findFlags);


            if (foundCursor.isNull()) {
                QMessageBox::information(&searchDialog, "Поиск", "Текст не найден.");
            } else {
                editor->setStyleSheet("selection-background-color: blue; selection-color: white");
                editor->setTextCursor(foundCursor);
            }

        } else {
            // Обычный поиск без проверки на полные слова
            QTextCursor cursor = editor->textCursor();

            // Для обратного поиска нужно вручную сдвигать курсор назад перед поиском
            editor->setStyleSheet("selection-background-color: blue; selection-color: white");
            if (!forward && cursor.position() > 0) {
                cursor.movePosition(QTextCursor::PreviousCharacter);
                editor->setTextCursor(cursor);
            }

            if (!editor->find(searchText, findFlags)) {
                QMessageBox::information(&searchDialog, "Поиск", "Текст не найден.");
            }
        }
    };

    // Соединяем кнопки "Следующее" и "Предыдущее" с действиями
    connect(nextButton, &QPushButton::clicked, [&]() { search(true); });
    connect(prevButton, &QPushButton::clicked, [&]() { search(false); });
    connect(closeButton, &QPushButton::clicked, &searchDialog, &QDialog::accept);

    // Показываем диалог
    searchDialog.exec();
}