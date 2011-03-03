/*
 * ForageMap.h
 *
 *  Created on: 2/24/2011
 *      Author: Anakis
 */

#ifndef FORAGEMAP_H_
#define FORAGEMAP_H_

#include "engine/engine.h"
#include "ForageAreaCollection.h"

class ForageMap : public VectorMap<String, Reference<ForageAreaCollection*> > {

};


#endif /*FORAGEMAP_H_*/
