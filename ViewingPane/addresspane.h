#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>

class ViewingPane;

class AddressPane : public QWidget
{
    Q_OBJECT
public:
    explicit AddressPane(ViewingPane *parent = nullptr);
    int getAddressPaneWidth() const;
    int numberOfAddressPaneCharacters() const;

public slots:
    void updateWidth();

signals:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

private:
    ViewingPane* viewingPane;
    int numberOfDigits(qint64 number) const;
    int base = 10;



    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // LINENUMBERAREA_H
