/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/


#ifndef MANUFACTURESCHEMATICOBJECTMESSAGE3_H_
#define MANUFACTURESCHEMATICOBJECTMESSAGE3_H_

#include "server/zone/packets/BaseLineMessage.h"

class ManufactureSchematicObjectMessage3 : public BaseLineMessage {
public:
	ManufactureSchematicObjectMessage3(uint64 oid, float complexity, String playerName)
			: BaseLineMessage(oid, 0x4D53434F, 3, 0x09) {

		insertFloat(complexity);
		insertAscii("String_id_table");
		insertInt(0);

		insertAscii("");
		UnicodeString empty = "";
		insertUnicode(empty);

		insertInt(0);
		insertInt(0x0A);
		insertInt(1);
		insertInt(1);
		insertByte(0);

		insertAscii("crafting");
		insertInt(0);
		insertAscii("complexity");
		insertFloat(complexity);

		//UnicodeString playerName = "Link";
		insertUnicode(playerName);
		insertInt(25);
		insertFloat(8.0f);

		setSize();
	}

	ManufactureSchematicObjectMessage3(ManufactureSchematic* manufactureSchematic,
			String playerName) : BaseLineMessage(manufactureSchematic->getObjectID(), 0x4D53434F, 3, 0x09) {

		insertFloat(manufactureSchematic->getComplexity());
		insertAscii(manufactureSchematic->getObjectNameStringIdFile());
		insertInt(0);
		insertAscii(manufactureSchematic->getObjectNameStringIdName());

		insertUnicode(manufactureSchematic->getCustomObjectName());

		insertInt(0);  // Unknown
		insertInt(manufactureSchematic->getManufactureLimit()); // Manufacturing Count
		insertInt(1);
		insertInt(1);
		insertByte(0);

		insertAscii("crafting");
		insertInt(0);
		insertAscii("complexity");
		insertFloat(manufactureSchematic->getComplexity());

		//UnicodeString playerName = "Link";
		insertUnicode(playerName);
		insertInt(25);
		insertFloat(8.0f);

		setSize();
	}

	/*ManufactureSchematicObjectMessage3(ManufactureSchematic* manufactureSchematic, UnicodeString& playerName)
			: BaseLineMessage(manufactureSchematic->getObjectID(), 0x4D53434F, 3, 0x09) {

		insertFloat(manufactureSchematic->getComplexity());
		insertAscii(manufactureSchematic->getStfFile());
		insertInt(0);
		insertAscii(manufactureSchematic->getStfName());

		insertUnicode(manufactureSchematic->getCustomName());

		insertInt(0);  // Unknown
		insertInt(0x0A); // Unknown
		insertInt(1);
		insertInt(1);
		insertByte(0);

		insertAscii("crafting");
		insertInt(0);
		insertAscii("complexity");
		insertFloat(manufactureSchematic->getComplexity());

		//UnicodeString playerName = "Link";
		insertUnicode(playerName);
		insertInt(25);
		insertFloat(8.0f);

		setSize();
	}*/
};

#endif /*MANUFACTURESCHEMATICOBJECTMESSAGE3_H_*/
