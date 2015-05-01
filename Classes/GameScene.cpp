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
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = Game::create();
    layer->DrawLevel( level );
    // add layer as a child to scene
    scene->addChild(layer);

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

    Size visibleSize = Director::getInstance( )->getVisibleSize( );
    Vec2 origin = Director::getInstance( )->getVisibleOrigin( );

    _player = Sprite::create( "Player.png" );
    _player->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    this->addChild( _player, ZOrder::BACKGROUND );

    return true;
}

void Game::DrawLevel( unsigned int level )
{
	// to do
}
