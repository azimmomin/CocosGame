/*
 * LevelSelectScene.cpp
 *
 *  Created on: Apr 29, 2015
 *      Author: Azim Momin
 */

#include "LevelSelectScene.h"
#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* LevelSelect::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = LevelSelect::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool LevelSelect::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    _currentLevel = 1;

    Size visibleSize = Director::getInstance( )->getVisibleSize( );
    Vec2 origin = Director::getInstance( )->getVisibleOrigin( );

    auto menu = Menu::create( );

    for ( int i = 1; i <= _currentLevel; i += 1 )
	{
		auto str = __String::createWithFormat( "%d", i );
		auto label = Label::createWithTTF( str->getCString( ), "fonts/Marker Felt.ttf", LABEL_FONT_SIZE );
		label->setTextColor( Color4B::RED );

		auto menuLevelItem = MenuItemLabel::create( label );
		menuLevelItem->setCallback( CC_CALLBACK_1( LevelSelect::LoadLevelCallback, this, i ) );
		menu->addChild( menuLevelItem );
	}

    for ( int i = _currentLevel + 1; i <= NUM_LEVELS + 1; i += 1 )
    {
    	auto str = __String::createWithFormat( "%d", i );
    	auto label = Label::createWithTTF( str->getCString( ), "fonts/Marker Felt.ttf", LABEL_FONT_SIZE );
    	label->setTextColor( Color4B::GRAY );

    	auto menuLevelItem = MenuItemLabel::create( label );
    	menuLevelItem->setCallback( CC_CALLBACK_1( LevelSelect::LoadLevelCallback, this, i ) );
    	menu->addChild( menuLevelItem );
    }
    // Need to align all children into rows
    menu->alignItemsHorizontallyWithPadding( LABEL_PADDING_HORIZONTAL );
    menu->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    this->addChild( menu, ZOrder::FOREGROUND );
    return true;
}

void LevelSelect::LoadLevelCallback( Ref* pSender, unsigned int level )
{
	if ( level > _currentLevel )
	{
		return;
	}
	else
	{
		auto gameScene = Game::createScene( level );
		Director::getInstance( )->replaceScene( TransitionFade::create( SCENE_TRANSITION_TIME, gameScene, SCENE_TRANSITION_COLOR ) );
	}
}
