#pragma once

#include <QMainWindow>

#include "DebugHelpers.hpp"
#include "MetadataWidget.hpp"

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    ~MainWindow() override;


private:
    MetadataWidget* m_metadataWidget = nullptr;
};