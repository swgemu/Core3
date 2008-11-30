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
	String lootItemName;
	uint64 lootItemTemplateCRC;
	uint64 lootItemTemplateType;
	String lootItemTemplateName;
	String lootItemAttributes;
	String lootItemAppearance;
	int lootItemLevel;
	int lootItemChance;
	String lootItemLastDropStamp;
	String lootItemDontDropBefore;
	int lootItemUnique;
	int lootItemNoTrade;
	String lootItemRace;
	String lootItemDeveloperNote;
	String lootItemType;
	String lootItemTypeHex;
	String lootItemPath;
	String lootItemString;
	uint16 lootItemMask;

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
		lootItemMask = 0xFFFF;

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

	inline void setLootItemName(String lootitemname) {
		lootItemName = lootitemname;
	}

	inline void setLootItemTemplateCRC(uint64 lootitemtemplatecrc) {
		lootItemTemplateCRC = lootitemtemplatecrc;
	}

	inline void setLootItemTemplateType(uint64 lootitemtemplatetype) {
		lootItemTemplateType = lootitemtemplatetype;
	}

	inline void setLootItemTemplateName(String lootitemtemplatename) {
		lootItemTemplateName = lootitemtemplatename;
	}

	inline void setLootItemAttributes(String lootitemattributes) {
		lootItemAttributes = lootitemattributes;
	}

	inline void setLootItemAppearance(String lootitemappearance) {
		lootItemAppearance = lootitemappearance;
	}

	inline void setLootItemLevel(int lootitemlevel) {
		lootItemLevel = lootitemlevel;
	}

	inline void setLootItemChance(int lootitemchance) {
		lootItemChance = lootitemchance;
	}

	inline void setLootItemLastDropStamp(String lootitemlastdropstamp) {
		lootItemLastDropStamp = lootitemlastdropstamp;
	}

	inline void setLootItemDontDropBefore(String lootitemdontdropbefore) {
		lootItemDontDropBefore = lootitemdontdropbefore;
	}

	inline void setLootItemUnique(int lootitemunique) {
		lootItemUnique = lootitemunique;
	}

	inline void setLootItemNoTrade(int lootitemnotrade) {
		lootItemNoTrade = lootitemnotrade;
	}

	inline void setLootItemRace(String lootitemrace) {
		lootItemRace = lootitemrace;
	}

	inline void setLootItemDeveloperNote(String lootitemdevelopernote) {
		lootItemDeveloperNote = lootitemdevelopernote;
	}

	inline void setLootItemTypeHex(String lootitemtypehex) {
		lootItemTypeHex = lootitemtypehex;
	}

	inline void setLootItemPath(String lootitempath) {
		lootItemPath = lootitempath;
	}

	inline void setLootItemString(String lootitemString) {
		lootItemString = lootitemString;
	}

	inline void setLootItemMask(uint16 lootitemmask) {
		lootItemMask = lootitemmask;
	}

	//getters

	inline int getLootItemGroup() {
		return lootItemGroup;
	}

	inline String getLootItemName() {
		return lootItemName;
	}

	inline uint64 getLootItemTemplateCRC() {
		return lootItemTemplateCRC;
	}

	inline uint64 getLootItemTemplateType() {
		return lootItemTemplateType;
	}

	inline String getLootItemTemplateName() {
		return lootItemTemplateName;
	}

	inline String getLootItemAttributes() {
		return lootItemAttributes;
	}

	inline String getLootItemAppearance() {
		return lootItemAppearance;
	}

	inline int getLootItemLevel() {
		return lootItemLevel;
	}

	inline int getLootItemChance() {
		return lootItemChance;
	}

	inline String getLootItemLastDropStamp() {
		return lootItemLastDropStamp;
	}

	inline String getLootItemDontDropBefore() {
		return lootItemDontDropBefore;
	}

	inline int getLootItemUnique() {
		return lootItemUnique;
	}

	inline int getLootItemNoTrade() {
		return lootItemNoTrade;
	}

	inline String getLootItemRace() {
		return lootItemRace;
	}

	inline String getLootItemDeveloperNote() {
		return lootItemDeveloperNote;
	}

	inline String getLootItemTypeHex() {
		return lootItemTypeHex;
	}

	inline String getLootItemPath() {
		return lootItemPath;
	}

	inline String getLootItemString() {
		return lootItemString;
	}

	inline uint16 getLootItemMask() {
		return lootItemMask;
	}

};

#endif /*LOOTTABLETEMPLATE_H_*/
