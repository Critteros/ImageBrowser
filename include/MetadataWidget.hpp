#pragma once

#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>


#include "MetadataModel.hpp"

#include "DebugHelpers.hpp"


class MetadataWidget : public QWidget {
Q_OBJECT


public:
    explicit MetadataWidget(QWidget *parent = nullptr);

public slots:

    void onFileCLick(const QString &filepath);

private:
    void setupModels();

    void setupViews();

private:

    // Organizers
    QVBoxLayout *m_layout = nullptr;

    //Models
    MetadataModel *m_metadataModel = nullptr;

    // Views
    QTableView *m_tableView = nullptr;


};