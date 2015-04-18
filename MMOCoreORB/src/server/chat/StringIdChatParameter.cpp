/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "StringIdChatParameter.h"

StringIdChatParameter::StringIdChatParameter() : StringId() {
	unknownByte = 0;
	DI = 0;
	DF = 0;
}

StringIdChatParameter::StringIdChatParameter(const StringId& id) : StringId(id) {
	unknownByte = 0;
	DI = 0;
	DF = 0;
}

StringIdChatParameter::StringIdChatParameter(const char * cstr) : StringId (cstr) {
	unknownByte = 0;
	DI = 0;
	DF = 0;
}

StringIdChatParameter::StringIdChatParameter(const String& fullPath) : StringId (fullPath) {
	unknownByte = 0;
	DI = 0;
	DF = 0;
}

StringIdChatParameter::StringIdChatParameter(const String& fil, const String& stringId) : StringId(fil, stringId) {
	unknownByte = 0;
	DI = 0;
	DF = 0;
}

StringIdChatParameter::StringIdChatParameter(const StringIdChatParameter& custom) : Object(), ChatParameter(), StringId(custom) {

	TT = custom.TT;
	TU = custom.TU;
	TO = custom.TO;

	DI = custom.DI;
	DF = custom.DF;

	unknownByte = custom.unknownByte;
}

void StringIdChatParameter::addToPacketStream(Message* packet) {
	packet->insertAscii(file);
	packet->insertInt(0);
	packet->insertAscii(stringID);

	packet->insertLong(TU.getPointerParameter());
	packet->insertAscii(TU.getFileParameter());
	packet->insertInt(0);
	packet->insertAscii(TU.getStringIDParameter());
	packet->insertUnicode(TU.getUnicodeParameter());

	packet->insertLong(TT.getPointerParameter());
	packet->insertAscii(TT.getFileParameter());
	packet->insertInt(0);
	packet->insertAscii(TT.getStringIDParameter());
	packet->insertUnicode(TT.getUnicodeParameter());

	packet->insertLong(TO.getPointerParameter());
	packet->insertAscii(TO.getFileParameter());
	packet->insertInt(0);
	packet->insertAscii(TO.getStringIDParameter());
	packet->insertUnicode(TO.getUnicodeParameter());

	packet->insertInt(DI);
	packet->insertFloat(DF);
	packet->insertByte(unknownByte);
}

void StringIdChatParameter::parse(Message* message) {

}

bool StringIdChatParameter::toBinaryStream(ObjectOutputStream* stream) {

	StringId::toBinaryStream(stream);

	return TT.toBinaryStream(stream) &&
			TU.toBinaryStream(stream) &&
			TO.toBinaryStream(stream) &&
			TypeInfo<uint32 >::toBinaryStream(&DI, stream) &&
			TypeInfo<float >::toBinaryStream(&DF, stream);
}

bool StringIdChatParameter::parseFromBinaryStream(ObjectInputStream* stream) {

	StringId::parseFromBinaryStream(stream);

	TT.parseFromBinaryStream(stream);
	TU.parseFromBinaryStream(stream);
	TO.parseFromBinaryStream(stream);
	TypeInfo<uint32 >::parseFromBinaryStream(&DI, stream);
	TypeInfo<float >::parseFromBinaryStream(&DF, stream);

	return true;
}

