/*
 * Player.h
 *
 *  Created on: May 3, 2015
 *      Author: Azim Momin
 */

#ifndef __PLAYER__H_
#define __PLAYER__H_

#include "Definitions.h"
#include "Projectile.h"
#include "Entity.h"

class Player : public Entity
{
private:
	Player( );                                          // Will be a singleton class
	Player( Player const& copy )             = delete;  // Copy Constructor ( Does nothing )
	Player& operator=( Player const& copy )  = delete;  // Assignment Operator ( Does nothing )

	Vec2           _velocity;
	int            _jumpCount;
	bool           _isFalling;
	int            _numProjectiles;
public:
	virtual        ~Player( );
	void           Fall( );
	static Player& GetInstance( )                       // Meyer's Singleton for thread safety in C++11 onwards
	{
		static Player mPlayerInstance;
		return mPlayerInstance;
	};

	int            GetJumpCount( )  const;
	void           IncrementJumpCount( );
	void           Jump( );
	void           Move( );
	void           ResetJumpCount( );
	void           SetFalling( const bool isFalling );
	void           Shoot( Layer *layer );
	void           UpdateState( const PlayerAction &dir );
};

#endif /* __PLAYER__H_ */
