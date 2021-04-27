#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QString>
#include <QFile>
#include <QByteArray>



// Number of bytes of the file that are put into memory
const int BYTESINMEMORY = 1000000000;

/* Large files are often not able to fit into memory (RAM).
 The DataStorage class is an abstraction of for the file, in which
 the file is split into blocks, and a block of size BYTESINMEMORY is kept into memory.
 When bytes outside of the block are fetched, this block will be put into memory (arrayInMemory).
 and the corresponding bytes will returned.

 NOTE: Efficiency of this abstraction highly depends on locality.
*/

class DataStorage
{
public:
    DataStorage(const QString& filePath);

    // Fetch byte at position i
    char at(qint64 i);

    // Size in number of bytes of the file
    qint64 size() const;
    // Number of blocks of size BYTESINMEMORY that are needed for the file
    int numberOfBlocks() const;

private:
    // Sets arrayInMemory to the bytes that fall into the block with number blockNumber
    void loadBlockInMemory(int blockNumber);

private:
    // The file we are reading from
    QFile file;

    // Size of file
    qint64 fileSize = 0;

    // Array that is 'cached' into memory
    QByteArray arrayInMemory;
    // Block number that is currently 'cached' into memory
    int blockNrInMemory;
};

#endif // DATASTORAGE_H
