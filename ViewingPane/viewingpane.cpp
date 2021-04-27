#include "viewingpane.h"
#include "decodingpane.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QDebug>
#include <QScrollBar>



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
    // When data is changed, the scrollbars need to adapt accordingly...
    connect(this, SIGNAL(dataChanged()), this, SLOT(setScrollBar()));

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

int ViewingPane::visibleNumberOfLines() const
{
    int noLines = numberOfLines();
    int noLinesThatFitInView = numberOfLinesThatFitInView();
    if(noLines > noLinesThatFitInView) {
        return noLinesThatFitInView;
    } else {
        return noLines;
    }
}

int ViewingPane::invisibleNumberOfLines() const
{
    return numberOfLines() - visibleNumberOfLines();
}

int ViewingPane::numberOfLinesThatFitInView() const
{
    return viewport()->size().height() / charHeight;
}

int ViewingPane::numberOfLines() const
{
    if(!dataStorage) return 0;

    int totalNumberOfBytes = dataStorage->size();
    int noLines = totalNumberOfBytes / columns;
    if(totalNumberOfBytes % columns != 0) noLines++;
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

int ViewingPane::getColumns() const
{
    return this->columns;
}

void ViewingPane::setScrollBar()
{
    // setting up scrolling line by line...,
    verticalScrollBar()->setPageStep(numberOfLinesThatFitInView());
    verticalScrollBar()->setRange(0, invisibleNumberOfLines());
}

int ViewingPane::getEncodingPaneWidth() const
{
    return columns*numberOfDigitsPerByte()*charWidth;
}

int ViewingPane::numberOfDigits(qint64 number) const
{
    return QString::number(number, base).size();
}

int ViewingPane::numberOfDigitsPerByte() const
{
    // return how many digits needed in base to represent byte 1111 1111
    return QString::number(255, base).size();
}


