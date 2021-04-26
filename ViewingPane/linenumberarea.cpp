#include "linenumberarea.h"

#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QFontMetrics>

LineNumberArea::LineNumberArea(QWidget *parent) : QWidget(parent)
{
    charHeight = fontMetrics().height();
}

void LineNumberArea::setBytesPerLine(int bytesPerLine)
{
    this->bytesPerLine = bytesPerLine;
}

void LineNumberArea::setTotalNumberOfBytes(int totalNumberOfBytes)
{
    this->totalNumberOfBytes = totalNumberOfBytes;
}


void LineNumberArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(event->rect(), Qt::lightGray);


    if(bytesPerLine == 0 || totalNumberOfBytes == 0) return;

    const int noLines = numberOfLines();
    for(int i = 0; i < noLines; i++) {

        int y = charHeight * (i+1);
        QString number = QString("%1").arg((qint64) i * (qint64) bytesPerLine, numberOfAddressPaneCharacters(), base, QChar('0'));

        painter.setPen(Qt::black);
        painter.drawText(0, y, width(), charHeight, Qt::AlignRight, number);
    }

}

int LineNumberArea::numberOfLines()
{
    int numberOfLines = 0;
    if(bytesPerLine <= 0 || totalNumberOfBytes <= 0) return numberOfLines;

    numberOfLines = totalNumberOfBytes / bytesPerLine;
    if( totalNumberOfBytes % bytesPerLine != 0) numberOfLines++;
    return numberOfLines;
}


