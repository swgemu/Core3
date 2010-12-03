/*
 * PathGraph.cpp
 *
 *  Created on: 03/12/2010
 *      Author: victor
 */

#include "PathGraph.h"


void PathGraph::readObject(IffStream* iffStream) {
	iffStream->openForm('PGRF');
	iffStream->openForm('0001');
	iffStream->openChunk('META');

	unkownMetaInt = iffStream->getInt();

	iffStream->closeChunk('META');

	iffStream->openChunk('PNOD');

	int nodesSize = iffStream->getInt();

	for (int i = 0; i < nodesSize; ++i) {
		PathNode pathNode;

		pathNode.readObject(iffStream);

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

void PathGraph::connectNodes(Vector<PathEdge>& pathEdges) {
	for (int i = 0; i < pathEdges.size(); ++i) {
		PathEdge* pathEdge = &pathEdges.get(i);

		int from = pathEdge->getFromConnection();
		int to = pathEdge->getToConnection();

		PathNode* fromNode = &pathNodes.get(from);
		PathNode* toNode = &pathNodes.get(to);

		fromNode->addChild(toNode);
	}
}
