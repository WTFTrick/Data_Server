#include "dgenerator.h"

DGenerator::DGenerator( quint32 sizeDataContainer) : sizeArray(sizeDataContainer)
{

}

DGenerator::~DGenerator()
{

}

void DGenerator::getData(QVector<InfoChannel> *arrData)
{
    InfoChannel inf_chan;
    arrData->clear();

    for (quint32 i = 0; i < sizeArray; i++)
    {
        inf_chan.nm_channel = i;
        inf_chan.freq = std::rand() % 70;

        arrData->append( inf_chan );

        if (i < 3)
            qDebug() << i << ")" << inf_chan.nm_channel << "-" << inf_chan.freq;
    }
}

