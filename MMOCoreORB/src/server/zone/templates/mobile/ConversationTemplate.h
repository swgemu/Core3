/*
 * ConversationTemplate.h
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#ifndef CONVERSATIONTEMPLATE_H_
#define CONVERSATIONTEMPLATE_H_

#include "engine/engine.h"

#include "ConversationScreen.h"

namespace server {
namespace zone {
namespace templates {
namespace mobile {

class ConversationTemplate : public Object {
protected:
	String initialScreenID;
	VectorMap<String, Reference<ConversationScreen*> > screens;

public:
	ConversationTemplate() {
		screens.setNoDuplicateInsertPlan();
	}

	virtual ~ConversationTemplate() {

	}

	void readObject(LuaObject* templateData) {
		initialScreenID = templateData->getStringField("initialScreen");

		LuaObject screensTable = templateData->getObjectField("screens");

		for (int i = 1; i <= screensTable.getTableSize(); ++i) {
			lua_rawgeti(templateData->getLuaState(), -1, i);

			LuaObject luaObj(templateData->getLuaState());

			Reference<ConversationScreen*> screen = new ConversationScreen();
			screen->readObject(&luaObj);

			screens.put(screen->getScreenID(), screen);

			luaObj.pop();
		}

		screensTable.pop();
	}

	ConversationScreen* getInitialScreen() {
		return screens.get(initialScreenID);
	}

	ConversationScreen* getScreen(const String& screenID) {
		return screens.get(screenID);
	}
};

}
}
}
}

using namespace server::zone::templates::mobile;

#endif /* CONVERSATIONTEMPLATE_H_ */
