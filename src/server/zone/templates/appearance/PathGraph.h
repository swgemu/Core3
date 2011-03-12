/*
 * PathGraph.h
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#ifndef PATHGRAPH_H_
#define PATHGRAPH_H_

#include "PathNode.h"
#include "../IffTemplate.h"

class FloorMesh;

class PathGraph : public IffTemplate {
	Vector<PathNode*> pathNodes;
	//Vector<PathEdge> pathEdges;

	int unkownMetaInt;

	Vector<int> ecnt;
	Vector<int> estr;

	FloorMesh* floorMesh;

protected:
	void connectNodes(Vector<PathEdge>& pathEdges);

public:
	PathGraph(FloorMesh* floor) {
		floorMesh = floor;
	}

	~PathGraph() {
		while (pathNodes.size() > 0)
			delete pathNodes.remove(0);
	}

	void readObject(IffStream* iffStream);

	float calculateManhattanDistance(PathNode* node1, PathNode* node2) {
		/*return abs(node1->getX() - node2->getX()) + abs(node1->getY() - node2->getY())
				+ abs(node1->getZ() - node2->getZ());*/

		return node1->getPosition().squaredDistanceTo(node2->getPosition());
	}

	PathNode* getNode(int globalNumberID);

	inline PathNode* findNearestNode(float x, float z, float y) {
		return findNearestNode(Vector3(x, y, z));
	}

	PathNode* findNearestNode(const Vector3& pointAlfa);
	PathNode* findNearestGlobalNode(const Vector3& pointAlfa);
	PathNode* findGlobalNode(int globalNodeID);

	inline void addPathNode(PathNode* pathNode) {
		pathNodes.add(pathNode);
	}

	inline Vector<PathNode*>* getPathNodes() {
		return &pathNodes;
	}

	inline Vector<PathNode*> getGlobalNodes() {
		Vector<PathNode*> nodes;

		for (int i = 0; i < pathNodes.size(); ++i) {
			if (pathNodes.get(i)->getGlobalGraphNodeID() != -1)
				nodes.add(pathNodes.get(i));
		}

		return nodes;
	}

	inline FloorMesh* getFloorMesh() {
		return floorMesh;
	}

};


#endif /* PATHGRAPH_H_ */
