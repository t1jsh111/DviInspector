#include "decodingpane.h"

#include "viewingpane.h"

#include <QPainter>
#include <QDebug>
#include <QScrollBar>


int COLUMN_PADDING_CHARS_DECODING = 1;

DecodingPane::DecodingPane(ViewingPane *parent) : QWidget(parent)
{
    viewingPane = parent;
    updateWidth();
}

void DecodingPane::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    //painter.fillRect(event->rect(), QColor(160, 160, 160));

    int firstLineNumber = viewingPane->verticalScrollBar()->value();
    int numberOfVisibleLines = viewingPane->visibleNumberOfLines();
    int bytesPerLine = viewingPane->getColumns();

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
            xPos += (j+1) * COLUMN_PADDING_CHARS_DECODING * charWidth;
            xPos += j * QString("set_char_255").length() * charWidth;

            int yPos = (i+1) * charHeight;
            char byte = dataStorage->at(index);
            QString command = getCommandAndSkipParameters(byte, index);

            i = index / bytesPerLine;
            j = index % bytesPerLine;

            qInfo() << "command: " << command;
            painter.drawText(xPos, yPos, command);
        }

    }

}

void DecodingPane::updateWidth()
{
    this->setFixedWidth(getNewWidth());
}


int DecodingPane::getNewWidth() const
{
    int columns = viewingPane->getColumns();
    int charWidth = viewingPane->getCharWidth();
    int maxKeyWordLength = QString("post_post").length();

    int newWidth = 0;
    // add space for the columns
    newWidth += charWidth * columns * maxKeyWordLength;
    // add padding between the columns
    newWidth += charWidth * columns * COLUMN_PADDING_CHARS_DECODING;
    // one additional padding for the end
    newWidth += charWidth * COLUMN_PADDING_CHARS_DECODING;

    return newWidth;
}

QString DecodingPane::getCommandAndSkipParameters(int commandCode, int &index)
{
    switch (commandCode) {
    case 0 ... 127:
        return QString("set_char_%1").arg(commandCode);
    case 128 ... 131:
        index += commandCode % 127;
        return QString("set%1").arg(commandCode % 127);
    case 132:
        index += 8;
        return QString("set_rule");
    case 133 ... 136:
        index += commandCode % 132;
        return QString("put%1").arg(commandCode % 132);
    case 137:
        index += 8;
        return QString("put_rule");
    case 138:
        return QString("nop");
    case 139:
        index += 44;
        return QString("bop");
    case 140:
        return QString("eop");
    case 141:
        return QString("push");
    case 142:
        return QString("pop");
    case 143 ... 146:
        index += commandCode % 142;
        return QString("right%1").arg(commandCode % 142);
    case 147 ... 151:
        index += commandCode % 147;
        return QString("w%1").arg(commandCode % 147);
    case 152 ... 156:
        index += commandCode % 152;
        return QString("x%1").arg(commandCode % 152);
    case 157 ... 160:
        index += commandCode % 156;
        return QString("down%1").arg(commandCode % 156);
    case 161 ... 165:
        index += commandCode % 161;
        return QString("y%1").arg(commandCode % 161);
    case 166 ... 170:
        index += commandCode % 166;
        return QString("z%1").arg(commandCode % 166);
    case 171 ... 234:
        return QString("fnt_num_%1").arg(commandCode % 171);
    case 235 ... 238:
        index += commandCode % 234;
        return QString("fnt%1").arg(commandCode % 234);
    case 239 ... 242: {
        index++;
        int k = combineMultipleBytes(index, commandCode % 238);
        index += commandCode % 238;
        index += k;
        return QString("xxx%1").arg(commandCode % 238); }
    case 243 ... 246 : {
        index += commandCode % 242;
        index += 12;
        int a = combineMultipleBytes(index, 1);
        index++;
        int l = combineMultipleBytes(index, 1);
        index++;
        index += a+l; }
    case 247 : {
        index += 13;
        int k = combineMultipleBytes(index, 1);
        index += k;
        return QString("pre");
    }
    case 248 :
        return QString("post");
    case 249 :
        return QString("post_post");
    case 250 ... 255 :
        return QString("post_post");
    default: return QString("sad");

    }

}

int DecodingPane::combineMultipleBytes(int index, int numberOfBytes)
{
    if(viewingPane->getDataStorage() == nullptr) return 0;

    int value = 0;
    for(int i = 0; i < numberOfBytes; i++) {
        unsigned char cValue = viewingPane->getDataStorage()->at(index);
        value = value << 8 | cValue;
    }
    return value;
}





