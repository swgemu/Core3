/*
 * PortalLayout.cpp
 *
 *  Created on: 03/12/2010
 *      Author: victor
 */

#include "PortalLayout.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "MeshAppearanceTemplate.h"
#include "PathNode.h"
#include "FloorMesh.h"
#include "engine/util/u3d/AStarAlgorithm.h"

PortalLayout::PortalLayout() {
	pathGraph = NULL;

	setLoggingName("PortalLayout");
}

PortalLayout::~PortalLayout() {
	delete pathGraph;
	pathGraph = NULL;
}

void PortalLayout::parse(IffStream* iffStream) {
	try {
		iffStream->openForm('PRTO');

		uint32 type = iffStream->getNextFormType();

		if (type != '0003' && type != '0004') {
			StringBuffer stream;
			stream << "invalid PROTO type 0x" << hex << type;
			error(stream);

			return;
		}

		iffStream->openForm(type);

		Chunk* data = iffStream->openChunk('DATA');

		uint32 var1 = iffStream->getInt();
		uint32 var2 = iffStream->getInt();

		iffStream->closeChunk('DATA');

		iffStream->openForm('PRTS');

		//skipping PRTS
		iffStream->closeForm('PRTS');

		//open CELS form
		parseCELSForm(iffStream);

		//path graph

		uint32 nextType = iffStream->getNextFormType();

		if (nextType == 'PGRF') {
			pathGraph = new PathGraph(NULL);
			pathGraph->readObject(iffStream);
		}

		iffStream->closeForm(type);

		iffStream->closeForm('PRTO');
	} catch (Exception& e) {
		String err = "unable to parse file ";
		err += iffStream->getFileName();
		error(err);
	}

	connectFloorMeshGraphs();
}

int PortalLayout::getCellID(const String& cellName) {
	for (int i = 0; i < cellProperties.size(); ++i) {
		CellProperty& cell = cellProperties.get(i);

		if (cell.getName() == cellName)
			return i;
	}

	return -1;
}

void PortalLayout::connectFloorMeshGraphs() {
	for (int i = 0; i < cellProperties.size(); ++i) {
		FloorMesh* floorMesh = getFloorMesh(i);

		if (floorMesh == NULL)
			continue;

		PathGraph* pathGraph = floorMesh->getPathGraph();

		if (pathGraph == NULL)
			continue;

		Vector<PathNode*> globalNodes = pathGraph->getGlobalNodes();

		for (int j = 0; j < globalNodes.size(); ++j) {
			PathNode* node = globalNodes.get(j);

			int globalID = node->getGlobalGraphNodeID();

			for (int k = 0; k < cellProperties.size(); ++k) {
				if (i != k) {
					FloorMesh* newMesh = getFloorMesh(k);

					if (newMesh != NULL) {
						PathGraph* newPathGraph = newMesh->getPathGraph();

						if (newPathGraph != NULL) {
							Vector<PathNode*> newGlobalNodes = newPathGraph->getGlobalNodes();

							for (int l = 0; l < newGlobalNodes.size(); ++l) {
								PathNode* newNode = newGlobalNodes.get(l);

								int newGlobalID = newNode->getGlobalGraphNodeID();

								if (globalID == newGlobalID)
									node->addChild(newNode);
							}
						}
					}
				}
			}
		}
	}

}

int PortalLayout::getFloorMeshID(int globalNodeID, int floorMeshToExclude) {
	for (int i = 0; i < cellProperties.size(); ++i) {
		if (i == floorMeshToExclude)
			continue;

		FloorMesh* floorMesh = getFloorMesh(i);
		PathNode* node = floorMesh->getGlobalNode(globalNodeID);

		if (node != NULL)
			return i;
	}

	return -1;
}

void PortalLayout::parseCELSForm(IffStream* iffStream) {
	try {
		iffStream->openForm('CELS');

		uint32 nextType;

		while (iffStream->getRemainingSubChunksNumber() > 0 && (nextType = iffStream->getNextFormType()) == 'CELL') {
			CellProperty cell(cellProperties.size());

			try {
				cell.readObject(iffStream);
			} catch (Exception& e) {
				error(e.getMessage());
			} catch (...) {
				error("Unreported exception caught parsing cell property");
			}

			cellProperties.add(cell);
		}

		iffStream->closeForm('CELS');

	} catch (Exception& e) {
		error(e.getMessage());
		error("parsing CELS for " + iffStream->getFileName());
	} catch (...) {
		//error("parsing CELS for " + iffStream->getFileName());

		throw;
	}
}

Vector<PathNode*>* PortalLayout::getPath(PathNode* node1, PathNode* node2) {
	return AStarAlgorithm<PathGraph, PathNode>::search<uint32>(node1->getPathGraph(), node1, node2);
}
