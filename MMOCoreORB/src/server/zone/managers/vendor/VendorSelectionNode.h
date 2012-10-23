/*
 * VendorSelectionNode.h
 *
 *  Created on: Mar 23, 2011
 *      Author: polonel
 */

#ifndef VENDORSELECTIONNODE_H_
#define VENDORSELECTIONNODE_H_

#include "engine/engine.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

class VendorSelectionNode : public Object {

	String nodeTitle;
	String nodePath;
	String suiDisplay;
	int hiringRequired;

	SortedVector<Reference<VendorSelectionNode*> > childNodes;

public:
	VendorSelectionNode() : Object() {
		hiringRequired = 0;
	}

	VendorSelectionNode(const VendorSelectionNode& node) : Object() {
		nodeTitle = node.nodeTitle;
		nodePath = node.nodePath;
		suiDisplay = node.suiDisplay;
		hiringRequired = node.hiringRequired;
		childNodes = node.childNodes;

	}

	VendorSelectionNode& operator= (const VendorSelectionNode& node) {
		if (this == &node)
			return *this;

		nodeTitle = node.nodeTitle;
		nodePath = node.nodePath;
		suiDisplay = node.suiDisplay;
		hiringRequired = node.hiringRequired;
		childNodes = node.childNodes;

		return *this;
	}

	void parseFromLua(LuaObject& lua) {
		if (!lua.isValidTable())
			return;

		nodeTitle = lua.getStringField("nodeName");
		nodePath = lua.getStringField("nodePath");

		if (!lua.getStringField("suiDisplay").isEmpty())
			suiDisplay = lua.getStringField("suiDisplay");

		hiringRequired = lua.getIntField("hiringRequired");

		LuaObject childNodes = lua.getObjectField("childNodes");

		if (childNodes.isValidTable()) {
			for (int i = 1; i < childNodes.getTableSize() + 1; ++i) {
				lua_State* L = lua.getLuaState();
				lua_rawgeti(L, -1, i);
				LuaObject luaNode(L);

				if (luaNode.isValidTable()) {
					Reference<VendorSelectionNode*> childNode = new VendorSelectionNode();
					childNode->parseFromLua(luaNode);

					addChildNode(childNode);
				}

				luaNode.pop();
			}
		}

		childNodes.pop();
	}

	inline int compareTo(const VendorSelectionNode& node) const {
		if (hiringRequired > node.hiringRequired)
			return -1;

		if (hiringRequired < node.hiringRequired)
			return 1;

		return 0;
	}

	inline void addChildNode(VendorSelectionNode* node) {
		childNodes.add(node);
	}

	inline void setNodeName(const String& name) {
		nodeTitle = name;
	}

	inline void setNodePath(const String& path) {
		nodePath = path;
	}

	inline void setHiringRequired(int hiring) {
		hiringRequired = hiring;
	}

	inline bool hasChildNode() {
		return childNodes.size() > 0;
	}

	inline void addChildrenToListBox(SuiListBox* listBox, int hiringSkill) {
		for (int i = 0; i < childNodes.size(); ++i) {
			VendorSelectionNode* child = childNodes.get(i);
			if (child->getHiringRequired() <= hiringSkill)
				listBox->addMenuItem(child->getNodeName(), i);
		}
	}

	VendorSelectionNode* getNode(int idx) {
		if (idx < 0 || idx >= childNodes.size())
			return NULL;

		return childNodes.get(idx);
	}

	inline int getChildNodeSize() {
		return childNodes.size();
	}

	String getRandomTemplate(int skillLevel) {

		if(childNodes.size() == 0)
			return "";

		VendorSelectionNode* node = NULL;
		int loop = 0;

		do {
			node = childNodes.get(System::random(childNodes.size() - 1));
			loop++;
		} while((node == NULL || node->getHiringRequired() > skillLevel) && loop < 10 );

		if(node == NULL)
			return "";

		return node->getTemplatePath();
	}

	inline String& getNodeName() {
		return nodeTitle;
	}

	inline int getHiringRequired() {
		return hiringRequired;
	}

	inline String& getSuiDisplay() {
		return suiDisplay;
	}

	inline String& getTemplatePath() {
		return nodePath;
	}

};

#endif /* VENDORSELECTIONNODE_H_ */
