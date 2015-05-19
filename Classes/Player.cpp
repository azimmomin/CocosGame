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
	_numProjectiles = PROJECTILE_COUNT;
	Size visibleSize = Director::getInstance( )->getVisibleSize( );
	Vec2 origin = Director::getInstance( )->getVisibleOrigin( );

	_entitySprite = Sprite::create( "Player.png" );
	_entitySprite->setAnchorPoint( Vec2::ZERO );
	// Will be placed in bottom right corner.
	_entitySprite->setPosition( Vec2( _entitySprite->getContentSize( ).width / 2, _entitySprite->getContentSize( ).height / 2  ) );

	auto playerPhysicsBody = PhysicsBody::createBox( _entitySprite->getContentSize( ), PhysicsMaterial( ) );
	playerPhysicsBody->setDynamic( false );
	_entitySprite->setPhysicsBody( playerPhysicsBody );
	_entitySprite->getPhysicsBody( )->setCollisionBitmask( PLAYER_COLLISION_BITMASK );
	_entitySprite->getPhysicsBody( )->setContactTestBitmask( true );
}

Player::~Player( )
{
	CC_SAFE_RELEASE( _entitySprite );
}

void Player::Fall( )
{
	Size visibleSize = Director::getInstance( )->getVisibleSize( );
	// Once player hits ground reset everything
	if ( _entitySprite->getPositionY( ) <= _entitySprite->getContentSize( ).height / 2 )
	{
		SetFalling( false );
		ResetJumpCount( );
		return;
	}
	else if ( _isFalling )
	{
		_entitySprite->setPositionY( _entitySprite->getPositionY( ) - ( PLAYER_FALL_SPEED * visibleSize.height ) );
	}
}

int Player::GetJumpCount( ) const
{
	return _jumpCount;
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
		_entitySprite->setPositionY( _entitySprite->getPositionY( ) + ( PLAYER_JUMP_SPEED * visibleSize.height ) );
		IncrementJumpCount( );
	}
	// Player will start falling at the end of the jump
	SetFalling( true );
}

void Player::Move( )
{
	_entitySprite->runAction( MoveBy::create( FRAME_TIME, _velocity ) );
}

void Player::ResetJumpCount( )
{
	_jumpCount = 0;
	_numProjectiles = PROJECTILE_COUNT;
}

void Player::SetFalling( const bool isFalling )
{
	_isFalling = isFalling;
}

void Player::Shoot( )
{
	if ( _numProjectiles > 0 )
	{
		Size contentSize = entitySprite->getContentSize( );
		Vec2 projPos( _entitySprite->getPositionX( ) + contentSize.width,
				      _entitySprite->getPositionY( ) + contentSize.height / 2 );
		EntityManager::AddEntity( new Projectile( projPos ) );
		_numProjectiles -= 1;
	}
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
