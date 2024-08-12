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
    connect(&consoleAct, &QAction::triggered, this, &BookInput::consoleClicked); //I suspect the evnt loop is interfering with the normal functioning of the console in/out

    titleStartMarker = "<title>";
    authorStartMarker = "<author>";
    isbnStartMarker = "<isbn>";
    dateStartMarker = "<date>";
    contentStartMarker = "<content>";
    startMarkers << titleStartMarker << authorStartMarker << isbnStartMarker << dateStartMarker << contentStartMarker;

    titleEndMarker = "</title>";
    authorEndmarker = "</author>";
    isbnEndMarker = "</isbn>";
    dateEndMarker = "</date>";
    contentEndMarker = "</content>";
    endMarkers << titleEndMarker << authorEndmarker << isbnEndMarker << dateEndMarker << contentEndMarker;

    titleStartPos = -1;
    authorStartPos = -1;
    isbnStartPos = -1;
    dateStartPos = -1;
    contentStartPos = -1;
    startPos << titleStartPos << authorStartPos <<isbnStartPos << dateStartPos << contentStartPos;

    titleEndPos = -1;
    authorEndPos = -1;
    isbnEndPos = -1;
    dateEndPos = -1;
    contentEndPos = -1;
    endPos << titleEndPos << authorEndPos << isbnEndPos << dateEndPos << contentEndPos;

    titleContent = "";
    authorContent = "";
    isbnContent = "";
    dateString = "";
    content = "";

    currentText = "";
    bgn = -1;
    end = -1;
}

BookInput::~BookInput() {
    delete editor;
    delete tempEditor;
}

void BookInput::openClicked() {
    QString filePath;
    filePath = QFileDialog::getOpenFileName(0, "Select file", "", "All files (*)");

    //Xml reader to format text into editor
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
    QString fileName = "";
    fileName = QFileDialog::getOpenFileName(this,tr("Open file"),"",tr("(*.xml);(*.txt)"));
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open file";
    } else {
        QTextStream stream(&file);
        stream << this->write();
        file.close();
        qDebug() << "Close file";
    }
}

void BookInput::closeClicked() {

}

void BookInput::consoleClicked() {
    book->obtainBookInfo();
}

void BookInput::read(QTextEdit *e) {
    startMarkers.clear();
    endMarkers.clear();
    startPos.clear();
    endPos.clear();
    startMarkers << titleStartMarker << authorStartMarker << isbnStartMarker << dateStartMarker << contentStartMarker;
    endMarkers << titleEndMarker << authorEndmarker << isbnEndMarker << dateEndMarker << contentEndMarker;
    startPos << titleStartPos << authorStartPos <<isbnStartPos << dateStartPos << contentStartPos;
    endPos << titleEndPos << authorEndPos << isbnEndPos << dateEndPos << contentEndPos;
    bookContents.clear();
    bookContents << titleContent << authorContent <<isbnContent << dateString << content;
    currentText.clear();
    bgn = -1;
    end = -1;
    QString text = e->toPlainText();

    for(int i=0; i< text.length(); i++) {
        if(text[i] == '<') {
            qDebug() << "'<' at: " << i;
            bgn = i;
        }
        else if(text[i] == '>') {
            qDebug() << "'>' at: " << i;
            end = i;
            currentText.clear();
            for(int n = bgn; n<=end; n++) {
                currentText.append(e->toPlainText().at(n));
                qDebug() << "cur txt: " << currentText;
            }

            for(int n=0; n<bookContents.length(); n++) {
                if(currentText == startMarkers[n]) {
                    //Starting with char following <*>
                    startPos[n] = i+1;
                } else if(currentText == endMarkers[n]) {
                    //Ending with char preceeding </*>
                    endPos[n] = i-currentText.length();
                }
            }
        }
    }

    for(int i=0; i<bookContents.length(); i++) {
        currentText.clear();
        for(int n = startPos[i]; n<=endPos[i]; n++) {
            currentText.append(text[n]);
        }
        bookContents[i].append(currentText);
        qDebug() << currentText;
    }

    for(int i=0; i<startMarkers.length(); i++) {
        if(startMarkers[i] == titleStartMarker) {
            book->setTitle(bookContents[i]);
        } else if(startMarkers[i] == authorStartMarker) {
            QStringList a = bookContents[i].split(',').toList();
            book->setAuthors(a);
        } else if(startMarkers[i] == dateStartMarker) {
            book->setPublicationDate(QDate::fromString(bookContents[i],"dd,MM,yyyy"));
        } else if(startMarkers[i] == isbnStartMarker) {
            book->setIsbn(bookContents[i]);
        } else if(startMarkers[i] == contentStartMarker) {
            book->setContent(bookContents[i]);
        }
    }

    this->refreshUi();
}

QString BookInput::write() {
    binding.clear();
    this->refreshBook();
    /*QString a = "";
    QStringList aList = book->getAuthors();
    for(int i=0; i<aList.length(); i++) {
        a.append(aList[i]);
        if(!(i-1 == aList.length())) {
            a.append(',');
        }
    }*/
    for(int i=0; i<bookContents.length(); i++) {
        binding.append(startMarkers[i]);
        binding.append(bookContents[i]);
        binding.append(endMarkers[i]);
    }

    return binding;
}

void BookInput::refreshBook() {
    book->setTitle(titleIn.text());
    QStringList aList = authorIn.text().split(',').toList();
    book->setAuthors(aList);
    book->setIsbn(isbnIn.text());
    book->setPublicationDate(dateIn.date());

    //Keep debugging bro
    //I suspect it is because you are directly accessing memory that's not been given yet.
    //SeebookContents[i]...
    qDebug() << "bookContentsLength(): " << bookContents.length();
    bookContents.clear();
    for(int i=0; i<startMarkers.length(); i++) {
        qDebug() << i;
        if(startMarkers[i] == titleStartMarker) {
            bookContents.append(book->getTitle());
        } else if(startMarkers[i] == authorStartMarker) {
            QString a = "";
            for(int i=0; i<aList.length(); i++) {
                a.append(aList[i]);
                if(!(i-1 == aList.length())) {
                    a.append(',');
                }
            }
        } else if(startMarkers[i] == dateStartMarker) {
            bookContents.append(book->getPublicationDate().toString("dd,MM,yyyy"));
        } else if(startMarkers[i] == isbnStartMarker) {
            bookContents.append(book->getIsbn());
        } else if(startMarkers[i] == contentStartMarker) {
            bookContents.append(book->getContent());
        }
    }
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
