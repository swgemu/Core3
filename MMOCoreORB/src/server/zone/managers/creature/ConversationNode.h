/*
 * ConversationNode.h
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#ifndef CONVERSATIONNODE_H_
#define CONVERSATIONNODE_H_

#include "engine/engine.h"

class ConversationNode : public Object {
	String id, leftDialog, optionText, optionLink;

	Vector<Reference<ConversationNode*> > children;

	ConversationNode* parent;
public:
	ConversationNode(ConversationNode* parent) {
		this->parent = parent;
	}

	ConversationNode* findNode(const String& id) {
		if (this->id == id)
			return this;

		for (int i = 0; i < children.size(); ++i) {
			ConversationNode* node = children.get(i);
			ConversationNode* found = node->findNode(id);

			if (found != NULL)
				return found;
			else
				continue;
		}

		return NULL;

	}

	void readObject(LuaObject* templateData) {
		id = templateData->getStringField("id");
		leftDialog = templateData->getStringField("leftDialog");
		optionText = templateData->getStringField("optionText");
		optionLink = templateData->getStringField("optionLink");

		LuaObject res = templateData->getObjectField("children");

		//System::out << "Conversation Node child size:" << res.getTableSize() << endl;

		for (int i = 1; i <= res.getTableSize(); ++i) {
			lua_rawgeti(templateData->getLuaState(), -1, i);

			LuaObject luaObj(templateData->getLuaState());

			ConversationNode* node = new ConversationNode(this);
			node->readObject(&luaObj);

			luaObj.pop();

			children.add(node);
		}

		//System::out << "children size:" << children.size() << endl;

		res.pop();
	}

	Vector<Reference<ConversationNode*> >* getChildren() {
		return &children;
	}

	inline ConversationNode* getParent() {
		return parent;
	}

	String getOptionText() {
		return optionText;
	}

	String getID() {
		return id;
	}

	String getOptionLink() {
		return optionLink;
	}

	String getLeftDialog() {
		return leftDialog;
	}


};


#endif /* CONVERSATIONNODE_H_ */
