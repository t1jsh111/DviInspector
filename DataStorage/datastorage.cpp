#include "datastorage.h"

#include <cmath>
#include <QDebug>

DataStorage::DataStorage(const QString &filePath) : file(filePath)
{
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen())
        throw std::runtime_error(std::string("Failed to open file `") + file.fileName().toStdString() + "`");

    fileSize = file.size();

    //Put block zero into memory
    file.seek(0);
    arrayInMemory = file.read(BYTESINMEMORY);
    blockNrInMemory = 0;

    file.close();
}

char DataStorage::at(qint64 i)
{
    int blockNumber = (qint64) i / (qint64) BYTESINMEMORY;
    int position = (qint64) i % ((qint64) BYTESINMEMORY);

    if(blockNumber != blockNrInMemory) {
        loadBlockInMemory(blockNumber);
    }

    return arrayInMemory.at(position);

}


qint64 DataStorage::size() const
{
    return this->fileSize;
}

int DataStorage::numberOfBlocks() const
{
    int blockNumbers = (qint64) fileSize / (qint64) BYTESINMEMORY;
    // Additional block for rounding up
    if( ((qint64) fileSize % (qint64) BYTESINMEMORY ) != 0 ) blockNumbers++;

    return blockNumbers;
}

void DataStorage::loadBlockInMemory(int blockNumber)
{
    if(blockNumber == blockNrInMemory) return;

    file.open(QIODevice::ReadOnly);
    if(!file.isOpen())
        throw std::runtime_error(std::string("Failed to open file `") + file.fileName().toStdString() + "`");

    file.seek(blockNumber*BYTESINMEMORY);
    arrayInMemory = file.read(BYTESINMEMORY);
    blockNrInMemory = blockNumber;

    file.close();

}


