/*
 * EntityManager.h
 *
 *  Created on: May 14, 2015
 *      Author: Azim Momin
 */

#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "cocos2d.h"
#include <vector>
#include "Projectile.h"

USING_NS_CC;

class EntityManager
{
public:

private:
	EntityManager( );                                                 // Will be a singleton class
	EntityManager( EntityManager const& copy )             = delete;  // Copy Constructor ( Does nothing )
	EntityManager& operator=( EntityManager const& copy )  = delete;  // Assignment Operator ( Does nothing )

	vector<Entity*> _bullets;
public:
	void           AddEntity( Entity entity );
	static Player& GetInstance( )                       // Meyer's Singleton for thread safety in C++11 onwards
	{
		static Player mPlayerInstance;
		return mPlayerInstance;
	};
};
#endif /* __ENTITYMANAGER_H__ */
