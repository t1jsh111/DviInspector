#include "rawpane.h"



RawPane::RawPane(QWidget *parent)
{
    setColumns(16);
    setBase(16);

}

void RawPane::setColumns(int columns)
{
    this->columns = columns;
}

void RawPane::setBase(int base)
{
    this->base = base;
}
