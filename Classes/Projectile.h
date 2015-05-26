/*
 * Projectile.h
 *
 *  Created on: May 13, 2015
 *      Author: Azim Momin
 */

#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "Definitions.h"
#include "PassiveEntity.h"

USING_NS_CC;

class Projectile : public PassiveEntity
{
public:
	Projectile( Vec2 position );
	~Projectile( );
	virtual void Update( ) override;
};

#endif /* __PROJECTILE_H__ */
