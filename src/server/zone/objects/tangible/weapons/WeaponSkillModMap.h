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

#ifndef WEAPONSKILLMODMAP_H_
#define WEAPONSKILLMODMAP_H_

#include "engine/engine.h"

class Dot {
protected:
	/*
	 * Type is the type of dot: BLEEDING, DISEASED, ONFIRE, POISONED
	 */
	int type;
	/*
	 * Attribute is the stat that the dot affects.
	 */
	int attribute;

	//obvious
	int strength;
	/*
	 * duration of the applied dot in seconds
	 */
	int duration;
	/*
	 * how often the dot is applied to the victim
	 */
	int potency;
	/*
	 * number of remaining uses on this dot
	 */
	int uses;

public:
	/*
	 * Constructor
	 */
	Dot() {
		type = 0;
		attribute = 0;
		strength = 0;
		duration = 0;
		potency = 0;
		uses = 0;
	}

	inline bool hasStats() {//attribute can be 0
		return (type > 0 || strength > 0 || duration > 0 || potency > 0);
	}

	void setType(int t) {
		type = t;
	}

	void setAttribute(int a) {
		attribute = a;
	}

	void setStrength(int s) {
		strength = s;
	}

	void setDuration(int d) {
		duration = d;
	}

	void setPotency(int p) {
		potency = p;
	}

	void setUses(int u) {
		uses = u;
	}

	int getType() {
		return type;
	}

	int getAttribute() {
		return attribute;
	}

	int getStrength() {
		return strength;
	}

	int getDuration() {
		return duration;
	}

	int getPotency() {
		return potency;
	}

	int getUses() {
		return uses;
	}
};
/*
 * WeaponSkillModMap is a class that represents all the mods associated with
 * a weapon
 */
class WeaponSkillModMap {
protected:
	/*
	 * innateSkillModMap is a list of UNIQUE innate mods of skills. skill is stored in an int,
	 * then converted to the string in TangibleObjectImplementation::generateSkillMods()
	 */
	VectorMap<int, int> innateSkillModMap;
	int maxValue;
	/*
	 * dotVector is a list of dots in order of when they were added to the weapon
	 */
	Vector<Dot*> dotVector;
	int maxDots;

public:
	/*
	 * Constructor
	 */
	WeaponSkillModMap() {
		maxValue = 1000000;
		maxDots = 100000;
	}

	~WeaponSkillModMap() {
		while(dotVector.size() > 0)
			delete dotVector.get(0);
	}

/*	void insertStatMods(AttributeListMessage* alm) {

		String statname, key;
		int value;

		for (int i = 0; i < activeSkillModMap.size(); ++i) {
			key = activeSkillModMap.elementAt(i)->getKey();
			statname = "cat_skill_mod_bonus.@stat_n:" + key;
			value = activeSkillModMap.get(key);

			alm->insertAttribute(statname, value);
		}
	}*/

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
					innateSkillModMap.put(Integer::valueOf(key), value);
				}
			}
		}
	}

	void makeDotMap(String attribute) {

		String temp, key, property;
		int value;
		Dot* dot;
		dotVector.removeAll();

		StringTokenizer maintokenizer(attribute);
		maintokenizer.setDelimeter(";");

		while(maintokenizer.hasMoreTokens()) {
			maintokenizer.getStringToken(temp);

			StringTokenizer propertytokenizer(temp);
			propertytokenizer.setDelimeter(",");

			dot = new Dot();

			while (propertytokenizer.hasMoreTokens()) {

				propertytokenizer.getStringToken(property);

				StringTokenizer keyvaluetokenizer(property);
				keyvaluetokenizer.setDelimeter("=");

				if (keyvaluetokenizer.hasMoreTokens()) {
					keyvaluetokenizer.getStringToken(key);
					if (keyvaluetokenizer.hasMoreTokens()) {
						value = keyvaluetokenizer.getIntToken();
						if (key == "type")
							dot->setType(value);
						else if (key == "attribute")
							dot->setAttribute(value);
						else if (key == "strength")
							dot->setStrength(value);
						else if (key == "duration")
							dot->setDuration(value);
						else if (key == "potency")
							dot->setPotency(value);
						else if (key == "uses")
							dot->setUses(value);
					}
				}
			}
			if (dot->hasStats())
				dotVector.add(dot);
		}
	}

	String getDotString() {

		int key;
		Dot* data;
		StringBuffer socketBuffer;

		for (int i = 0; i < dotVector.size(); ++i) {
			data = dotVector.get(i);
			//socketBuffer << i << "=";

			int type = data->getType();
			socketBuffer << "type=" << type << ",";

			int attribute = data->getAttribute();
			socketBuffer << "attribute=" << attribute << ",";

			int strength = data->getStrength();
			socketBuffer << "strength=" << strength << ",";

			int duration = data->getDuration();
			socketBuffer << "duration=" << duration << ",";

			int potency = data->getPotency();
			socketBuffer << "potency=" << potency << ",";

			int uses = data->getUses();
			socketBuffer << "uses=" << uses << ",";

			socketBuffer << ";";
		}
		return socketBuffer.toString();
	}

	String getSkillModString() {

		StringBuffer skills;

		for (int i = 0; i < innateSkillModMap.size(); ++i) {
			skills << innateSkillModMap.elementAt(i)->getKey() << "="
					<< innateSkillModMap.elementAt(i)->getValue() << ";";
		}

		return skills.toString();
	}

	//void putSkillMod(String key, int value) {
	//	innateSkillModMap.put(key, value);
	//}

	void putSkillMod(int key, int value) {
		if (value > maxValue)
			value = maxValue;
		if (!innateSkillModMap.contains(key))
			innateSkillModMap.put(key, value);
	}

	//void removeSkillMod(String key) {
	//	innateSkillModMap.drop(key);
	//}

	void removeSkillMod(int key) {
		innateSkillModMap.drop(key);
	}

	//void removeSkillMod(int index) {
	//	innateSkillModMap.removeElementAt(index);
	//}

	void addDot(Dot* dot) {
		if (getDotCount() < maxDots)
			dotVector.add(dot);
	}

	/*String& getActiveSkillModKey(int i) {
		return activeSkillModIndex.get(i);
	}

	int getActiveSkillModValue(String key) {
		return activeSkillModMap.get(key);
	}

	bool contains(String key) {
		return activeSkillModMap.contains(key);
	}*/

	int getDotCount() {
		return dotVector.size();
	}

	/*String getKey(int i) {
		return activeSkillModMap.elementAt(i)->getKey();
	}

	int getActiveSkillModCount() {
		return activeSkillModIndex.size();
	}*/
};

#endif /*WEAPONSKILLMODMAP_H_*/
