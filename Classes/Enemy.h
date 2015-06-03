/*
 * Enemy.h
 *
 *  Created on: Jun 2, 2015
 *      Author: Azim Momin
 */

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "PassiveEntity.h"
#include "Definitions.h"

class Enemy: public PassiveEntity
{
public:
	Enemy( Vec2 pos );
	virtual ~Enemy( );
	virtual void Update( ) override;
};

#endif /* __ENEMY_H__ */
