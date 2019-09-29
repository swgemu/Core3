/*
 * PathGraph.h
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#ifndef PATHGRAPH_H_
#define PATHGRAPH_H_

#include "templates/appearance/PathNode.h"
#include "templates/IffTemplate.h"

class FloorMesh;

class PathGraph : public IffTemplate {
	enum PathGraphType
	{
		Cell,
		Building,
		City,

		None,
	};


	Vector<PathNode*> pathNodes;
	Vector<PathEdge> pathEdges;

	PathGraphType type;

	Vector<int> edgeCounts;
	Vector<int> edgeStarts;

	FloorMesh* floorMesh;

protected:
	void connectNodes(Vector<PathEdge>& pathEdges);

public:
	PathGraph(FloorMesh* floor) {
		floorMesh = floor;
		type = None;
	}

	~PathGraph() {
		pathNodes.forEach([](auto node) { delete node; });
	}

	void readObject(IffStream* iffStream);

	static float calculateManhattanDistance(const PathNode* node1, const PathNode* node2) {
		/*return abs(node1->getX() - node2->getX()) + abs(node1->getY() - node2->getY())
				+ abs(node1->getZ() - node2->getZ());*/

		return node1->getPosition().squaredDistanceTo(node2->getPosition());
	}

	const PathNode* getNode(int globalNumberID) const;

	inline const PathNode* findNearestNode(float x, float z, float y) const {
		return findNearestNode(Vector3(x, y, z));
	}

	const PathNode* findNearestNode(const Vector3& pointAlfa) const;
	Vector<const PathNode*> getEntrances() const;
	const PathNode* findNearestGlobalNode(const Vector3& pointAlfa) const;
	const PathNode* findGlobalNode(int globalNodeID) const;

	inline void addPathNode(PathNode* pathNode) {
		pathNodes.add(pathNode);
	}

	inline const Vector<PathEdge>* getPathEdges() const {
		return &pathEdges;
	}

	inline const Vector<PathNode*>* getPathNodes() const {
		return &pathNodes;
	}

	inline Vector<const PathNode*> getGlobalNodes() const {
		Vector<const PathNode*> nodes;

		for (int i = 0; i < pathNodes.size(); ++i) {
			if (pathNodes.get(i)->getGlobalGraphNodeID() != -1)
				nodes.add(pathNodes.get(i));
		}

		return nodes;
	}

	inline Vector<PathNode*> getGlobalNodes() {
		Vector<PathNode*> nodes;

		for (int i = 0; i < pathNodes.size(); ++i) {
			if (pathNodes.get(i)->getGlobalGraphNodeID() != -1)
				nodes.add(pathNodes.get(i));
		}

		return nodes;
	}

	inline const FloorMesh* getFloorMesh() const {
		return floorMesh;
	}

	inline PathGraphType getType() const {
		return type;
	}

};


#endif /* PATHGRAPH_H_ */
