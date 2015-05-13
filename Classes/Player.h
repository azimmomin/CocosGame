/*
 * Player.h
 *
 *  Created on: May 3, 2015
 *      Author: Azim Momin
 */

#ifndef __PLAYER__H_
#define __PLAYER__H_

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Player
{
private:
	Player( );                                          // Will be a singleton class
	Player( Player const& copy )             = delete;  // Copy Constructor ( Does nothing )
	Player& operator=( Player const& copy )  = delete;  // Assignment Operator ( Does nothing )

	Sprite*        _image                    = NULL;
	Vec2           _velocity;
	int            _jumpCount;
	bool           _isFalling;

public:
	void           Fall( );
	static Player& GetInstance( )                       // Meyer's Singleton for thread safety in C++11 onwards
	{
		static Player mPlayerInstance;
		return mPlayerInstance;
	};

	int            GetJumpCount( )  const;
	Sprite*        GetSprite( ) const;
	void           IncrementJumpCount( );
	void           Jump( );
	void           Move( );
	void           ResetJumpCount( );
	void           SetFalling( const bool isFalling );
	void           Shoot( );
	void           UpdateState( const PlayerAction &dir );
};

#endif /* __PLAYER__H_ */
