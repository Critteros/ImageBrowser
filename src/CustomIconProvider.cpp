#include "CustomIconProvider.hpp"

#include <QDir>

CustomIconProvider::CustomIconProvider(QObject *parent) : QFileIconProvider(), QObject(parent) {

}

QIcon CustomIconProvider::icon(const QFileInfo &info) const {

    // Handle icons for special folders
    if (info.fileName() == ".." || info.fileName() == ".") {
        return QFileIconProvider::icon(QFileInfo(info.absoluteFilePath()));
    }

    if (m_thumbExtensions.contains(info.completeSuffix().toLower())) {
        qDebug() << "Thumbnail for" << info.fileName();
        const auto filePath = info.filePath();
        QPixmap pixmap(m_thumbSize);
        pixmap.load(filePath);
        
        return {pixmap};
    }

    return QFileIconProvider::icon(info);
}

void CustomIconProvider::onIconSizeChange(const QSize &newSize) {
    qDebug() << "Changing icon size to:" << newSize;
    m_thumbSize = newSize;
}

void CustomIconProvider::setAllowedExtensions(const QStringList &extensions) {
    m_thumbExtensions = extensions;
}
