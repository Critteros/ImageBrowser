#pragma once

#include <QMainWindow>
#include <QFileSystemModel>
#include <QListView>

#include "DebugHelpers.hpp"
#include "MetadataWidget.hpp"
#include "CustomIconProvider.hpp"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow();

    ~MainWindow() override;

private:
    void setupFileView();

    void setupFileModel();


private:
    QFileSystemModel *m_filesystemModel = nullptr;
    QListView *m_fileView = nullptr;
    CustomIconProvider *m_iconProvider = nullptr;
};