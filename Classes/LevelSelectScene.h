/*
 * LevelSelectScene.h
 *
 *  Created on: Apr 29, 2015
 *      Author: Azim Momin
 */

#ifndef __LEVELSELECT_SCENE_H__
#define __LEVELSELECT_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class LevelSelect: public cocos2d::Layer {
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene( );
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init( );
	// implement the "static create()" method manually
	CREATE_FUNC( LevelSelect );
private:
	void LoadLevelCallback( Ref* pSender, unsigned int level );
	unsigned int _currentLevel;
};

#endif /* __LEVELSELECT_SCENE_H__ */
