/*
 * GameScene.h
 *
 *  Created on: May 1, 2015
 *      Author: Azim Momin
 */

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class Game : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene( unsigned int level );
	virtual bool init( );
	// implement the "static create()" method manually
	CREATE_FUNC( Game );
private:
	void DrawLevel( unsigned int level );
	cocos2d::Sprite *_player;
};

#endif /* __GAME_SCENE_H__ */
