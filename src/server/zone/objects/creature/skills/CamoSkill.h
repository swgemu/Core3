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

#ifndef CAMOSKILL_H_
#define CAMOSKILL_H_

#include "Skill.h"

class CamoSkill : public Skill {
public:
	/**
	 * Static Fields:
	 * The camo type to distinguish between mask scent and conceal
	 * including the planets
	 */
	static const int CORELLIA = 0;
	static const int DANTOOINE = 1;
	static const int DATHOMIR = 2;
	static const int ENDOR = 3;
	static const int LOK = 4;
	static const int NABOO = 5;
	static const int RORI = 6;
	static const int TALUS = 7;
	static const int TATOOINE = 8;
	static const int YAVIN = 9;
	static const int MASKSCENT = 10;
	static const int NONE = 11;

protected:
	/*
	 * Duration of the skill
	 */
	float duration;

	/*
	 * Type of the skill : mask scent or conceal = planet
	 */
	int camoType;

public:
	/*
	 * The constructor
	 * \param name The skill name
	 * \param cat The skill category : self or target.
	 * \param serv The ZoneProcessServerImplementation.
	 */
	CamoSkill(const String& name,const int cat, ZoneProcessServerImplementation* serv) : Skill(name, CAMO, cat, serv) {
		duration = 0;
		camoType = NONE;
		category = 0;
	}

	/*
	 * Activates the self skill (mask scent)
	 *  \param creature The creature, that activates the skill.
	 *  \param modifier The modifiers, not used.
	 */
	virtual void doSkill(CreatureObject* creature, String& modifier) {

	}

	/*
	 * Activates the target skill (conceal).
	 * \param creature The creature, that activates the skill.
	 * \param target The target to conceal, if null the self.
	 * \param modifier The modifiers, not used.
	 */
	virtual void doSkill(CreatureObject* creature,SceneObject* target, String& modifier) {

	}

	/*
	 * Does the animation.
	 * \param creature The creature The creature, that activates the skill.
	 */
	void doAnimations(CreatureObject* creature) {
	}

	/*
	 * Deactivates the conceal skill.
	 * \param creature The creature, that is unconcealed.
	 */
	virtual void finish(CreatureObject* creature) {
	}

	/*
	 * Returns the speed of the skill.
	 * \return creature The creature The creature, that activates the skill.
	 */
	float calculateSpeed(CreatureObject* creature) {
			return 0;
	}

	/*
	 * Checks if the skill can be used.
	 * \param creature The creature, that is checked.
	 * \return Returns false if not usefull else true.
	 */
	virtual bool isUseful(CreatureObject* creature) {
		return false;
	}

	/*
	 * Calculates the costs of the skill.
	 * \param creature The creature, that is checked.
	 * \return Returns if costs are applied.
	 */
	virtual bool calculateCost(CreatureObject* creature) {
		return true;
	}

	/*
	 * Sets the camo type.
	 * \param camo The camo type.
	 */
	virtual void setCamoType(int camo) {
		camoType = camo;
	}

	/*
	 * Sets the duration.
	 * 	\param dur : The duration.
	 */
	virtual void setDuration(float dur) {
		duration = dur;
	}


	/*
	 * Returns the duration.
	 * \return int The duration.
	 */
	inline float getDuration() {
		return duration;
	}

	/*
	 * Returns the camo type.
	 * \return int The camo type.
	 */
	inline int getCamoType() {
		return camoType;
	}
};

#endif
