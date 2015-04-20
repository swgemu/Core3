/*
 * PortalLayout.h
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#ifndef PORTALLAYOUT_H_
#define PORTALLAYOUT_H_

#include "../IffTemplate.h"
#include "CellProperty.h"

class MeshAppearanceTemplate;
class PathNode;
class FloorMesh;
class PathGraph;

class PortalLayout : public IffTemplate, public Logger {
	PathGraph* pathGraph;

	Vector<CellProperty> cellProperties;
public:
	PortalLayout();
	~PortalLayout();

	void readObject(IffStream* templateData) {
		parse(templateData);
	}

	void parse(IffStream* iffStream);

	void parseCELSForm(IffStream* iffStream);

	void connectFloorMeshGraphs();

	int getFloorMeshID(int globalNodeID, int floorMeshToExclude);

	Vector<PathNode*>* getPath(PathNode* node1, PathNode* node2);

	int getCellID(const String& cellName);

	inline int getCellTotalNumber() {
		return MAX(0, cellProperties.size() - 1); //exclude the outside cell
	}

	inline int getFloorMeshNumber() {
		return cellProperties.size();
	}

	inline FloorMesh* getFloorMesh(int cellIndex) {
		return cellProperties.get(cellIndex).getFloorMesh();
	}

	inline MeshAppearanceTemplate* getMeshAppearanceTemplate(int cellIndex) {
		return cellProperties.get(cellIndex).getAppearanceTemplate();
	}

	inline int getAppearanceTemplatesSize() {
		return cellProperties.size();
	}

};

#endif /* PORTALLAYOUT_H_ */
