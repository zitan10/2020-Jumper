#include <iostream>
#include <string>
#include "pch.h"
using namespace std;

#include "olcConsoleGameEngine.h"


class JumperGame : public olcConsoleGameEngine
{
public:
	JumperGame()
	{
		m_sAppName = L"Jumper";
	}

private:
	float jumperPosition = 0.0f;
	float jumperVelocity = 0.0f;
	float jumperAcceleration = 0.0f;

	float gravity = 100.0f;

	float sectionWidth;
	list<int> listSection;

	float levelPosition = 0.0f;

	int jumpCount = 0;

	bool collision = false;
	bool newGame = false;


protected:
	// Called by olcConsoleGameEngine
	virtual bool OnUserCreate()
	{
		listSection = { 0, 0, 0, 0 };
		sectionWidth = (float)ScreenWidth() / (float)(listSection.size() - 1);

		return true;
	}

	// Called by olcConsoleGameEngine
	virtual bool OnUserUpdate(float fElapsedTime)
	{

		//New Game - initialize values
		if (newGame) {
			collision = false;
			newGame = false;
			listSection = { 0, 0, 0, 0 };
			jumperPosition = 0.0f;
			jumperVelocity = 0.0f;
			jumperAcceleration = 0.0f;
		}

		if (collision) {
			DrawString(1, 1, L"GAME OVER");
			DrawString(1, 2, L"PRESS SPACE TO RESET");
			//Space key resets game
			if (m_keys[VK_SPACE].bPressed) {
				newGame = true;
			}
		}

		else {

			if (m_keys[VK_SPACE].bPressed && jumpCount < 2 && jumperVelocity >= gravity / 5.0f) {
				//Stop falling, fly up
				jumperAcceleration = 0.0f;
				jumperVelocity = -gravity * 2 / 4.0f;
				jumpCount++;
			}
			else
				//Increase effect of gravity
				jumperAcceleration += gravity * fElapsedTime;

			if (jumperAcceleration >= gravity)
				jumperAcceleration = gravity;

			jumperVelocity += jumperAcceleration * fElapsedTime;
			jumperPosition += jumperVelocity * fElapsedTime;
			//14 is speed level
			levelPosition += 14.0f * fElapsedTime;

			//Roof is at position 1
			if (jumperPosition < 1) {
				jumperPosition = 1;
			}
			//Floor is at position 47
			else if (jumperPosition > 47) {
				jumperPosition = 47;
			}

			//Reset Double Jump when Jumper touches ground
			if (jumperPosition == 47) {
				jumpCount = 0;
			}

			//Get Random obstacles
			if (levelPosition > sectionWidth) {
				levelPosition -= sectionWidth;
				listSection.pop_front();
				int i = rand() % (ScreenHeight() - 20);
				if (i <= 10) i = 0;
				listSection.push_back(i);
			}

			//Clear Screen - remove image of bird old position
			Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

			int nSection = 0;
			for (auto s : listSection) {
				if (s != 0) {
					Fill(nSection * sectionWidth + 10 - levelPosition, ScreenHeight() - s, nSection * sectionWidth + 15 - levelPosition, ScreenHeight(), PIXEL_SOLID, FG_DARK_CYAN);
				}
				nSection++;
			}
			//Keep Jumper at same X position
			int JumperPositionX = (int)(ScreenWidth() / 3.0f);

			//Check if Jumper collided with obstacle
			collision = m_bufScreen[(int)(jumperPosition + 0) * ScreenWidth() + JumperPositionX].Char.UnicodeChar != L' ' ||
				m_bufScreen[(int)(jumperPosition + 0) * ScreenWidth() + JumperPositionX + 6].Char.UnicodeChar != L' ';

			//Draw the Jumper
			if (jumperVelocity > 0 && jumperPosition != 47)
			{
				//Jumper image when falling
				DrawString(JumperPositionX, jumperPosition, L"(xʖx)");
			}
			else
			{
				//Jumper image when jumping
				DrawString(JumperPositionX, jumperPosition, L"(°ʖ°)");
			}
		}
		return true;
	}
};


int main()
{
	// Use olcConsoleGameEngine derived app
	JumperGame game;
	game.ConstructConsole(80, 48, 16, 16);
	game.Start();
	return 0;
}