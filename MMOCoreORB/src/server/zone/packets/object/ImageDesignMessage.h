/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef IMAGEDESIGNMESSAGE_H_
#define IMAGEDESIGNMESSAGE_H_


#include "engine/engine.h"
#include "ObjectControllerMessage.h"

class ImageDesignStartMessage : public ObjectControllerMessage {
public:
	ImageDesignStartMessage(CreatureObject* object, CreatureObject* designer, CreatureObject* targetPlayer, uint64 tentID, const String& hairTemplate)
		: ObjectControllerMessage(object->getObjectID(), 0x1B, 0x023A) {

		insertLong(designer->getObjectID()); // Image Designer
		insertLong(targetPlayer->getObjectID()); // Image Design Target
		insertLong(tentID);
		//insertShort(type); // 0 = designer, 1 = target <-- research this
		insertAscii(hairTemplate);

	}
};

class ImageDesignRejectMessage : public ObjectControllerMessage {
	
public:
	ImageDesignRejectMessage(uint64 object, uint64 designer, uint64 client, uint64 tent, int type = 0) 
		: ObjectControllerMessage(object, 0x1B, 0x0239) {

		insertLong(designer); // Image Designer? 
		insertLong(client); // Image Design Target
		insertLong(tent); // Boolish - in an ID tent? or a cell id?
		insertByte(type); // 0 = designer, 1 = target

	}
};

class ImageDesignChangeMessage : public ObjectControllerMessage {
	
public:
	ImageDesignChangeMessage(uint64 object, uint64 designer, uint64 client, uint64 tent, int type = 0)
		: ObjectControllerMessage(object, 0x1B, 0x0238) {

		insertLong(designer); // Image Designer? 
		insertLong(client); // Image Design Target
		insertLong(tent); // Boolish - in an ID tent? or a cell id?
		insertByte(type); // 0 = designer, 1 = target

	}


};

/*
class ImageDesignDisplayUI : public BaseMessage {
	
public:
	ImageDesignDisplayUI(Player* player) {
		insertShort(5); // opcount from ZonePacketHandler
		insertInt(0x80CE5E46); // opcode handleObjectControllerMessage(pack);
		insertInt(0x0B); 
		insertInt(0x023A); 
		insertLong(player->getPlayerObject()->getObjectID()); 
		insertInt(0); 
		insertLong(player->getPlayerObject()->getObjectID());
		insertLong(player->getPlayerObject()->getObjectID());

//0000:   00 09 06 BB 00 19 34 05 00 46 5E CE 80 0B 00 00   ......4..F^.....
//0010:   00 3A 02 00 00 14 29 A7 E5 35 00 00 00 00 00 00   .:....)..5......
//0020:   00 14 29 A7 E5 35 00 00 00 14 29 A7 E5 35 00 00   ..)..5....)..5..
//0030:   00 

		
		insertLong(0); // 8
		insertShort(0); // 2
		insertShort(0x052A);
		insertByte(0);
		
		//insertLong(player->getPlayerObject()->getObjectID());
		//insertInt(0);
		//insertInt(0x0280);
		//insertLong(0);
		//insertInt(0); 
		insertInt(0x80CE5E46); // opcode handleObjectControllerMessage(pack);
		insertInt(0x0B); 
		insertInt(0x0117);
		insertLong(player->getPlayerObject()->getObjectID());
		
		insertInt(0);
		insertInt(0x0280);
		
		insertInt(0);
		insertInt(0);
		insertInt(0);
		insertInt(0);

//00 00 00 00 00 00 00 00 00 00 2A 05 00 46 5E   ...........*..F^
//0040:   CE 80 0B 00 00 00 17 01 00 00 14 29 A7 E5 35 00   ...........)..5.
//0050:   00 00 00 00 00 00 80 02 00 00 00 00 00 00 00 00   ................
//0060:   00 00 00 00 00 00 01 B9 B8                        ......... 


		

		
	}
	
};

*/

#endif /*IMAGEDESIGNMESSAGE_H_*/
