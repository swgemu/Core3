/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STOPNPCCONVERSATION_H_
#define STOPNPCCONVERSATION_H_

class StopNpcConversation : public ObjectControllerMessage {
	
public:

	StopNpcConversation(CreatureObject* creo, uint64 npcID) 
		: ObjectControllerMessage(creo->getObjectID(), 0x0B, 0xDE, false) {
	
		insertLong(npcID);			
	}
	
};

#endif
