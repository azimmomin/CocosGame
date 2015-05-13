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
	_isFalling = false;
	_jumpCount = 0;
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

void Player::Fall( )
{
	Size visibleSize = Director::getInstance( )->getVisibleSize( );
	// Once player hits ground reset everything
	if ( _image->getPositionY( ) <= _image->getContentSize( ).height / 2 )
	{
		SetFalling( false );
		ResetJumpCount( );
		return;
	}
	else if ( _isFalling )
	{
		_image->setPositionY( _image->getPositionY( ) - ( PLAYER_FALL_SPEED * visibleSize.height ) );
	}
}

int Player::GetJumpCount( ) const
{
	return _jumpCount;
}

Sprite* Player::GetSprite( ) const
{
	return _image;
}

void Player::IncrementJumpCount( )
{
	_jumpCount += 1;
}

void Player::Jump( )
{
	Size visibleSize = Director::getInstance( )->getVisibleSize( );
	if ( GetJumpCount( ) < MAX_JUMP_COUNT )
	{
		_image->setPositionY( _image->getPositionY( ) + ( PLAYER_JUMP_SPEED * visibleSize.height ) );
		IncrementJumpCount( );
	}
	// Player will start falling at the end of the jump
	SetFalling( true );
}

void Player::Move( )
{
	_image->runAction( MoveBy::create( FRAME_TIME, _velocity ) );
}

void Player::ResetJumpCount( )
{
	_jumpCount = 0;
}

void Player::SetFalling( const bool isFalling )
{
	_isFalling = isFalling;
}

void Player::Shoot( )
{

}

// Currently only meant for movement since jumping and shooting don't affect the
// state of the player in terms of it's velocity or life.
void Player::UpdateState( const PlayerAction &action )
{
	if ( action == PlayerAction::LEFT )
	{
		_velocity.x = std::max( -MAX_PLAYER_VELOCITY, _velocity.x - PLAYER_ACCELERATION );
	}
	else if ( action == PlayerAction::RIGHT  )
	{
		_velocity.x = std::min( MAX_PLAYER_VELOCITY, _velocity.x + PLAYER_ACCELERATION );
	}
	else
	{
		CCLOG( "%s", "PLAYER ACTION IS NOT A MOVEMENT" );
	}
}
