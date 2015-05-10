/*
 * GameScene.cpp
 *
 *  Created on: May 1, 2015
 *      Author: Azim Momin
 */
#define COCOS2D_DEBUG 1
#include "GameScene.h"
#include "Definitions.h"

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
    _heldDir    = MoveDirection::NONE;

    this->addChild( Player::GetInstance( ).GetSprite( ), ZOrder::BACKGROUND );
    auto touchListener = EventListenerTouchAllAtOnce::create( );
    touchListener->onTouchesBegan = CC_CALLBACK_2( Game::onTouchesBegan, this );
    touchListener->onTouchesEnded = CC_CALLBACK_2( Game::onTouchesEnded, this );
    touchListener->onTouchesMoved = CC_CALLBACK_2( Game::onTouchesMoved, this );
    touchListener->onTouchesCancelled = CC_CALLBACK_2( Game::onTouchesEnded, this );
//    auto touchListener = EventListenerTouchOneByOne::create( );
//    touchListener->setSwallowTouches( true );
//    touchListener->onTouchBegan = CC_CALLBACK_2( Game::onTouchBegan, this );
//    touchListener->onTouchEnded = CC_CALLBACK_2( Game::onTouchEnded, this );
//    touchListener->onTouchCancelled = CC_CALLBACK_2( Game::onTouchEnded, this );
//    touchListener->onTouchMoved = CC_CALLBACK_2( Game::onTouchMoved, this );
    Director::getInstance( )->getEventDispatcher( )
    		->addEventListenerWithSceneGraphPriority( touchListener, this );
    this->schedule( schedule_selector( Game::UpdateGame ), FRAME_TIME );
    return true;
}

void Game::onTouchesBegan( const std::vector< Touch * > &touches, Event *unused_event )
{
	for ( auto touch : touches )
	{
		if ( touch )
		{
			MoveDirection dir = GetMoveDirFromVec( touch->getLocationInView( ) );
			if ( dir == MoveDirection::RIGHT || dir == MoveDirection::LEFT )
			{
				Player::GetInstance( ).UpdateVelocity( dir );
				InitiateMove( dir );
				_isMoveHeld = true;
				_heldDir = dir;
			}
			else if ( dir == MoveDirection::UP )
			{
				InitiateJump(  );
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
			MoveDirection dir = GetMoveDirFromVec( touch->getLocationInView( ) );
			if ( dir == MoveDirection::RIGHT || dir == MoveDirection::LEFT )
			{
				_isMoveHeld = false;
				_heldDir = MoveDirection::NONE;
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
			MoveDirection dir = GetMoveDirFromVec( touch->getLocationInView( ) );
			MoveDirection prevDir = GetMoveDirFromVec( touch->getPreviousLocationInView( ) );
			// We don't worry about movements within the held move button or jump button
			// slide touch from movement to same movement or non movement.
			if ( prevDir == _heldDir && dir != _heldDir )
			{
				if ( dir == MoveDirection::NONE || dir == MoveDirection::UP )
				{
					_isMoveHeld = false;
					_heldDir = MoveDirection::NONE;
				}
				else
				{
					_isMoveHeld = true;
					_heldDir = dir;
					Player::GetInstance( ).UpdateVelocity( dir );
					InitiateMove( dir );
				}
			}
			// slide touch from non movement area to movement area.
			else if ( ( prevDir != MoveDirection::RIGHT && prevDir != MoveDirection::LEFT  ) &&
					   ( dir == MoveDirection::RIGHT || dir == MoveDirection::LEFT ) )
			{
				_isMoveHeld = true;
				_heldDir = dir;
				Player::GetInstance( ).UpdateVelocity( dir );
				InitiateMove( dir );
			}
		}
	}
}

MoveDirection Game::GetMoveDirFromVec( Vec2 position )
{
	Point p = Director::getInstance( )->convertToGL( position );
	Size visibleSize = Director::getInstance( )->getVisibleSize( );
	Vec2 origin = Director::getInstance( )->getVisibleOrigin( );
	float leftBound = visibleSize.width / 6 + origin.x;
	float rightBound = visibleSize.width / 3 + origin.x;
	MoveDirection dir = MoveDirection::NONE;
	if ( p.x >= 0 && p.x < leftBound )
	{
		dir = MoveDirection::LEFT;
	}
	else if ( p.x >= leftBound && p.x < rightBound )
	{
		dir = MoveDirection::RIGHT;
	}
	else
	{
		dir = MoveDirection::UP;
	}
	return dir;                 // NOTE: This should never actually return NONE if the touch is on the screen.
}

void Game::UpdateGame( float dt )
{
	if (_isMoveHeld && _heldDir != MoveDirection::NONE )
	{
		//CCLOG("IS HELD");
		// Only update player's position if it is within visible screen.
		// Note that the player's anchor point will be at it's local (0, 0)
		Player::GetInstance( ).UpdateVelocity( _heldDir );
		InitiateMove( _heldDir );
	}
}

void Game::InitiateJump( )
{
	Player::GetInstance( ).UpdateVelocity( MoveDirection::UP );
	Player::GetInstance( ).Move( ); // this way we don't have to wait for left or right movement before jump happens.
	                                // Still crappy but it's a start.
}

void Game::InitiateMove( MoveDirection dir )
{
	auto playerBBox = Player::GetInstance( ).GetSprite( )->getBoundingBox( );
	Size visibleSize = Director::getInstance( )->getVisibleSize( );
	//Vec2 origin = Director::getInstance( )->getVisibleOrigin( );
	if ( ( dir == MoveDirection::LEFT && playerBBox.getMinX( ) > 0 ) ||
		 ( dir == MoveDirection::RIGHT && playerBBox.getMaxX( ) < visibleSize.width ) )
	{
		Player::GetInstance( ).Move( );
	}
}
