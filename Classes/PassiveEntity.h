/*
 * PassiveEntity.h
 *
 *  Created on: May 18, 2015
 *      Author: Azim Momin
 */

#ifndef PASSIVEENTITY_H_
#define PASSIVEENTITY_H_

#include "Entity.h"

class PassiveEntity: public Entity
{
public:
	PassiveEntity( ) {};
	virtual ~PassiveEntity( )   = 0;
	virtual void Update( )      = 0;
};

#endif /* PASSIVEENTITY_H_ */
