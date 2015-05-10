/*
 * Definitions.h
 *
 *  Created on: Apr 30, 2015
 *      Author: Azim Momin
 */

#include "cocos2d.h"

#ifndef __DEFINITIONS__H_
#define __DEFINITIONS__H_

#define LABEL_FONT_SIZE 100
#define LABEL_PADDING_VERTICAL 20
#define LABEL_PADDING_HORIZONTAL 20.0F

#define SCENE_TRANSITION_TIME 0.5
#define SCENE_TRANSITION_COLOR cocos2d::Color3B::RED

#define NUM_LEVELS 9

#define PLAYER_COLLISION_BITMASK 0x00000001
#define PLAYER_SPEED 10
#define GRAVITY cocos2d::Vec2( 0.0f, -98.0f )

#define FRAME_TIME 0.0167 // 1 / 60 ==> 60 frames per second

#define GAME_PHYSICS_MATERIAL cocos2d::PhysicsMaterial( 0.0f, -100.0f, 0.0f )
enum ZOrder
{
	BACKGROUND   = 0,
	MIDDLEGROUND = 1,
	FOREGROUND   = 2
};

enum MoveDirection
{
	NONE  = 0,
	RIGHT = 1,
	LEFT  = 2,
	UP    = 3       // JUMP
};
#endif /* __DEFINITIONS__H_ */
