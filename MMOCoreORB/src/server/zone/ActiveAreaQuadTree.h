#ifndef ACTIVEAREAQUADTREE_H_
#define ACTIVEAREAQUADTREE_H_

#include "system/lang.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/ActiveAreaQuadTreeNode.h"

namespace server {
namespace zone {

class ActiveAreaQuadTree : public Object {
	Reference<ActiveAreaQuadTreeNode*> root;

public:
	ActiveAreaQuadTree() {
		root = nullptr;
	}

	ActiveAreaQuadTree(float minx, float miny, float maxx, float maxy) {
		root = new ActiveAreaQuadTreeNode(minx, miny, maxx, maxy, nullptr);
	}


	void getActiveAreas(float x, float y, Vector<ActiveArea*>& areas) const {
		getActiveAreas(root, x, y, areas);
	}

	void getActiveAreas(const Reference<ActiveAreaQuadTreeNode*>& node, float x, float y, Vector<ActiveArea*>& areas) const {
		if (node == nullptr) {
			return;
		}

		for (const auto& areaEntry : node->activeAreas) {
			if (areaEntry->containsPoint(x, y)) {
				areas.add(areaEntry->getArea());
			}
		}

		const auto& nodeSW = node->swNode;
		const auto& nodeSE = node->seNode;
		const auto& nodeNW = node->nwNode;
		const auto& nodeNE = node->neNode;

		if (nodeSW != nullptr && nodeSW->testInside(x, y)) {
			getActiveAreas(nodeSW.get(), x, y, areas);
		}
		else if (nodeSE != nullptr && nodeSE->testInside(x, y)) {
			getActiveAreas(nodeSE.get(), x, y, areas);
		}
		else if (nodeNW != nullptr && nodeNW->testInside(x, y)) {
			getActiveAreas(nodeNW.get(), x, y, areas);
		}
		else if (nodeNE != nullptr && nodeNE->testInside(x, y)) {
			getActiveAreas(nodeNE.get(), x, y, areas);
		}
	}

	void insert(Reference<ActiveArea*> area) {
		insert(root, area);
	}

	void insert(const Reference<ActiveAreaQuadTreeNode*>& node, Reference<ActiveArea*> area) {
	/*	if (node == root) {
			System::out << "inserting to activearea quad tree\n";
			StackTrace::printStackTrace();
		}*/
		if (!node->hasSubNodes()) {
			if ((node->maxX - node->minX <= 8) && (node->maxY - node->minY <= 8)) {
				node->insertArea(area);

				return;
			}
		}

		if (node->testAreaInside(area)) {
			if (node->testInSWArea(area)) {
				if (node->swNode == nullptr) {
					node->swNode = new ActiveAreaQuadTreeNode(node->minX, node->minY, node->dividerX, node->dividerY, node);
				}

				insert(node->swNode, area);

				return;
			}
			else if (node->testInNWArea(area)) {
				if (node->nwNode == nullptr)
					node->nwNode = new ActiveAreaQuadTreeNode(node->minX, node->dividerY, node->dividerX, node->maxY, node);

				insert(node->nwNode, area);

				return;
			}
			else if (node->testInSEArea(area)) {
				if (node->seNode == nullptr)
					node->seNode = new ActiveAreaQuadTreeNode(node->dividerX, node->minY, node->maxX, node->dividerY, node);

				insert(node->seNode, area);

				return;
			}
			else if (node->testInNEArea(area)) {
				if (node->neNode == nullptr)
					node->neNode = new ActiveAreaQuadTreeNode(node->dividerX, node->dividerY, node->maxX, node->maxY, node);

				insert(node->neNode, area);

				return;
			}
		}

		// insert here
		node->insertArea(area);

		return;
	}

	void remove(Reference<ActiveArea*> area) {
		insert(root, area);
	}

	void remove(const Reference<ActiveAreaQuadTreeNode*>& node, Reference<ActiveArea*> area) const {
/*		if (node == root) {
			System::out << "removing from activearea quad tree\n";
			StackTrace::printStackTrace();
		}*/
		if (node == nullptr) {
			return;
		}

		for (const auto& areaEntry : node->activeAreas) {
			if (areaEntry->getArea() == area) {
				node->removeArea(areaEntry);
			}
		}

		float x = area->getPositionX();
		float y = area->getPositionY();

		const auto& nodeSW = node->swNode;
		const auto& nodeSE = node->seNode;
		const auto& nodeNW = node->nwNode;
		const auto& nodeNE = node->neNode;

		if (nodeSW != nullptr && nodeSW->testInside(x, y)) {
			remove(nodeSW.get(), area);
		}
		else if (nodeSE != nullptr && nodeSE->testInside(x, y)) {
			remove(nodeSE.get(), area);
		}
		else if (nodeNW != nullptr && nodeNW->testInside(x, y)) {
			remove(nodeNW.get(), area);
		}
		else if (nodeNE != nullptr && nodeNE->testInside(x, y)) {
			remove(nodeNE.get(), area);
		}
	}
};
} // namespace zone
} // namespace server

#endif /* ACTIVEAREAQUADTREE_H_ */
