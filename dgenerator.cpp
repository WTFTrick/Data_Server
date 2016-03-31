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

    quint32 frChannel;

    for (quint32 i = 0; i < sizeArray; i++)
    {
        if (i == 1500)
            frChannel = 102;
        else
            frChannel = std::rand() % 73;

        arrData->append( frChannel );
    }

}

