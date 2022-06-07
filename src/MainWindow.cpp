#include "MainWindow.hpp"


#include "FileExplorer.hpp"

#include <iostream>
#include <exiv2/exiv2.hpp>

MainWindow::MainWindow() : QMainWindow() {

    m_splitter = new QSplitter(Qt::Horizontal);

    m_fileExplorer = new FileExplorer;
    m_metadataWidget = new MetadataWidget;

    m_splitter->addWidget(m_fileExplorer);
    m_splitter->addWidget(m_metadataWidget);
    m_splitter->setStretchFactor(0, 4);
    m_splitter->setStretchFactor(1, 2);

    m_fileExplorer->setIconSize(FILE_ICON_SIZE);

    m_splitter->setMinimumSize(MAIN_WIDGET_MIN_SIZE);

    QObject::connect(m_fileExplorer, &FileExplorer::fileClicked, m_metadataWidget, &MetadataWidget::onFileCLick);

//    auto image = Exiv2::ImageFactory::open("test.jpg");
//    image->readMetadata();
//    Exiv2::ExifData &exifData = image->exifData();
//    Exiv2::ExifData::const_iterator end = exifData.end();
//    for (Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i) {
//        const char *tn = i->typeName();
//        std::cout << std::setw(44) << std::setfill(' ') << std::left
//                  << i->key() << " "
//                  << "0x" << std::setw(4) << std::setfill('0') << std::right
//                  << std::hex << i->tag() << " "
//                  << std::setw(9) << std::setfill(' ') << std::left
//                  << (tn ? tn : "Unknown") << " "
//                  << std::dec << std::setw(3)
//                  << std::setfill(' ') << std::right
//                  << i->count() << "  "
//                  << std::dec << i->value()
//                  << "\n";
//    }

    setCentralWidget(m_splitter);
}


MainWindow::~MainWindow() = default;
