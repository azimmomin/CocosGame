#include "MainMenuScene.h"
#include "LevelSelectScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	//    auto closeItem = MenuItemImage::create(
	//                                           "CloseNormal.png",
	//                                           "CloseSelected.png",
	//                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	//
	//	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
	//                                origin.y + closeItem->getContentSize().height/2));
	//
	//    // create menu, it's an autorelease object
	//    auto menu = Menu::create(closeItem, NULL);
	//    menu->setPosition(Vec2::ZERO);
	//    this->addChild(menu, 1);

    auto startLabel = Label::createWithTTF( "Start", "fonts/Marker Felt.ttf", LABEL_FONT_SIZE );
    startLabel->setTextColor( Color4B::RED );

    auto continueLabel = Label::createWithTTF("Continue", "fonts/Marker Felt.ttf", LABEL_FONT_SIZE );
    continueLabel->setTextColor( Color4B::GRAY );

    auto exitLabel = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", LABEL_FONT_SIZE );
    exitLabel->setTextColor( Color4B::RED );

    // The start label will be positioned a little above the center in order to allow the entire
    // menu to be centered.
    auto startMenuItem = MenuItemLabel::create( startLabel );
    startMenuItem->setPosition( Vec2( origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2 + continueLabel->getContentSize( ).height ) );

    startMenuItem->setCallback( CC_CALLBACK_1( MainMenu::switchToLevelSelectSceneCallback, this ) );
    // The continue label will be placed below the start label with a little padding (LABEL_PADDING_VERTICAL).
    //    auto continueMenuItem = MenuItemLabel::create( continueLabel );
    //    continueMenuItem->setPosition( Vec2( origin.x + visibleSize.width / 2,
    //    		origin.y + visibleSize.height / 2 - LABEL_PADDING_VERTICAL ) );

    // The exit label will be placed below the start label with same padding.
    auto exitMenuItem = MenuItemLabel::create( exitLabel );
    exitMenuItem->setPosition( Vec2( origin.x + visibleSize.width / 2,
        	origin.y + visibleSize.height / 2 -
        	( startLabel->getContentSize( ).height + 2 * LABEL_PADDING_VERTICAL ) ) );

    exitMenuItem->setCallback( CC_CALLBACK_1( MainMenu::menuCloseCallback, this ) );
    auto menu = Menu::create( startMenuItem, exitMenuItem, NULL );
    menu->setPosition( Vec2::ZERO );
    this->addChild( menu, ZOrder::FOREGROUND );

    return true;
}


void MainMenu::menuCloseCallback( Ref* pSender )
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WP8 ) || ( CC_TARGET_PLATFORM == CC_PLATFORM_WINRT )
	MessageBox( "You pressed the close button. Windows Store Apps do not implement a close button.","Alert" );
    return;
#endif

    Director::getInstance( )->end( );

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    exit( 0 );
#endif
}

void MainMenu::switchToLevelSelectSceneCallback( cocos2d::Ref* pSender )
{
	auto levelScene = LevelSelect::createScene( );
	Director::getInstance( )->replaceScene( TransitionFade::create( SCENE_TRANSITION_TIME, levelScene, SCENE_TRANSITION_COLOR ) );
}
