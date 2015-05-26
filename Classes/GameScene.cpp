/*
 * GameScene.cpp
 *
 *  Created on: May 1, 2015
 *      Author: Azim Momin
 */
#define COCOS2D_DEBUG 1
#include "GameScene.h"
#include "Definitions.h"
#include "EntityManager.h"

USING_NS_CC;

Scene* Game::createScene( unsigned int level )
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics( );
    scene->getPhysicsWorld( )->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    scene->getPhysicsWorld( )->setGravity( GRAVITY );
    Size visibleSize = Director::getInstance( )->getVisibleSize( );

    auto edgeBody = PhysicsBody::createEdgeBox( visibleSize, GAME_PHYSICS_MATERIAL, 5 );
    auto edgeNode = Node::create( );
    edgeNode->setPosition( visibleSize.width / 2, visibleSize.height / 2 );
    edgeNode->setPhysicsBody( edgeBody );
    scene->addChild( edgeNode );

    // 'layer' is an autorelease object
    auto layer = Game::create( );

    // add layer as a child to scene
    scene->addChild( layer );

    // return the scene
    return scene;
}

bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    _isMoveHeld = false;
    _heldDir    = PlayerAction::NONE;

    this->addChild( Player::GetInstance( ).GetSprite( ), ZOrder::FOREGROUND );
    auto touchListener = EventListenerTouchAllAtOnce::create( );
    touchListener->onTouchesBegan = CC_CALLBACK_2( Game::onTouchesBegan, this );
    touchListener->onTouchesEnded = CC_CALLBACK_2( Game::onTouchesEnded, this );
    touchListener->onTouchesMoved = CC_CALLBACK_2( Game::onTouchesMoved, this );
    touchListener->onTouchesCancelled = CC_CALLBACK_2( Game::onTouchesEnded, this );
    Director::getInstance( )->getEventDispatcher( )
    		->addEventListenerWithSceneGraphPriority( touchListener, this );
    this->schedule( schedule_selector( Game::UpdateGame ), FRAME_TIME );
    return true;
}

Game::~Game( )
{
	EntityManager::UnloadEntityManager( );
}

PlayerAction Game::GetActionFromVec( Vec2 position )
{
	Point p = Director::getInstance( )->convertToGL( position );
	Size visibleSize = Director::getInstance( )->getVisibleSize( );
	Vec2 origin = Director::getInstance( )->getVisibleOrigin( );
	float leftBound = visibleSize.width / 6 + origin.x;
	float rightBound = visibleSize.width / 3 + origin.x;
	float jumpBound = ( visibleSize.width * 5 / 6 ) + origin.x;
	PlayerAction action = PlayerAction::NONE;

	if ( p.x >= 0 && p.x < leftBound )
	{
		action = PlayerAction::LEFT;
	}
	else if ( p.x >= leftBound && p.x < rightBound )
	{
		action = PlayerAction::RIGHT;
	}
	else if ( p.x >= rightBound && p.x < jumpBound )
	{
		action = PlayerAction::JUMP;
	}
	else
	{
		action = PlayerAction::SHOOT;
	}
	return action;                 // NOTE: This should never actually return NONE if the touch is on the screen.
}

void Game::InitiateAttack( )
{
	// Need to pass this layer so we can add a bullet sprite to it.
	Player::GetInstance( ).Shoot( this );
}

void Game::InitiateJump( )
{
	Player::GetInstance( ).Jump( );
}

void Game::InitiateMove( PlayerAction action )
{
	auto playerBBox = Player::GetInstance( ).GetSprite( )->getBoundingBox( );
	Size visibleSize = Director::getInstance( )->getVisibleSize( );
	//Vec2 origin = Director::getInstance( )->getVisibleOrigin( );
	if ( ( action == PlayerAction::LEFT && playerBBox.getMinX( ) > 0 ) ||
		 ( action == PlayerAction::RIGHT && playerBBox.getMaxX( ) < visibleSize.width ) )
	{
		Player::GetInstance( ).Move( );
	}
}

void Game::onTouchesBegan( const std::vector< Touch * > &touches, Event *unused_event )
{
	for ( auto touch : touches )
	{
		if ( touch )
		{
			PlayerAction action = GetActionFromVec( touch->getLocationInView( ) );
			if ( action == PlayerAction::RIGHT || action == PlayerAction::LEFT )
			{
				Player::GetInstance( ).UpdateState( action );
				InitiateMove( action );
				_isMoveHeld = true;
				_heldDir = action;
			}
			else if ( action == PlayerAction::JUMP )
			{
				InitiateJump(  );
			}
			else if ( action == PlayerAction::SHOOT )
			{
				InitiateAttack( );
			}
		}
	}
}

void Game::onTouchesEnded( const std::vector< Touch * > &touches, Event *unused_event )
{
	for ( auto touch : touches )
	{
		if ( touch )
		{
			PlayerAction action = GetActionFromVec( touch->getLocationInView( ) );
			if ( action == PlayerAction::RIGHT || action == PlayerAction::LEFT )
			{
				_isMoveHeld = false;
				_heldDir = PlayerAction::NONE;
			}
		}
	}
}

void Game::onTouchesMoved( const std::vector< Touch * > &touches, Event *unused_event )
{
	for ( auto touch : touches )
	{
		if ( touch )
		{
			PlayerAction currAction = GetActionFromVec( touch->getLocationInView( ) );
			PlayerAction prevAction = GetActionFromVec( touch->getPreviousLocationInView( ) );
			// We don't worry about movements within the held move button or jump button
			// slide touch from movement to same movement or non movement.
			if ( prevAction == _heldDir && currAction != _heldDir )
			{
				if ( currAction == PlayerAction::NONE || currAction == PlayerAction::JUMP || currAction == PlayerAction::SHOOT )
				{
					_isMoveHeld = false;
					_heldDir = PlayerAction::NONE;
				}
				else
				{
					_isMoveHeld = true;
					_heldDir = currAction;
					Player::GetInstance( ).UpdateState( currAction );
					InitiateMove( currAction );
				}
			}
			// slide touch from non movement area to movement area.
			else if ( ( prevAction != PlayerAction::RIGHT && prevAction != PlayerAction::LEFT  ) &&
					   ( currAction == PlayerAction::RIGHT || currAction == PlayerAction::LEFT ) )
			{
				_isMoveHeld = true;
				_heldDir = currAction;
				Player::GetInstance( ).UpdateState( currAction );
				InitiateMove( currAction );
			}
		}
	}
}

void Game::UpdateGame( float dt )
{
	if ( _isMoveHeld && _heldDir != PlayerAction::NONE )
	{
		//CCLOG("IS HELD");
		// Only update player's position if it is within visible screen.
		// Note that the player's anchor point will be at it's local (0, 0)
		Player::GetInstance( ).UpdateState( _heldDir );
		InitiateMove( _heldDir );
	}
	Player::GetInstance( ).Fall( );
}
