#include "viewingpane.h"
#include "decodingpane.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QDebug>



const int MIN_NUMBER_OF_ADDRESS_PANE_CHARS = 2;

ViewingPane::ViewingPane(QWidget *parent) : QAbstractScrollArea(parent)
{

    // Note that font is passed to childwidgets, which is desirable behaviour for our case...
    setFont(QFont("Courier", 10));
    charWidth = fontMetrics().horizontalAdvance(QLatin1Char('0'));
    charHeight = fontMetrics().height();

    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->setContentsMargins(0,0,0,0);
    this->setContentsMargins(0,0,0,0);
    this->setLayout(hlayout);


    addresPane = new AddressPane(this);
    connect(this, SIGNAL(dataChanged()), addresPane, SLOT(updateWidth()));
    //addresPane->setFixedWidth(100);

    //lineNumberArea->setFixedWidth(getAddressPaneWidth());
    hlayout->addWidget(addresPane);
    hlayout->addStretch(1);



}

void ViewingPane::setData(const QSharedPointer<DataStorage> &dataStorage)
{
    this->dataStorage = dataStorage;
    qInfo() << "dataChanged";
    emit dataChanged();
}


void ViewingPane::resizeEvent(QResizeEvent *event)
{
    QAbstractScrollArea::resizeEvent(event);

    QRect cr = contentsRect();

//    qInfo() << "cr.left()" << cr.left() << "cr.right()" << cr.right();
//    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), 50, cr.height()));
}

int ViewingPane::numberOfLines() const
{
//    int numberOfLines = 0;
//    if(bytesPerLine <= 0 || totalNumberOfBytes <= 0) return numberOfLines;
    int totalNumberOfBytes = dataStorage->size();
    int noLines = totalNumberOfBytes / columns;
    if(totalNumberOfBytes / columns ) noLines++;
    qInfo() << "noOfLines" << noLines;
    return noLines;
}

int ViewingPane::getCharWidth() const
{
    return this->charWidth;
}

int ViewingPane::getCharHeight() const
{
    return this->charHeight;
}

int ViewingPane::getEncodingPaneWidth()
{
    return columns*numberOfDigitsPerByte()*charWidth;
}



int ViewingPane::numberOfDigits(qint64 number)
{
    return QString::number(number, base).size();
}

int ViewingPane::numberOfDigitsPerByte()
{
    // return how many digits needed in base to represent byte 1111 1111
    return QString::number(255, base).size();
}

//int ViewingPane::numberOfAddressPaneCharacters()
//{
//    if(!dataStorage) return MIN_NUMBER_OF_ADDRESS_PANE_CHARS;

//    return std::max(numberOfDigits(dataStorage->size()), MIN_NUMBER_OF_ADDRESS_PANE_CHARS);
//}

