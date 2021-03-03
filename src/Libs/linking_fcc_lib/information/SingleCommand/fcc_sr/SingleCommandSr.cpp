#include "linkingFcc/infornation/SingleCommand/fcc_sr/SingleCommandSr.h"

SingleCommandSr::SingleCommandSr(const Periodicity periodecity, const uint16_t numberCommand)
    : _periodecity(periodecity), _numberCommand(numberCommand)
{
}

QByteArray SingleCommandSr::serialize() const
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out.setByteOrder(QDataStream::LittleEndian);

    uint16_t templateFullSingleCommand{1};
    uint16_t word2{0};
    templateFullSingleCommand |= (uint16_t)_periodecity << 2;
    templateFullSingleCommand |= _numberCommand << 4;
    templateFullSingleCommand &= ~(1 << 15);

    out << templateFullSingleCommand;
    out << word2;

    return array;
}

void SingleCommandSr::unserialize(StructSingleCommand& structSingleCommand)
{
    _periodecity = (Periodicity)structSingleCommand.typeCommand;
    _numberCommand = structSingleCommand.code;
}
