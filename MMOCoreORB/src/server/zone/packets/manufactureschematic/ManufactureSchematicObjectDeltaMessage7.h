/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef MANUFACTURESCHEMATICOBJECTDELTAMESSAGE7_H_
#define MANUFACTURESCHEMATICOBJECTDELTAMESSAGE7_H_

#include "server/zone/packets/DeltaMessage.h"
#include "templates/params/RangedIntCustomizationVariable.h"

class ManufactureSchematicObjectDeltaMessage7 : public DeltaMessage {
public:
	ManufactureSchematicObjectDeltaMessage7(SceneObject* schematic) :
		DeltaMessage(schematic->getObjectID(), 0x4D53434F, 7) {
	}

	void updateForAssembly(ManufactureSchematic* manufactureSchematic, float failureRate){
		initialAssemblyUpdate(manufactureSchematic);
		update9(manufactureSchematic, true);
		//update0A(manufactureSchematic);
		update0B(manufactureSchematic);
		update0C(manufactureSchematic);
		update12(failureRate);
		update13(manufactureSchematic);
	}

	void updateCustomizationOptions(VectorMap<String, Reference<CustomizationVariable*> >* vars,
			int custpoints){
		update0D(vars);
		update0E(vars);
		update0F(vars);
		update10(vars, custpoints);
		update11();
	}

	// update 8
	void initialAssemblyUpdate(ManufactureSchematic* manufactureSchematic) {
		CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();

		startUpdate(0x08);

		int totalGroups = craftingValues->getTotalVisibleAttributeGroups();
		int counter = manufactureSchematic->getExperimentingCounter();

		insertInt(totalGroups);
		insertInt(totalGroups);

		for (int i = 0; i < totalGroups; i++) {
			String title = craftingValues->getVisibleAttributeGroup(i);

			insertByte(1);
			insertShort(i);
			insertAscii("crafting");  // I think this is always "crafting"
			insertInt(0);
			insertAscii(title);
		}

		// Initialize update 9************
		startUpdate(9);

		startList(totalGroups, totalGroups);  // totalGroups, counter

		for (int i = 0; i < totalGroups; i++) {
			addListFloatElement(i, 0); //0
		}
		//!*********************************
		// Initialize update 0A************
		startUpdate(0x0A);

		startList(totalGroups, totalGroups);

		for (int i = 0; i < totalGroups; i++) {
			addListFloatElement(i, 0);
		}
		//!*********************************
		// Initialize update 0B************
		startUpdate(0x0B);

		startList(totalGroups, totalGroups);

		for (int i = 0; i < totalGroups; i++) {
			addListFloatElement(i, 0);
		}
		//!*********************************
		// Initialize update 0C************
		startUpdate(0x0C);

		startList(totalGroups, totalGroups);

		for (int i = 0; i < totalGroups; i++) {
			addListFloatElement(i, 0);
		}
		//!**********************************

	}

	// This sends the experimental values shown in the Screen after hitting assemble
	void update9(ManufactureSchematic* manufactureSchematic, bool initial) {
		int count;

		startUpdate(0x09);

		CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();

		int totalGroups = craftingValues->getTotalVisibleAttributeGroups();

		if (initial) {
			manufactureSchematic->setExperimentingCounter(totalGroups * 2);
			manufactureSchematic->setExperimentingCounter(totalGroups * 3);
		}

		count = manufactureSchematic->getExperimentingCounterPrevious();

		//manufactureSchematic->info(true) << "Visible Groups: " << totalGroups << " Current Count: " << count;

		startList(totalGroups, count);

		for (int i = 0; i < totalGroups; i++) {
			String group = craftingValues->getVisibleAttributeGroup(i);

			float value = craftingValues->getCurrentVisiblePercentage(group);

			if(value > 0 && value < .01)
				value = .01f;

			removeListFloatElement(i, value);
		}
	}

	void update0A(ManufactureSchematic* manufactureSchematic) {

		CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();

		startUpdate(0x0A);

		int totalGroups = craftingValues->getTotalVisibleAttributeGroups();

		startList(totalGroups, totalGroups * 2);

		for (int i = 0; i < totalGroups; i++) {
			removeListFloatElement(i, 1.0f);
		}
	}
	// I think this is usually 1.0
	void update0B(ManufactureSchematic* manufactureSchematic) {

		CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();

		startUpdate(0x0B);

		int totalGroups = craftingValues->getTotalVisibleAttributeGroups();

		startList(totalGroups, totalGroups * 2);

		for (int i = 0; i < totalGroups; i++) {
			removeListFloatElement(i, 1.0f);
		}
	}
	// This is the MAX experimental value.  How many bars
	void update0C(ManufactureSchematic* manufactureSchematic) {

		CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();

		startUpdate(0x0C);

		int totalGroups = craftingValues->getTotalVisibleAttributeGroups();

		startList(totalGroups, totalGroups * 2);

		float value;

		for (int i = 0; i < totalGroups; i++) {

			value = craftingValues->getMaxVisiblePercentage(i);

			removeListFloatElement(i, value);
		}
	}

	void update0D(VectorMap<String, Reference<CustomizationVariable*> >* vars) {

		startUpdate(0x0D);

		startList(vars->size(), vars->size());

		for (int i = 0; i < vars->size(); ++i) {

			insertByte(0x01);
			insertShort(i);
			RangedIntCustomizationVariable* var = cast<RangedIntCustomizationVariable*>(vars->get(i).get());
			if(var == nullptr)
				insertAscii("");
			else
				insertAscii(vars->elementAt(i).getKey());
		}
	}

	// Starting COlor chooser position
	void update0E(VectorMap<String, Reference<CustomizationVariable*> >* vars) {

		startUpdate(0x0E);

		startList(vars->size(), vars->size());

		for (int i = 0; i < vars->size(); ++i) {

			insertByte(0x01);
			insertShort(i);
			RangedIntCustomizationVariable* var = cast<RangedIntCustomizationVariable*>(vars->get(i).get());
			if(var == nullptr)
				insertInt(0);
			else
				insertInt(var->getDefaultValue());
		}
	}

	void update0F(VectorMap<String, Reference<CustomizationVariable*> >* vars) {

		startUpdate(0x0F);

		startList(vars->size(), vars->size());

		for (int i = 0; i < vars->size(); ++i) {
			insertByte(0x01);
			insertShort(i);
			insertInt(0);
		}
	}

	// Number of palette colors
	void update10(VectorMap<String, Reference<CustomizationVariable*> >* vars, int custpoints) {

		startUpdate(0x10);

		startList(vars->size(), vars->size());

		for (int i = 0; i < vars->size(); ++i) {
			insertByte(0x01);
			insertShort(i);
			insertInt(custpoints);
		}
	}

	void update11() {

		startUpdate(0x11);
		insertByte(1);
	}

	void update12(float failureRate){
		startUpdate(0x12);
		insertFloat(failureRate);
	}

	void update13(ManufactureSchematic* manufactureSchematic){

		ManagedReference<DraftSchematic*> draftSchematic = manufactureSchematic->getDraftSchematic();
		if(draftSchematic == nullptr)
			return;

		startUpdate(0x13);

		/// Template List
		int templateCount = draftSchematic->getTemplateListSize();

		startList(templateCount, templateCount);

		/// The first template is the
		for(int i = 0; i < templateCount; ++i) {
			insertByte(0x01);
			insertShort(i);
			insertAscii(draftSchematic->getTemplate(i));
		}
	}

	void update14() {

		startUpdate(0x14);
		insertByte(1);
	}

};

#endif /*MANUFACTURESCHEMATICOBJECTMESSAGE7_H_*/
