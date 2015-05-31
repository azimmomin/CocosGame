/*
 * EntityManager.cpp
 *
 *  Created on: May 14, 2015
 *      Author: Azim Momin
 */
#define COCOS2D_DEBUG 1
#include "EntityManager.h"
#include <iostream>

namespace EntityManager
{
	void AddEntity( Layer *layer, PassiveEntity *p )
	{
		if ( sIsUpdating )
		{
			sPendingEntities.push_back( p );
		}
		else
		{
			sPassiveEntities.push_back( p );
			layer->addChild( p->GetSprite( ), ZOrder::FOREGROUND, p->GetTag( ) );
		}
	}

	void UpdateAll( Layer *layer )
	{
		// Update all entities currently checked into this manager.
		sIsUpdating = true;

		std::list< PassiveEntity* > ::iterator it = sPassiveEntities.begin( );
		for ( ; it != sPassiveEntities.end( ); it++ )
		{
			(*it)->Update( );
		}

		sIsUpdating = false;

		// Check in all entities that were added while we were updating.
		// These will be updated in the next frame.
		it = sPendingEntities.begin( );
		for ( ; it != sPendingEntities.end( ); it++ )
		{
			sPassiveEntities.push_back( *it );
			layer->addChild( (*it)->GetSprite( ) );
		}
		sPendingEntities.clear( ); // clear pending list. note that the projectile
		                           // hasn't been deleted, just transferred to another list.

		// Remove any entities that are no longer on the screen.
		it = sPassiveEntities.begin( );
		while ( it != sPassiveEntities.end( ) )
		{
			if ( !layer->getBoundingBox( ).containsPoint( (*it)->GetSprite( )->getPosition( ) ) )
			{
				// delete PassiveEntity and the remove pointer from list.
				CCLOG("removing projectile");
				//PassiveEntity *holder = *it;
				//layer->removeChildByTag( (*it)->GetTag( ), false );
				it = sPassiveEntities.erase( it );
				// need to remove projectile from layer here.
				CCLOG( "After erasing." );
				//delete holder;
				CCLOG( "finished removing projectile" );
			}
			else
			{
				it++;
			}
		}
	}

	void UnloadEntityManager( )
	{
		std::list< PassiveEntity* >::iterator it = sPendingEntities.begin( );
		for ( ; it != sPendingEntities.end( ); it++ )
		{
			delete *it;
		}
		it = sPassiveEntities.begin( );
		for ( ; it != sPendingEntities.end( ); it++ )
		{
			delete *it;
		}
		sPendingEntities.clear( );
		sPassiveEntities.clear( );
	}
}
