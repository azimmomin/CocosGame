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
#define COCOS2D_DEBUG 1

#include "Player.h"
#include <algorithm>

USING_NS_CC;


Player::Player( )
{
	_velocity = Vec2( 0, 0 );
	Size visibleSize = Director::getInstance( )->getVisibleSize( );
	Vec2 origin = Director::getInstance( )->getVisibleOrigin( );

	_image = Sprite::create( "Player.png" );
	_image->setAnchorPoint( Vec2::ZERO );
	// Will be placed in bottom right corner.
	_image->setPosition( Vec2( _image->getContentSize( ).width / 2, _image->getContentSize( ).height / 2  ) );
	//_image->setPosition( origin.x, origin.y );
	auto playerPhysicsBody = PhysicsBody::createBox( _image->getContentSize( ), PhysicsMaterial( ) );
	//playerPhysicsBody->setDynamic( false );
	_image->setPhysicsBody( playerPhysicsBody );
	_image->getPhysicsBody( )->setCollisionBitmask( PLAYER_COLLISION_BITMASK );
	_image->getPhysicsBody( )->setContactTestBitmask( true );
}

Sprite* Player::GetSprite( ) const
{
	return _image;
}

void Player::Move( )
{
	CCLOG( "VELOCITY: %.2f", _velocity.x );
	_image->runAction( MoveBy::create( FRAME_TIME, _velocity ) );
}

void Player::UpdateVelocity( const MoveDirection &dir )
{
	if ( dir == MoveDirection::LEFT )
	{
		_velocity.x = std::max( -MAX_PLAYER_VELOCITY, _velocity.x - PLAYER_ACCELERATION );
	}
	else if ( dir == MoveDirection::RIGHT  )
	{
		_velocity.x = std::min( MAX_PLAYER_VELOCITY, _velocity.x + PLAYER_ACCELERATION );
	}
	else if ( dir == MoveDirection::UP )
	{
		_velocity.y += 0.5f; // This is really bad right now.
	}
	else
	{
		// This should never happen
		CCLOG( "%s", "MOVEDIRECTION IS NONE" );
	}
}
