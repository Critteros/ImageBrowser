#include "MetadataWidget.hpp"

#include <QVBoxLayout>

MetadataWidget::MetadataWidget(QWidget *parent): QWidget(parent) {

    auto widgetLayout = new QVBoxLayout;

    m_groupBox =  new QGroupBox("Metadata", this);
    auto groupBoxLayout = new QVBoxLayout;
    groupBoxLayout->addWidget(new QLabel("text"));
    m_groupBox->setLayout(groupBoxLayout);


//    m_textLabel = new QLabel("Label");
//    auto groupboxLayout = new QVBoxLayout;
//
//    groupboxLayout->addWidget(m_textLabel);
//    m_groupBox->setLayout(groupboxLayout);



    widgetLayout->addWidget(m_groupBox, 1);

    setLayout(widgetLayout);
}
