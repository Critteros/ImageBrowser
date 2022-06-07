#include "MetadataWidget.hpp"

#include <QHeaderView>
#include <QImageReader>
#include <QFileInfo>

MetadataWidget::MetadataWidget(QWidget *parent) : QWidget(parent) {

    setupModels();
    setupViews();

    m_layout = new QVBoxLayout;
    m_layout->addWidget(m_tableView);


    setLayout(m_layout);
}

void MetadataWidget::setupModels() {
    m_metadataModel = new MetadataModel(this);

}

void MetadataWidget::setupViews() {
    m_tableView = new QTableView;

    m_tableView->verticalHeader()->setVisible(false);
    m_tableView->verticalHeader()->setDefaultSectionSize(m_tableView->verticalHeader()->minimumSectionSize());
    m_tableView->horizontalHeader()->setVisible(false);
    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    m_tableView->setTabKeyNavigation(false);
    m_tableView->setShowGrid(false);

    m_tableView->setModel(m_metadataModel);

}

void MetadataWidget::onFileCLick(const QString &filepath) {

    if (QFileInfo(filepath).isDir()) {
        m_metadataModel->clearStoredMetadata();
        return;
    }

    if (!QImageReader(filepath).format().isEmpty()) {
        m_metadataModel->loadAndParseImage(filepath);
        return;
    }

}
