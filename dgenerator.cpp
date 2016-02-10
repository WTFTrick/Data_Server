#include "dgenerator.h"

DGenerator::DGenerator( quint32 sizeDataContainer) : sizeArray(sizeDataContainer)
{

}

DGenerator::~DGenerator()
{

}

void DGenerator::getData(QVector<quint32> *arrData)
{
    arrData->clear();

    //qDebug() << "sizeArray =" << sizeArray;
    for (quint32 i = 0; i < sizeArray; i++)
    {
        quint32 frChannel = std::rand() % 70;
        arrData->append( frChannel );

        if (i < 3)
            qDebug() << i << ")" << frChannel;
    }
}

