/*
 * Enemy.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: Azim Momin
 */

#include "Enemy.h"

Enemy::Enemy( Vec2 pos )
{
	SetTag( EntityTag::ENEMY );
	_entitySprite = Sprite::create( "Enemy.png" );
	_entitySprite->setAnchorPoint( Vec2::ZERO );
	_entitySprite->setPosition( pos );

	auto projectilePhysicsBody = PhysicsBody::createBox( _entitySprite->getContentSize( ), PhysicsMaterial( ) );
	projectilePhysicsBody->setDynamic( false );
	_entitySprite->setPhysicsBody( projectilePhysicsBody );
	_entitySprite->getPhysicsBody( )->setCollisionBitmask( ENEMY_COLLISION_BITMASK );
	_entitySprite->getPhysicsBody( )->setContactTestBitmask( true );
}

Enemy::~Enemy( )
{
	CC_SAFE_RELEASE( _entitySprite );
}

void Enemy::Update( )
{
	//TODO: DOES NOTHING FOR NOW
}
