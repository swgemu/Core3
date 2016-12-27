/*
 * HairAssetData.h
 *
 *  Created on: 29/03/2012
 *      Author: victor
 */

#ifndef HAIRASSETDATA_H_
#define HAIRASSETDATA_H_

#include "system/lang.h"
#include "templates/datatables/DataTableRow.h"

class HairAssetData : public Object {
	String sharedTemplate;
	String playerTemplate;
	int skillModValue;
	bool availableAtCreation;
	String serverTemplate;
	String serverPlayerTemplate;

public:
	HairAssetData() {
		skillModValue = 0;
		availableAtCreation = 0;
	}

	void readObject(DataTableRow* row) {
		row->getValue(0, sharedTemplate);
		row->getValue(1, playerTemplate);
		row->getValue(2, skillModValue);
		row->getValue(3, availableAtCreation);
		row->getValue(4, serverTemplate);
		row->getValue(5, serverPlayerTemplate);
	}

	bool isAvailableAtCreation() const {
		return availableAtCreation;
	}

	String getPlayerTemplate() const {
		return playerTemplate;
	}

	String getServerPlayerTemplate() const {
		return serverPlayerTemplate;
	}

	void setServerPlayerTemplate(const String& serverPlayerTemplate) {
		this->serverPlayerTemplate = serverPlayerTemplate;
	}

	String getServerTemplate() const {
		return serverTemplate;
	}

	String getSharedTemplate() const {
		return sharedTemplate;
	}

	int getSkillModValue() const {
		return skillModValue;
	}
};


#endif /* HAIRASSETDATA_H_ */
