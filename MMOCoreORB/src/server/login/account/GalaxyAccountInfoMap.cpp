#include "server/login/account/GalaxyAccountInfoMap.h"

GalaxyAccountInfoMap::GalaxyAccountInfoMap() {

}

bool GalaxyAccountInfoMap::toBinaryStream(ObjectOutputStream* stream) {
	uint32 count = size();
	
	TypeInfo<uint32>::toBinaryStream(&count, stream);
	
	for (auto& element : *this) {
		GalaxyAccountInfo *value = element.getValue();
		String& key = element.getKey();
		
		key.toBinaryStream(stream);
		value->toBinaryStream(stream);
	}
	
	return true;
}


bool GalaxyAccountInfoMap::parseFromBinaryStream(ObjectInputStream* stream) {
	uint32 count = 0;
	TypeInfo<uint32>::parseFromBinaryStream(&count, stream);
	
	for (int i=0; i<count; i++) {
		String key;
		key.parseFromBinaryStream(stream);
		
		Reference<GalaxyAccountInfo*> value = new GalaxyAccountInfo();
		value->parseFromBinaryStream(stream);
		
		put(key, value);
	}
	
	return true;
}

