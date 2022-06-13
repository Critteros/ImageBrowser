#pragma once

#include <QString>
#include <QStringList>
#include <QImage>
#include <QPainter>
#include <QImageReader>
#include <QFileInfo>

inline void saveImageWithText(const QString &pathToFile, const QStringList &multilineTextList) {
    // Concatenate into one
    auto text = multilineTextList.join("\n");
    auto image = QImage(pathToFile);
    auto painter = QPainter(&image);
    painter.setPen(QPen(Qt::black));
    painter.setFont(QFont("Times", 40));
    painter.drawText(image.rect(), Qt::AlignTop | Qt::AlignLeft, text);
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