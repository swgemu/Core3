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

#ifndef ATTACHMENTIMPLEMENTATION_H_
#define ATTACHMENTIMPLEMENTATION_H_

#include "engine/engine.h"
#include "Attachment.h"

class Player;

class AttachmentImplementation : public AttachmentServant {
protected:
	int attachmentType;
		
	int skillMod0Type;
	int skillMod0Value;
	
	int skillMod1Type;
	int skillMod1Value;
	
	int skillMod2Type;
	int skillMod2Value;
	
public:
	static const int CLOTHING =  1;
	static const int ARMOR = 2;

public:
	AttachmentImplementation(uint64 objID, int attachmentType);
	
	virtual ~AttachmentImplementation();

	void initialize();
	
	void parseItemAttributes();
	
	void remove(Player* player);
	
	void generateAttributes(SceneObject* obj);
	void addAttributes(AttributeListMessage* alm);
		
	void setSkillModValue(int index, int value);
	void setSkillModType(int index, int type);
	
	void setSkillMods(int modifier);
	int getModValue(int luck, int modifier);

	inline void setSkillMod0Type(int skillModType) {
		skillMod0Type = skillModType;
		String name = "skillMod0Type";
		itemAttributes->setIntAttribute(name, skillModType);
	}

	inline void setSkillMod1Type(int skillModType) {
		skillMod1Type = skillModType;
		String name = "skillMod1Type";
		itemAttributes->setIntAttribute(name, skillModType);
	}

	inline void setSkillMod2Type(int skillModType) {
		skillMod2Type = skillModType;
		String name = "skillMod2Type";
		itemAttributes->setIntAttribute(name, skillModType);
	}
	
	inline void setSkillMod0Value(int skillModValue) {
		skillMod0Value = skillModValue;
		String name = "skillMod0Value";
		itemAttributes->setIntAttribute(name, skillModValue);
	}

	inline void setSkillMod1Value(int skillModValue) {
		skillMod1Value = skillModValue;
		String name = "skillMod1Value";
		itemAttributes->setIntAttribute(name, skillModValue);
	}
	
	inline void setSkillMod2Value(int skillModValue) {
		skillMod2Value = skillModValue;
		String name = "skillMod2Value";
		itemAttributes->setIntAttribute(name, skillModValue);
	}
	
	int getSkillModType(int index);
	int getSkillModValue(int index);
	
	int getBestSkillMod();
	
	inline int getSkillMod0Type() {
		return skillMod0Type;
	}
	inline int getSkillMod1Type() {
		return skillMod1Type;
	}
	inline int getSkillMod2Type() {
		return skillMod2Type;
	}
	inline int getSkillMod0Value() {
		return skillMod0Value;
	}
	inline int getSkillMod1Value() {
		return skillMod1Value;
	}
	inline int getSkillMod2Value() {
		return skillMod2Value;
	}
};

#endif /*ATTACHMENTIMPLEMENTATION_H_*/
