#include "ActiveAreaQuadTree.h"

using namespace server::zone;

ActiveAreaQuadTreeNode::ActiveAreaQuadTreeNode() {
	activeAreas.setNoDuplicateInsertPlan();

	minX = 0;
	minY = 0;
	maxX = 0;
	maxY = 0;

	dividerX = 0;
	dividerY = 0;
}

ActiveAreaQuadTreeNode::ActiveAreaQuadTreeNode(float minx, float miny, float maxx, float maxy, ActiveAreaQuadTreeNode *parent) {
	activeAreas.setNoDuplicateInsertPlan();

	parentNode = parent;

	minX = minx;
	minY = miny;
	maxX = maxx;
	maxY = maxy;

	dividerX = (minX + maxX) / 2;
	dividerY = (minY + maxY) / 2;
}

ActiveAreaQuadTreeNode::~ActiveAreaQuadTreeNode() {
}
