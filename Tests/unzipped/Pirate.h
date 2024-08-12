#pragma once
#include <memory>
using namespace std;

/*
    ___
    \_/
     |._
     |'."-._.-""--.-"-.__.-'/
     |  \       .-.        (
     |   |     (@.@)        )
     |   |   '=.|m|.='     /
     |  /    .='`"``=.    /
     |.'                 (
     |.-"-.__.-""-.__.-"-.)
     |
     |
*/
class Pirate
{
    int m_rank;
    int m_pirateId;
    int m_coins;
    int m_fleetId;

public:
    ~Pirate();
    /*
     * @brief            pirate constructor
     * @param id         pirate id
     * @param cannons    number of coins
     */
    Pirate(int rank, int id, int coins, int fleetId);

    /*
     * @breif            returns the number of coins of a ship
     * @return           m_coins
     */
    int getCoins() const;

    /*
     * @breif            returns the id of the pirate
     * @return           m_pirateId
     */
    int getId() const;

    /*
     * @breif            adds an amount of coins to a pirate
     * @param number     amount of coins to add
     */
    void addCoins(int number);
    /*
     * @brief            returns the entry index of the ship
     * @return           m_entry
     */
    int getRank() const;

    /*
     * @brief            sets the entry field of a pirate
     * @param entry      index of insert to the ship
     */
    void setRank(int rank);

    int getFleet() const;
    void setFleet(int fleetId);
    bool operator==(const Pirate &other) const;
};