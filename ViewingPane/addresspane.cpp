#include "addresspane.h"

#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QFontMetrics>
#include <QtGlobal>
#include <QScrollBar>

#include "viewingpane.h"

int MINIMUM_ADDRESS_PANE_WIDTH = 0;

AddressPane::AddressPane(ViewingPane *parent) : QWidget(parent)
{
    this->viewingPane = parent;
    updateWidth();
}

int AddressPane::getAddressPaneWidth() const
{
   if(!viewingPane) return MINIMUM_ADDRESS_PANE_WIDTH;

   int numberOfDigitsInAddressPane = numberOfAddressPaneCharacters();
   int width = qMax(numberOfDigitsInAddressPane * viewingPane->getCharWidth(), MINIMUM_ADDRESS_PANE_WIDTH);
   return width;
}

int AddressPane::numberOfAddressPaneCharacters() const
{
    int highestAddress = viewingPane->numberOfLines() * viewingPane->getColumns();
    // TODO: reconsider the zero case....
    if(highestAddress == 0) return 0;
    int numberOfDigitsInAddressPane = numberOfDigits(highestAddress);
    return numberOfDigitsInAddressPane;
}

void AddressPane::updateWidth()
{
    setFixedWidth(getAddressPaneWidth());
    update();
}



void AddressPane::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QColor paneColor = palette().color(QPalette::Midlight);
    painter.fillRect(event->rect(), QBrush(paneColor));

    int firstLineNumber = viewingPane->verticalScrollBar()->value();
    int numberOfVisibleLines = viewingPane->visibleNumberOfLines();
    int bytesPerLine = viewingPane->getColumns();
    //qInfo() << "firstLineNumber" << firstLineNumber;
    for(int i = 0; i < numberOfVisibleLines; i++) {
        int lineNumber = firstLineNumber + i;
        QString address = QString("%1").arg((qint64) lineNumber * (qint64) bytesPerLine, numberOfAddressPaneCharacters(), base, QChar('0'));

        int yPos = (i+1) * viewingPane->getCharHeight();
        //painter.setPen(Qt::black);
        painter.drawText(0, yPos, address);

    }


}

int AddressPane::numberOfDigits(qint64 number) const
{
    return QString::number(number, base).size();
}

void AddressPane::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
//    setFixedWidth(getAddressPaneWidth());
}




