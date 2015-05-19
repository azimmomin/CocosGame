/*
 * GameScene.h
 *
 *  Created on: May 1, 2015
 *      Author: Azim Momin
 */

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"

class Game : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene( unsigned int level );
	virtual bool init( );
	// implement the "static create()" method manually
	CREATE_FUNC( Game );
	virtual ~Game( );
private:
	PlayerAction GetActionFromVec( cocos2d::Vec2 position );
	void InitiateAttack( );
	void InitiateJump( );
	void InitiateMove( PlayerAction action );
	void onTouchesBegan( const std::vector< Touch * > &touches, Event *unused_event ) override;
	void onTouchesEnded( const std::vector< Touch * > &touches, Event *unused_event ) override;
	void onTouchesMoved( const std::vector< Touch * > &touches, Event *unused_event ) override;
	void UpdateGame( float dt );

	bool _isMoveHeld;
	PlayerAction _heldDir;
};

#endif /* __GAME_SCENE_H__ */
