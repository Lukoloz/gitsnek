#include "Snake.h"

Snake::Snake(const Location& in_loc)
{
	segments[0].InitHead(in_loc);
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (int i = nSegments - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

Location Snake::GetNextHeadLocation(const Location& delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

bool Snake::IsInTile(const Location& target) const
{
	for (int i = 0; i < nSegments; i++)
	{
		if (target == segments[i].GetLocation())
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsInTileExceptEnd(const Location& target) const
{
	for (int i = 0; i < nSegments - 1; i++)
	{
		if (target == segments[i].GetLocation())
		{
			return true;
		}
	}
	return false;
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax)
	{
		segments[nSegments].InitBody();
		nSegments++;
		setColors();
	}
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < nSegments; i++)
	{
		segments[i].Draw(brd);
	}
}

void Snake::Reset(const Location& in_loc)
{
	nSegments = 1;
	segments[0].InitHead(in_loc);
	nextBodyColor = { unsigned char(0), unsigned char(255), unsigned char(0) };
}

void Snake::setColors()
{
	Color temp_c;
	for (int i = 1; i < nSegments; i++)
	{
		temp_c = { unsigned char(0),unsigned char(255 - (i - 1) * 150 / (nSegments - 1)) ,unsigned char(0) };
		segments[i].setColor(temp_c);
	}
}

void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody()
{
	c = Snake::bodyColor;
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

void Snake::Segment::setColor(const Color& in_c)
{
	c = in_c;
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
