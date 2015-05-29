/*
 * EntityManager.h
 *
 *  Created on: May 14, 2015
 *      Author: Azim Momin
 */

#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "cocos2d.h"
#include <list>
#include "Projectile.h"

USING_NS_CC;

/** EntityManager.h
 *  Manages all PASSIVE entities. I.E. the ones not under direct control of the player.
 */
namespace EntityManager
{
	void AddEntity( Layer *layer, PassiveEntity *p );
//	void AddEntity( Layer *layer );
	void UpdateAll( Layer *layer );
	void UnloadEntityManager( );

	//static std::list< PassiveEntity* > sPassiveEntities;
	//static std::list< PassiveEntity* > sPendingEntities;
	static std::list< PassiveEntity* > sPassiveEntities;
	static std::list< PassiveEntity* > sPendingEntities;
	static bool                        sIsUpdating = false;
};

#endif // __ENTITYMANAGER_H__

