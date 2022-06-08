#pragma once

#include <QLabel>
#include <QWidget>

#include "DebugHelpers.hpp"

class ClickableLabel : public QLabel {
Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

    ~ClickableLabel() override;

signals:

    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;

};