/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* Player class
* Ben A, Kaleb, Reese, Ethan, Thomas, Adam, Devon
* Player Class (inherits from Character class)
* Inherits sprite functionality from Sprite class.
* Inherits character functionality from Character class.
* Player class represents the player character in the game.
* It handles player movement, rendering, and attacking functionality.
---------------------------------------------------------------------------------------------------------------------------------------*/


#pragma once
#include "raylib.h"
#include "character.h"
#include "sheetSprite.h"
#include "animation.h"
#include "enemy.h"
#include "globals.h"

const float WALK_TIMER_MAX = 0.5f;                       //Maximum allowed time between "walking" sound effect triggers
const int INTERACTION_RANGE = Settings::TILE_SIZE * 2;   //The range within which the player can interact with interactables, in pixels

class Player : public Character
{

	private:

	float attackRange;                            //Attack radius
	int attackDamage;                             //Damage per hit
	int health;                                   //Player health
	int dodgeCooldown;                            //Cooldown length of dodge ability
	float walkTimer;                              //Time between steps
	SheetSprite sprite;                           //Set of 4 sprites for the player
	Animation animation = Animation( 4, 0.15 );   //Players movement animation
	bool isInvincible = false;                    //Tracks if the player is invincible-KF
	float invincibilityTimer = 0.0f;              //Timer for invincibility frames-KF
	const float invincibilityDuration = 0.7f;     //Duration of invincibility in seconds-KF

	void interactWithNearest( );                  //Interacts with the nearest Interactable if there is one in range -devon

	public:

	const static int maxHp = 5;                   //The max value that player hp can be, and the value it starts at

	/*-----------------------------------------------------------------------------------------------------------------------------------
	 * @brief : Parameterized Class constructor.
	------------------------------------------------------------------------------------------------------------------------------------*/
	Player( int id, Vector2 position )
		: Character( id, position ), attackRange( 25.0f ), attackDamage( 1 ), health( maxHp ), dodgeCooldown( 0 )
	{
		Animation animation = Animation( 4, 0.1 );
		sprite = SheetSprite( "playerWalk1", { 16, 0, 16, 16 }, position, position.y );
		walkTimer = 0.0f;
	}

	/*-----------------------------------------------------------------------------------------------------------------------------------
	 * @brief : Accessors for Invicibility Frame
	------------------------------------------------------------------------------------------------------------------------------------*/
	void setInvincible( bool invincible );   //Sets the invincibility state and resets the timer if invincible.
	void updateInvincibility( );
	bool getIsInvincible( ) const
	{
		return isInvincible;
	}
	/*-----------------------------------------------------------------------------------------------------------------------------------
	 * @brief : Getter for the Player object's health
	------------------------------------------------------------------------------------------------------------------------------------*/
	int getHealth( )
	{
		return health;
	}

	void updateDirection( ) override;                                 //Sets the movement direction of the character based on control input.
	void onTick( const std::vector<Rectangle> colliders ) override;   //Updates the state of the player during a single frame.
	void onRender( ) override;                                        //Renders the player on screen.
	void attack( std::vector<Enemy*>& enemies );                      //Attacks enemy objects if within range and key is pressed.
	void defend( std::vector<Enemy*>& enemies );                      //Allows the player to defend against enemy attacks.
	void takeDamage( int damage );                                    //Decrements player health based off enemy damage and checks for player death.
	void healHp( int hp );                                            //Heals the player by hp amount, up until the max hp
	void dodge( );                                                    //Increases players speed by 1.4 times for 1 second when input and cools down for another 2 seconds
};

