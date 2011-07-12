/*
 * SharedBuildingObjectTemplate.cpp
 *
 *  Created on: 05/05/2010
 *      Author: victor
 */

#include "SharedBuildingObjectTemplate.h"

void SharedBuildingObjectTemplate::parseVariableData(const String& varName, Chunk* data) {
	if (varName == "terrainModificationFileName") {
		terrainModificationFileName.parse(data);
	} else if (varName == "interiorLayoutFileName") {
		interiorLayoutFileName.parse(data);
	}
}

void SharedBuildingObjectTemplate::parseVariableData(const String& varName, LuaObject* templateData) {
	lua_State* state = templateData->getLuaState();

	if (varName == "terrainModificationFileName") {
		terrainModificationFileName = Lua::getStringParameter(state);
	} else if (varName == "interiorLayoutFileName") {
		interiorLayoutFileName = Lua::getStringParameter(state);
	} else if (varName == "sign") {
		LuaObject signObject(state);
		ChildObject object;
		object.parseFromLua(&signObject);
		sign = object;
		signObject.pop();
	} else if (varName == "publicStructure") {
		publicStructure = (bool) Lua::getByteParameter(state);
	} else if (varName == "alwaysPublic") {
		alwaysPublic = (bool) Lua::getByteParameter(state);
	} else {
		templateData->pop();
	}	
}

void SharedBuildingObjectTemplate::parseFileData(IffStream* iffStream) {
	iffStream->openChunk('PCNT');

	int variableCount = iffStream->getInt();

	iffStream->closeChunk('PCNT');

	for (int i = 0; i < variableCount; ++i) {
	//while (iffStream->getRemainingSubChunksNumber() > 0) {
		Chunk* chunk = iffStream->openChunk('XXXX');

		if (chunk == NULL)
			continue;

		String varName;
		iffStream->getString(varName);

		//std::cout << "parsing wtf shit:[" << varName.toStdString() << "]\n";
		parseVariableData(varName, chunk);

		iffStream->closeChunk();
	}
}


void SharedBuildingObjectTemplate::readObject(IffStream* iffStream) {
	uint32 nextType = iffStream->getNextFormType();

	if (nextType != 'SBOT') {
		//Logger::console.error("expecting SHOT got " + String::hexvalueOf((int)nextType));

		SharedTangibleObjectTemplate::readObject(iffStream);

		return;
	}

	iffStream->openForm('SBOT');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream);

		derv = iffStream->getNextFormType();
	}

	iffStream->openForm(derv);

	try {
		parseFileData(iffStream);
	} catch (Exception& e) {
		String msg;
		msg += "exception caught parsing file data ->";
		msg += e.getMessage();

		Logger::console.error(msg);
	}

	iffStream->closeForm(derv);

	if (iffStream->getRemainingSubChunksNumber() > 0) {
		readObject(iffStream);
	}

	iffStream->closeForm('SBOT');
}

void SharedBuildingObjectTemplate::readObject(LuaObject* templateData) {
	SharedStructureObjectTemplate::readObject(templateData);

	lua_State* L = templateData->getLuaState();

	if (!templateData->isValidTable())
		return;

	int i = 0;

	lua_pushnil(L);  
	while (lua_next(L, -2) != 0) {
		// 'key' is at index -2 and 'value' at index -1 
		//printf("%s - %s\n",
		//		lua_tostring(L, -2), lua_typename(L, lua_type(L, -1)));

		int type = lua_type(L, -2);

		if (type == LUA_TSTRING) {
			size_t len = 0;
			const char* varName = lua_tolstring(L, -2, &len);

			parseVariableData(varName, templateData);
		} else
			lua_pop(L, 1);
		

		++i;
	}
	
	return;

	/*terrainModificationFileName = templateData->getStringField("terrainModificationFileName");
	interiorLayoutFileName = templateData->getStringField("interiorLayoutFileName");

	LuaObject signObject = templateData->getObjectField("sign");
	ChildObject object;
	object.parseFromLua(&signObject);
	sign = object;
	signObject.pop();

	publicStructure = (bool) templateData->getByteField("publicStructure");

	alwaysPublic = (bool) templateData->getByteField("alwaysPublic");*/
}
