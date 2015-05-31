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
	int     GetTag( )    const
	{
		return _tag;
	}
	void    SetTag( int tag )
	{
		_tag = tag;
	}
protected:

	Sprite* _entitySprite = NULL;
	int     _tag;
};
#endif /* __ENTITY_H__ */
