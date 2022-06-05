#include "CustomIconProvider.hpp"

#include <QDir>

CustomIconProvider::CustomIconProvider(QObject *parent) : QFileIconProvider(), QObject(parent) {

}

QIcon CustomIconProvider::icon(const QFileInfo &info) const {

//    qDebug() << "Requesting icon for" << info.fileName();

    if (info.fileName() == ".." || info.fileName() == ".") {

        return QFileIconProvider::icon(QFileInfo(info.absoluteFilePath()));

//        return {QFileIconProvider::icon(QFileIconProvider::Folder).pixmap(m_thumbSize)};
    }

    if (m_thumbExtensions.contains(info.completeSuffix().toLower())) {
        qDebug() << "Thumbnail for" << info.fileName();
        const auto filePath = info.filePath();
        QPixmap pixmap(m_thumbSize);
        pixmap.load(filePath);
//        pixmap = pixmap.scaled(m_thumbSize, Qt::KeepAspectRatio);
//        pixmap.scaledToWidth(m_thumbSize.width());


        qDebug() << pixmap.size();
        return {pixmap};
    }
//    qDebug() << QFileIconProvider::icon(info).availableSizes();
    return QFileIconProvider::icon(info);
}

void CustomIconProvider::onIconSizeChange(const QSize &newSize) {
    qDebug() << "Changing icon size to:" << newSize;
    m_thumbSize = newSize;
}

void CustomIconProvider::setAllowedExtensions(const QStringList &extensions) {
    m_thumbExtensions = extensions;
}
