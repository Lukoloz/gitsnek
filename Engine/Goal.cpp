#include "Goal.h"

Goal::Goal(std::mt19937& rng, const Board& brd, const Snake& snek)
{
	Respawn(rng, brd, snek);
}

Location Goal::GetLocation() const
{
	return loc;
}

void Goal::Respawn(std::mt19937& rng, const Board& brd, const Snake& snek)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);
	Location newLoc;

	do
	{
		newLoc = { xDist(rng),yDist(rng) };
	} while (snek.IsInTile(newLoc));

	loc = newLoc;
}

void Goal::Draw(Board& brd)
{
	brd.DrawCell(loc, c);
}