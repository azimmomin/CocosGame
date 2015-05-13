/*
 * Projectile.h
 *
 *  Created on: May 13, 2015
 *      Author: Azim Momin
 */

#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "Definitions.h"
#include "Entity.h"

USING_NS_CC;

class Projectile : Entity
{
public:
	Projectile( Vec2 position );
	~Projectile( );
};

#endif /* __PROJECTILE_H__ */
