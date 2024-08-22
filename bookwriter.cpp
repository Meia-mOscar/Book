#include "bookwriter.h"
#include <QMetaProperty>
#include <QVariant>

BookWriter::BookWriter() {
    fileName.clear();
}

QString BookWriter::write(Book *b) {

    const QMetaObject *mObject = b->metaObject();
    int index = mObject->indexOfProperty("binding");
    QMetaProperty mProperty = mObject->property(index);
    QVariant variant = mProperty.read(b);

    fileName = QFileDialog::getOpenFileName(&widget,("Open file"),"",("(*.xml);(*.txt)"));
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open file";
    } else {
        QTextStream stream(&file);
        b->setBookAttributes();
        b->write();
        stream << variant.toString();
        //stream << b->getBinding();
        file.close();
        qDebug() << "Close file";
    }
    return b->getBinding();
}
