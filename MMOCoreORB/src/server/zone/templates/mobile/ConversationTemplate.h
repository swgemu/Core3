/*
 * ConversationTemplate.h
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#ifndef CONVERSATIONTEMPLATE_H_
#define CONVERSATIONTEMPLATE_H_

#include "engine/engine.h"

#include "ConversationNode.h"

namespace server {
namespace zone {
namespace templates {
namespace mobile {


class ConversationTemplate : public Object {
protected:
	Reference<ConversationNode*> root;

public:
	ConversationTemplate() {

	}

	virtual ~ConversationTemplate() {

	}

	void readObject(LuaObject* templateData) {
		root = new ConversationNode(NULL);
		root->readObject(templateData);
	}

	inline ConversationNode* getNode(const String& id) {
		return root->findNode(id);
	}

	inline ConversationNode* getRoot() {
		return root;
	}


};

}
}
}
}

using namespace server::zone::templates::mobile;

#endif /* CONVERSATIONTEMPLATE_H_ */
