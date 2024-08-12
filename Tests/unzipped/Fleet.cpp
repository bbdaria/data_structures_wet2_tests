#include "Fleet.h"

int Fleet::getShips() const
{
    return m_numberOfShips;
}
void Fleet::addPirates(int pirates)
{
    m_numberOfPirates += pirates;
}

int Fleet::getPirates() const
{
    return m_numberOfPirates;
}
int Fleet::getId() const
{
    auto temp = shared_ptr<Fleet>(const_cast<Fleet *>(this));
    while (temp)
    {
        temp = temp->m_united;
    }
    return temp->m_newId;
}
void Fleet::setUnited(shared_ptr<Fleet> other, int id)
{
    m_united = other;
    bool layout = (other->getId() == id);
    m_offsetRank -= other->m_offsetRank;
    if (layout)
    {
        m_offsetRank += other->m_numberOfPirates;
    }
    else
    {
        other->m_offsetRank += m_numberOfPirates;
        m_offsetRank -= m_numberOfPirates;
    }
    other->m_numberOfPirates += m_numberOfPirates;
    other->m_numberOfShips += m_numberOfShips;
}
int Fleet::getRank() const
{
    int sum = 0;
    auto temp = shared_ptr<Fleet>(const_cast<Fleet *>(this));
    while (temp)
    {
        sum += temp->m_offsetRank;
        temp = temp->m_united;
    }
    return sum;
}
void Fleet::setNewId(int id)
{
    m_newId = id;
}
void Fleet::pathShortning(shared_ptr<Fleet> head)
{
    auto united = m_united;
    auto temp = shared_ptr<Fleet>(const_cast<Fleet *>(this));
    int rank = getRank() - head->m_offsetRank;
    while (united && united != head)
    {
        temp->m_united = head;
        rank -= temp->m_offsetRank;
        temp->m_offsetRank += rank;
        temp = united;
        united = united->m_united;
    }
}

bool Fleet::available()
{
    auto head = getUnited();
    return head->m_newId == m_id;
}
shared_ptr<Fleet> Fleet::getUnited()
{
    auto temp = shared_ptr<Fleet>(const_cast<Fleet *>(this));
    while (temp->m_united)
    {
        temp = temp->m_united;
    }
    pathShortning(temp);
    return temp;
}
bool Fleet::operator==(const Fleet &other) const
{
    return m_id == other.m_id;
}
