#pragma once

#include <QString>
#include <QStringList>
#include <QImage>
#include <QPainter>
#include <QImageReader>
#include <QFileInfo>
#include <QPalette>

inline void saveImageWithText(const QString &pathToFile, const QString &multilineTextString) {
    auto image = QImage(pathToFile);
    auto painter = QPainter(&image);
    painter.setPen(QPen(Qt::black));
    painter.setFont(QFont("Times", 4*(qMin(image.width(), image.height())/200)));
    painter.drawText(image.rect(), Qt::AlignTop | Qt::AlignLeft, multilineTextString);
    // Add "Copy" to filename
    auto splitted = pathToFile.split(".");
    splitted[splitted.length() - 2] += "Copy";
    auto savePath = splitted.join(".");
    image.save(savePath);
}

inline bool checkIfImage(const QString &filepath) {
    if (QFileInfo(filepath).isDir()) {
        return false;
    } else {
        if (!QImageReader(filepath).format().isEmpty())
            return true;
    }
    return false;
}

inline QPalette getPalette(){
    QPalette palette(QColor("#424c55"), QColor("#424c55"));
    return palette;
}