/*
 * Projectile.cpp
 *
 *  Created on: May 13, 2015
 *      Author: Azim Momin
 */

#include "Projectile.h"

Projectile::Projectile( Vec2 position )
{
	_entitySprite = Sprite::create( "Projectile.png" );
	_entitySprite->setAnchorPoint( Vec2::ZERO );
	_entitySprite->setPosition( position );

	auto projectilePhysicsBody = PhysicsBody::createBox( _image->getContentSize( ), PhysicsMaterial( ) );
	projectilePhysicsBody->setDynamic( false );
	_entitySprite->setPhysicsBody( projectilePhysicsBody );
	_entitySprite->getPhysicsBody( )->setCollisionBitmask( PROJECTILE_COLLISION_BITMASK );
	_entitySprite->getPhysicsBody( )->setContactTestBitmask( true );
}

~Projectile( )
{
	// don't have to delete anything yet.
}
