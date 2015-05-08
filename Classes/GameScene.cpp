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
    // layer->DrawLevel( level );

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

    _isHeld = false;
    _heldDir = MoveDirection::NONE;

    this->addChild( Player::GetInstance( ).GetSprite( ), ZOrder::BACKGROUND );

    auto touchListener = EventListenerTouchOneByOne::create( );
    touchListener->setSwallowTouches( true );
    touchListener->onTouchBegan = CC_CALLBACK_2( Game::onTouchBegan, this );
    touchListener->onTouchEnded = CC_CALLBACK_2( Game::onTouchEnded, this );
    touchListener->onTouchCancelled = CC_CALLBACK_2( Game::onTouchEnded, this );
    touchListener->onTouchMoved = CC_CALLBACK_2( Game::onTouchMoved, this );
    Director::getInstance( )->getEventDispatcher( )
    		->addEventListenerWithSceneGraphPriority( touchListener, this );
    this->schedule( schedule_selector( Game::UpdateGame ), FRAME_TIME );
    return true;
}

void Game::DrawLevel( unsigned int level )
{
	// to do
}

bool Game::onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* unused_event )
{
	CCLOG( "TOUCH BEGAN" );
	if ( touch )
	{
		MoveDirection dir = GetMoveDirFromTouch( touch );
		if ( dir == MoveDirection::RIGHT || dir == MoveDirection::LEFT )
		{
			_isHeld = true;
			_heldDir = dir;
			MovePlayer( dir );
		}
	}
	return true;
}

void Game::onTouchEnded( cocos2d::Touch* touch, cocos2d::Event* unused_event )
{
	CCLOG( "TOUCH ENDED" );
	if ( touch )
		{
			MoveDirection dir = GetMoveDirFromTouch( touch );
			if ( dir == MoveDirection::RIGHT || dir == MoveDirection::LEFT )
			{
				//Player::GetInstance( ).Move( dir );
				_isHeld = false;
				_heldDir = MoveDirection::NONE;
			}
		}
}

void Game::onTouchMoved( cocos2d::Touch* touch, cocos2d::Event* unused_event )
{
	CCLOG( "TOUCH MOVED" );
	if ( touch )
	{
		MoveDirection dir = GetMoveDirFromTouch( touch );
		if ( dir != _heldDir )
		{
			_isHeld = true;
			_heldDir = dir;
			MovePlayer( dir );
		}
	}
}
MoveDirection Game::GetMoveDirFromTouch( Touch *touch )
{
	Point p = Director::getInstance( )->convertToGL( touch->getLocationInView( ) );
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
	return dir;
}

void Game::UpdateGame( float dt )
{
	if (_isHeld)
	{
		CCLOG("IS HELD");
		// Only update player's position if it is within visible screen.
		// Note that the player's anchor point will be at it's local (0, 0)
		MovePlayer( _heldDir );
	}
}

void Game::MovePlayer( MoveDirection dir )
{
	auto playerBBox = Player::GetInstance( ).GetSprite( )->getBoundingBox( );
	Size visibleSize = Director::getInstance( )->getVisibleSize( );
	//Vec2 origin = Director::getInstance( )->getVisibleOrigin( );
	if ( dir == MoveDirection::LEFT && playerBBox.getMinX( ) > 0 )
	{
		Player::GetInstance( ).Move( dir );
	}
	else if ( dir == MoveDirection::RIGHT && playerBBox.getMaxX( ) < visibleSize.width )
	{
		Player::GetInstance( ).Move( dir );
	}
}
