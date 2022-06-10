#pragma once

#include <QString>
#include <QStringList>
#include <QImage>
#include <QPainter>

void saveImageWithText(const QString& pathToFile, const QStringList& multilineTextList){
    // Concatenate into one
    auto text = multilineTextList.join("\n");
    auto image = QImage(pathToFile);
    auto painter = QPainter(&image);
    painter.setPen(QPen(Qt::black));
    painter.setFont(QFont("Times", 40));
    painter.drawText(image.rect(), Qt::AlignTop | Qt::AlignLeft, text);
    // Add "Copy" to filename
    auto splitted = pathToFile.split(".");
    splitted[splitted.length() -2] += "Copy";
    auto savePath = splitted.join(".");
    image.save(savePath);
}