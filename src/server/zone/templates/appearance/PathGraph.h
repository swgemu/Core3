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

class PathGraph : public IffTemplate {
	Vector<PathNode> pathNodes;
	//Vector<PathEdge> pathEdges;

	int unkownMetaInt;

	Vector<int> ecnt;
	Vector<int> estr;

protected:
	void connectNodes(Vector<PathEdge>& pathEdges);

public:
	PathGraph() {
	}

	void readObject(IffStream* iffStream);

};


#endif /* PATHGRAPH_H_ */
