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
    QString getTitle() const;
    QStringList getAuthors() const;
    QString getIsbn() const;
    QDate getPublicationDate() const;
    QString getContent() const;
    QString getBinding();
    void setTitle(QString t);
    void setAuthors(QStringList a);
    void setIsbn(QString i);
    void setPublicationDate(QDate p);
    void setContent(QString c);

    void obtainBookInfo();
    //I suspect the evnt loop interferes with the std functioning of console in/out...
    void saveBook(Book b);

    void read(QString *txt);
    void write();
    void setBookAttributes();
    void refreshBook();
private:
    QString title;
    QStringList authors;
    QString isbn;
    QDate publicationhDate;
    QString content;

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
    int bgn;
    int end;
    QString currentText;
    int titleStartPos;
    int authorStartPos;
    int isbnStartPos;
    int dateStartPos;
    int contentStartPos;
    QList<int> startPos;
    int titleEndPos;
    int authorEndPos;
    int isbnEndPos;
    int dateEndPos;
    int contentEndPos;
    QList<int> endPos;
    QStringList bookAttributes;
    QString binding;
};

#endif // BOOK_H
