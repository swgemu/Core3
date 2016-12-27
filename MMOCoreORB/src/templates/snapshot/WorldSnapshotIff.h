/*
 * WorldSnapshotIff.h
 *
 *  Created on: Mar 30, 2011
 *      Author: crush
 */

#ifndef WORLDSNAPSHOTIFF_H_
#define WORLDSNAPSHOTIFF_H_

#include "templates/IffTemplate.h"
#include "templates/snapshot/WorldSnapshotNode.h"

class WorldSnapshotIff : public IffTemplate {
	Vector<WorldSnapshotNode> nodes;
	Vector<String> objectTemplateNameList;

public:
	WorldSnapshotIff();

	void readObject(IffStream* iffStream);

	inline int getNodeCount() {
		return nodes.size();
	}

	inline WorldSnapshotNode* getNode(int idx) {
		return &nodes.get(idx);
	}

	inline String getObjectTemplateName(int idx) const {
		return objectTemplateNameList.get(idx);
	}
};

#endif /* WORLDSNAPSHOTIFF_H_ */
