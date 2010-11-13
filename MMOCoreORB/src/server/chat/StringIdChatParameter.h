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

#ifndef STRINGIDCHATPARAMETER_H_
#define STRINGIDCHATPARAMETER_H_

#include "engine/engine.h"

#include "server/chat/ChatParameter.h"
#include "server/zone/objects/scene/variables/StringIdParameter.h"
#include "server/zone/objects/scene/variables/StringId.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {
namespace variables {
	class StringIdParameter;
}
}
}
}
}

using namespace server::zone::objects::scene::variables;

namespace server {
namespace chat {

class StringIdChatParameter : public ChatParameter, public StringId {
protected:
	StringIdParameter TT;
	StringIdParameter TU;
	StringIdParameter TO;

	uint32 DI;
	float DF;

	byte unknownByte;

	inline void addSerializableVariables() {
		addSerializableVariable("TT", &TT);
		addSerializableVariable("TU", &TU);
		addSerializableVariable("TO", &TO);
		addSerializableVariable("DI", &DI);
		addSerializableVariable("DF", &DF);

		unknownByte = 0;
		DI = 0;
		DF = 0;
	}

	/**
	* Inserts stf string identifier and variables into a packet
	* @pre { packet is a valid Message }
	* @post { data is inserted into packet }
	* @param packet Message that data is to be inserted into
	*/
	void addToPacketStream(Message* packet);

public:
	StringIdChatParameter();
	StringIdChatParameter(const StringId& id);
	StringIdChatParameter(const char * cstr);
	StringIdChatParameter(const String& fullPath);
	StringIdChatParameter(const String& fil, const String& stringId);
	StringIdChatParameter(const UnicodeString& custom);
	StringIdChatParameter(const StringIdChatParameter& custom);

	StringIdChatParameter& operator=(const StringIdChatParameter& id) {
		if (this == &id)
			return *this;

		TT = id.TT;
		TU = id.TU;
		TO = id.TO;

		DI = id.DI;
		DF = id.DF;

		unknownByte = id.unknownByte;

		ChatParameter::operator=(id);
		StringId::operator=(id);

		return *this;
	}

	void parse(Message* message);

	/**
	* Sets the TT variable
	* @pre { obj is one of the following:
	* 		String, UnicodeString, pointer to SceneObject that is in the client's memory,
	* 		objectid of SceneObject that is in the client's memory, StringId, pointer to StringId
	*  	   }
	* @post { TT variable is set }
	* @param obj Data that the TT variable is to be set as
	*/
	template<class T>
	inline void setTT(const T& obj) {
		TT.set(obj);
	}

	/**
	* Sets the TT variable of this stf string to another stf string
	* @pre { }
	* @post { TT variable is set }
	* @param file stf file name that contains the stf string
	* @param stringid stringid of stf string
	*/
	inline void setTT(const String& file, const String& stringid) {
		TT.set(file, stringid);
	}

	/**
	* Sets the TU variable of a stf string
	* @pre { obj is one of the following:
	* 		String, UnicodeString, pointer to SceneObject that is in the client's memory,
	* 		objectid of SceneObject that is in the client's memory, StringId, pointer to StringId
	*  	   }
	* @post { TU variable is set }
	* @param obj Data that the TU variable is to be set as
	*/
	template<class T>
	inline void setTU(const T& obj) {
		TU.set(obj);
	}

	/**
	* Sets the TU variable of this stf string to another stf string
	* @pre { }
	* @post { TU variable is set }
	* @param file stf file name that contains the stf string
	* @param stringid stringid of stf string
	*/
	inline void setTU(const String& file, const String& stringid) {
		TU.set(file, stringid);
	}

	/**
	* Sets the TO variable of a stf string
	* @pre { obj is one of the following:
	* 		String, UnicodeString, pointer to SceneObject that is in the client's memory,
	* 		objectid of SceneObject that is in the client's memory, StringId, pointer to StringId
	*  	   }
	* @post { TO variable is set }
	* @param obj Data that the TO variable is to be set as
	*/
	template<class T>
	inline void setTO(const T& obj) {
		TO.set(obj);
	}

	/**
	* Sets the TO variable of this stf string to another stf string
	* @pre { }
	* @post { TO variable is set }
	* @param file stf file name that contains the stf string
	* @param stringid stringid of stf string
	*/
	inline void setTO(const String& file, const String& stringid) {
		TO.set(file, stringid);
	}

	/**
	* Sets the DI variable
	* @pre { }
	* @post { DI variable is set }
	* @param i value for DI
	*/
	inline void setDI(uint32 i) {
		DI = i;
	}

	/**
	* Sets the DF variable
	* @pre { }
	* @post { DF variable is set }
	* @param f value for DF
	*/
	inline void setDF(float f) {
		DF = f;
	}

	inline void setUnknownByte(uint16 val) {
		unknownByte = val;
	}
};

}
}

using namespace server::chat;

#endif /* STRINGIDCHATPARAMETER_H_ */
