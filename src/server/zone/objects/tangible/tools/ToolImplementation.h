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

#ifndef TOOLIMPLEMENTATION_H_
#define TOOLIMPLEMENTATION_H_

#include "../../player/Player.h"

#include "Tool.h"

class ToolImplementation : public ToolServant {
	uint32 toolType;
	float effectiveness;

public:
	//Smuggler Tool Types
	static const uint32 PRECLASERKNIFE = 100;
	static const uint32 FLOWANALYZERNODE = 101;
	static const uint32 MOLECULARCLAMP = 102;
	static const uint32 UPGRADEKIT = 103;

public:
	ToolImplementation(uint64 objID, uint32 tempCRC, const UnicodeString& n, const String& tempn, uint32 tooltype);
	ToolImplementation(uint64 objID, uint32 tooltype);

	void init();

	void generateAttributes(SceneObject* obj);

	void parseItemAttributes();

	void addAttributes(AttributeListMessage* alm);
	virtual void addHeaderAttributes(AttributeListMessage* alm);
	virtual void addFooterAttributes(AttributeListMessage* alm);


	//Setters
	inline void setToolType(uint32 value) {
		toolType = value;
		String attr = "toolType";
		itemAttributes->setIntAttribute(attr, toolType);
	}

	inline void setEffectiveness(float value) {
		effectiveness = value;
		String attr = "effectiveness";
		itemAttributes->setFloatAttribute(attr, effectiveness);
	}

	//Getters
	inline uint32 getToolType() {
		return toolType;
	}

	inline float getEffectiveness() {
		return effectiveness;
	}


	//Smuggler Tools
	inline bool isPrecisionLaserKnife() {
		return toolType == PRECLASERKNIFE;
	}

	inline bool isFlowAnalyzerNode() {
		return toolType == FLOWANALYZERNODE;
	}

	inline bool isMolecularClamp() {
		return toolType == MOLECULARCLAMP;
	}

	inline bool isUpgradeKit() {
		return toolType == UPGRADEKIT;
	}

	inline bool isRepairTool() {
		return (toolType==WEAPON || toolType==ARMOR || toolType==CLOTHING);
	}

};

#endif /* TOOLIMPLEMENTATION_H_ */
