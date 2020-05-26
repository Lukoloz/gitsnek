#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(const Location& loc, Color c)
{
	gfx.DrawRectDim(loc.x * dimension + 1, loc.y * dimension + 1, dimension - 2, dimension - 2, c);
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInBoard(const Location& target) const
{
	return target.x >= 0 && target.x < width
		&& target.y >= 0 && target.y < height;
}
