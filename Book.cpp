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

void Book::obtainBookInfo() {
    /*
    Dismissible pop up
    Back, Next (and save on last)
    title, author, isbn, publiicationDate
    */

    QLineEdit titleInfo;
    titleInfo.clear();
    formLayout->addRow("Title:", &titleInfo);
    QLineEdit authorInfo;
    authorInfo.clear();
    formLayout->addRow("Author:", &authorInfo);
    QLineEdit isbnInfo;
    isbnInfo.clear();
    formLayout->addRow("ISBN:", &isbnInfo);
    QDateEdit dateInfo;
    dateInfo.clear();
    formLayout->addRow("Publication date:", &dateInfo);

    QPushButton cancelBtn;
    cancelBtn.setText("cancel");
    buttonLayout->addWidget(&cancelBtn);
    QPushButton saveBtn;
    saveBtn.setText("save");
    buttonLayout->addWidget(&saveBtn);

    formLayout->addRow(buttonLayout);
}

void Book::saveBook(Book b) {

}
