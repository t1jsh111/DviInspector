#ifndef RAWPANE_H
#define RAWPANE_H

#include <QWidget>

class RawPane : public QWidget
{
    Q_OBJECT
public:
    explicit RawPane(QWidget *parent = nullptr);

    void setColumns(int columns);
    void setBase(int base);

signals:

private:
    int columns;
    int base;

};

#endif // RAWPANE_H
