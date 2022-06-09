#pragma once

#include <QStackedWidget>
#include <QWidget>
#include <QFileSystemModel>
#include <QListView>


#include "ClickableLabel.hpp"
#include "CustomIconProvider.hpp"

#include "DebugHelpers.hpp"

/**
 * @brief Component that consists of navigable folder view with image preview on doubleclick
 */
class FileExplorer : public QStackedWidget {
Q_OBJECT

public:
    explicit FileExplorer(QWidget *parent = nullptr);

private:
    void setupViews();
    void setupModels();

public slots:
    void changeRootIndex(const QString &newPath);
    void setIconSize(const QSize &newSize);

signals:

    void fileClicked(const QString &filePath);

private:
    // Models and stuff close to them
    QFileSystemModel *m_filesystemModel = nullptr;
    CustomIconProvider *m_fileIconProvider = nullptr;

    // Views
    QListView *m_listView = nullptr;
    ClickableLabel *m_imageLabel = nullptr;


};