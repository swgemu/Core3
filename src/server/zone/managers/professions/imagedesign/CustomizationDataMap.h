/*
 * CustomizationDataMap.h
 *
 *  Created on: Feb 11, 2011
 *      Author: crush
 */

#ifndef CUSTOMIZATIONDATAMAP_H_
#define CUSTOMIZATIONDATAMAP_H_

#include "engine/engine.h"
#include "CustomizationData.h"

#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/templates/datatables/DataTableRow.h"
#include "server/zone/templates/datatables/DataTableCell.h"

class CustomizationDataMap : public VectorMap<String, CustomizationData> {
public:
	CustomizationDataMap() {
		setAllowDuplicateInsertPlan();
	}

	void parseFromIffStream(IffStream* iffStream) {
		if (iffStream == NULL)
			return;

		DataTableIff dataTable;
		dataTable.readObject(iffStream);

		for (int i = 0; i < dataTable.getRowsSize(); i++) {
			DataTableRow* dataRow = dataTable.getRow(i);
			CustomizationData customizationData;
			bool valueBool;
			int valueInt;
			float valueFloat;

			customizationData.setSpeciesGender(dataRow->getCell(0)->toString());
			customizationData.setCustomizationGroup(dataRow->getCell(1)->toString());
			customizationData.setType(dataRow->getCell(2)->toString());
			customizationData.setCustomizationName(dataRow->getCell(3)->toString());
			customizationData.setVariables(dataRow->getCell(4)->toString());

			dataRow->getCell(5)->getValue(valueBool);
			customizationData.setIsScale(valueBool);

			dataRow->getCell(6)->getValue(valueBool);
			customizationData.setReverse(valueBool);

			customizationData.setColorLinked(dataRow->getCell(7)->toString());
			customizationData.setColorLinkedtoSelf0(dataRow->getCell(8)->toString());
			customizationData.setColorLinkedtoSelf1(dataRow->getCell(9)->toString());

			dataRow->getCell(10)->getValue(valueInt);
			customizationData.setCameraYaw(valueInt);

			dataRow->getCell(11)->getValue(valueBool);
			customizationData.setDiscrete(valueBool);

			dataRow->getCell(12)->getValue(valueBool);
			customizationData.setRandomizable(valueBool);

			dataRow->getCell(13)->getValue(valueBool);
			customizationData.setRandomizableGroup(valueBool);

			dataRow->getCell(14)->getValue(valueBool);
			customizationData.setIsVarHairColor(valueBool);

			customizationData.setImageDesignSkillMod(dataRow->getCell(15)->toString());

			dataRow->getCell(16)->getValue(valueInt);
			customizationData.setSkillModValue(valueInt);

			customizationData.setModificationType(dataRow->getCell(17)->toString());

			put(dataRow->getCell(0)->toString(), customizationData);

		}

		delete iffStream;
		iffStream = NULL;
	}
};

#endif /* CUSTOMIZATIONDATAMAP_H_ */
