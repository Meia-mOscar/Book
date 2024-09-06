#include "BookInput.h"

BookInput::BookInput (QWidget* parent)
    : QMainWindow(parent){
    setWindowTitle("Book editor");
    file.setTitle("File");
    openAct.setText("open");
    saveAct.setText("save");
    closeAct.setText("close");
    consoleAct.setText("console");
    file.addAction(&openAct);
    file.addAction(&saveAct);
    file.addAction(&closeAct);
    file.addAction(&consoleAct);
    menuBar.addMenu(&file);
    this->setMenuBar(&menuBar);

    authorIn.setPlaceholderText("Comma separated values");
    titleLable.setText("Title");
    authorLable.setText("Author");
    isbnLable.setText("ISBN");
    dateLable.setText("Published date");

    lineEditLayout.addWidget(&titleLable);
    lineEditLayout.addWidget(&titleIn);
    lineEditLayout.addWidget(&authorLable);
    lineEditLayout.addWidget(&authorIn);
    lineEditLayout.addWidget(&isbnLable);
    lineEditLayout.addWidget(&isbnIn);
    lineEditLayout.addWidget(&dateLable);
    lineEditLayout.addWidget(&dateIn);

    editor->setDocument(&document);
    editorLayout.addWidget(editor);

    centralWidget.setLayout(&mainLayout);
    mainLayout.addLayout(&lineEditLayout);
    mainLayout.addLayout(&editorLayout);
    setCentralWidget(&centralWidget);

    connect(&openAct, &QAction::triggered, this, &BookInput::openClicked);
    connect(&saveAct, &QAction::triggered, this, &BookInput::saveClicked);
    connect(&closeAct, &QAction::triggered, this, &BookInput::closeClicked);
    connect(&consoleAct, &QAction::triggered, this, &BookInput::consoleClicked);
}

BookInput::~BookInput() {
    delete editor;
    delete tempEditor;
}

void BookInput::openClicked() {
    QString filePath;
    filePath = QFileDialog::getOpenFileName(0, "Select file", "", "All files (*)");

    if(!filePath.isEmpty()) {
        QFile file(filePath);
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            tempEditor->setPlainText(file.readAll());
            this->read(tempEditor);
        }
    } else {
        qDebug() << "File selection cancelled by user";
    }
}

void BookInput::saveClicked() {
    this->refreshBook();
    writer->write(book);
}

void BookInput::closeClicked() {

}

void BookInput::consoleClicked() {
    book->obtainBookInfo();
}

void BookInput::read(QTextEdit *e) {
    QString txt = e->toPlainText();
    //qDebug() << "read txt";
    book->read(&txt);
    //qDebug() << "refresh UI";
    this->refreshUi();
}

QString BookInput::write() {
    this->refreshBook();
    book->write();
    return book->getBinding();
}

void BookInput::refreshBook() {
    book->setTitle(titleIn.text());
    QStringList aList = authorIn.text().split(',').toList();
    book->setAuthors(aList);
    book->setIsbn(isbnIn.text());
    book->setPublicationDate(dateIn.date());
    book->setBookAttributes();
}

void BookInput::refreshUi() {
    titleIn.setText(book->getTitle());
    QString a = "";
    QStringList aList = book->getAuthors();
    for(int i=0; i<aList.length(); i++) {
        a.append(aList[i]);
        if(!(i-1 == aList.length())) {
            a.append(',');
        }
    }
    authorIn.setText(a);
    isbnIn.setText(book->getIsbn());
    dateIn.setDate(book->getPublicationDate());
    editor->setText(book->getContent());
}
