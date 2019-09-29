/*
 * PortalLayout.h
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#ifndef PORTALLAYOUT_H_
#define PORTALLAYOUT_H_

#include "templates/IffTemplate.h"
#include "templates/appearance/CellProperty.h"
#include "templates/appearance/MeshData.h"
#include "templates/appearance/PathNode.h"
#include "templates/appearance/FloorMesh.h"
#include "templates/appearance/AppearanceTemplate.h"
#include "templates/appearance/PathGraph.h"

class PortalGeometry : public Object {
	Reference<MeshData*> geometry;
	AABB boundingBox;
public:
	PortalGeometry() : geometry(new MeshData()), boundingBox(Vector3(0, 0, 0), Vector3(0, 0, 0)) { }

	MeshData* getGeometry() {
		return geometry;
	}

	const MeshData* getGeometry() const {
		return geometry;
	}

	const AABB& getBoundingBox() const {
		return boundingBox;
	}

	void setBoundingBox(const AABB& aabb) {
		boundingBox = aabb;
	}
};

class PortalLayout : public IffTemplate, public Logger {
	PathGraph* pathGraph;
	Vector<Reference<PortalGeometry*> > portalGeometry;
	Vector<Reference<CellProperty*> > cellProperties;
public:
	PortalLayout();
	~PortalLayout();

	const PathGraph *getPathGraph() const {
		return pathGraph;
	}

	void readPortalGeometry0003(IffStream *iff, int numPortals);
	void readPortalGeometry0004(IffStream *iff, int numPortals);

	void readObject(IffStream* templateData) {
		parse(templateData);
	}

	void parse(IffStream* iffStream);

	void parseCELSForm(IffStream* iffStream, int numCells);

	void connectFloorMeshGraphs();

	int getFloorMeshID(int globalNodeID, int floorMeshToExclude) const;

	Vector<const PathNode*>* getPath(const PathNode* node1, const PathNode* node2) const;

	int getCellID(const String& cellName) const;

	inline int getCellTotalNumber() const {
		//exclude the outside cell
		return Math::max(0, cellProperties.size() - 1);
	}

	inline int getFloorMeshNumber() const {
		return cellProperties.size();
	}

	inline const FloorMesh* getFloorMesh(int cellIndex) const {
		return cellProperties.get(cellIndex)->getFloorMesh();
	}

	inline FloorMesh* getFloorMesh(int cellIndex) {
		return cellProperties.get(cellIndex)->getFloorMesh();
	}

	inline const AppearanceTemplate* getAppearanceTemplate(int cellIndex) const {
		return cellProperties.get(cellIndex)->getAppearanceTemplate();
	}

	const Vector<Reference<CellProperty*> >& getCellProperties() const {
		return cellProperties;
	}

	inline const CellProperty* getCellProperty(int cellIndex) const {
		return cellProperties.get(cellIndex);
	}

	inline int getAppearanceTemplatesSize() const {
		return cellProperties.size();
	}

	inline const MeshData* getPortalGeometry(int idx) const {
		return portalGeometry.get(idx)->getGeometry();
	}

	const AABB& getPortalBounds(int idx) const {
		return portalGeometry.get(idx)->getBoundingBox();
	}

	static uint32 loadCRC(IffStream* iffStream);
};

#endif /* PORTALLAYOUT_H_ */
