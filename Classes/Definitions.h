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
#define PROJECTILE_COLLISION_BITMASK 0x00000002

#define PLAYER_SPEED 10
#define PLAYER_ACCELERATION 2.0f
#define MAX_PLAYER_VELOCITY 10.0f

#define PLAYER_JUMP_SPEED 0.1f
#define PLAYER_FALL_SPEED 0.0075f
#define MAX_JUMP_COUNT 2                    // For double jumping

#define GRAVITY cocos2d::Vec2( 0.0f, -98.0f )

#define FRAME_TIME 0.0167 // 1 / 60 ==> 60 frames per second

#define GAME_PHYSICS_MATERIAL cocos2d::PhysicsMaterial( 0.0f, -100.0f, 0.0f )

#define PROJECTILE_COUNT 3
#define PROJECTILE_SPEED 5
enum ZOrder
{
	BACKGROUND   = 0,
	MIDDLEGROUND = 1,
	FOREGROUND   = 2
};

enum PlayerAction
{
	NONE  = 0,
	RIGHT = 1,
	LEFT  = 2,
	JUMP  = 3,
	SHOOT = 4
};
#endif /* __DEFINITIONS__H_ */
