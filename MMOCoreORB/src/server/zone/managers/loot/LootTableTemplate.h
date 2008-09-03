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

#ifndef LOOTTABLETEMPLATE_H_
#define LOOTTABLETEMPLATE_H_

#include "engine/engine.h"

#include "LootTable.h"

class LootTableTemplate {
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
	string lootItemTypeHex;
	string lootItemPath;
	string lootItemString;

	Vector<LootTableFields*> * lootTableFields;

public:
	LootTableTemplate() {
		lootItemGroup = 0 ;
		lootItemName = "";
		lootItemTemplateCRC = 0;
		lootItemTemplateType = 0;
		lootItemTemplateName = "";
		lootItemAttributes = "";
		lootItemAppearance = "";
		lootItemLevel = 0;
		lootItemChance = 0;
		lootItemLastDropStamp = "";
		lootItemDontDropBefore = "";
		lootItemUnique = 0;
		lootItemNoTrade = 0;
		lootItemRace = "";
		lootItemDeveloperNote = "";
		lootItemString = "";
		lootItemTypeHex = "0x0";
		lootItemPath = "";
		lootItemString = "";


		lootTableFields = new Vector<LootTableFields*>();
	}

	~LootTableTemplate() {
		while (lootTableFields->size() > 0) {
			LootTableFields* ltf = lootTableFields->remove(0);

			delete ltf;
		}

		delete lootTableFields;
		lootTableFields = NULL;
	}

	//setters
	inline void setLootItemGroup(int lootitemgroup) {
		lootItemGroup = lootitemgroup;
	}

	inline void setLootItemName(string lootitemname) {
		lootItemName = lootitemname;
	}

	inline void setLootItemTemplateCRC(uint64 lootitemtemplatecrc) {
		lootItemTemplateCRC = lootitemtemplatecrc;
	}

	inline void setLootItemTemplateType(uint64 lootitemtemplatetype) {
		lootItemTemplateType = lootitemtemplatetype;
	}

	inline void setLootItemTemplateName(string lootitemtemplatename) {
		lootItemTemplateName = lootitemtemplatename;
	}

	inline void setLootItemAttributes(string lootitemattributes) {
		lootItemAttributes = lootitemattributes;
	}

	inline void setLootItemAppearance(string lootitemappearance) {
		lootItemAppearance = lootitemappearance;
	}

	inline void setLootItemLevel(int lootitemlevel) {
		lootItemLevel = lootitemlevel;
	}

	inline void setLootItemChance(int lootitemchance) {
		lootItemChance = lootitemchance;
	}

	inline void setLootItemLastDropStamp(string lootitemlastdropstamp) {
		lootItemLastDropStamp = lootitemlastdropstamp;
	}

	inline void setLootItemDontDropBefore(string lootitemdontdropbefore) {
		lootItemDontDropBefore = lootitemdontdropbefore;
	}

	inline void setLootItemUnique(int lootitemunique) {
		lootItemUnique = lootitemunique;
	}

	inline void setLootItemNoTrade(int lootitemnotrade) {
		lootItemNoTrade = lootitemnotrade;
	}

	inline void setLootItemRace(string lootitemrace) {
		lootItemRace = lootitemrace;
	}

	inline void setLootItemDeveloperNote(string lootitemdevelopernote) {
		lootItemDeveloperNote = lootitemdevelopernote;
	}

	inline void setLootItemTypeHex(string lootitemtypehex) {
		lootItemTypeHex = lootitemtypehex;
	}

	inline void setLootItemPath(string lootitempath) {
		lootItemPath = lootitempath;
	}

	inline void setLootItemString(string lootitemstring) {
		lootItemString = lootitemstring;
	}

	//getters

	inline int getLootItemGroup() {
		return lootItemGroup;
	}

	inline string getLootItemName() {
		return lootItemName;
	}

	inline uint64 getLootItemTemplateCRC() {
		return lootItemTemplateCRC;
	}

	inline uint64 getLootItemTemplateType() {
		return lootItemTemplateType;
	}

	inline string getLootItemTemplateName() {
		return lootItemTemplateName;
	}

	inline string getLootItemAttributes() {
		return lootItemAttributes;
	}

	inline string getLootItemAppearance() {
		return lootItemAppearance;
	}

	inline int getLootItemLevel() {
		return lootItemLevel;
	}

	inline int getLootItemChance() {
		return lootItemChance;
	}

	inline string getLootItemLastDropStamp() {
		return lootItemLastDropStamp;
	}

	inline string getLootItemDontDropBefore() {
		return lootItemDontDropBefore;
	}

	inline int getLootItemUnique() {
		return lootItemUnique;
	}

	inline int getLootItemNoTrade() {
		return lootItemNoTrade;
	}

	inline string getLootItemRace() {
		return lootItemRace;
	}

	inline string getLootItemDeveloperNote() {
		return lootItemDeveloperNote;
	}

	inline string getLootItemTypeHex() {
		return lootItemTypeHex;
	}

	inline string getLootItemPath() {
		return lootItemPath;
	}

	inline string getLootItemString() {
		return lootItemString;
	}


};

#endif /*LOOTTABLETEMPLATE_H_*/
