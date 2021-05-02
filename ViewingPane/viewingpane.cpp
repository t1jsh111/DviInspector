#include "viewingpane.h"
#include "decodingpane.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QDebug>
#include <QScrollBar>
#include <QWidget>



ViewingPane::ViewingPane(QWidget *parent) : QAbstractScrollArea(parent)
{

    // Note that font is passed to childwidgets, which is desirable behaviour for our case...
    setFont(QFont("Courier", 6));
    charWidth = fontMetrics().horizontalAdvance(QLatin1Char('0'));
    charHeight = fontMetrics().height();

    scollAreaContents = new QWidget(this);

    QHBoxLayout* hlayout = new QHBoxLayout;
    //hlayout->setSpacing(0);
    hlayout->setContentsMargins(0,0,0,0);
    this->setContentsMargins(0,0,0,0);
    this->setViewportMargins(0,0,0,0);
    scollAreaContents->setLayout(hlayout);
    this->setViewport(scollAreaContents);


    addresPane = new AddressPane(this);
    connect(this, SIGNAL(dataChanged()), addresPane, SLOT(updateWidth()));
    // When data is changed, the scrollbars need to adapt accordingly...
    connect(this, SIGNAL(dataChanged()), this, SLOT(setScrollBar()));

    rawPane = new RawPane(this);
    decodingPane = new DecodingPane(this);




    hlayout->addWidget(addresPane);
    hlayout->addWidget(rawPane);
    hlayout->addWidget(decodingPane);
    hlayout->addStretch(1);

    // TODO: Find a better way to set the minimum size so that all widgets in the viewport fit
    setMinimumWidth(getMinimumWidth());
    //resize(addresPane->width() + rawPane->width() + 50, 300);
    qInfo() << "viewport width" << viewport()->width() << "viewport min width" << viewport()->minimumWidth() << " scrollarea minimum width" << this->minimumWidth();
    qInfo() << "set width addresPane->width() + rawPane->width() + 50 " <<addresPane->width() + rawPane->width() + 50;



}

void ViewingPane::setData(const QSharedPointer<DataStorage> &dataStorage)
{
    this->dataStorage = dataStorage;
    emit dataChanged();
    //setMinimumWidth(addresPane->width;() + rawPane->width()+ 40 );
    setMinimumWidth(getMinimumWidth());


}


void ViewingPane::resizeEvent(QResizeEvent *event)
{
    QAbstractScrollArea::resizeEvent(event);

    QRect cr = contentsRect();

//    qInfo() << "cr.left()" << cr.left() << "cr.right()" << cr.right();
    //    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), 50, cr.height()));
}

void ViewingPane::paintEvent(QPaintEvent *event)
{
    //setScrollBar();
}

void ViewingPane::scrollContentsBy(int dx, int dy)
{
    //this->viewport()->move(dx,0);
    //QPoint topLeft = viewport()->rect().topLeft();
    //this->viewport()->layout()->m move(topLeft.x() - dx ,0);
    this->scollAreaContents->move(dx+5,0);
    int hvalue = horizontalScrollBar()->value();
    int vvalue = verticalScrollBar()->value();
    QPoint topLeft = viewport()->rect().topLeft();

    qInfo() << "topLeft.x() - hvalue" << topLeft.x() - hvalue;
    //qInfo() << "topLeft.y() - vvalue" << topLeft.y() - vvalue;

    scollAreaContents->move(topLeft.x() - hvalue, 0);
    QAbstractScrollArea::scrollContentsBy(dx,dy);
    scollAreaContents->update();
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
    horizontalScrollBar()->setSingleStep(charWidth);
    horizontalScrollBar()->setRange(0,getChildrenWidth() - getMinimumWidth());
}

int ViewingPane::getEncodingPaneWidth() const
{
    return columns*numberOfDigitsPerColumn()*charWidth;
}


int ViewingPane::getChildrenWidth() const
{
    // TODO: This is still rather awkward...
    // In particular manually children need to be added
    int totalWidth = 0;
    totalWidth += addresPane->width();
    totalWidth += rawPane->width();
    totalWidth += decodingPane->width();
    return totalWidth;
}

int ViewingPane::getMinimumWidth() const
{
    // TODO: This is still rather awkward...
    // In particular manually children need to be added
    // And a fixed padding of 40 is added whereas we desire it to be adjusted to the scrollbar.
    int totalWidth = 0;
    totalWidth += addresPane->width();
    totalWidth += rawPane->width();
    totalWidth += 40;
    return totalWidth;
}

int ViewingPane::numberOfDigits(qint64 number) const
{
    return QString::number(number, base).size();
}

int ViewingPane::numberOfDigitsPerColumn() const
{
    // return how many digits needed in base to represent byte 1111 1111
    return QString::number(255, base).size();
}

void ViewingPane::scroll(QWheelEvent *event)
{
    this->wheelEvent(event);
}

DataStorage *ViewingPane::getDataStorage()
{
    return this->dataStorage.get();
}




