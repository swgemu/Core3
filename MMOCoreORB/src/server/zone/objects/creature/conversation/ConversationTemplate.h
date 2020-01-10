/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef CONVERSATIONTEMPLATE_H_
#define CONVERSATIONTEMPLATE_H_

#include "engine/engine.h"

#include "ConversationScreen.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace conversation {

class ConversationTemplate : public Object, public Logger {
public:
	enum ConversationTemplateType {
		ConversationTemplateTypeNormal,
		ConversationTemplateTypeDeliverMission,
		ConversationTemplateTypeInformantMission,
		ConversationTemplateTypeLua,
		ConversationTemplateTypePersonality
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

		conversationTemplateType = ConversationTemplateTypeNormal;
	}

	virtual ~ConversationTemplate() {

	}

	void readObject(LuaObject* templateData);

	const String& getLuaClassHandler() const {
		return luaClassHandler;
	}

	ConversationScreen* getInitialScreen() const {
		return screens.get(initialScreenID);
	}

	ConversationScreen* getScreen(const String& screenID) const {
		return screens.get(screenID);
	}

	ConversationTemplateType getConversationTemplateType() const {
		return conversationTemplateType;
	}

	uint32 getCRC() const {
		return crc;
	}
};

}
}
}
}
}

using namespace server::zone::objects::creature::conversation;

#endif /* CONVERSATIONTEMPLATE_H_ */
