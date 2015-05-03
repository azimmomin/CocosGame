/*
 * GameScene.cpp
 *
 *  Created on: May 1, 2015
 *      Author: Azim Momin
 */

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

    auto edgeBody = PhysicsBody::createEdgeBox( visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3 );
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

    this->addChild( Player::GetInstance( ).GetSprite( ), ZOrder::BACKGROUND );

    auto touchListener = EventListenerTouchOneByOne::create( );
    touchListener->setSwallowTouches( true );
    touchListener->onTouchBegan = CC_CALLBACK_2( Game::onTouchBegan, this );
    Director::getInstance( )->getEventDispatcher( )
    		->addEventListenerWithSceneGraphPriority( touchListener, this );
    return true;
}

void Game::DrawLevel( unsigned int level )
{
	// to do
}

bool Game::onTouchBegan( cocos2d::Touch* touch, cocos2d::Event* unused_event )
{
	Player::GetInstance( ).Move( MoveDirection::RIGHT );
	//this->schedule( schedule_selector( Game::ContinueMoving ), 2 );
	this->schedule( [&]( float interval ){
		Player::GetInstance( ).Move( MoveDirection::RIGHT );
	}, 1.0f, CC_REPEAT_FOREVER, 0.1f, "continue" );
	return true;
}

void Game::onTouchEnded( cocos2d::Touch* touch, cocos2d::Event* unused_event )
{
	this->unschedule( "continue" );
}

void Game::ContinueMoving( float interval )
{
	Player::GetInstance( ).Move( MoveDirection::RIGHT );
}
