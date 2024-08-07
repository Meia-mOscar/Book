#ifndef BOOK_H
#define BOOK_H
#include <QString>
#include <QDate>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>

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
    void obtainBookInfo();
    void saveBook(Book b);
private:
    QString title;
    QString author;
    QString isbn;
    QDate publicationhDate;

    QWidget *centralWidget = new QWidget();
    QFormLayout *formLayout = new QFormLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
};

#endif // BOOK_H
