/*
 * DelegateSuiCallback.h
 *
 *  Created on: 19/01/2012
 *      Author: victor
 */

#ifndef DELEGATESUICALLBACK_H_
#define DELEGATESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"

class DelegateSuiCallback : public SuiCallback {
public:
	DelegateSuiCallback(ZoneServer* serv);

	void run(server::zone::objects::creature::CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args);
};

#endif /* DELEGATESUICALLBACK_H_ */
