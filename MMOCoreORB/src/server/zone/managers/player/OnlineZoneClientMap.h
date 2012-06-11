/*
 * OnlineZoneClientMap.h
 *
 *  Created on: 11/06/2012
 *      Author: victor
 */

#ifndef ONLINEZONECLIENTMAP_H_
#define ONLINEZONECLIENTMAP_H_

#include "engine/engine.h"
#include "server/zone/ZoneClientSession.h"

class OnlineZoneClientMap : public HashTable<uint32, Vector<Reference<ZoneClientSession*> > > {

};


#endif /* ONLINEZONECLIENTMAP_H_ */
