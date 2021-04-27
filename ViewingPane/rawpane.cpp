#include "rawpane.h"

#include "viewingpane.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QScrollBar>

int COLUMN_PADDING_CHARS = 1;

RawPane::RawPane(ViewingPane *parent) : QWidget(parent)
{
    viewingPane = parent;
    updateWidth();

}

void RawPane::updateWidth()
{
    this->setFixedWidth(getNewWidth());
}

int RawPane::getNewWidth() const
{
    int columns = viewingPane->getColumns();
    int charWidth = viewingPane->getCharWidth();
    int digitsPerColumn = viewingPane->numberOfDigitsPerColumn();

    int newWidth = 0;
    // add space for the columns
    newWidth += charWidth * columns * digitsPerColumn;
    // add padding between the columns
    newWidth += charWidth * columns * COLUMN_PADDING_CHARS;
    // one additional padding for the end
    newWidth += charWidth * COLUMN_PADDING_CHARS;

    return newWidth;

}

void RawPane::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    //painter.fillRect(event->rect(), QColor(160, 160, 160));

    int firstLineNumber = viewingPane->verticalScrollBar()->value();
    int numberOfVisibleLines = viewingPane->visibleNumberOfLines();
    int bytesPerLine = viewingPane->getColumns();
    int digitsPerByte = viewingPane->numberOfDigitsPerColumn();

    int charWidth = viewingPane->getCharWidth();
    int charHeight = viewingPane->getCharHeight();

    DataStorage* dataStorage = viewingPane->getDataStorage();

    if(!dataStorage) return;

    for(int i = 0; i < numberOfVisibleLines; i++) {
        int lineNumber = firstLineNumber + i;

        for(int j = 0; j < bytesPerLine; j++) {
            int index = lineNumber * bytesPerLine + j;
            if(index >= dataStorage->size()) break;

            //int index = 0;
            int xPos = 0;
            xPos += (j+1) * COLUMN_PADDING_CHARS * charWidth;
            xPos += j * digitsPerByte * charWidth;

            int yPos = (i+1) * charHeight;
            char byte = dataStorage->at(index);
            QString number = QString::number((uint8_t) byte, base).rightJustified(digitsPerByte, '0');

            painter.drawText(xPos, yPos, number);
        }

    }

}

void RawPane::wheelEvent(QWheelEvent *event)
{
    QWidget::wheelEvent(event);
    viewingPane->scroll(event);

}

