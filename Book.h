#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QStringList>
#include <QDate>
#include <QWidget>
#include <QTextStream>

class Book {
public:
    Book();
    Book(QString t, QStringList a, QString i, QDate p);
    ~Book();
    void setTitle(QString t);
    void setAuthors(QStringList a);
    void setIsbn(QString i);
    void setPublicationDate(QDate p);
    void setContent(QString c);
    QString getTitle() const;
    QStringList getAuthors() const;
    QString getIsbn() const;
    QDate getPublicationDate() const;
    QString getContent() const;
    void obtainBookInfo();
    void saveBook(Book b);
private:
    QString title;
    QStringList authors;
    QString isbn;
    QDate publicationhDate;
    QString content;
};

#endif // BOOK_H
