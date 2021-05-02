#ifndef VIEWINGPANESCROLLINGAREA_H
#define VIEWINGPANESCROLLINGAREA_H

#include <QWidget>
#include <QScrollArea>

class ViewingPaneScrollingArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit ViewingPaneScrollingArea(QWidget *parent = nullptr);

signals:

};

#endif // VIEWINGPANESCROLLINGAREA_H
