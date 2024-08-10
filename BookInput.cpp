#include "BookInput.h"

BookInput::BookInput (QWidget* parent)
    : QMainWindow(parent){
    setWindowTitle("Book editor");
    file.setTitle("File");
    openAct.setText("open");
    saveAct.setText("save");
    closeAct.setText("close");
    file.addAction(&openAct);
    file.addAction(&saveAct);
    file.addAction(&closeAct);
    menuBar.addMenu(&file);
    this->setMenuBar(&menuBar);

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
    mainLayout.addLayout(&editorLayout);
    setCentralWidget(&centralWidget);

    connect(&openAct, &QAction::triggered, this, &BookInput::openClicked);
    connect(&saveAct, &QAction::triggered, this, &BookInput::saveClicked);
    connect(&closeAct, &QAction::triggered, this, &BookInput::closeClicked);
}

BookInput::~BookInput() {
    delete editor;
}

void BookInput::openClicked() {
    QString filePath;
    filePath = QFileDialog::getOpenFileName(0, "Select file", "", "All files (*)");

    //Xml reader to format text into editor
    if(!filePath.isEmpty()) {
        QFile file(filePath);
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            return editor->setPlainText(file.readAll());
        }
    } else {
        qDebug() << "File selection cancelled by user";
    }
}

void BookInput::saveClicked() {

}

void BookInput::closeClicked() {

}
