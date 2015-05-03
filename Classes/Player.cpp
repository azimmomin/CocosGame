/*
 * Player.cpp
 *
 *  Created on: May 3, 2015
 *      Author: Azim Momin
 */

#include "Player.h"

USING_NS_CC;


Player::Player( )
{
	Size visibleSize = Director::getInstance( )->getVisibleSize( );
	Vec2 origin = Director::getInstance( )->getVisibleOrigin( );

	_image = Sprite::create( "Player.png" );
	_image->setPosition( Vec2( _image->getContentSize( ).width, _image->getContentSize( ).height ) );

	auto playerPhysicsBody = PhysicsBody::createBox( _image->getContentSize( ), PhysicsMaterial( ) );
	playerPhysicsBody->setDynamic( true );
	_image->setPhysicsBody( playerPhysicsBody );
	_image->getPhysicsBody( )->setCollisionBitmask( PLAYER_COLLISION_BITMASK );
	_image->getPhysicsBody( )->setContactTestBitmask( true );
}

Sprite* Player::GetSprite( ) const
{
	return _image;
}

void Player::Move( const MoveDirection dir )
{
	MoveBy* moveBy;
	if ( dir == MoveDirection::LEFT )
	{
		moveBy = MoveBy::create( 2, Vec2( -20, 0 ) );
	}
	else if ( dir == MoveDirection::RIGHT )
	{
		moveBy = MoveBy::create( 2, Vec2( 20, 0 ) );
	}
	else
	{
		CCLOG( "%s", "Incorrect move direction" );
	}
	_image->runAction( moveBy );
}
