/*
 * PathGraph.cpp
 *
 *  Created on: 03/12/2010
 *      Author: victor
 */

#include "PathGraph.h"
#include "engine/util/u3d/AStarAlgorithm.h"
#include "FloorMesh.h"

uint32 PathNode::getID() {
	int cellID = pathGraph->getFloorMesh()->getCellID();

	return (cellID << 16) + id;
}

void PathGraph::readObject(IffStream* iffStream) {
	iffStream->openForm('PGRF');
	iffStream->openForm('0001');
	iffStream->openChunk('META');

	unkownMetaInt = iffStream->getInt();

	iffStream->closeChunk('META');

	iffStream->openChunk('PNOD');

	int nodesSize = iffStream->getInt();

	for (int i = 0; i < nodesSize; ++i) {
		PathNode* pathNode = new PathNode(this);

		pathNode->readObject(iffStream);

		pathNodes.add(pathNode);
	}

	iffStream->closeChunk('PNOD');

	iffStream->openChunk('PEDG');

	Vector<PathEdge> pathEdges;

	int pathEdgeSize = iffStream->getInt();

	for (int i = 0; i < pathEdgeSize; ++i) {
		PathEdge pathEdge;

		pathEdge.readObject(iffStream);

		pathEdges.add(pathEdge);
	}

	iffStream->closeChunk('PEDG');

	iffStream->openChunk('ECNT');

	int ecntSize = iffStream->getInt();

	for (int i = 0; i < ecntSize; ++i) {
		ecnt.add(iffStream->getInt());
	}

	iffStream->closeChunk('ECNT');

	iffStream->openChunk('ESTR');

	int estrSize = iffStream->getInt();

	for (int i = 0; i < estrSize; ++i) {
		estr.add(iffStream->getInt());
	}

	iffStream->closeChunk('ESTR');
	iffStream->closeForm('0001');
	iffStream->closeForm('PGRF');

	connectNodes(pathEdges);
}

PathNode* PathGraph::getNode(int globalNumberID) {
	for (int i = 0; i < pathNodes.size(); ++i) {
		PathNode* pathNode = pathNodes.get(i);

		if (pathNode->getGlobalGraphNodeID() == globalNumberID)
			return pathNode;
	}

	return NULL;
}

PathNode* PathGraph::findGlobalNode(int globalNodeID) {
	for (int i = 0; i < pathNodes.size(); ++i) {
		PathNode* pathNode = pathNodes.get(i);

		if (pathNode->getGlobalGraphNodeID() == globalNodeID)
			return pathNode;
	}

	return NULL;
}

PathNode* PathGraph::findNearestGlobalNode(const Vector3& pointAlfa) {
	float minDistance = 160000000.f;
	PathNode* node = NULL;

	for (int i = 0; i < pathNodes.size(); ++i) {
		PathNode* pathNode = pathNodes.get(i);

		if (pathNode->getGlobalGraphNodeID() == -1)
			continue;

		Vector3 point(pathNode->getX(), pathNode->getY(), pathNode->getZ());

		float sqrDistance = pointAlfa.squaredDistanceTo(point);

		if (sqrDistance < minDistance) {
			minDistance = sqrDistance;
			node = pathNode;
		}
	}

	return node;
}

PathNode* PathGraph::findNearestNode(const Vector3& pointAlfa) {
	float minDistance = 160000000.f;
	PathNode* node = NULL;

	for (int i = 0; i < pathNodes.size(); ++i) {
		PathNode* pathNode = pathNodes.get(i);

		Vector3 point(pathNode->getX(), pathNode->getY(), pathNode->getZ());

		float sqrDistance = pointAlfa.squaredDistanceTo(point);

		if (sqrDistance < minDistance) {
			minDistance = sqrDistance;
			node = pathNode;
		}
	}

	return node;
}

void PathGraph::connectNodes(Vector<PathEdge>& pathEdges) {
	for (int i = 0; i < pathEdges.size(); ++i) {
		PathEdge* pathEdge = &pathEdges.get(i);

		int from = pathEdge->getFromConnection();
		int to = pathEdge->getToConnection();

		PathNode* fromNode = pathNodes.get(from);
		PathNode* toNode = pathNodes.get(to);

		/*Vector<PathNode*>* path = AStarAlgorithm<PathGraph, PathNode>::search<uint32>(this, fromNode, toNode);

		if (path != NULL) {
			System::out << "found path\n";
			delete path;
		} else {
			System::out << "didint find path\n";
		}*/

		fromNode->addChild(toNode);
	}
}
