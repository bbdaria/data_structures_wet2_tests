#include "pirates24b2.h"
#include <memory>

oceans_t::oceans_t() = default;

oceans_t::~oceans_t() = default;

StatusType oceans_t::add_fleet(int fleetId)
{
	if (fleetId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	auto fleet = m_fleetId->find(fleetId);
	if (fleet)
	{
		return StatusType::FAILURE;
	}
	try
	{
		m_fleets->insert(make_shared<Fleet>(fleetId), fleetId);
		m_fleetId->insert(make_shared<int>(fleetId), fleetId);
	}
	catch (const std::bad_alloc &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType oceans_t::add_pirate(int pirateId, int fleetId)
{
	if (pirateId <= 0 || fleetId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	auto fleet = m_fleets->find(fleetId);
	if (!fleet || !fleet->available())
	{
		// if the fleet is not available this will return failure too
		return StatusType::FAILURE;
	}
	fleet = fleet->getUnited();
	auto pirate = m_pirates->find(pirateId);
	if (pirate)
	{
		return StatusType::FAILURE;
	}
	try
	{
		shared_ptr<Pirate> newPirate = make_shared<Pirate>(fleet->getPirates() - fleet->getRank() + 1, pirateId, 0, fleet->getId());
		m_pirates->insert(newPirate, pirateId);
		fleet->addPirates(1);
	}
	catch (const std::bad_alloc &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType oceans_t::pay_pirate(int pirateId, int salary)
{
	if (pirateId <= 0 || salary <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	auto pirate = m_pirates->find(pirateId);
	if (!pirate)
	{
		return StatusType::FAILURE;
	}
	pirate->addCoins(salary);
	return StatusType::SUCCESS;
}

output_t<int> oceans_t::num_ships_for_fleet(int fleetId)
{
	if (fleetId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	auto fleet = m_fleets->find(fleetId);
	if (!fleet || !fleet->available())
	{
		return StatusType::FAILURE;
	}
	fleet = fleet->getUnited();
	return fleet->getShips();
}

output_t<int> oceans_t::get_pirate_money(int pirateId)
{
	if (pirateId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	auto pirate = m_pirates->find(pirateId);
	if (!pirate)
	{
		return StatusType::FAILURE;
	}
	return pirate->getCoins();
}

StatusType oceans_t::unite_fleets(int fleetId1, int fleetId2)
{
	if (fleetId1 <= 0 || fleetId2 <= 0 || fleetId1 == fleetId2)
	{
		return StatusType::INVALID_INPUT;
	}
	auto fleet1 = m_fleets->find(fleetId1);
	auto fleet2 = m_fleets->find(fleetId2);
	if (!fleet1 || !fleet2 || !fleet1->available() || !fleet2->available())
	{
		return StatusType::FAILURE;
	}
	if (fleet1->getPirates() == 0 || fleet2->getPirates() == 0)
	{
		return StatusType::FAILURE;
	}
	int id = fleet1->getPirates() >= fleet2->getPirates() ? fleet1->getId() : fleet2->getId();
	auto smaller = fleet1->getShips() < fleet2->getShips() ? fleet1 : fleet2;
	auto larger = smaller == fleet1 ? fleet2 : fleet1;
	smaller->setUnited(larger, id);
	larger->setNewId(id);
	return StatusType::SUCCESS;
}

StatusType oceans_t::pirate_argument(int pirateId1, int pirateId2)
{
	if (pirateId1 <= 0 || pirateId2 <= 0 || pirateId1 == pirateId2)
	{
		return StatusType::INVALID_INPUT;
	}
	auto pirate1 = m_pirates->find(pirateId1);
	auto pirate2 = m_pirates->find(pirateId2);
	if (!pirate1 || !pirate2)
	{
		return StatusType::FAILURE;
	}
	auto fleet1 = m_fleets->find(pirate1->getFleet());
	auto fleet2 = m_fleets->find(pirate2->getFleet());
	bool answer = fleet1->getUnited() == fleet2->getUnited();
	if (!answer)
	{
		return StatusType::FAILURE;
	}
	int rank1 = pirate1->getRank() + fleet1->getRank();
	int rank2 = pirate2->getRank() + fleet2->getRank();
	pirate1->addCoins(rank2 - rank1);
	pirate2->addCoins(rank1 - rank2);
	return StatusType::SUCCESS;
}
