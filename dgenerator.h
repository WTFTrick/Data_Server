#ifndef DGENERATOR_H
#define DGENERATOR_H

#include <QVector>
#include <QDebug>


#include "ichannel.h"


class DGenerator
{

public:
    DGenerator( quint32 sizeDataContainer);
    ~DGenerator();

    void getData( QVector<quint32> *arrData );


private:
    quint32 sizeArray;

};

#endif // DGENERATOR_H
