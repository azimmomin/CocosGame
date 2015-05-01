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

enum ZOrder
{
	BACKGROUND = 0,
	MIDDLEGROUND = 1,
	FOREGROUND = 2
};
#endif /* __DEFINITIONS__H_ */
