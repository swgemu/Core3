	/*
 * PortalLayout.cpp
 *
 *  Created on: 03/12/2010
 *      Author: victor
 */

#include "PortalLayout.h"
#include "engine/util/u3d/AStarAlgorithm.h"

void PortalLayout::readPortalGeometry0003(IffStream *iff, int numPortals) {
	portalGeometry.removeAll(numPortals);

	for(int i=0; i<numPortals; i++) {
		iff->openChunk('PRTL');
		uint32 size = iff->getUnsignedInt();

		Reference<PortalGeometry*> portal = new PortalGeometry();
		Reference<MeshData*> mesh = portal->getGeometry();
		Vector<Vector3> *verts = mesh->getVerts();
		Vector<MeshTriangle> *tris = mesh->getTriangles();

		Vector3 min(50000, 50000, 50000);
		Vector3 max(-50000, -50000, -50000);

		verts->removeAll(size);

		for (int i=0; i<size; i++) {
			float x = iff->getFloat();
			float y = iff->getFloat();
			float z = iff->getFloat();

			if(x < min.getX())
				min.setX(x);

			if(x > max.getX())
				max.setX(x);

			if(y < min.getY())
				min.setY(y);

			if (y > max.getY())
				max.setY(y);

			if (z < min.getZ())
				min.setZ(z);

			if (z > max.getZ())
				max.setZ(z);

			Vector3 vert(x, y, z);
			verts->add(vert);
		}

		iff->closeChunk('PRTL');
		portal->setBoundingBox(AABB(min, max));
		Vector3 center = portal->getBoundingBox().center();

		tris->removeAll(size * 2, 2);

		for (int i=0; i<size; i++) {
			Vector3 &vert = verts->get(i);

			vert = center + ((vert - center) * 1.1);

			// Triangle fan
			if ( i >= 2) {
				MeshTriangle triA;
				triA.set(2, 0);
				triA.set(1, i-1);
				triA.set(0, i);
				tris->add(triA);

				MeshTriangle triB;
				triB.set(0, 0);
				triB.set(1, i-1);
				triB.set(2, i);
				tris->add(triB);
			}
		}
		portalGeometry.add(portal);
	}
}

void PortalLayout::readPortalGeometry0004(IffStream *iff, int numPortals) {
	portalGeometry.removeAll(numPortals);

	for(int i=0; i<numPortals; i++) {
		iff->openForm('IDTL');
		iff->openForm('0000');
		Chunk *vertChunk = iff->openChunk('VERT');
		uint32 size = vertChunk->getChunkSize() / 12;

		Reference<PortalGeometry*> portal = new PortalGeometry();
		Reference<MeshData*> mesh = portal->getGeometry();
		Vector<Vector3> *verts = mesh->getVerts();
		Vector<MeshTriangle> *tris = mesh->getTriangles();

		Vector3 min(50000, 50000, 50000);
		Vector3 max(-50000, -50000, -50000);

		verts->removeAll(size);

		for (int i=0; i<size; i++) {
			float x = iff->getFloat();
			float y = iff->getFloat();
			float z = iff->getFloat();

			if(x < min.getX())
				min.setX(x);

			if(x > max.getX())
				max.setX(x);

			if(y < min.getY())
				min.setY(y);

			if (y > max.getY())
				max.setY(y);

			if (z < min.getZ())
				min.setZ(z);

			if (z > max.getZ())
				max.setZ(z);

			Vector3 vert(x, y, z);
			verts->add(vert);
		}

		iff->closeChunk('VERT');

		portal->setBoundingBox(AABB(min, max));
		Vector3 center = portal->getBoundingBox().center();

		Chunk *indxChunk = iff->openChunk('INDX');

		uint32 numIdx = indxChunk->getChunkSize() / 12;

		tris->removeAll(numIdx);

		for (int i=0; i<numIdx; i++) {
			int a = iff->getInt();
			int b = iff->getInt();
			int c = iff->getInt();
			tris->add(MeshTriangle(c, b, a));
		}

		iff->closeChunk('INDX');
		iff->closeForm('0000');
		iff->closeForm('IDTL');

		portalGeometry.add(portal);
	}
}

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

		uint32 numPortals = iffStream->getInt();
		uint32 numCells = iffStream->getInt();

		iffStream->closeChunk('DATA');

		iffStream->openForm('PRTS');

		if (type == '0003')
			readPortalGeometry0003(iffStream, numPortals);
		else
			readPortalGeometry0004(iffStream, numPortals);

		iffStream->closeForm('PRTS');

		//open CELS form
		parseCELSForm(iffStream, numCells);

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

	for (auto& cell : cellProperties) {
		for (int i=0; i<cell->getNumberOfPortals(); i++) {
			const CellPortal* portal = cell->getPortal(i);
			int idx = portal->getGeometryIndex();

			for (auto& connected : cellProperties) {
				if (cell == connected)
					continue;

				for (int j=0; j<connected->getNumberOfPortals(); j++) {
					const CellPortal* connectedPortal = connected->getPortal(j);
					if (connectedPortal->getGeometryIndex() == idx) {
						cell->addConnectedCell(connected->getCellID());
					}
				}
			}
		}
	}

	connectFloorMeshGraphs();
}

int PortalLayout::getCellID(const String& cellName) {
	for (int i = 0; i < cellProperties.size(); ++i) {
		CellProperty* cell = cellProperties.get(i);

		if (cell->getName() == cellName)
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

void PortalLayout::parseCELSForm(IffStream* iffStream, int numCells) {
	try {
		iffStream->openForm('CELS');

		uint32 nextType;

		for (int i=0; i<numCells; i++) {
			Reference<CellProperty*> cell = new CellProperty(cellProperties.size());
			cell->readObject(iffStream);
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

uint32 PortalLayout::loadCRC(IffStream* iffStream) {
	uint32 crc = 0;
	try {
		iffStream->openForm('PRTO');
		uint32 type = iffStream->getNextFormType();
		iffStream->openForm(type);

		Chunk *chunk = iffStream->openChunk();
		while (chunk != NULL && chunk->getChunkID() != 'CRC ') // Yes the space is intentional
		{
			iffStream->closeChunk();
			chunk = iffStream->openChunk();
		}

		if (chunk != NULL && chunk->getChunkID() == 'CRC ')
			crc = iffStream->getUnsignedInt();

		iffStream->closeChunk('CRC ');
		iffStream->closeForm(type);
		iffStream->closeForm('PRTO');
	} catch (Exception& e) {
		String err = "unable to parse portal crc ";
		err += iffStream->getFileName();
		static Logger logger;
		logger.error(err);
	}

	return crc;
}
