#include "Pirate.h"

Pirate::~Pirate()
{
}
Pirate::Pirate(int rank, int id, int coins, int fleetId) : m_rank(rank),
                                                           m_pirateId(id),
                                                           m_coins(coins),
                                                           m_fleetId(fleetId) {}

int Pirate::getCoins() const
{
    return m_coins;
}

int Pirate::getId() const
{
    return m_pirateId;
}
void Pirate::addCoins(int number)
{
    m_coins += number;
}

int Pirate::getRank() const
{
    return m_rank;
}

void Pirate::setRank(int rank)
{
    m_rank = rank;
}
int Pirate::getFleet() const
{
    return m_fleetId;
}
void Pirate::setFleet(int fleetId)
{
    m_fleetId = fleetId;
}

bool Pirate::operator==(const Pirate &other) const
{
    return m_pirateId == other.m_pirateId;
}