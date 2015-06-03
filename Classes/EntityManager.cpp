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

		// Remove any projectile entities that are no longer on the screen.
		// As of right now we are not going to delete enemies that go off the screen.
		// Note that this means that a bullet that flies off screen will not kill
		// an enemy that is off the screen.
		it = sPassiveEntities.begin( );
		while ( it != sPassiveEntities.end( ) )
		{
			if ( !layer->getBoundingBox( ).containsPoint( (*it)->GetSprite( )->getPosition( ) )
				 && (*it)->GetTag( ) == EntityTag::PROJECTILE )
			{
				// delete PassiveEntity and the remove pointer from list and from Game layer.
				layer->removeChild( (*it)->GetSprite( ), true );
				it = sPassiveEntities.erase( it );
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
