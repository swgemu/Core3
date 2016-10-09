/*
 * RecastNavMesh.h
 *
 *  Created on: April 29, 2016
 *      Author: gslomin
 */

#ifndef RECASTNAVMESH_H_
#define RECASTNAVMESH_H_

#include "engine/engine.h"


class MeshGrid : public Object {
	Vector<Reference<MeshData*>> grid;
	int gridWidth;
public:
	MeshGrid(float tileSize, Reference<MeshData*> data) {
		const AABB bounds = data->buildAABB();
		
	}
};


#endif /* RECASTNAVMESH_H_ */
