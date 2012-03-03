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

StringIdChatParameter::StringIdChatParameter(const StringIdChatParameter& custom) : ChatParameter(), StringId(custom) {

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

