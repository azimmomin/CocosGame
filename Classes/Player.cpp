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
	_velocity  = Vec2( 0, 0 );
	_isJumping = false;
	_isFalling = false;
	Size visibleSize = Director::getInstance( )->getVisibleSize( );
	Vec2 origin = Director::getInstance( )->getVisibleOrigin( );

	_image = Sprite::create( "Player.png" );
	_image->setAnchorPoint( Vec2::ZERO );
	// Will be placed in bottom right corner.
	_image->setPosition( Vec2( _image->getContentSize( ).width / 2, _image->getContentSize( ).height / 2  ) );

	auto playerPhysicsBody = PhysicsBody::createBox( _image->getContentSize( ), PhysicsMaterial( ) );
	playerPhysicsBody->setDynamic( false );
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

void Player::Jump( )
{
	Size visibleSize = Director::getInstance( )->getVisibleSize( );

	if ( _isJumping )
	{
		_image->setPositionY( _image->getPositionY( ) + ( PLAYER_JUMP_SPEED * visibleSize.height ) );
	}
	_isFalling = true;
}

void Player::Fall( )
{
	Size visibleSize = Director::getInstance( )->getVisibleSize( );
	Vec2 origin = Director::getInstance( )->getVisibleOrigin( );
	if ( _image->getPositionY( ) <= _image->getContentSize( ).height / 2 )
	{
		_isFalling = false;
		return;
	}
	else if ( _isFalling )
	{
		_image->setPositionY( _image->getPositionY( ) - ( PLAYER_FALL_SPEED * visibleSize.height ) );
	}
}

void Player::UpdateState( const MoveDirection &dir )
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
		//_velocity.y += std::min( MAX_PLAYER_JUMP_THRUST, _velocity.y + PLAYER_JUMP_THRUST ); // This is really bad right now.
		_isJumping = true;
		_isFalling = false;
	}
	else
	{
		// This should never happen
		CCLOG( "%s", "MOVEDIRECTION IS NONE" );
	}
}
