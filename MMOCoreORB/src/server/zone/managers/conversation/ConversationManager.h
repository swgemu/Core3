/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CONVERSATIONMANAGER_H_
#define CONVERSATIONMANAGER_H_

#include "engine/engine.h"

namespace server {
namespace zone {

	namespace objects {
	 namespace creature {
	  namespace conversation {
	   class ConversationObserver;
	  }
	 }
	}

namespace managers {
namespace conversation {

/**
 * Class responsible for creating and storing player to NPC conversation observers. It creates one
 * object per conversation template and reuses it for every NPC needing it.
 */
class ConversationManager : public Singleton<ConversationManager>, public Logger, public Object {
	/**
	 * Map with conversation template crc as the key and the created conversation observer as the value.
	 */
	HashTable<uint32, ManagedReference<objects::creature::conversation::ConversationObserver*> > conversationObservers;

public:
	/**
	 * Constructor.
	 */
	ConversationManager();

	/**
	 * Destructor.
	 */
	~ConversationManager();

	/**
	 * Function that creates or picks an already created conversation observer depending on the template.
	 * @param conversationTemplateCRC the CRC value of the template for the conversation observer.
	 * @return a conversation observer running the template.
	 */
	objects::creature::conversation::ConversationObserver* getConversationObserver(uint32 conversationTemplateCRC);
};

}
}
}
}

using namespace server::zone::managers::conversation;

#endif /* CONVERSATIONMANAGER_H_ */
