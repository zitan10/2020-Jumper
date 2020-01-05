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
		m_sAppName = L"Flappy Bird";
	}

private:
	float jumperPosition = 0.0f;
	float jumperVelocity = 0.0f;
	float jumperAcceleration = 0.0f;

	float gravity = 100.0f;

	float sectionWidth;
	list<int> listSection;

	float levelPosition = 0.0f;

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
		if (m_keys[VK_SPACE].bPressed && jumperPosition == 40) {
			//Stop falling, fly up
			jumperAcceleration = 0.0f;
			jumperVelocity = -gravity / 4.0f;
		}
		else
			//Increase effect of gravity
			jumperAcceleration += gravity * fElapsedTime;

		if (jumperAcceleration >= gravity)
			jumperAcceleration = gravity;

		jumperVelocity += jumperAcceleration * fElapsedTime;
		jumperPosition += jumperVelocity * fElapsedTime;

		//Floor is at position 40
		if (jumperPosition > 40) {
			jumperPosition = 40;
		}

		//14 is speed level
		levelPosition += 14.0f * fElapsedTime;

		if(levelPosition > sectionWidth) {
			levelPosition -= sectionWidth;
		}

		//Clear Screen - remove image of bird old position
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		//Keep Bird at same X position
		int JumperPositionX = (int)(ScreenWidth() / 3.0f);

		//Draw Bird
		if (jumperVelocity > 0)
		{
			/*
			DrawString(JumperPositionX, jumperPosition + 0, L"\\\\\\");
			DrawString(JumperPositionX, jumperPosition + 1, L"<\\\\\\=Q");
			*/
			DrawString(JumperPositionX, jumperPosition + 0, L"         /  \~~~/  \"");
			DrawString(JumperPositionX, jumperPosition + 1, L"   ,----(     ..    )");
			DrawString(JumperPositionX, jumperPosition + 2, L"  /      \__     __/");
			DrawString(JumperPositionX, jumperPosition + 3, L" /|         (\  |(");
			DrawString(JumperPositionX, jumperPosition + 4, L"^ \   /___\  /\ |");
			DrawString(JumperPositionX, jumperPosition + 5, L"  |__|   |__|-");
		}
		else
		{
			/*
			DrawString(JumperPositionX, jumperPosition + 0, L"<///=Q");
			DrawString(JumperPositionX, jumperPosition + 1, L"///");
			*/
			DrawString(JumperPositionX, jumperPosition + 0, L"         /  \~~~/  \"");
			DrawString(JumperPositionX, jumperPosition + 1, L"   ,----(     ..    )");
			DrawString(JumperPositionX, jumperPosition + 2, L"  /      \__     __/");
			DrawString(JumperPositionX, jumperPosition + 3, L" /|         (\  |(");
			DrawString(JumperPositionX, jumperPosition + 4, L"^ \   /___\  /\ |");
			DrawString(JumperPositionX, jumperPosition + 5, L"  |__|   |__|-");
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