#pragma once

#include <QSet>
#include <QString>
#include <QPair>


QList<QPair<QString, QString>> extractMetadataFromFile(const QString& pathToImage);