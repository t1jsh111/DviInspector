#ifndef VIEWINGPANE_H
#define VIEWINGPANE_H

#include <QWidget>
#include <QAbstractScrollArea>
#include <QSharedPointer>

#include "addresspane.h"
#include "DataStorage/datastorage.h"

class ViewingPane : public QAbstractScrollArea
{
    Q_OBJECT
public:
    explicit ViewingPane(QWidget *parent = nullptr);

    void setData(const QSharedPointer<DataStorage>& dataStorage);
    int numberOfLines() const;
    int getCharWidth() const;
    int getCharHeight() const;

signals:
    void dataChanged();

private:
    int numberOfDigits(qint64 number);
    int numberOfDigitsPerByte();

    int getEncodingPaneWidth();
//    int numberOfAddressPaneCharacters();
//    int getAddressPaneWidth();



    const int columns = 16;
    const int base = 10;

    int charWidth = 10;
    int charHeight = 10;

    AddressPane* addresPane;
    QSharedPointer<DataStorage> dataStorage;


    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // VIEWINGPANE_H
