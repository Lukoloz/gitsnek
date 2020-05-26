#pragma once
#include "Colors.h"
#include "Location.h"
#include "Board.h"

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody();
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;
		void setColor(const Color& in_c);
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& in_loc);
	void MoveBy(const Location& delta_loc);
	Location GetNextHeadLocation(const Location& delta_loc) const;
	bool IsInTile(const Location& target) const;
	bool IsInTileExceptEnd(const Location& target) const;
	void Grow();
	void Draw(Board& brd) const;
	void Reset(const Location& in_loc);
	void setColors();
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = { unsigned char(0), unsigned char(255), unsigned char(0) };
	Color nextBodyColor = { unsigned char (0), unsigned char (255), unsigned char (0) };
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};