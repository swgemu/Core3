/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file SpawnMap.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#ifndef SPAWNMAP_H_
#define SPAWNMAP_H_

#include "engine/engine.h"


class SpawnMap : public VectorMap<String, SpawnDensityMap> {

public:
	SpawnMap() {

	}

	~SpawnMap() {

	}


};


#endif /* SPAWNMAP_H_ */
