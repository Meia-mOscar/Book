#include "Book.h"
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>

Book::Book(){}

Book::Book(QString t, QString a, QString i, QDate p) : title(t), author(a), isbn(i), publicationhDate(p) {}

void Book::setTitle(QString t) {
    title = t;
    return;
}

void Book::setAuthor(QString a) {
    author = a;
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

QString Book::getAuthor() const {
    return author;
}

QString Book::getIsbn() const {
    return isbn;
}

QDate Book::getPublicationDate() const {
    return publicationhDate;
}

QFormLayout* Book::obtainBookInfo() {
    form->addRow("Title", &titleIn);
    form->addRow("Author", &authorIn);
    form->addRow("ISBN", &isbnIn);
    form->addRow("Publish date", &dateIn);
    return form;
}

void Book::saveBook(Book b) {

}
