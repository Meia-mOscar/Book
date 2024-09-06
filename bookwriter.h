#ifndef BOOKWRITER_H
#define BOOKWRITER_H
#include "Book.h"
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QFile>

class BookWriter
{
public:
    BookWriter();
    QString write(Book *b);
private:
    QString fileName;
    QFile file;
    QWidget widget;
};

#endif // BOOKWRITER_H
