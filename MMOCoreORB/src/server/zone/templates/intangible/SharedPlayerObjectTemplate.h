/*
 * SharedPlayerObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDPLAYEROBJECTTEMPLATE_H_
#define SHAREDPLAYEROBJECTTEMPLATE_H_

#include "../SharedIntangibleObjectTemplate.h"

class SharedPlayerObjectTemplate : public SharedIntangibleObjectTemplate {
protected:
	SortedVector<String> playerDefaultGroupPermissions;

public:
	SharedPlayerObjectTemplate() {

	}

	~SharedPlayerObjectTemplate() {

	}

	void readObject(IffStream* iffStream) {
		uint32 nextType = iffStream->getNextFormType();

		if (nextType != 'SPLY') {
			//Logger::console.error("expecting SHOT got " + String::hexvalueOf((int)nextType));

			SharedIntangibleObjectTemplate::readObject(iffStream);

			return;
		}

		iffStream->openForm('SPLY');

		uint32 derv = iffStream->getNextFormType();

		if (derv == 'DERV') {
			loadDerv(iffStream);

			derv = iffStream->getNextFormType();
		}


		iffStream->openForm(derv);

		try {
			//parseFileData(iffStream);
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

		iffStream->closeForm('SPLY');
	}

	void readObject(LuaObject* templateData) {
		SharedIntangibleObjectTemplate::readObject(templateData);

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
	}

	void parseVariableData(const String& varName, LuaObject* templateData) {
		if (varName == "playerDefaultGroupPermissions") {
			LuaObject perms(templateData->getLuaState());

			for (int i = 1; i <= perms.getTableSize(); ++i) {
				playerDefaultGroupPermissions.put(perms.getStringAt(i));
			}

			perms.pop();
		} else {
			templateData->pop();
		}
	}

	SortedVector<String>* getPlayerDefaultGroupPermissions() {
		return &playerDefaultGroupPermissions;
	}

};

#endif /* SHAREDPLAYEROBJECTTEMPLATE_H_ */
