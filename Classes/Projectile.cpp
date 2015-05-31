/*
 * Projectile.cpp
 *
 *  Created on: May 13, 2015
 *      Author: Azim Momin
 */
#define COCOS2D_DEBUG 1
#include "Projectile.h"

Projectile::Projectile( Vec2 position )
{
	_entitySprite = Sprite::create( "Projectile.png" );
	_entitySprite->setAnchorPoint( Vec2::ZERO );
	_entitySprite->setPosition( position );

	auto projectilePhysicsBody = PhysicsBody::createBox( _entitySprite->getContentSize( ), PhysicsMaterial( ) );
	projectilePhysicsBody->setDynamic( false );
	_entitySprite->setPhysicsBody( projectilePhysicsBody );
	_entitySprite->getPhysicsBody( )->setCollisionBitmask( PROJECTILE_COLLISION_BITMASK );
	_entitySprite->getPhysicsBody( )->setContactTestBitmask( true );
}

Projectile::~Projectile( )
{
	CC_SAFE_RELEASE( _entitySprite );
}

void Projectile::Update( )
{
	_entitySprite->setPositionX( _entitySprite->getPositionX( ) + PROJECTILE_SPEED );
}
