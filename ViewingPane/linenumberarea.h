#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>

class LineNumberArea : public QWidget
{
    Q_OBJECT
public:
    explicit LineNumberArea(QWidget *parent = nullptr);

    void setBytesPerLine(int bytesPerLine);
    void setTotalNumberOfBytes(int totalNumberOfBytes);

signals:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

private:
    unsigned int bytesPerLine = 0;
    quint64 totalNumberOfBytes = 0;

    int charHeight;

    // Line numbers are expressed in base 10. Possibly in the future this can be configured..
    int base = 10;

    int numberOfLines();
};

#endif // LINENUMBERAREA_H
