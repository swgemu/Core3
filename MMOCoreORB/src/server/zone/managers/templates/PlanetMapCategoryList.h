/*
 * PlanetMapCategoryList.h
 *
 *  Created on: Apr 26, 2011
 *      Author: polonel
 */

#ifndef PLANETMAPCATEGORYLIST_H_
#define PLANETMAPCATEGORYLIST_H_

#include "engine/engine.h"

class PlanetMapCategory;

class PlanetMapCategoryList : public VectorMap<String, Reference<PlanetMapCategory*> > {

public:
	PlanetMapCategoryList() : VectorMap<String, Reference<PlanetMapCategory*> >() {
	}
};


#endif /* PLANETMAPCATEGORYLIST_H_ */
