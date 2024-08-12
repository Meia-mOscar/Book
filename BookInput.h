#ifndef BOOKINPUT_H
#define BOOKINPUT_H

#include "Book.h"
#include <QMainWindow>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QLabel>
#include <QTextEdit>
#include <QTextDocument>
#include <QFileDialog>
#include <QFile>
#include <QTextCursor>
#include <QStringList>
#include <QList>

class BookInput : public QMainWindow {
    Q_OBJECT
public:
    BookInput(QWidget *parent = 0);
    ~BookInput();
public slots:
    void openClicked();
    void saveClicked();
    void closeClicked();
    void consoleClicked();
private:
    void read(QTextEdit *e);
    QString write();
    void refreshBook();
    void refreshUi();
    QMenuBar menuBar;
    QMenu file;
    QAction openAct;
    QAction saveAct;
    QAction closeAct;
    QAction consoleAct;
    QVBoxLayout mainLayout;
    QHBoxLayout lineEditLayout;
    QHBoxLayout editorLayout;
    QWidget centralWidget;
    QLabel titleLable;
    QLabel authorLable;
    QLabel isbnLable;
    QLabel dateLable;
    QLineEdit titleIn;
    QLineEdit authorIn;
    QLineEdit isbnIn;
    QDateEdit dateIn;
    QTextEdit *editor = new QTextEdit;
    QTextEdit *tempEditor = new QTextEdit;
    QTextDocument document;
    Book *book = new Book;

    //The following vars are used in reading from & writing to files
    QString titleStartMarker;
    QString authorStartMarker;
    QString isbnStartMarker;
    QString dateStartMarker;
    QString contentStartMarker;
    QStringList startMarkers;
    QString titleEndMarker;
    QString authorEndmarker;
    QString isbnEndMarker;
    QString dateEndMarker;
    QString contentEndMarker;
    QStringList endMarkers;

    int titleStartPos;
    int authorStartPos;
    int isbnStartPos;
    int dateStartPos;
    int contentStartPos;
    int titleEndPos;
    int authorEndPos;
    int isbnEndPos;
    int dateEndPos;
    int contentEndPos;
    QList<int> startPos;
    QList<int> endPos;

    QString titleContent;
    QString authorContent;
    QString isbnContent;
    QString dateString;
    QString content;
    QStringList bookContents;

    QString currentText;
    int bgn;
    int end;

    QString binding;
};

#endif // BOOKINPUT_H
