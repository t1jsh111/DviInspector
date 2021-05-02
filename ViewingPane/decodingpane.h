#ifndef DECODINGPANE_H
#define DECODINGPANE_H

#include <QWidget>

class ViewingPane;
class DecodingPane : public QWidget
{
public:
    explicit DecodingPane(ViewingPane *parent = nullptr);
    void updateWidth();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
private:
    QString getCommandAndSkipParameters(int commandCode, int& index);
    ViewingPane* viewingPane;
    int getNewWidth() const;



    int combineMultipleBytes(int index, int numberOfBytes);

};

#endif // DECODINGPANE_H
