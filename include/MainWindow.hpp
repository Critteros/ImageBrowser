#pragma once

#include <QMainWindow>
#include <QSplitter>

#include "DebugHelpers.hpp"
#include "MetadataWidget.hpp"

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() override;
    
private slots:

private:
    QSplitter *centralWidget;
    void createToolBar();
    QSplitter* createLayout();

};