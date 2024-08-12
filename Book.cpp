#include "Book.h"
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>

Book::Book(){}

Book::Book(QString t, QStringList a, QString i, QDate p) : title(t), authors(a), isbn(i), publicationhDate(p) {}

void Book::setTitle(QString t) {
    title = t;
    return;
}

void Book::setAuthors(QStringList a) {
    for(int i=0; i<a.length(); i++) {
        authors.append(a[i]);
    }
    return;
}

void Book::setIsbn(QString i) {
    isbn = i;
    return;
}

void Book::setPublicationDate(QDate p) {
    publicationhDate = p;
    return;
}

QString Book::getTitle() const {
    return title;
}

QStringList Book::getAuthors() const {
    return authors;
}

QString Book::getIsbn() const {
    return isbn;
}

QDate Book::getPublicationDate() const {
    return publicationhDate;
}

void Book::obtainBookInfo() {
    QTextStream out(stdout);
    QTextStream in(stdin);

    out << "Enter Book's Title:" << Qt::endl;
    out.flush();
    QString titleIn = in.readLine();
    out << "in: " << titleIn;
    this->setTitle(titleIn);

    out << "Enter Author(s) (comma separated):\n";
    QString authorsIn = in.readLine();
    QStringList authorsListIn = authorsIn.split(',').toList();
    this->setAuthors(authorsListIn);

    out << "Enter ISBN:\n";
    QString isbnIn = in.readLine();
    this->setIsbn(isbnIn);

    out << "Enter publication date (Date format: 'dd/MM/yyyy): ";
    QString dateIn = in.readLine();
    this->setPublicationDate(QDate::fromString(dateIn, "dd/MM/yyy"));
}

void Book::saveBook(Book b) {

}

void Book::setContent(QString c) {
    content = c;
    return;
}

QString Book::getContent() const {
    return content;
}
