/*
 * CharacterBuilderMenuNode.h
 *
 *  Created on: Jun 6, 2010
 *      Author: crush
 */

#ifndef CHARACTERBUILDERMENUNODE_H_
#define CHARACTERBUILDERMENUNODE_H_

#include "engine/lua/LuaObject.h"

class CharacterBuilderMenuNode : public Object {
	WeakReference<CharacterBuilderMenuNode*> parentNode;

	String displayName;
	String templatePath;
	uint32 templateCRC;

	SortedVector<Reference<CharacterBuilderMenuNode*> > childNodes;

public:
	CharacterBuilderMenuNode(const String& name) {
		displayName = name;
		parentNode = nullptr;
		templateCRC = 0;
		childNodes.setInsertPlan(SortedVector<CharacterBuilderMenuNode*>::NO_DUPLICATE);
	}

	CharacterBuilderMenuNode(const String& name, const String& tplPath) {
		parentNode = nullptr;
		displayName = name;
		templatePath = tplPath;
		templateCRC = tplPath.hashCode();
		childNodes.setInsertPlan(SortedVector<CharacterBuilderMenuNode*>::NO_DUPLICATE);
	}

	int readLuaObject(LuaObject& luaObject, bool recursive) {
		int tableSize = luaObject.getTableSize();

		if (tableSize % 2 != 0)
			return 0;

		for (int i = 1; i <= tableSize; i += 2) {
			String title = luaObject.getStringAt(i);

			lua_State* L = luaObject.getLuaState();
			lua_rawgeti(L, -1, i + 1);
			LuaObject a(L);

			CharacterBuilderMenuNode* node = new CharacterBuilderMenuNode(title);
			node->setParentNode(this);

			if (a.isValidTable()) {
				node->readLuaObject(a, true);
				a.pop();
			} else {
				a.pop();
				node->setTemplatePath(luaObject.getStringAt(i + 1));
			}

			childNodes.put(node);
		}

		return 0;
	}

	int compareTo(CharacterBuilderMenuNode* obj) {
		return displayName.compareTo(obj->getDisplayName());
	}

	inline void setTemplatePath(const String& tplPath) {
		templatePath = tplPath;
		templateCRC = tplPath.hashCode();
	}

	inline void setParentNode(CharacterBuilderMenuNode* parent) {
		parentNode = parent;
	}

	inline CharacterBuilderMenuNode* getParentNode() {
		return parentNode.get().get();
	}

	inline const CharacterBuilderMenuNode* getParentNode() const {
		return parentNode.get().get();
	}

	inline bool hasParentNode() const {
		return parentNode.get() != nullptr;
	}

	inline bool hasChildNodes() const {
		return childNodes.size() > 0;
	}

	inline const String& getDisplayName() const {
		return displayName;
	}

	inline const String& getTemplatePath() const {
		return templatePath;
	}

	inline uint32 getTemplateCRC() const {
		return templateCRC;
	}

	inline int getChildNodeSize() const {
		return childNodes.size();
	}

	inline const CharacterBuilderMenuNode* getChildNodeAt(int index) const {
		if (childNodes.size() < index + 1 || index < 0)
			return nullptr;

		return childNodes.get(index);
	}

	inline CharacterBuilderMenuNode* getChildNodeAt(int index) {
		if (childNodes.size() < index + 1 || index < 0)
			return nullptr;

		return childNodes.get(index);
	}
};

#endif /* CHARACTERBUILDERMENUNODE_H_ */
