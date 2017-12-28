/*
 * WorldSnapshotIff.h
 *
 *  Created on: Mar 30, 2011
 *      Author: crush
 */

#ifndef WORLDSNAPSHOTIFF_H_
#define WORLDSNAPSHOTIFF_H_

#include <algorithm>

#include "system/lang/String.h"
#include "system/util/Vector.h"
#include "templates/IffTemplate.h"
#include "templates/snapshot/WorldSnapshotNode.h"

namespace engine {
namespace util {
class IffStream;
}  // namespace util
}  // namespace engine

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
