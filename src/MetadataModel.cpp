#include "MetadataModel.hpp"


MetadataModel::MetadataModel(QObject *parent) : QAbstractTableModel(parent) {

}

int MetadataModel::rowCount(const QModelIndex &parent) const {
    const auto exifCount = m_metadata.exifCount();
    const auto iptcCount = m_metadata.iptcCount();

    qsizetype total = 0;
    if (exifCount != 0) {
        total += 1 + exifCount;
    }
    if (iptcCount != 0) {
        total += 1 + iptcCount;
    }

    return static_cast<int>(total);
}

int MetadataModel::columnCount(const QModelIndex &parent) const {
    return 2;
}

QVariant MetadataModel::data(const QModelIndex &index, int role) const {

    switch (role) {
        case Qt::DisplayRole: {
            return dataForDisplay(index);
        }

        default:
            return {};
    }

}

void MetadataModel::clearStoredMetadata() {
    qDebug() << "Clearing stored metadata";
    m_metadata.clear();

}

void MetadataModel::loadAndParseImage(const QString &filepath) {
    qDebug() << "Loading image: " << filepath;
    beginResetModel();

    m_metadata = loadImageMetadata(filepath);
    calculatePresentationDetails();
    endResetModel();
}

MetadataModel::ImageMetadata MetadataModel::loadImageMetadata(const QString &filepath) {
    // There extract metaata
    auto metadataContainer = MetadataModel::ImageMetadata();

    for (int i = 0; i < 10; i++) {
        metadataContainer.addExif(QString("EXIF-KEY-%1").arg(i), QString("EXIF-VALUE-%1").arg(i));
        metadataContainer.addIpct(QString("IPTC-KEY-%1").arg(i), QString("IPCT-VALUE-%1").arg(i));

    }

    return metadataContainer;
}

void MetadataModel::calculatePresentationDetails() {

    auto container = MetadataModel::PresentationDetails();
    const auto exifCount = m_metadata.exifCount();
    const auto iptcCount = m_metadata.iptcCount();

    MetadataModel::PresentationDetails::index_t indexer = 0;

    if (exifCount != 0) {
        container.exifLabelLocation = indexer++;
        container.exifDataStart = indexer++;

        indexer += static_cast<decltype(indexer)>(exifCount);
        container.exifDataEnd = indexer;
    }

    if (iptcCount != 0) {
        container.iptcLabelLocation = indexer++;
        container.iptcDataStart = indexer++;

        indexer += static_cast<decltype(indexer)>(iptcCount);
        container.iptcDataEnd = indexer;
    }

    // To be implemented
    m_presentationDetails = container;
    emit dataChanged(createIndex(0, 0), createIndex(rowCount(QModelIndex()), 2));
}

QVariant MetadataModel::dataForDisplay(const QModelIndex &index) const {

    const auto row = index.row();
    const auto field = index.column();

    if (row == m_presentationDetails.iptcLabelLocation) {
        if (field == MetadataModel::FIELD_VALUE) {
            return {};
        }
        return MetadataModel::PresentationDetails::IPTC_LABEL;
    }

    if (row == m_presentationDetails.exifLabelLocation) {
        if (field == MetadataModel::FIELD_VALUE) {
            return {};
        }
        return MetadataModel::PresentationDetails::EXIF_LABEL;
    }

    return QString("Row%1, Column%2")
            .arg(index.row() + 1)
            .arg(index.column() + 1);

}


MetadataModel::ImageMetadata &MetadataModel::ImageMetadata::addExif(const QString &key, const QString &value) {
    EXIF_metadata << QPair<QString, QString>(key, value);
    return *this;
}

MetadataModel::ImageMetadata &MetadataModel::ImageMetadata::addIpct(const QString &key, const QString &value) {
    IPTC_metadata << QPair<QString, QString>(key, value);
    return *this;
}

MetadataModel::ImageMetadata &MetadataModel::ImageMetadata::clear() {
    clearExif();
    clearIptc();
    return *this;
}

MetadataModel::ImageMetadata &MetadataModel::ImageMetadata::clearExif() {
    EXIF_metadata.clear();
    return *this;
}

MetadataModel::ImageMetadata &MetadataModel::ImageMetadata::clearIptc() {
    IPTC_metadata.clear();
    return *this;
}

qsizetype MetadataModel::ImageMetadata::exifCount() const {
    return EXIF_metadata.count();

}

qsizetype MetadataModel::ImageMetadata::iptcCount() const {
    return IPTC_metadata.count();
}
