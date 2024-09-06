#include "bookwriter.h"
#include <QMetaProperty>
#include <QVariant>

BookWriter::BookWriter() {
    fileName.clear();
}

QString BookWriter::write(Book *b) {

    const QMetaObject *mObject = b->metaObject();
    //Access property
    int index = mObject->indexOfProperty("binding");
    qDebug() << "indexOfProperty 'binding': " + QString::number(index);
    QMetaProperty mProperty = mObject->property(index);
    QMetaObject::invokeMethod(b, "write"); //sets the binding
    //b->write();
    QVariant variant = mProperty.read(b);
    qDebug() << variant.toString();

    fileName = QFileDialog::getOpenFileName(&widget,("Open file"),"",("(*.xml);(*.txt)"));
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open file";
    } else {
        QTextStream stream(&file);
        stream << variant.toString();
        //stream << b->getBinding();
        file.close();
        qDebug() << "Close file";
    }
    return b->getBinding();
}
