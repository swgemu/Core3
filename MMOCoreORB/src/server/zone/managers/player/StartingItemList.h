/*
 * StartingItemsMap.h
 *
 *  Created on: 26/02/2010
 *      Author: victor
 */

#ifndef STARTINGITEMSLIST_H_
#define STARTINGITEMSLIST_H_

#include "engine/engine.h"

#include "server/zone/managers/templates/TemplateManager.h"

class StartingItem : public Object {
	uint32 templateCRC;
	bool equipped;

public:
	StartingItem() {
		templateCRC = 0;
		equipped = false;
	}

	StartingItem(const StartingItem& l) : Object() {
		templateCRC = l.templateCRC;
		equipped = l.equipped;
	}

	StartingItem& operator=(const StartingItem& l) {
		templateCRC = l.templateCRC;
		equipped = l.equipped;

		return *this;
	}

	inline uint32 getTemplateCRC() {
		return templateCRC;
	}

	inline bool createEquipped() {
		return equipped;
	}

	friend class StartingItemList;
};

class StartingSkill {
	Vector<StartingItem>* all;
	Vector<StartingItem>* humanoidMale;
	Vector<StartingItem>* humanoidFemale;
	Vector<StartingItem>* trandoMale;
	Vector<StartingItem>* trandoFemale;
	Vector<StartingItem>* ithoMale;
	Vector<StartingItem>* ithoFemale;
	Vector<StartingItem>* wookMale;
	Vector<StartingItem>* wookFemale;

public:
	StartingSkill() {
		all = new Vector<StartingItem>();
		humanoidMale = new Vector<StartingItem>();
		humanoidFemale = new Vector<StartingItem>();
		trandoMale = new Vector<StartingItem>();
		trandoFemale = new Vector<StartingItem>();
		ithoMale = new Vector<StartingItem>();
		ithoFemale = new Vector<StartingItem>();
		wookMale = new Vector<StartingItem>();
		wookFemale = new Vector<StartingItem>();
	}

	~StartingSkill() {
		delete all;
		all = NULL;

		delete humanoidMale;
		humanoidMale = NULL;

		delete humanoidFemale;
		humanoidFemale = NULL;

		delete trandoMale;
		trandoMale = NULL;

		delete trandoFemale;
		trandoFemale = NULL;

		delete ithoMale;
		ithoMale = NULL;

		delete ithoFemale;
		ithoFemale = NULL;

		delete wookMale;
		wookMale = NULL;

		delete wookFemale;
		wookFemale = NULL;
	}

	Vector<StartingItem>* get(const String& species, const String& sex) {
		if (species.compareTo("all") == 0) {
			return all;
		} else if (species.compareTo("ithorian") == 0) {
			if (sex.compareTo("male") == 0) {
				return ithoMale;
			} else {
				return ithoFemale;
			}
		} else if (species.compareTo("trandoshan") == 0) {
			if (sex.compareTo("male") == 0) {
				return trandoMale;
			} else {
				return trandoFemale;
			}
		} else if (species.compareTo("wookiee") == 0) {
			if (sex.compareTo("male") == 0) {
				return wookMale;
			} else {
				return wookFemale;
			}
		} else {
			if (sex.compareTo("male") == 0) {
				return humanoidMale;
			} else {
				return humanoidFemale;
			}
		}
	}
};

class StartingItemSkillSet : public HashTable<String, StartingSkill *> {
public:
	StartingItemSkillSet() {
	}

	int hash(const String& str) {
		return str.hashCode();
	}
};

class StartingItemList : public Lua, public Singleton<StartingItemList> {
	StartingItemSkillSet* professions;

public:
	StartingItemList() {
		professions = new StartingItemSkillSet();
		init();

		setLoggingName("StartingItemList");
		Lua::init();
		lua_register(getLuaState(), "AddStartingItemToServer", addStartingItemToServer);
	}

	~StartingItemList() {
		HashTableIterator<String, StartingSkill*> iterator(professions);

		iterator.resetIterator();

		while (iterator.hasNext()) {
			StartingSkill* prof = iterator.next();

			delete prof;
		}

		delete professions;
		professions = NULL;
	}

	void loadItems() {
		runFile("scripts/managers/player_manager.lua", getLuaState());
	}

	static int addStartingItemToServer(lua_State* l) {
		String species, sex, profession;
		try {
			LuaObject itemwrapper(l);

			species = itemwrapper.getStringField("species");
			sex = itemwrapper.getStringField("sex");
			profession = itemwrapper.getStringField("profession");

			LuaObject itemconfig(itemwrapper.getObjectField("item"));

			StartingItem item;
			item.equipped = itemconfig.getByteField("equipped");

			String templ = itemconfig.getStringField("template");

			try {
				item.templateCRC = templ.hashCode();
			} catch (ArrayIndexOutOfBoundsException& e) {
				StringBuffer msg;
				msg << "trying to add a default player item with invalid template:" << templ;
				StartingItemList::instance()->error(msg.toString());

				return 0;
			}

			if (!TemplateManager::instance()->existsTemplate(item.templateCRC)) {
				StringBuffer msg;
				msg << "trying to add a default player item with invalid template:" << templ;
				StartingItemList::instance()->error(msg.toString());

				return 0;
			}

			StartingItemList::instance()->addItemToSkill(profession, species, sex, item);

		} catch (Exception& e) {
			StringBuffer msg;
			msg << "error adding item to profession list" << endl;
			msg << "profession: " << profession << " species: " << species << " sex " << sex;
			StartingItemList::instance()->error(msg.toString());
			StartingItemList::instance()->error(e.getMessage());
		}

		return 0;
	}

	void addItemToSkill(const String& profession, const String& species, const String& sex, const StartingItem& item) {
		professions->get(profession)->get(species, sex)->add(item);
	}

	Vector<StartingItem>* getSkillItems(const String& profession, const String& species, const String& sex) {
		return (professions->get(profession)->get(species, sex));
	}

	void init() {
		professions->put("general", new StartingSkill());
		professions->put("artisan", new StartingSkill());
		professions->put("brawler", new StartingSkill());
		professions->put("entertainer", new StartingSkill());
		professions->put("marksman", new StartingSkill());
		professions->put("medic", new StartingSkill());
		professions->put("scout", new StartingSkill());
	}
};


#endif /* STARTINGITEMSMAP_H_ */
