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

#ifndef WEARABLESKILLMODMAP_H_
#define WEARABLESKILLMODMAP_H_

#include "engine/engine.h"
#include "server/zone/packets/scene/AttributeListMessage.h"

class AttachmentEntry : public Serializable {
protected:
	/*
	 * skillModifiers is an ordered index of skill mods in the entry
	 */
	Vector<String> skillModifiers;
	Vector<int> skillModValues;
	/*
	 * skillModifierValues is a list of the skill mod values
	 */
	VectorMap<String, int> skillModifierValues;

public:
	/*
	 * Constructor
	 */
	AttachmentEntry() : Serializable() {
		addSerializableVariable("skillModifiers", &skillModifiers);
		addSerializableVariable("skillModifierValues", &skillModifierValues);
	}

	AttachmentEntry(const AttachmentEntry& entry) : Object(), Serializable() {
		skillModifiers = entry.skillModifiers;
		skillModifierValues = entry.skillModifierValues;

		addSerializableVariable("skillModifiers", &skillModifiers);
		addSerializableVariable("skillModifierValues", &skillModifierValues);
	}

	AttachmentEntry& operator=(const AttachmentEntry& entry) {
		if (this == &entry)
			return *this;

		skillModifiers = entry.skillModifiers;
		skillModifierValues = entry.skillModifierValues;

		return *this;
	}


	void add(const String& key, int value) {
		skillModifiers.add(key);
		skillModifierValues.put(key, value);
	}

	void remove(const String& key) {
		skillModifiers.removeElement(key);
		skillModifierValues.drop(key);
	}

	void remove(int key) {
		skillModifiers.remove(key);
		skillModifierValues.removeElementAt(key);
	}

	String getKey(int i) {
		return skillModifiers.get(i);
	}

	int get(String key) {
		return skillModifierValues.get(key);
	}

	int size() {
		return skillModifiers.size();
	}

	String getHighestSkillMod() {
		String highestSkillMod;
		int highestValue = -26;

		for (int i = 0; i < skillModifierValues.size(); ++i) {
			int value = skillModifierValues.elementAt(i).getValue();

			if (highestValue < value) {
				highestValue = value;
				highestSkillMod = skillModifierValues.elementAt(i).getKey();
			}

		}

		return highestSkillMod;
	}

};

/*
 * WearableSkillModMap is a class that represents all the mods associated with
 * the wearable item
 */
class WearableSkillModMap : public Serializable {
protected:
	/*
	 * innateSkillModMap is a list of innate mods from crafting / BE Additives
	 */
	VectorMap<String, int> innateSkillModMap;
	/*
	 * attachmentVector is a list of Clothing / Armor attachments in order of how they were added to the item
	 */
	Vector<AttachmentEntry> attachmentVector;
	int maxAttachments;
	/*
	 * activeSkillMods is a list of active skill mods based on innate mods and attachment application rules
	 */
	VectorMap<String, int> activeSkillModMap;
	SortedVector<String> activeSkillModIndex;

public:
	/*
	 * Constructor
	 */
	WearableSkillModMap() {
		maxAttachments = 0;

		activeSkillModIndex.setNoDuplicateInsertPlan();

		addSerializableVariables();
	}

	WearableSkillModMap(const WearableSkillModMap& sk) : Object(), Serializable() {
		innateSkillModMap = sk.innateSkillModMap;
		attachmentVector = sk.attachmentVector;
		maxAttachments = sk.maxAttachments;
		activeSkillModMap = sk.activeSkillModMap;
		activeSkillModIndex = sk.activeSkillModIndex;

		activeSkillModIndex.setNoDuplicateInsertPlan();

		addSerializableVariables();
	}

	void addSerializableVariables() {
		addSerializableVariable("innateSkillModMap", &innateSkillModMap);
		addSerializableVariable("attachmentVector", &attachmentVector);
		addSerializableVariable("activeSkillModMap", &activeSkillModMap);
		addSerializableVariable("activeSkillModIndex", &activeSkillModIndex);
	}

	WearableSkillModMap& operator=(const WearableSkillModMap& sk) {
		if (this == &sk)
			return *this;

		innateSkillModMap = sk.innateSkillModMap;
		attachmentVector = sk.attachmentVector;
		maxAttachments = sk.maxAttachments;
		activeSkillModMap = sk.activeSkillModMap;
		activeSkillModIndex = sk.activeSkillModIndex;

		return *this;
	}

	~WearableSkillModMap() {
		/*while (attachmentVector.size() > 0) {
			AttachmentEntry* entry = attachmentVector.remove(0);
			delete entry;
		}*/
	}

	void insertStatMods(AttributeListMessage* alm) {

		String statname, key;
		int value;

		for (int i = 0; i < activeSkillModMap.size(); ++i) {
			key = activeSkillModMap.elementAt(i).getKey();
			statname = "cat_skill_mod_bonus.@stat_n:" + key;
			value = activeSkillModMap.get(key);

			if (value > 0)
				alm->insertAttribute(statname, value);

		}
	}

	void makeSkillModMap(String attribute) {

		String temp, key;
		int value;
		innateSkillModMap.removeAll();

		StringTokenizer maintokenizer(attribute);
		maintokenizer.setDelimeter(";");

		while(maintokenizer.hasMoreTokens()) {
			maintokenizer.getStringToken(temp);

			StringTokenizer propertytokenizer(temp);
			propertytokenizer.setDelimeter("=");

			if (propertytokenizer.hasMoreTokens()) {

				if (propertytokenizer.hasMoreTokens()) {
					propertytokenizer.getStringToken(key);
					value = propertytokenizer.getIntToken();
					innateSkillModMap.put(key, value);
				}
			}
		}
	}

	void makeAttachmentMap(String attribute) {

		String temp, key, property;
		int value;
		AttachmentEntry entry;
		attachmentVector.removeAll();

		StringTokenizer maintokenizer(attribute);
		maintokenizer.setDelimeter(";");

		while(maintokenizer.hasMoreTokens()) {
			maintokenizer.getStringToken(temp);

			StringTokenizer propertytokenizer(temp);
			propertytokenizer.setDelimeter(",");

			//entry = new AttachmentEntry();

			while (propertytokenizer.hasMoreTokens()) {

				propertytokenizer.getStringToken(property);

				StringTokenizer keyvaluetokenizer(property);
				keyvaluetokenizer.setDelimeter("=");

				if (keyvaluetokenizer.hasMoreTokens()) {
					keyvaluetokenizer.getStringToken(key);
					if (keyvaluetokenizer.hasMoreTokens()) {
						value = keyvaluetokenizer.getIntToken();
						entry.add(key, value);
					}
				}
			}
			attachmentVector.add(entry);
		}
	}

	void rebuildActiveSkillModMap() {
		activeSkillModMap.removeAll();
		activeSkillModIndex.removeAll();
		AttachmentEntry* entry;
		int statValue;

		for (int i = 0; i < attachmentVector.size(); ++i) {
			entry = &attachmentVector.get(i);

			if (entry != NULL) {
				String statName = getBestAttachmentSkillMod(entry);

				if (!statName.isEmpty()) {
					statValue = entry->get(statName);

					if (statValue < 0)
						statValue = statValue * -1;

					activeSkillModMap.put(statName, statValue);
					activeSkillModIndex.put(statName);

				} else
					// If a skill mod wasn't actually added. Remove the Attachment from the Vector
					// This can occur if the tape is applied to a wearable that already has a higher value
					attachmentVector.remove(i);
			}
		}
	}

	String getBestAttachmentSkillMod(AttachmentEntry* entry) {
		int lowestValue = -26;
		String highestSkillMod = entry->getHighestSkillMod();
		int highestSkillValue = entry->get(highestSkillMod);

		for (int i = 0; i < entry->size(); ++i) {
			String key = entry->getKey(i);
			int value = entry->get(key);

			if (value > lowestValue) {
				if (!activeSkillModMap.contains(highestSkillMod))
					return highestSkillMod;

				if (!activeSkillModMap.contains(key)) {
					if (key != highestSkillMod) {
						if (highestSkillValue > activeSkillModMap.get(highestSkillMod))
							return highestSkillMod;
						else
							return key;
					}

					return highestSkillMod;

				} else if (value > activeSkillModMap.get(key))
					return key;

			}

		}

		return "";

	}

	String getAttachmentString() {

		int key;
		AttachmentEntry* data;
		StringBuffer socketBuffer;

		for (int i = 0; i < attachmentVector.size(); ++i) {
			data = &attachmentVector.get(i);

			for(int j = 0; j < data->size(); ++j) {
				String key = data->getKey(j);
				int value = data->get(key);

				socketBuffer << key << "=" << value << ",";
			}
			socketBuffer << ";";
		}
		return socketBuffer.toString();
	}

	String getSkillModString() {

		StringBuffer skills;

		for (int i = 0; i < innateSkillModMap.size(); ++i) {
			skills << innateSkillModMap.elementAt(i).getKey() << "="
					<< innateSkillModMap.elementAt(i).getValue() << ";";
		}

		return skills.toString();
	}

	void putSkillMod(String key, int value) {
		innateSkillModMap.put(key, value);
	}

	void removeSkillMod(String key) {
		innateSkillModMap.drop(key);
	}

	void removeSkillMod(int index) {
		innateSkillModMap.removeElementAt(index);
	}

	void addAttachment(const AttachmentEntry& entry) {
		attachmentVector.add(entry);
		rebuildActiveSkillModMap();
	}

	String& getActiveSkillModKey(int i) {
		return activeSkillModMap.elementAt(i).getKey();
	}

	int getActiveSkillModValue(String key) {
		return activeSkillModMap.get(key);
	}

	bool contains(String key) {
		return activeSkillModMap.contains(key);
	}

	int getUsedSocketCount() {
		return attachmentVector.size();
	}

	String getKey(int i) {
		return activeSkillModMap.elementAt(i).getKey();
	}

	int getActiveSkillModCount() {
		return activeSkillModMap.size();
	}
};

#endif /*WEARABLESKILLMODMAP_H_*/
