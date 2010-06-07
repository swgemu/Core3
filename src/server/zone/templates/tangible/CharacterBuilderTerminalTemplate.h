/*
 * CharacterBuildterTerminalTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef CHARACTERBUILDTERTERMINALTEMPLATE_H_
#define CHARACTERBUILDTERTERMINALTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"
#include "server/zone/objects/tangible/terminal/characterbuilder/CharacterBuilderMenuNode.h"

class CharacterBuilderTerminalTemplate : public SharedTangibleObjectTemplate {
	CharacterBuilderMenuNode* rootNode;

public:
	CharacterBuilderTerminalTemplate() {
		rootNode = NULL;
	}

	~CharacterBuilderTerminalTemplate() {
		if (rootNode != NULL) {
			delete rootNode;
			rootNode = NULL;
		}
	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		LuaObject luaItemList = templateData->getObjectField("itemList");

		//Ensure that the luaItemList root level is of an even order.
		if (luaItemList.getTableSize() % 2 != 0) {
			System::out << "[CharacterBuilderTerminalTemplate] Dimension mismatch in itemList. Item count must be a multiple of 2." << endl;
			luaItemList.pop();
			return;
		}

		rootNode = new CharacterBuilderMenuNode("root");
		rootNode->readLuaObject(luaItemList, true);

		luaItemList.pop();
    }

    inline CharacterBuilderMenuNode* getItemList() const {
        return rootNode;
    }

};



#endif /* CHARACTERBUILDTERTERMINALTEMPLATE_H_ */
