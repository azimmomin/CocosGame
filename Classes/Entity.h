/*
 * Entity.h
 *
 *  Created on: May 13, 2015
 *      Author: Azim Momin
 */

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Entity
{
public:
	Entity( ) {};
	virtual ~Entity( )    = 0;
	Sprite*   GetSprite( ) const
	{
		return _entitySprite;
	};
	EntityTag GetTag( )    const
	{
		return _tag;
	}
	void      SetTag( EntityTag tag )
	{
		_tag = tag;
	}
protected:

	Sprite*   _entitySprite = NULL;
	EntityTag _tag;
};
#endif /* __ENTITY_H__ */
