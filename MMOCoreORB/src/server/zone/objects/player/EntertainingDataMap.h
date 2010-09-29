/*
 * EntertainingDataMap.h
 *
 *  Created on: 22/09/2010
 *      Author: victor
 */

#ifndef ENTERTAININGDATAMAP_H_
#define ENTERTAININGDATAMAP_H_

#include "engine/engine.h"
#include "EntertainingData.h"

class EntertainingDataMap : public VectorMap<ManagedReference<CreatureObject*>, EntertainingData > {

};

#endif /* ENTERTAININGDATAMAP_H_ */
