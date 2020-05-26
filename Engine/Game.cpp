/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
    :
    wnd(wnd),
    gfx(wnd),
    brd(gfx),
    rng(std::random_device()()),
    snek({ 3,3 }),
    goal(rng, brd, snek)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
    if (!gameIsOver)
    {
        if (wnd.kbd.KeyIsPressed(VK_UP))
        {
            if (!(delta_loc_old == Location({ 0,-1 })))
            {
                delta_loc = { 0,-1 };
            }
        }
        else if (wnd.kbd.KeyIsPressed(VK_DOWN))
        {
            if (!(delta_loc_old == Location({ 0,1 })))
            {
                delta_loc = { 0,1 };
            }
        }
        else if (wnd.kbd.KeyIsPressed(VK_LEFT))
        {
            if (!(delta_loc_old == Location({ -1,0 })))
            {
                delta_loc = { -1,0 };
            }
        }
        else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
        {
            if (!(delta_loc_old == Location({ 1,0 })))
            {
                delta_loc = { 1,0 };
            }
        }

        snekMovePeriod = (int)(10 / ((double)score / 15 + 1));
        if (++snekMoveCounter >= snekMovePeriod)
        {
            snekMoveCounter = 0;
            delta_loc_old = { delta_loc.x * -1,delta_loc.y * -1 };
            Location next = snek.GetNextHeadLocation(delta_loc);
            if (!brd.IsInBoard(next) || snek.IsInTileExceptEnd(next))
            {
                gameIsOver = true;
            }
            else
            {
                const bool eating = (next == goal.GetLocation());

                if (eating)
                {
                    score++;
                    snek.Grow();
                }

                snek.MoveBy(delta_loc);

                if (eating)
                {
                    goal.Respawn(rng, brd, snek);
                }
            }
        }

    }
    else
    {
        if (wnd.kbd.KeyIsPressed(VK_RETURN))
        {
            Reset();
        }
    }
}

void Game::ComposeFrame()
{
    snek.Draw(brd);
    goal.Draw(brd);
    if (gameIsOver)
    {
        //SpriteCodex::DrawGameOver(200, 200, gfx);
        SpriteCodex::DrawSnakePng(100, 100, gfx);
    }
}

void Game::Reset()
{
    delta_loc = { 1,0 };
    delta_loc_old = { -1,0 };
    snek.Reset({ 3,3 });
    goal.Respawn(rng, brd, snek);
    snekMovePeriod = 5;
    snekMoveCounter = 0;
    score = 0;
    gameIsOver = false;
}
