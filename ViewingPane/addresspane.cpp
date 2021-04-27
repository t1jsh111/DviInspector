#include "addresspane.h"

#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QFontMetrics>
#include <QtGlobal>

#include "viewingpane.h"

int MINIMUM_ADDRESS_PANE_WIDTH = 0;

AddressPane::AddressPane(ViewingPane *parent) : QWidget(parent)
{
    this->viewingPane = parent;//<ViewingPane*>(parent);
}

int AddressPane::getAddressPaneWidth()
{
   if(!viewingPane) return MINIMUM_ADDRESS_PANE_WIDTH;

   int numberOfDigitsInAddressPane = numberOfDigits(viewingPane->numberOfLines());
   return qMax(numberOfDigitsInAddressPane * viewingPane->getCharWidth(), MINIMUM_ADDRESS_PANE_WIDTH);
}

void AddressPane::updateWidth()
{
    qInfo() << "updateWidth";
    setFixedWidth(getAddressPaneWidth());
    update();
}



void AddressPane::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(event->rect(), Qt::lightGray);

}

int AddressPane::numberOfDigits(qint64 number)
{
    return QString::number(number, base).size();
}

void AddressPane::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
//    setFixedWidth(getAddressPaneWidth());
}




