/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
 */

#ifndef CONVERSATIONTEMPLATE_H_
#define CONVERSATIONTEMPLATE_H_

#include "engine/engine.h"

#include "ConversationScreen.h"

#include "server/zone/managers/conversation/ConversationManager.h"

namespace server {
namespace zone {
namespace templates {
namespace mobile {

class ConversationTemplate : public Object, public Logger {
public:
	enum ConversationTemplateType {
		ConversationTemplateTypeNormal,
		ConversationTemplateTypeTrainer,
		ConversationTemplateTypeDeliverMission,
		ConversationTemplateTypeInformantMission,
		ConversationTemplateTypeLua
	};
protected:
	String initialScreenID;
	VectorMap<String, Reference<ConversationScreen*> > screens;
	ConversationTemplateType conversationTemplateType;
	uint32 crc;
	String luaClassHandler;

public:

	ConversationTemplate(uint32 hashCode) : Logger("ConversationTemplate") {
		screens.setNoDuplicateInsertPlan();
		crc = hashCode;
	}

	virtual ~ConversationTemplate() {

	}

	void readObject(LuaObject* templateData) {
		initialScreenID = templateData->getStringField("initialScreen");

		String templateType;

		try {
			templateType = templateData->getStringField("templateType");
		}
		catch (Exception&) {
			Logger::info("Missing templateType.", true);
			templateType = "Normal";
		}

		if (templateType == "Trainer") {
			conversationTemplateType = ConversationTemplateTypeTrainer;
		} else if (templateType == "DeliverNPC") {
			conversationTemplateType = ConversationTemplateTypeDeliverMission;
		} else if (templateType == "InformantNPC") {
			conversationTemplateType = ConversationTemplateTypeInformantMission;
		} else if (templateType == "Lua") {
			conversationTemplateType = ConversationTemplateTypeLua;
		} else {
			conversationTemplateType = ConversationTemplateTypeNormal;
		}

		luaClassHandler = templateData->getStringField("luaClassHandler");

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

		ConversationManager::instance()->getConversationObserver(crc);
	}

	String getLuaClassHandler() {
		return luaClassHandler;
	}

	ConversationScreen* getInitialScreen() {
		return screens.get(initialScreenID);
	}

	ConversationScreen* getScreen(const String& screenID) {
		return screens.get(screenID);
	}

	ConversationTemplateType getConversationTemplateType() {
		return conversationTemplateType;
	}

	uint32 getCRC() {
		return crc;
	}
};

}
}
}
}

using namespace server::zone::templates::mobile;

#endif /* CONVERSATIONTEMPLATE_H_ */
