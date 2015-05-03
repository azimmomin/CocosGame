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
	Sprite* _image  = NULL;
	Player( );                                          // Will be a singleton class
	Player( Player const& copy )             = delete;  // Copy Constructor ( Does nothing )
	Player& operator=( Player const& copy )  = delete;  // Assignment Operator ( Does nothing )
public:
	static Player& GetInstance( )                       // Meyer's Singleton for thread safety in C++11 onwards
	{
		static Player mPlayerInstance;
		return mPlayerInstance;
	}
	Sprite* GetSprite( ) const;
	void Move( const MoveDirection dir );
};

#endif /* __PLAYER__H_ */
