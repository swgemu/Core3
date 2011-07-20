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

#ifndef IMAGEDESIGNMESSAGE_H_
#define IMAGEDESIGNMESSAGE_H_


#include "engine/engine.h"
#include "ObjectControllerMessage.h"

class ImageDesignStartMessage : public ObjectControllerMessage {
public:
	ImageDesignStartMessage(CreatureObject* object, CreatureObject* designer, CreatureObject* targetPlayer, uint64 tentID, int type = 0)
		: ObjectControllerMessage(object->getObjectID(), 0x0B, 0x023A) {

		insertLong(designer->getObjectID()); // Image Designer
		insertLong(targetPlayer->getObjectID()); // Image Design Target
		insertLong(tentID);
		insertShort(type); // 0 = designer, 1 = target <-- research this

	}
};

class ImageDesignRejectMessage : public ObjectControllerMessage {
	
public:
	ImageDesignRejectMessage(uint64 object, uint64 designer, uint64 client, uint64 tent, int type = 0) 
		: ObjectControllerMessage(object, 0x0B, 0x0239) {

		insertLong(designer); // Image Designer? 
		insertLong(client); // Image Design Target
		insertLong(tent); // Boolish - in an ID tent? or a cell id?
		insertByte(type); // 0 = designer, 1 = target

	}
};

class ImageDesignChangeMessage : public ObjectControllerMessage {
	
public:
	ImageDesignChangeMessage(uint64 object, uint64 designer, uint64 client, uint64 tent, int type = 0)
		: ObjectControllerMessage(object, 0x0B, 0x0238) {

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
