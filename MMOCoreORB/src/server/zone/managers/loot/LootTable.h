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

#ifndef LOOTTABLE_H_
#define LOOTTABLE_H_

#include "../../objects.h"

class LootTableFields {
	uint64 lootItemID;
	int lootItemGroup;
	string lootItemName;
	uint64 lootItemTemplateCRC;
	uint64 lootItemTemplateType;
	string lootItemTemplateName;
	string lootItemAttributes;
	string lootItemAppearance;
	int lootItemLevel;
	int lootItemChance;
	string lootItemLastDropStamp;
	string lootItemDontDropBefore;
	int lootItemUnique;
	int lootItemNoTrade;
	string lootItemRace;
	string lootItemDeveloperNote;
	string lootItemType;
	
public:

	//setters
	void setLootItemID(uint64 lootitemid) {
		lootItemID = lootitemid;
	}
	
	void setLootItemGroup(int lootitemgroup) {
		lootItemGroup = lootitemgroup;
	}
	
	void setLootItemName(string lootitemname) {
		lootItemName = lootitemname;
	}	
	
	void setLootItemTemplateCRC(uint64 lootitemtemplatecrc) {
		lootItemTemplateCRC = lootitemtemplatecrc;
	}	
	
	void setLootItemTemplateType(uint64 lootitemtemplatetype) {
		lootItemTemplateType = lootitemtemplatetype;
	}	
	
	void setLootItemTemplateName(string lootitemtemplatename) {
		lootItemTemplateName = lootitemtemplatename;
	}
	
	void setLootItemAttributes(string lootitemattributes) {
		lootItemAttributes = lootitemattributes;
	}
	
	void setLootItemAppearance(string lootitemappearance) {
		lootItemAppearance = lootitemappearance;
	}	
	
	void setLootItemLevel(int lootitemlevel) {
		lootItemLevel = lootitemlevel;
	}
	
	void setLootItemChance(int lootitemchance) {
		lootItemChance = lootitemchance;
	}
	
	void setLootItemLastDropStamp(string lootitemlastdropstamp) {
		lootItemLastDropStamp = lootitemlastdropstamp;
	}	
	
	void setLootItemDontDropBefore(string lootitemdontdropbefore) {
		lootItemDontDropBefore = lootitemdontdropbefore;
	}	
	
	void setLootItemUnique(int lootitemunique) {
		lootItemUnique = lootitemunique;
	}		
	
	void setLootItemNoTrade(int lootitemnotrade) {
		lootItemNoTrade = lootitemnotrade;
	}	
	
	void setLootItemRace(string lootitemrace) {
		lootItemRace = lootitemrace;
	}
	
	void setLootItemDeveloperNote(string lootitemdevelopernote) {
		lootItemDeveloperNote = lootitemdevelopernote;
	}

	//getters
	uint64 getLootItemID() {
		return lootItemID;
	}
	
	int getLootItemGroup() {
		return lootItemGroup;
	}
	
	string getLootItemName() {
		return lootItemName;
	}	
	
	uint64 getLootItemTemplateCRC() {
		return lootItemTemplateCRC;
	}	
	
	uint64 getLootItemTemplateType() {
		return lootItemTemplateType;
	}

	string getLootItemTemplateName() {
		return lootItemTemplateName;
	}
	
	string getLootItemAttributes() {
		return lootItemAttributes;
	}
	
	string getLootItemAppearance() {
		return lootItemAppearance;
	}	
	
	int getLootItemLevel() {
		return lootItemLevel;
	}
	
	int getLootItemChance() {
		return lootItemChance;
	}
	
	string getLootItemLastDropStamp() {
		return lootItemLastDropStamp;
	}	
	
	string getLootItemDontDropBefore() {
		return lootItemDontDropBefore;
	}	
	
	int getLootItemUnique() {
		return lootItemUnique;
	}		
	
	int getLootItemNoTrade() {
		return lootItemNoTrade;
	}	
	
	string getLootItemRace() {
		return lootItemRace;
	}
	
	string getLootItemDeveloperNote() {
		return lootItemDeveloperNote;
	}

};

#endif /*LOOTTABLE_H_*/
