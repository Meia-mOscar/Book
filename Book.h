#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QStringList>
#include <QDate>
#include <QWidget>
#include <QTextStream>

class Book : public QObject {
    Q_OBJECT
    /*Add notify, slot mechanism
     * ALso, repeat this for all public interfacing functions
     * Move what functions can be to private, i.e. those only accessed in the class itself\
     * Both setBookAttributes & write can be accessed as follows:
     *  QMetaObject::invokeMethod(&book, "write");
     *  QMetaObject::invokeMethod(&book, "setBookAttributed");
*/
    Q_PROPERTY(QString binding READ getBinding CONSTANT)
    Q_PROPERTY(QString title READ getTitle WRITE setTitle)
    Q_PROPERTY(QStringList authors READ getAuthors WRITE setAuthors)
    Q_PROPERTY(QString isbn READ getIsbn WRITE setIsbn)
    Q_PROPERTY(QDate publicationDate READ getPublicationDate WRITE setPublicationDate)
    Q_PROPERTY(QString content READ getContent WRITE setContent)
public:
    Book();
    Book(QString t, QStringList a, QString i, QDate p);
    ~Book();
    QString getTitle() const;
    QStringList getAuthors() const;
    QString getIsbn() const;
    QDate getPublicationDate() const;
    QString getContent() const;
    QString getBinding() const;
    void setTitle(QString t);
    void setAuthors(QStringList a);
    void setIsbn(QString i);
    void setPublicationDate(QDate p);
    void setContent(QString c);
    void read(QString *txt);
    void obtainBookInfo();
    void setBookAttributes();

    //Accessing using QMetaObject is not yet working.
    Q_INVOKABLE void write();

private:
    //I suspect the evnt loop interferes with the std functioning of console in/out...
    void saveBook(Book b); //Make it 'this'?
    void refreshBook();
    QString title;
    QStringList authors;
    QString isbn;
    QDate publicationDate;
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
