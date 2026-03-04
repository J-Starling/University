#include "emailvalidator.h"

EmailValidator::EmailValidator(QWidget* parent): QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    menuBar = new QMenuBar(this);
    menu = new QMenu("Menu", this);

    loadAction = new QAction("Load from file", this);
    saveAction = new QAction("Save result to file", this);
    fontAction = new QAction("Font", this);

    menu->addAction(loadAction);
    menu->addAction(saveAction);
    menu->addAction(fontAction);

    menu->setTearOffEnabled(true);

    menuBar->addMenu(menu);
    mainLayout->setMenuBar(menuBar);

    QVBoxLayout* layout = new QVBoxLayout;
    mainLayout->addLayout(layout);

    title = new QLabel("Change all emails in the text to \"[contacts not allowed]\"");
    layout->addWidget(title);

    QSplitter *splitter = new QSplitter(Qt::Horizontal);

    QWidget *left = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout(left);
    QLabel *leftLabel = new QLabel("Text:");
    leftText = new QTextEdit;
    leftLayout->addWidget(leftLabel);
    leftLayout->addWidget(leftText);

    QWidget *right = new QWidget;
    QVBoxLayout *rightLayout = new QVBoxLayout(right);
    QLabel *rightLabel = new QLabel("Result:");
    rightText = new QTextEdit;
    rightText->setReadOnly(true);
    rightLayout->addWidget(rightLabel);
    rightLayout->addWidget(rightText);

    splitter->addWidget(left);
    splitter->addWidget(right);
    splitter->setSizes(QList<int>() << 400 << 400);

    layout->addWidget(splitter);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    execute = new QPushButton("Execute");
    clear = new QPushButton("Clear");
    buttonLayout->addWidget(execute);
    buttonLayout->addWidget(clear);
    layout->addLayout(buttonLayout);

    setWindowTitle("Email Validator");
    resize(900, 600);

    connect(execute, SIGNAL(clicked()), this, SLOT(processText()));
    connect(clear, SIGNAL(clicked()), this, SLOT(clearText()));
    connect(leftText, SIGNAL(textChanged()), rightText, SLOT(clear()));
    connect(loadAction, SIGNAL(triggered()), this, SLOT(loadFromFile()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveToFile()));
    connect(fontAction, SIGNAL(triggered()), this, SLOT(showFontDialog()));
}

EmailValidator::~EmailValidator() {}

void EmailValidator::processText()
{
    QString inputText = leftText->toPlainText();

    if (inputText.isEmpty()) {
        rightText->setPlainText("The string is empty");
        return;
    }

    QString result = replaceEmails(inputText);
    rightText->setPlainText(result);
}

void EmailValidator::clearText()
{
    leftText->clear();
    rightText->clear();
}

void EmailValidator::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open file", "", "Text files (*.txt);;All files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            leftText->setPlainText(in.readAll());
            file.close();
        } else {
            QMessageBox::warning(this, "Error", "Cannot open file for reading");
        }
    }
}

void EmailValidator::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save result", "", "Text files (*.txt);;All files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << rightText->toPlainText();
            file.close();
            QMessageBox::information(this, "Success", "File saved successfully");
        } else {
            QMessageBox::warning(this, "Error", "Cannot open file for writing");
        }
    }
}

void EmailValidator::showFontDialog()
{
    bool o;
    QFont font = QFontDialog::getFont(&o, leftText->font(), this);
    if (o) {
        leftText->setFont(font);
        rightText->setFont(font);
    }
}

bool EmailValidator::isValidEmail(const QString &email)
{
    // Базовые проверки
    if (email.isEmpty()) return false;

    // 1. Только один @
    if (email.count('@') != 1) return false;

    int atPos = email.indexOf('@');
    QString localPart = email.left(atPos);
    QString domain = email.mid(atPos + 1);

    // 2. Длина локальной части <=64
    if (localPart.isEmpty() || localPart.length() > 64) return false;

    // 3. Доменная часть не пустая и содержит точку
    if (domain.isEmpty() || domain.indexOf('.') == -1) return false;

    // 4. Доменная часть без нижних подчеркиваний и двойных точек
    if (domain.contains('_') || domain.contains("..")) return false;

    // 5. Проверка локальной части на специальные символы
    bool inQuotes = false;
    bool escapeNext = false;

    for (int i = 0; i < localPart.length(); ++i) {
        QChar c = localPart[i];

        if (escapeNext) {
            escapeNext = false;
            continue;
        }

        if (c == '\\') {
            if (!inQuotes) return false;
            escapeNext = true;
            continue;
        }

        if (c == '"') {
            inQuotes = !inQuotes;
            continue;
        }

        if (!inQuotes) {
            // Запрещенные символы вне кавычек
            if (c == '(' || c == ')' || c == ',' || c == ':' || c == ';' ||
                c == '<' || c == '>' || c == '[' || c == ']' || c == ' ') {
                return false;
            }
        }
    }

    // 6. Непарные кавычки
    if (inQuotes) return false;

    // 7. Проверка структуры кавычек
    if (localPart.contains('"')) {
        // Кавычки должны быть парными и в правильных позициях
        int quoteCount = localPart.count('"');
        if (quoteCount % 2 != 0) return false;

        bool inQuoteBlock = false;
        for (int i = 0; i < localPart.length(); ++i) {
            QChar c = localPart[i];

            if (c == '"') {
                if (!inQuoteBlock) {
                    // Открывающая кавычка должна быть в начале или после точки
                    if (i > 0 && localPart[i-1] != '.') return false;
                } else {
                    // Закрывающая кавычка должна быть в конце или перед точкой
                    if (i < localPart.length() - 1 && localPart[i+1] != '.' && localPart[i+1] != '@') return false;
                }
                inQuoteBlock = !inQuoteBlock;
            }
        }
    }

    return true;
}

QString EmailValidator::replaceEmails(const QString &text)
{
    QString result = text;

    QRegularExpression atSymbolRegex(R"(\b\S+@\S+\b)");
    QRegularExpressionMatchIterator it = atSymbolRegex.globalMatch(text);

    QVector<QPair<int, int>> replacements;

    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        QString potentialEmail = match.captured(0);

        QString cleanEmail = potentialEmail;
        while (cleanEmail.length() > 0 &&
               (cleanEmail.endsWith('.') || cleanEmail.endsWith(',') ||
                cleanEmail.endsWith(';') || cleanEmail.endsWith(':') ||
                cleanEmail.endsWith(')') || cleanEmail.endsWith('!') ||
                cleanEmail.endsWith('?') || cleanEmail.endsWith(']'))) {
            cleanEmail.chop(1);
        }

        if (isValidEmail(cleanEmail)) {
            replacements.append(qMakePair(match.capturedStart(), cleanEmail.length()));
        }
    }

    for (int i = replacements.size() - 1; i >= 0; --i) {
        int start = replacements[i].first;
        int length = replacements[i].second;
        result.replace(start, length, "[contacts not allowed]");
    }

    return result;
}
