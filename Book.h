#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QDate>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QFormLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QDateEdit>

class Book {
public:
    Book();
    Book(QString t, QString a, QString i, QDate p);
    ~Book();
    void setTitle(QString t);
    void setAuthor(QString a);
    void setIsbn(QString i);
    void setPublicationDate(QDate p);
    QString getTitle() const;
    QString getAuthor() const;
    QString getIsbn() const;
    QDate getPublicationDate() const;
    QFormLayout *obtainBookInfo();
    void saveBook(Book b);
private:
    QString title;
    QString author;
    QString isbn;
    QDate publicationhDate;
    QFormLayout *form = new QFormLayout;
    QLineEdit titleIn;
    QLineEdit authorIn;
    QLineEdit isbnIn;
    QDateEdit dateIn;
};

#endif // BOOK_H
