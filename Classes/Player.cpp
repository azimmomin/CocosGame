/*
 * Player.cpp
 *
 *  Created on: May 3, 2015
 *      Author: Azim Momin
 *
 * This Singleton class will represent the main player in the game.
 * Responsibilities:
 *    - Hold Sprite for player.
 *    - Update position based on user input
 */

#include "Player.h"

USING_NS_CC;


Player::Player( )
{
	Size visibleSize = Director::getInstance( )->getVisibleSize( );
	Vec2 origin = Director::getInstance( )->getVisibleOrigin( );

	_image = Sprite::create( "Player.png" );
	_image->setAnchorPoint( Vec2::ZERO );
	_image->setPosition( Vec2( _image->getContentSize( ).width, _image->getContentSize( ).height ) );
	//_image->setPosition( origin.x, origin.y );
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
	if ( dir == MoveDirection::LEFT )
	{
		_image->runAction( MoveBy::create( FRAME_TIME, Vec2( -PLAYER_SPEED, 0 ) ) );
	}
	else if ( dir == MoveDirection::RIGHT )
	{
		_image->runAction( MoveBy::create( FRAME_TIME, Vec2( PLAYER_SPEED, 0 ) ) );
	}
	else
	{
		// This should never happen
		CCLOG( "%s", "MOVEDIRECTION IS NONE" );
	}
}
