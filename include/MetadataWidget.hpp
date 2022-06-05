#pragma once

#include <QWidget>
#include <QLabel>
#include <QGroupBox>


class MetadataWidget: public QWidget
{
    Q_OBJECT

public:
     explicit MetadataWidget(QWidget* parent = nullptr);
private:
    QLabel* m_textLabel = nullptr;
    QGroupBox* m_groupBox = nullptr;

};