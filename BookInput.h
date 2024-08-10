#ifndef BOOKINPUT_H
#define BOOKINPUT_H

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

class BookInput : public QMainWindow {
    Q_OBJECT
public:
    BookInput(QWidget *parent = 0);
    ~BookInput();
public slots:
    void openClicked();
    void saveClicked();
    void closeClicked();
private:
    QMenuBar menuBar;
    QMenu file;
    QAction openAct;
    QAction saveAct;
    QAction closeAct;
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
    QTextDocument document;
};

#endif // BOOKINPUT_H
