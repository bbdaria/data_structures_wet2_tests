#pragma once
#include "Pirate.h"
#include "HashMap.h"

class Fleet
{
    int m_id;
    int m_numberOfShips;
    int m_numberOfPirates;
    shared_ptr<Fleet> m_united;

    int m_offsetRank;
    int m_newId;

public:
    Fleet(int id) : m_id(id),
                    m_numberOfShips(1),
                    m_numberOfPirates(0),
                    m_united(nullptr),
                    m_offsetRank(0),
                    m_newId(id)
    {
    }
    ~Fleet() = default;
    int getShips() const;
    void addPirates(int pirates);
    int getPirates() const;
    int getId() const;
    void setUnited(shared_ptr<Fleet> other, int id);
    int getRank() const;
    void pathShortning(shared_ptr<Fleet> head);
    void setNewId(int id);
    shared_ptr<Fleet> getUnited();
    bool available();
    bool operator==(const Fleet &other) const;
};