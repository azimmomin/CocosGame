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
	virtual Sprite* GetSprite( ) const
	{
		return _entitySprite;
	}
	virtual ~Entity( )
	{
		CC_SAFE_RELEASE( _entitySprite );
	}
private:
	Sprite* _entitySprite = NULL;
};
#endif /* __ENTITY_H__ */
