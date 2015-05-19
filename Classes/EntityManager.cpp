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
			layer->addChild( e );
		}
		else
		{
			sPassiveEntities->push_back( e );
		}
	}

	void UpdateAll( Layer *layer )
	{
		sIsUpdating = true;

		std::list< PassiveEntity* > ::iterator it = sPassiveEntities->begin( );
		for ( ; it != sPassiveEntities->end( ); it += 1 )
		{
			it->Update( );
		}

		sIsUpdating = false;

		std::list< PassiveEntity* > ::iterator it = sPendingEntities->begin( );
		for ( ; it != sPendingEntities->end( ); it += 1 )
		{
			sPassiveEntities->push_back( it );
			layer->addChild( it );
		}
		sPassiveEntities->clear( );

		std::list< PassiveEntity* > ::iterator it = sPassiveEntities->begin( );
		while ( it != sPassiveEntities->end( ) )
		{
			if ( !layer->getBoundingBox( ).containsPoint( it->GetSprite( )->getPosition( ) ) )
			{
				it = list->erase( it );
			}
			else
			{
				it += 1;
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
