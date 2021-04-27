#ifndef VIEWINGPANE_H
#define VIEWINGPANE_H

#include <QWidget>
#include <QAbstractScrollArea>
#include <QSharedPointer>

#include "addresspane.h"
#include "DataStorage/datastorage.h"
#include "rawpane.h"

class ViewingPane : public QAbstractScrollArea
{
    Q_OBJECT
public:
    explicit ViewingPane(QWidget *parent = nullptr);

    void setData(const QSharedPointer<DataStorage>& dataStorage);

    int numberOfLines() const;
    int visibleNumberOfLines() const;
    int invisibleNumberOfLines() const;
    int numberOfLinesThatFitInView() const;

    int getCharWidth() const;
    int getCharHeight() const;

    int getColumns() const;

    int numberOfDigitsPerColumn() const;

    // TODO: invent cleaner solution for this...
    void scroll(QWheelEvent *event);

    DataStorage* getDataStorage();


signals:
    void dataChanged();

private slots:
    void setScrollBar();

private:
    int numberOfDigits(qint64 number) const;

    int getEncodingPaneWidth() const;
    int getChildrenWidth() const;


//    int numberOfAddressPaneCharacters();
//    int getAddressPaneWidth();



    const int columns = 16;
    const int base = 10;

    int charWidth = 10;
    int charHeight = 10;

    AddressPane* addresPane;
    RawPane* rawPane;
    QSharedPointer<DataStorage> dataStorage;


    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // VIEWINGPANE_H
