#include "Book.h"
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>

Book::Book(){
    titleStartMarker = "<title>";
    authorStartMarker = "<author>";
    isbnStartMarker = "<isbn>";
    dateStartMarker = "<date>";
    contentStartMarker = "<content>";
    startMarkers << titleStartMarker << authorStartMarker << isbnStartMarker << dateStartMarker << contentStartMarker;

    titleEndMarker = "</title>";
    authorEndmarker = "</author>";
    isbnEndMarker = "</isbn>";
    dateEndMarker = "</date>";
    contentEndMarker = "</content>";
    endMarkers << titleEndMarker << authorEndmarker << isbnEndMarker << dateEndMarker << contentEndMarker;

    titleStartPos = -1;
    authorStartPos = -1;
    isbnStartPos = -1;
    dateStartPos = -1;
    contentStartPos = -1;
    startPos << titleStartPos << authorStartPos <<isbnStartPos << dateStartPos << contentStartPos;

    titleEndPos = -1;
    authorEndPos = -1;
    isbnEndPos = -1;
    dateEndPos = -1;
    contentEndPos = -1;
    endPos << titleEndPos << authorEndPos << isbnEndPos << dateEndPos << contentEndPos;

    currentText = "";
    bgn = -1;
    end = -1;

    this->setBookAttributes();
}

Book::Book(QString t, QStringList a, QString i, QDate p) : title(t), authors(a), isbn(i), publicationhDate(p) {
    titleStartMarker = "<title>";
    authorStartMarker = "<author>";
    isbnStartMarker = "<isbn>";
    dateStartMarker = "<date>";
    contentStartMarker = "<content>";
    startMarkers << titleStartMarker << authorStartMarker << isbnStartMarker << dateStartMarker << contentStartMarker;

    titleEndMarker = "</title>";
    authorEndmarker = "</author>";
    isbnEndMarker = "</isbn>";
    dateEndMarker = "</date>";
    contentEndMarker = "</content>";
    endMarkers << titleEndMarker << authorEndmarker << isbnEndMarker << dateEndMarker << contentEndMarker;

    titleStartPos = -1;
    authorStartPos = -1;
    isbnStartPos = -1;
    dateStartPos = -1;
    contentStartPos = -1;
    startPos << titleStartPos << authorStartPos <<isbnStartPos << dateStartPos << contentStartPos;

    titleEndPos = -1;
    authorEndPos = -1;
    isbnEndPos = -1;
    dateEndPos = -1;
    contentEndPos = -1;
    endPos << titleEndPos << authorEndPos << isbnEndPos << dateEndPos << contentEndPos;

    currentText = "";
    bgn = -1;
    end = -1;

    this->setBookAttributes();
}

void Book::setTitle(QString t) {
    title = t;
    return;
}

void Book::setAuthors(QStringList a) {
    authors.clear();
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

void Book::read(QString *txt){
    currentText.clear();
    this->setBookAttributes();
    qDebug() << bookAttributes.length();
    bgn = -1;
    end = -1;
    for(int i=0; i< txt->length(); i++) {
        if(txt->at(i) == '<') {
            qDebug() << "'<' at: " << i;
            bgn = i;
        }
        else if(txt->at(i) == '>') {
            qDebug() << "'>' at: " << i;
            end = i;
            currentText.clear();
            for(int n = bgn; n<=end; n++) {
                currentText.append(txt->at(n));
                qDebug() << "cur txt: " << currentText;
            }

            for(int n=0; n<bookAttributes.length(); n++) {
                if(currentText == startMarkers[n]) {
                    //Starting with char following <*>
                    startPos[n] = i+1;
                } else if(currentText == endMarkers[n]) {
                    //Ending with char preceeding </*>
                    endPos[n] = i-currentText.length();
                }
            }
        }
    }

    for(int i=0; i<bookAttributes.length(); i++) {
        qDebug() << i;
        currentText.clear();
        for(int n = startPos[i]; n<=endPos[i]; n++) {
            currentText.append(txt->at(n));
        }
        bookAttributes[i] = (currentText);
        qDebug() << currentText;
    }

    qDebug() << startMarkers.length();
    for(int i=0; i<startMarkers.length(); i++) {
        qDebug() << "count: " << i;
        qDebug() << "marker: " << startMarkers.at(i);
        qDebug() << "attribute: " << bookAttributes.at(i);
        if(startMarkers[i] == titleStartMarker) {
            this->setTitle(bookAttributes[i]);
        } else if(startMarkers[i] == authorStartMarker) {
            QStringList a = bookAttributes[i].split(',').toList();
            this->setAuthors(a);
        } else if(startMarkers[i] == dateStartMarker) {
            this->setPublicationDate(QDate::fromString(bookAttributes[i],"dd,MM,yyyy"));
        } else if(startMarkers[i] == isbnStartMarker) {
            this->setIsbn(bookAttributes[i]);
        } else if(startMarkers[i] == contentStartMarker) {
            this->setContent(bookAttributes[i]);
        }
    }
}

QString Book::getBinding() {
    return binding;
}

void Book::write() {
    //refresh book
    binding.clear();
    for(int i=0; i<bookAttributes.length(); i++) {
        binding.append(startMarkers[i]);
        binding.append(bookAttributes[i]);
        binding.append(endMarkers[i]);
    }
}

void Book::setBookAttributes() {
    bookAttributes.clear();
    qDebug() << bookAttributes.length();
    qDebug() << startMarkers.length();
    for(int i=0; i<startMarkers.length(); i++) {
        qDebug() << i;
        if(startMarkers[i] == titleStartMarker) {
            bookAttributes.append(this->getTitle());
        } else if(startMarkers[i] == authorStartMarker) {
            QString a = "";
            for(int i=0; i<authors.length(); i++) {
                a.append(authors[i]);
                if(!(i-1 == authors.length())) {
                    a.append(',');
                }
            }
            bookAttributes.append(a);
        } else if(startMarkers[i] == dateStartMarker) {
            bookAttributes.append(this->getPublicationDate().toString("dd,MM,yyyy"));
        } else if(startMarkers[i] == isbnStartMarker) {
            bookAttributes.append(this->getIsbn());
        } else if(startMarkers[i] == contentStartMarker) {
            bookAttributes.append(this->getContent());
        }
    }
    qDebug() << bookAttributes.length();
}
