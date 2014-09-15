#include "AIE.h"
#include <iostream>
#include <math.h>
#include <MyMaths.h>
#include <cmath>


const int iScreenWidth = 672;		//GLOBALS
const int iScreenHeight = 780;
const char* gameTitle = "spess invadur";
const char* cScore1;
const char* cScore2;
unsigned int iArcadeMarquee;
float fDeltaT;
const char* pInvadersFont = "./fonts/invaders.fnt";
float fKeyPastOne = 0, fKeyPastTwo = 0;

//DECLARING STATES
void Load();
void UpdateGameState();
void UpdateMainMenu();

struct PlayerCannon					//CREATING A PLAYER
{
	//ALL PUBLICS BECAUSE WHO CARES RIGHT NOW I'M GOING TO REWRITE IT TOMORROW
	unsigned int iSpriteID;
	float Width;
	float Height;
	float x;
	float y;
	void SetSize(float a_fWidth, float a_fHeight)		//SETTING THE SIZE
	{
		Width = a_fWidth;
		Height = a_fHeight;
	}

	void SetPosition(float a_x, float a_y)			//SETTING THE POSITION
	{
		x = a_x;
		y = a_y;
	}

	unsigned int iMoveLeftKey, iMoveRightKey;
	void SetMovementKeys(unsigned int a_moveleft, unsigned int a_moveRight)			//MOVEMENT KEYS
	{
		iMoveLeftKey = a_moveleft;
		iMoveRightKey = a_moveRight;
	}

	unsigned int iLeftMovementExtreme, iRightMovementExtreme;
	void SetMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme)			//EXTREMES
	{
		iLeftMovementExtreme = a_leftExtreme;
		iRightMovementExtreme = a_rightExtreme;
	}
	void Move(float a_fTimeStep, float a_fSpeed)		//MOVEMENT CODE
	{

		/*if (IsKeyDown(iMoveLeftKey) && IsKeyDown(iMoveRightKey))
		{
			if (fKeyPastOne = 1 && fKeyPastTwo == 0)
			{
				x -= a_fTimeStep * a_fSpeed;
				if (x > (iRightMovementExtreme - fWidth*.5f))
				{
					x = (iRightMovementExtreme - fWidth*.5f);
				}
			}
			else
			{
				x -= a_fTimeStep * a_fSpeed;
				if (x < (iLeftMovementExtreme + fWidth*.5f))
				{
					x = (iLeftMovementExtreme + fWidth*.5f);
				}
			}
		}
		else
		{
			if (IsKeyDown(iMoveLeftKey))
			{
				fKeyPastOne = 1;
				x -= a_fTimeStep * a_fSpeed;
				if (x < (iLeftMovementExtreme + fWidth*.5f))
				{
					x = (iLeftMovementExtreme + fWidth*.5f);
				}
			}
			else
				fKeyPastOne = 0;
			if (IsKeyDown(iMoveRightKey))
			{
				fKeyPastTwo = 1;
				x += a_fTimeStep * a_fSpeed;
				if (x > (iRightMovementExtreme - fWidth*.5f))
				{
					x = (iRightMovementExtreme - fWidth*.5f);
				}
			}
			else
				fKeyPastTwo = 0;
		}*/
		if (IsKeyDown(iMoveLeftKey))
		{
			x -= a_fTimeStep * a_fSpeed;
			if (x < (iLeftMovementExtreme + Width*.5f))
			{
				x = (iLeftMovementExtreme + Width*.5f);
			}
		}
		if (IsKeyDown(iMoveRightKey))
		{
			x += a_fTimeStep * a_fSpeed;
			if (x >(iRightMovementExtreme - Width*.5f))
			{
				x = (iRightMovementExtreme - Width*.5f);
			}
		}
		MoveSprite(iSpriteID, x, y);
	}
	Box2D GetBox2D()			//COLLISION
	{
		Box2D b(x, y, x + (.5f * Width), y + (.5f * Height));
		//Box2D b(5, 5, 15, 15);
		//return Box2D(5,5,15,15);
		return b;
	}
};
PlayerCannon player;

char pkScore1[10] = "00000";		//MORE GLOBALS
char pkHighScore[10] = "00000";
char pkScore2[10] = "00000";
char pkCredit[10] = "99";

enum GAMESTATES
{
	eMAIN_MENU,
	eGAMEPLAY,
	eEND
};
GAMESTATES eCurrentState = eMAIN_MENU;

int FUCK(int FUCKING_NOTHING)		//GOD DAMNIT
{
	FUCKING_NOTHING = 0;
	return FUCKING_NOTHING;
}
struct Enemy						//ENEMY STRUCT
{
private:		//PRIVATES
	float fWidth, fHeight, x, y;
	unsigned int iLeftMovementExtreme, iRightMovementExtreme;
public:			//PUBLICS
	bool alive;
	unsigned int iSpriteID;
	float iDirection;

	void SetLoc(float a_x, float a_y)		//SETTING THE LOCATION
	{
		x = a_x;
		y = a_y;
	}
	void SetSize(float a_fWidth, float a_fHeight)		//SETTING THE SIZE
	{
		fWidth = a_fWidth;
		fHeight = a_fHeight;
	}
	//GETTING X AND Y
	float GetX()
	{
		return x;
	}
	float GetY()
	{
		return y;
	}
	void SetMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme)		//SETTING EXTREMES
	{
		iLeftMovementExtreme = a_leftExtreme;
		iRightMovementExtreme = a_rightExtreme;
	}
	void GoForward(float a_DeltaT)				//GOING FORWARD
	{
		x += (a_DeltaT * iDirection * iScreenWidth);
	}
	bool SwitchCheck()			//CHECKING EXTREMES AGAINST LOCATION
	{
		if (x < iLeftMovementExtreme || x > iRightMovementExtreme)
			return true;
		else
			return false;
	}
	Box2D GetBox2D()			//COLLISION BOX
	{
		Box2D b(x, y, x + fWidth, y + fHeight);
		return b;
	}
};
Enemy Aliens[15];

void CreateEnemies()				//DECLARING THE ENEMY CREATION
{
	float fEnemyX = iScreenWidth * 0.2f;
	float fEnemyY = iScreenHeight * 0.8f;
	float fTempLeft = 0, fTempRight = 0;
	for (int i = 0; i < 15; ++i)
	{
		Aliens[i].SetSize(32, 27);
		Aliens[i].SetMovementExtremes(67 + fTempLeft, 288 + fTempRight);
		Aliens[i].iSpriteID = CreateSprite("./images/invaders/invaders_1_00.png", 32, 27, true);
		Aliens[i].iDirection = .05f;
		Aliens[i].SetLoc(fEnemyX, fEnemyY);
		Aliens[i].alive = true;
		MoveSprite(Aliens[i].iSpriteID, Aliens[i].GetX(), Aliens[i].GetY());
		fEnemyX += 0.12f * iScreenWidth;
		fTempLeft += 0.12 * iScreenWidth;
		fTempRight += 0.12 * iScreenWidth;
		if (fEnemyX >= iScreenWidth * 0.8f)
		{
			fTempLeft = 0;
			fTempRight = 0;
			fEnemyX = iScreenWidth * 0.2f;
			fEnemyY = fEnemyY - 30;
		}
	}
}


int main( int argc, char* argv[] )
{	
    Initialise(iScreenWidth, iScreenHeight, false, gameTitle);
	Load();
	AddFont(pInvadersFont);
    do
    {
		ClearScreen();
		fDeltaT = GetDeltaTime();
		//END STATE CHANGE
		if (IsKeyDown(GLFW_KEY_ESCAPE))
			eCurrentState = eEND;
		//SET FONT
		SetFont(pInvadersFont);
		switch (eCurrentState)
		{
		case eMAIN_MENU:
			UpdateMainMenu();
			break;
		case eGAMEPLAY:
			UpdateGameState();
			break;
		case eEND:
			return 0;
		default:
			break;
		}
    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}

void Load()
{
    SetBackgroundColour(SColour(0, 40, 0, 255));
	iArcadeMarquee = CreateSprite("./images/oh-hi-marq.png", 750, 800, true);
	MoveSprite(iArcadeMarquee, 330, 380);
	player.SetSize(64.f, 32.f);
	player.SetMovementKeys('Z', 'X');
	player.iSpriteID = CreateSprite("./images/cannon.png",player.Width,player.Height,true);
	player.x = iScreenWidth * 0.5f;
	player.y = 80.f;
	player.SetMovementExtremes(32, 640);
	/*Point2D point(5.f, 5.f);
	Box2D box(0.f, 0.f, 10.f, 10.f);
	Box2D box2(5.f, 5.f, 15.f, 15.f);
	if (CheckBoxBox(box, box2) && CheckPointBox(point,box))
	{
		eCurrentState = eEND;
	}*/
};

void UpdateMainMenu()
{
	DrawString("Insert Coins", iScreenWidth*0.37f, iScreenHeight * 0.5f);
	DrawString("Credits", iScreenWidth * 0.41f, iScreenHeight * 0.4f);
	for (int a_i = 200; a_i < 480; a_i = a_i + 2)
	{
		DrawLine(200, a_i, 450, a_i, SColour(0x00, 0x00, 0x00, 0xFF)); //SCANLINES
	}
			if (IsKeyDown(GLFW_KEY_ENTER) && FUCK(0) == 0)
			{
				eCurrentState = eGAMEPLAY;
				CreateEnemies();
				int dudeguy = CreateSprite("./images/dudeguy.png", iScreenWidth, iScreenHeight, true);
				MoveSprite(dudeguy, iScreenWidth * 0.5f, iScreenHeight * 0.5f);
				DrawSprite(dudeguy);
			}
	DrawSprite(iArcadeMarquee);
};

void UpdateGameState()				//UPDATING THE GAME STATE
{
	if (IsKeyDown(GLFW_KEY_S), IsKeyDown(GLFW_KEY_H), IsKeyDown(GLFW_KEY_I), IsKeyDown(GLFW_KEY_T))
	{
		int dudeguy = CreateSprite("./images/dudeguy.png", iScreenWidth, iScreenHeight, true);
		MoveSprite(dudeguy, iScreenWidth * 0.5f, iScreenHeight * 0.5f);
		DrawSprite(dudeguy);
	}
	player.Move(fDeltaT, 100);
	MoveSprite(player.iSpriteID, player.x, player.y);
	DrawSprite(player.iSpriteID);

	bool EnemyTurn = false;

	for (int i = 0; i < 15; i++)
	{
		if (Aliens[i].SwitchCheck())
			EnemyTurn = true;
	}
	for (int i = 0; i < 15; i++)
	{
		if (EnemyTurn)
		{
			Aliens[i].SetLoc(Aliens[i].GetX(), Aliens[i].GetY() - 10);
			Aliens[i].iDirection *= -1.06;
		}
		Aliens[i].GoForward(fDeltaT);
		MoveSprite(Aliens[i].iSpriteID, Aliens[i].GetX(), Aliens[i].GetY());
		DrawSprite(Aliens[i].iSpriteID);
	}
	

	DrawString("SCORE < 1 >", iScreenWidth * 0.025f, iScreenHeight - 2);
	DrawString("HI-SCORE", iScreenWidth * 0.4f, iScreenHeight - 2);
	DrawString("SCORE < 2 >", iScreenWidth * 0.75f, iScreenHeight - 2);
	DrawString("3", iScreenWidth * 0.025f, .05f * iScreenHeight);
	DrawString("CREDIT 00", iScreenWidth * .75f, 0.05f * iScreenHeight);
	DrawLine(0, iScreenHeight * .075f, iScreenWidth, iScreenHeight * .075f, SColour(0x00, 0xFC, 0x00, 0xFF));
	DrawLine(0, iScreenHeight * .075f - 1, iScreenWidth, iScreenHeight * .075f - 1, SColour(0x00, 0xFC, 0x00, 0xFF));
	DrawLine(0, iScreenHeight * .075f - 2, iScreenWidth, iScreenHeight * .075f - 2, SColour(0x00, 0xFC, 0x00, 0xFF));
	for (int a_i = 0; a_i < 780; a_i = a_i + 2)
	{
		DrawLine(0, a_i, iScreenWidth, a_i, SColour(0x00, 0x00, 0x00, 0xFF)); //SCANLINES
	}
	for (int i = 0; i < 15; i++)
	{
		if (CheckBoxBox(player.GetBox2D(), Aliens[i].GetBox2D()))
			eCurrentState = eEND;
	}
};
