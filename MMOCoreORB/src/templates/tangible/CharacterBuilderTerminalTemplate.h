/*
 * CharacterBuildterTerminalTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef CHARACTERBUILDTERTERMINALTEMPLATE_H_
#define CHARACTERBUILDTERTERMINALTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"
#include "templates/tangible/CharacterBuilderMenuNode.h"

class CharacterBuilderTerminalTemplate : public SharedTangibleObjectTemplate {
	Reference<CharacterBuilderMenuNode*> rootNode;
	Vector<int> glowyBadgeIds;
	Vector<String> villageBranchUnlocks;

public:
	CharacterBuilderTerminalTemplate() : rootNode(NULL) {
	}

	~CharacterBuilderTerminalTemplate() {
		if (rootNode != NULL) {
			//delete rootNode;
			rootNode = NULL;
		}
	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		LuaObject luaGlowyBadges = templateData->getObjectField("glowyBadgeIds");

		for (int i = 1; i <= luaGlowyBadges.getTableSize(); ++i) {
			glowyBadgeIds.add(luaGlowyBadges.getIntAt(i));
		}

		luaGlowyBadges.pop();

		LuaObject luaBranchUnlocks = templateData->getObjectField("villageBranchUnlocks");

		for (int i = 1; i <= luaBranchUnlocks.getTableSize(); ++i) {
			villageBranchUnlocks.add(luaBranchUnlocks.getStringAt(i));
		}

		luaBranchUnlocks.pop();

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

    inline Vector<int> getGlowyBadgeIds() const {
        return glowyBadgeIds;
    }

    inline Vector<String> getVillageBranchUnlocks() const {
        return villageBranchUnlocks;
    }
};



#endif /* CHARACTERBUILDTERTERMINALTEMPLATE_H_ */
