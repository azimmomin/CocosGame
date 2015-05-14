/*
 * Entity.h
 *
 *  Created on: May 13, 2015
 *      Author: Azim Momin
 */

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"

USING_NS_CC;

class Entity
{
public:
	Entity( ) {};
	virtual ~Entity( )    = 0;
	Sprite* GetSprite( ) const
	{
		return _entitySprite;
	};
protected:

	Sprite* _entitySprite = NULL;
};
#endif /* __ENTITY_H__ */
