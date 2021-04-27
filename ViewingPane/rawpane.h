#ifndef RAWPANE_H
#define RAWPANE_H

#include <QWidget>

class ViewingPane;

class RawPane : public QWidget
{
    Q_OBJECT
public:
    explicit RawPane(ViewingPane *parent = nullptr);

    void setColumns(int columns);
    void setBase(int base);

public slots:
    void updateWidth();

signals:

private:
    const int base = 10;
    ViewingPane* viewingPane;
    int getNewWidth() const;



    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event);
};

#endif // RAWPANE_H
