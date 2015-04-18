/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef PERMISSIONLISTCREATEMESSAGE_H_
#define PERMISSIONLISTCREATEMESSAGE_H_

class PermissionListCreateMessage : public BaseMessage {
	Vector<String> nameList;
	UnicodeString cellName;

public:
	PermissionListCreateMessage(const String& cell) : BaseMessage() {
		insertShort(0x04);
		insertInt(0x52F364B8);  // CRC

		cellName = UnicodeString(cell);
    }

	void addName(const String& name) {
		nameList.add(name);
	}

	//Dumps the list, finishes packet.
	void generateMessage() {
		int size = nameList.size();

		//List Size
		insertInt(size);

		for(int i = 0; i < size; i++) {
			insertUnicode(UnicodeString(nameList.get(i)));
		}

		//Blank 2nd list, unk purpose
		insertInt(0);

		//Cell Name / Name of list (ADMIN,ENTRY etc)
		insertUnicode(cellName);
	}

};

#endif /* PERMISSIONLISTCREATEMESSAGE_H_ */
