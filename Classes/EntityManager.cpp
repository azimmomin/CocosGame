/*
 * EntityManager.cpp
 *
 *  Created on: May 14, 2015
 *      Author: Azim Momin
 */

#include "EntityManager.h"

namespace EntityManager
{
	void AddEntity( PassiveEntity *e, Layer *layer )
	{
		if ( sIsUpdating )
		{
			sPendingEntities->push_back( e );
			layer->addChild( e->GetSprite( ) );
		}
		else
		{
			sPassiveEntities->push_back( e );
		}
	}

	void UpdateAll( Layer *layer )
	{
		// Update all entities currently checked into this manager.
		sIsUpdating = true;

		std::list< PassiveEntity* > ::iterator it = sPassiveEntities->begin( );
		for ( ; it != sPassiveEntities->end( ); it++ )
		{
			(*it)->Update( );
		}

		sIsUpdating = false;

		// Check in all entities that were added while we were updating.
		// These will be updated in the next frame.
		it = sPendingEntities->begin( );
		for ( ; it != sPendingEntities->end( ); it++ )
		{
			sPassiveEntities->push_back( *it );
			layer->addChild( (*it)->GetSprite( ) );
		}
		sPassiveEntities->clear( );

		// Remove any entities that are no longer on the screen.
		it = sPassiveEntities->begin( );
		while ( it != sPassiveEntities->end( ) )
		{
			if ( !layer->getBoundingBox( ).containsPoint( (*it)->GetSprite( )->getPosition( ) ) )
			{
				it = sPassiveEntities->erase( it );
			}
			else
			{
				it++;
			}
		}
	}

	void UnloadEntityManager( )
	{
		sPendingEntities->clear( );
		delete sPendingEntities;
		sPassiveEntities->clear( );
		delete sPassiveEntities;
	}
}
