#ifndef BOOKINPUT_H
#define BOOKINPUT_H

#include "Book.h"
#include "bookwriter.h"
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
    BookWriter *writer = new BookWriter;
};

#endif // BOOKINPUT_H
