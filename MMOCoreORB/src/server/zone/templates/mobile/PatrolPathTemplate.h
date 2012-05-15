/*
 * PatrolPathTemplate.h
 *
 *  Created on: 20/01/2012
 *      Author: victor
 */

#ifndef PATROLPATHTEMPLATE_H_
#define PATROLPATHTEMPLATE_H_

#include "engine/engine.h"

#include "PatrolPathNode.h"

class PatrolPathTemplate : public Object {
	VectorMap<String, PatrolPathNode> pathMap;
public:
	PatrolPathTemplate() {
		pathMap.setNoDuplicateInsertPlan();
	}

	PatrolPathTemplate(const PatrolPathTemplate& tmp) : Object() {
		pathMap = tmp.pathMap;
	}

	PatrolPathTemplate& operator=(const PatrolPathTemplate& tmp) {
		if (this == &tmp)
			return *this;

		pathMap = tmp.pathMap;

		return *this;
	}

	void readObject(LuaObject* luaObject) {
		for (int i = 1; i <= luaObject->getTableSize(); ++i) {
			lua_rawgeti(luaObject->getLuaState(), -1, i);
			LuaObject node(luaObject->getLuaState());

			if (node.isValidTable()) {
				PatrolPathNode pathNode;
				pathNode.readObject(&node);

				pathMap.put(pathNode.getId(), pathNode);
			}

			node.pop();
		}
	}
};

#endif /* PATROLPATHTEMPLATE_H_ */
