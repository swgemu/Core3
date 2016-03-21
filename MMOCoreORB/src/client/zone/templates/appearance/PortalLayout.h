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
#include <osg/Node>
#include <osg/Geometry>
#include <osg/Notify>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osgViewer/Viewer>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osgGA/StateSetManipulator>

class MeshAppearanceTemplate;
class PathNode;
class FloorMesh;
class PathGraph;

class PortalLayout : public IffTemplate, public Logger {
	PathGraph* pathGraph;
	uint32 crc;
	Vector<CellProperty> cellProperties;
	FloorMesh* floorMesh;
	String name;
	String appearanceName;
	
	
public:
	PortalLayout();
	~PortalLayout();

	uint32 getCRC() {
		return crc;
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

	inline AppearanceTemplate* getMeshAppearanceTemplate(int cellIndex) {
		return cellProperties.get(cellIndex).getAppearanceTemplate();
	}

	inline int getAppearanceTemplatesSize() {
		return cellProperties.size();
	}
	virtual Vector<MeshData*> getTransformedMeshData(Matrix4 transform);
	
	static uint32 loadCRC(IffStream* iffStream);

	osg::ref_ptr<osg::Node> draw();
};

#endif /* PORTALLAYOUT_H_ */
