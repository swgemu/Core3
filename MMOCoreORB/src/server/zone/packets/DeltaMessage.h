/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DELTAMESSAGE_H_
#define DELTAMESSAGE_H_

#include "engine/engine.h"

class DeltaMessage : public BaseMessage {
	int updateCount;
	
public:
	DeltaMessage(uint64 oid, uint32 name, uint8 type) {
		insertShort(0x05);
		insertInt(0x12862153);
		insertLong(oid);
		insertInt(name);
		//insertInt(generateRandomObjectCRC());
		insertByte(type);
		insertInt(0);

		setCompression(true);
	
		updateCount = 0;
		insertShort(updateCount);
	}

	uint32 generateRandomObjectCRC() {
		int idx = System::random(4);
		
		if (idx == 0)
			return 0x4352454F;  // CREO;
		else if (idx == 1)
			return 0x504C4159;  // PLAY 
		else if (idx == 2)
			return 0x54414E4F;  // TANO 
		else 
			return System::random(0xFFFFFFFF); 
	};

	inline void startUpdate(uint16 type) {
		++updateCount;
		insertShort(type);
	}

	/*template<class E> void addToDeltaVectorUpdate(uint16 type, DeltaVector<E>* vector) {
		startUpdate(type);

		startList(1, vector->getNewUpdateCounter(1));

		insertByte(1);
		insertShort(vector->size() - 1);
		E& object = vector->get(vector->size() - 1);
		TypeInfo<E>::toBinaryStream(&object, this);
	}

	template<class E> void removeFromDeltaVectorUpdate(uint16 type, DeltaVector<E>* vector, int removedIndex) {
		startUpdate(type);

		startList(1, grup->getNewUpdateCounter(1));
		insertByte(0);
		insertShort(removedIndex);
	}*/

	inline void addByteUpdate(uint16 type, uint8 value) {
		startUpdate(type);
		insertByte(value);
	}

	inline void addShortUpdate(uint16 type, uint16 value) {
		startUpdate(type);
		insertShort(value);
	}

	inline void addIntUpdate(uint16 type, uint32 value) {
		startUpdate(type);
		insertInt(value);
	}

	inline void addLongUpdate(uint16 type, uint64 value) {
		startUpdate(type);
		insertLong(value);
	}

	inline void addFloatUpdate(uint16 type, float value) {
		startUpdate(type);
		insertFloat(value);
	}
	
	inline void addAsciiUpdate(uint16 type, const String& val) {
		startUpdate(type);
		insertAscii(val.toCharArray());
	}
	
	inline void addUnicodeUpdate(uint16 type, const String& val) {
		startUpdate(type);
		UnicodeString v = UnicodeString(val);
		insertUnicode(v);
	}

	inline void addUnicodeUpdate(uint16 type, const UnicodeString& val) {
		startUpdate(type);
		insertUnicode(val);
	}

	inline void startList(uint32 cnt, uint32 updcnt) {
		insertInt(cnt);
		insertInt(updcnt);
	}

	inline void addListIntElement(uint16 index, uint32 value) {
		insertByte(0x01);
		insertShort(index);
		insertInt(value);
	}
	
	inline void addListFloatElement(uint16 index, float value) {
		insertByte(0x01);
		insertShort(index);
		insertFloat(value);
	}

	inline void addListLongElement(uint16 index, uint64 value) {
		insertByte(0x01);
		insertShort(index);
		insertLong(value);
	}

	inline void addListAsciiElement(const String& value) {
		insertByte(0x00);
		insertAscii(value.toCharArray());
	}

	inline void removeListIntElement(uint16 index, uint32 value) {
		insertByte(0x02);
		insertShort(index);
		insertInt(value);
	}
	
	inline void removeListFloatElement(uint16 index, float value) {
		insertByte(0x02);
		insertShort(index);
		insertFloat(value);
	}

	inline void removeListLongElement(uint16 index, uint64 value) {
		insertByte(0x02);
		insertShort(index);
		insertLong(value);
	}

	inline void removeListLongElement(uint16 index) {
		insertByte(0x03);
		insertShort(index);
	}

	inline void removeListAsciiElement(const String& value) {
		insertByte(0x01);
		insertAscii(value.toCharArray());
	}

	inline void close() {
		insertInt(23, size() - 27);
		insertShort(27, updateCount);
	}
	
};

#endif /*DELTAMESSAGE_H_*/
