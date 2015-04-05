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
	Reference<CharacterBuilderMenuNode*> rootNode;
	int performanceBuff;
	int medicalBuff;
	int	performanceDuration;
	int	medicalDuration;

public:
	CharacterBuilderTerminalTemplate() : rootNode(NULL), performanceBuff(0),
		medicalBuff(0), performanceDuration(0), medicalDuration(0) {
	}

	~CharacterBuilderTerminalTemplate() {
		if (rootNode != NULL) {
			//delete rootNode;
			rootNode = NULL;
		}
	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		performanceBuff = templateData->getIntField("performanceBuff");
		medicalBuff = templateData->getIntField("medicalBuff");
		performanceDuration = templateData->getIntField("performanceDuration");
		medicalDuration = templateData->getIntField("medicalDuration");

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

    inline int getPerformanceBuff() const {
    	return performanceBuff;
    }

    inline int getMedicalBuff() const {
    	return medicalBuff;
    }

    inline int getPerformanceDuration() const {
    	return performanceDuration;
    }

    inline int getMedicalDuration() const {
    	return medicalDuration;
    }

};



#endif /* CHARACTERBUILDTERTERMINALTEMPLATE_H_ */
