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

	type = static_cast<PathGraphType>(iffStream->getInt());

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
		edgeCounts.add(iffStream->getInt());
	}

	iffStream->closeChunk('ECNT');

	iffStream->openChunk('ESTR');

	int estrSize = iffStream->getInt();

	for (int i = 0; i < estrSize; ++i) {
		edgeStarts.add(iffStream->getInt());
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

osg::ref_ptr<osg::Node> PathGraph::draw() {
	osg::Group* group = new osg::Group();
	osg::Geode* geode = new osg::Geode();
	geode->setName("PathGraph");
	osg::Geometry* geometry( new osg::Geometry() );
	osg::Vec3Array* vertices( new osg::Vec3Array() );
	
	
	for (int i = 0; i < pathEdges.size(); ++i) {
		PathEdge* pathEdge = &(pathEdges.get(i));
		
		int from = pathEdge->getFromConnection();
		int to = pathEdge->getToConnection();
		
		PathNode* fromNode = pathNodes.get(from);
		PathNode* toNode = pathNodes.get(to);
		
		vertices->push_back(osg::Vec3f(fromNode->getX(), fromNode->getZ()+0.2, fromNode->getY()));
		vertices->push_back(osg::Vec3f(toNode->getX(), toNode->getZ()+0.2, toNode->getY()));
	}
	
	
	for (int i=0; i < pathNodes.size(); i++) {
		PathNode *node = pathNodes.get(i);
		
		// create high detail sphere and add to our lod
		osg::TessellationHints* hints = new osg::TessellationHints;
		hints->setDetailRatio(0.05f);
		osg::Geode* geode2 = new osg::Geode();
		geode2->addDrawable( new osg::ShapeDrawable( new osg::Sphere(osg::Vec3(node->getX(), node->getZ()+0.2, node->getY()), 0.5), hints ) );
		
		geode2->getOrCreateStateSet()->setAttribute( new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE) );
		group->addChild(geode2);
		
	}
	
	geometry->setVertexArray(vertices);
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, vertices->size()));
	
	osg::Vec4Array* colors( new osg::Vec4Array() );
	colors->push_back( osg::Vec4( 0.0f, 0.0f, 1.0f, 0.5f ) );
	geometry->setColorArray( colors );
	geometry->setColorBinding( osg::Geometry::BIND_OVERALL );
	
	geode->addDrawable( geometry );
	
	group->addChild(geode);
	
	osg::StateSet* state = geode->getOrCreateStateSet();
	
	state->setMode(GL_LIGHTING, false);
	
 
	return group;
}
