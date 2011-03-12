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
	cellTotalNumber = 0;
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

void PortalLayout::connectFloorMeshGraphs() {
	for (int i = 0; i < floorMeshes.size(); ++i) {
		FloorMesh* floorMesh = floorMeshes.get(i);
		PathGraph* pathGraph = floorMesh->getPathGraph();

		if (pathGraph == NULL)
			continue;

		Vector<PathNode*> globalNodes = pathGraph->getGlobalNodes();

		for (int j = 0; j < globalNodes.size(); ++j) {
			PathNode* node = globalNodes.get(j);

			int globalID = node->getGlobalGraphNodeID();

			for (int k = 0; k < floorMeshes.size(); ++k) {
				if (i != k) {
					FloorMesh* newMesh = floorMeshes.get(k);
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

int PortalLayout::getFloorMeshID(int globalNodeID, int floorMeshToExclude) {
	for (int i = 0; i < floorMeshes.size(); ++i) {
		if (i == floorMeshToExclude)
			continue;

		FloorMesh* floorMesh = floorMeshes.get(i);
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
			try {
				iffStream->openForm('CELL');

				++cellTotalNumber;
				uint32 nextForm = iffStream->getNextFormType();

				if (nextForm != '0005') {
					//SWGForensics::instance->printToConsole(QString("wrong cell form ") + iffStream->getFileName().c_str());
					error(String("wrong cell form ") + iffStream->getFileName());

					continue;
				}

				iffStream->openForm('0005');

				Chunk* dataChunk = iffStream->openChunk('DATA');

				int sizeunk = iffStream->getInt();

				int readCase = iffStream->getByte();

				String cellName;
				iffStream->getString(cellName);

				String meshFile;
				iffStream->getString(meshFile);

				if (meshFile.length() > 1) {
					AppearanceTemplate* app = TemplateManager::instance()->getAppearanceTemplate(meshFile);

					if (app != NULL)
						appearanceTemplates.add(dynamic_cast<MeshAppearanceTemplate*>(app->getFirstMesh()));
				}

				int readCase2 = iffStream->getByte();

				if (dataChunk->hasData()) {
					String floorFile;
					iffStream->getString(floorFile);

					if (floorFile.length() > 1) {
						FloorMesh* floorMesh = TemplateManager::instance()->getFloorMesh(floorFile);

						floorMeshes.add(floorMesh);

						floorMesh->setCellID(floorMeshes.size() - 1);
					} else
						floorMeshes.add(NULL);
				} else
					floorMeshes.add(NULL);

				iffStream->closeChunk();

				iffStream->closeForm('0005');

				iffStream->closeForm('CELL');
			} catch (Exception& e) {
				error(e.getMessage());
				error("parsing CELL for " + iffStream->getFileName());
				e.printStackTrace();
			} catch (...) {
				error("parsing CELL for " + iffStream->getFileName());

				throw;
			}
		}

		iffStream->closeForm('CELS');

	} catch (Exception& e) {
		error(e.getMessage());
		error("parsing CELS for " + iffStream->getFileName());
	} catch (...) {
		//error("parsing CELS for " + iffStream->getFileName());

		throw;
	}


	if (cellTotalNumber > 0)
		--cellTotalNumber;
}

Vector<PathNode*>* PortalLayout::getPath(PathNode* node1, PathNode* node2) {
	return AStarAlgorithm<PathGraph, PathNode>::search<uint32>(node1->getPathGraph(), node1, node2);
}
