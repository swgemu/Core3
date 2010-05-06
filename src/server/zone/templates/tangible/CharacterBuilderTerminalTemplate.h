/*
 * CharacterBuildterTerminalTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef CHARACTERBUILDTERTERMINALTEMPLATE_H_
#define CHARACTERBUILDTERTERMINALTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class CharacterBuilderTerminalTemplate : public SharedTangibleObjectTemplate {
	VectorMap<uint32, String> itemList;

public:
	CharacterBuilderTerminalTemplate() {

	}

	~CharacterBuilderTerminalTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		LuaObject deedsList = templateData->getObjectField("deedsList");

        if (deedsList.getTableSize() % 2 == 0) {
            for (int i = 1;i <= deedsList.getTableSize();i += 2) {
                String itemName = deedsList.getStringAt(i);
                uint32 itemCRC = deedsList.getStringAt(i + 1).hashCode();
                itemList.put(itemCRC, itemName);
            }
        } else {
            System :: out << "Elements in deedsList must be of an even order.";
        }

        deedsList.pop();
    }

    VectorMap<uint32, String> getItemList() const {
        return itemList;
    }

};



#endif /* CHARACTERBUILDTERTERMINALTEMPLATE_H_ */
