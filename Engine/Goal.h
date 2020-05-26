#pragma once
#include <random>
#include "Board.h"
#include "Snake.h"

class Goal
{
public:
	Goal(std::mt19937& rng, const Board& brd, const Snake& snek);
	Location GetLocation() const;
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snek);
	void Draw(Board& brd);
private:
	static constexpr Color c = Colors::Red;
	Location loc;
};