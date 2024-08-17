#include "bookwriter.h"

BookWriter::BookWriter() {
    fileName.clear();
}

QString BookWriter::write(Book *b) {
    fileName = QFileDialog::getOpenFileName(&widget,("Open file"),"",("(*.xml);(*.txt)"));
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open file";
    } else {
        QTextStream stream(&file);
        b->setBookAttributes();
        b->write();
        stream << b->getBinding();
        file.close();
        qDebug() << "Close file";
    }
    return b->getBinding();
}
