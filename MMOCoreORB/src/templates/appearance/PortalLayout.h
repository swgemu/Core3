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

class AppearanceTemplate;
class PathNode;
class FloorMesh;
class PathGraph;

class PortalLayout : public IffTemplate, public Logger {
	PathGraph* pathGraph;

	Vector<CellProperty> cellProperties;
public:
	PortalLayout();
	~PortalLayout();
	
	PathGraph *getPathGraph() {
		return pathGraph;
	}

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

	inline AppearanceTemplate* getAppearanceTemplate(int cellIndex) {
		return cellProperties.get(cellIndex).getAppearanceTemplate();
	}
	
	inline CellProperty getCellProperty(int cellIndex) {
		return cellProperties.get(cellIndex);
	}

	inline int getAppearanceTemplatesSize() {
		return cellProperties.size();
	}

	static uint32 loadCRC(IffStream* iffStream);
};

#endif /* PORTALLAYOUT_H_ */
