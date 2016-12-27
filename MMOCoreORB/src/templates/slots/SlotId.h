/*
 * SlotId.h
 *
 *  Created on: May 25, 2011
 *      Author: crush
 */

#ifndef SLOTID_H_
#define SLOTID_H_

class SlotId : public Object {
	String slotName;
	byte unk1;
	byte unk2;
	byte unk3;
	String alternateName;
	uint16 unk4;
	byte unk5;
	byte unk6;

public:
	SlotId() : unk1(0), unk2(0), unk3(0), unk4(0), unk5(0), unk6(0) {
	}

	SlotId(const SlotId& sid) : Object() {
		slotName = sid.slotName;
		unk1 = sid.unk1;
		unk2 = sid.unk2;
		unk3 = sid.unk3;
		alternateName = sid.alternateName;
		unk4 = sid.unk4;
		unk5 = sid.unk5;
		unk6 = sid.unk6;
	}

	SlotId& operator= (const SlotId& sid) {
		if (this == &sid)
			return *this;

		slotName = sid.slotName;
		unk1 = sid.unk1;
		unk2 = sid.unk2;
		unk3 = sid.unk3;
		alternateName = sid.alternateName;
		unk4 = sid.unk4;
		unk5 = sid.unk5;
		unk6 = sid.unk6;

		return *this;
	}

	int compareTo(const SlotId& sid) const {
		return slotName.compareTo(sid.slotName);
	}

	void readObject(Chunk* chunk) {
		chunk->readString(slotName);
		unk1 = chunk->readByte();
		unk2 = chunk->readByte();
		unk3 = chunk->readByte();
		chunk->readString(alternateName);
		unk4 = chunk->readShort();
		unk5 = chunk->readByte();
		unk6 = chunk->readByte();
	}

	void writeHtmlTableRow(StringBuffer& str) {
		str << "<tr>";
		str << "<td>" << slotName << "</td>";
		str << "<td>" << unk1 << "</td>";
		str << "<td>" << unk2 << "</td>";
		str << "<td>" << unk3 << "</td>";
		str << "<td>" << alternateName << "</td>";
		str << "<td>" << unk4 << "</td>";
		str << "<td>" << unk5 << "</td>";
		str << "<td>" << unk6 << "</td>";
		str << "</tr>";
	}

	inline String& getSlotName() {
		return slotName;
	}
};

#endif /* SLOTID_H_ */
