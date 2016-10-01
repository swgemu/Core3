#ifndef NAVMESHREGION_H_
#define NAVMESHREGION_H_
#include "engine/engine.h"
#include "templates/appearance/MeshData.h"
#include "pathfinding/RecastNavMesh.h"
#include "pathfinding/RecastTileBuilder.h"

class NavmeshRegion : public Object, Logger {
protected:
	Reference<RecastNavMesh*> navMesh;
	
public:
	String name;
	Vector<Sphere> regionBounds;
	Vector<Reference<MeshData*> > sceneData;

	Sphere meshBounds;
	NavmeshRegion(String name) : Logger("Navmesh_" + name) {
		this->name = name;
	}
	
	Reference<RecastNavMesh*> getNavMesh() {
		return navMesh;
	}
	
	void setNavMesh(Reference<RecastNavMesh*> navMesh) {
		if (navMesh == NULL) {
			this->navMesh = NULL;
			return;
		}
		
		NavMeshSetHeader header = navMesh->getMeshHeader();
		Vector3 min(header.params.orig[0], header.params.orig[1], header.params.orig[2]);
		float width = sqrt(header.numTiles >> 2) * header.params.tileWidth;
		min = min + Vector3(width, 0, width);
		info("Loading navmesh (" + name + ") with min " + min.toString() + " Radius: " + String::valueOf(width), true);
		meshBounds = Sphere(min, width);
		this->navMesh = navMesh;
	}
};

#endif
