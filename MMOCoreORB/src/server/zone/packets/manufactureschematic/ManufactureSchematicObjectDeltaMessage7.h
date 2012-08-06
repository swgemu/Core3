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

#ifndef MANUFACTURESCHEMATICOBJECTDELTAMESSAGE7_H_
#define MANUFACTURESCHEMATICOBJECTDELTAMESSAGE7_H_

#include "../BaseLineMessage.h"
#include "server/zone/templates/params/RangedIntCustomizationVariable.h"

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

		startUpdate(8);

		int titleCount = craftingValues->getVisibleExperimentalPropertyTitleSize();
		int counter = manufactureSchematic->getExperimentingCounter();

		insertInt(titleCount);
		insertInt(titleCount);

		for (int i = 0; i < titleCount; i++) {
			String title = craftingValues->getVisibleExperimentalPropertyTitle(i);

			insertByte(1);
			insertShort(i);
			insertAscii("crafting");  // I think this is always "crafting"
			insertInt(0);
			insertAscii(title);
		}

		// Initialize update 9************
		startUpdate(9);

		startList(titleCount, titleCount);  // titleCount, counter

		for (int i = 0; i < titleCount; i++) {
			addListFloatElement(i, 0); //0
		}
		//!*********************************
		// Initialize update 0A************
		startUpdate(0x0A);

		startList(titleCount, titleCount);

		for (int i = 0; i < titleCount; i++) {
			addListFloatElement(i, 0);
		}
		//!*********************************
		// Initialize update 0B************
		startUpdate(0x0B);

		startList(titleCount, titleCount);

		for (int i = 0; i < titleCount; i++) {
			addListFloatElement(i, 0);
		}
		//!*********************************
		// Initialize update 0C************
		startUpdate(0x0C);

		startList(titleCount, titleCount);

		for (int i = 0; i < titleCount; i++) {
			addListFloatElement(i, 0);
		}
		//!**********************************

	}

	// This sends the experimental values shown in the Screen after hitting assemble
	void update9(ManufactureSchematic* manufactureSchematic, bool initial) {

		int count;

		startUpdate(9);

		CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();

		int titleCount = craftingValues->getVisibleExperimentalPropertyTitleSize();

		if (initial) {
			manufactureSchematic->setExperimentingCounter(titleCount * 2);
			manufactureSchematic->setExperimentingCounter(titleCount * 3);
		}

//System::out << "Visible: " << titleCount << "  Count: " << count << endl;

		count = manufactureSchematic->getExperimentingCounterPrevious();

		startList(titleCount, count);

		for (int i = 0; i < titleCount; i++) {

			String title = craftingValues->getVisibleExperimentalPropertyTitle(i);

			float value = craftingValues->getCurrentVisiblePercentage(title);

			if(value > 0 && value < .01)
				value = .01f;

			removeListFloatElement(i, value);

		}
	}

	void update0A(ManufactureSchematic* manufactureSchematic) {

		CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();

		startUpdate(0x0A);

		int titleCount = craftingValues->getVisibleExperimentalPropertyTitleSize();

		startList(titleCount, titleCount * 2);

		for (int i = 0; i < titleCount; i++) {
			removeListFloatElement(i, 1.0f);
		}
	}
	// I think this is usually 1.0
	void update0B(ManufactureSchematic* manufactureSchematic) {

		CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();

		startUpdate(0x0B);

		int titleCount = craftingValues->getVisibleExperimentalPropertyTitleSize();

		startList(titleCount, titleCount * 2);

		for (int i = 0; i < titleCount; i++) {
			removeListFloatElement(i, 1.0f);
		}
	}
	// This is the MAX experimental value.  How many bars
	void update0C(ManufactureSchematic* manufactureSchematic) {

		CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();

		startUpdate(0x0C);

		int titleCount = craftingValues->getVisibleExperimentalPropertyTitleSize();

		startList(titleCount, titleCount * 2);

		float value;

		for (int i = 0; i < titleCount; i++) {

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
			if(var == NULL)
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
			if(var == NULL)
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
		if(draftSchematic == NULL)
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
