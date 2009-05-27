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

#ifndef MODIFIEREFFECT_H_
#define MODIFIEREFFECT_H_

#include "engine/engine.h"
#include "../CreatureObject.h"
#include "../events/ModifierExpirationEvent.h"

class ModifierEffect : public VectorMap<String, float>, public DistributedObject {
protected:
	ModifierExpirationEvent* event;

	String effectName;
	float duration;
	uint8 effectType;

	bool stackable;

public:
	ModifierEffect(const String& name, float dur, uint8 type = 0) : VectorMap<String, float>(), DistributedObject() {
		//TODO: Set Insert plan
		effectName = name;
		duration = dur;
		effectType = type;
		stackable = true;

		event = NULL;
	}

	virtual void applyEffect(CreatureObject* creature);
	virtual void removeEffect(CreatureObject* creature);

	virtual float getModifier(const String& modname) {
		if (contains(modname))
			return get(modname);

		return 0;
	}

	virtual bool hasModifier(const String& modname) {
		return contains(modname);
	}

	//Setters
	inline void setEffectName(const String& name) {
		effectName = name;
	}

	inline void setDuration(float dur) {
		duration = dur;
	}

	inline void setStackable(bool value) {
		stackable = value;
	}

	//Getters
	inline String& getEffectName() {
		return effectName;
	}

	inline uint32 getEffectCRC() {
		return effectName.hashCode();
	}

	inline float getDuration() {
		return duration;
	}

	inline bool isStackable() {
		return stackable;
	}
};

#endif /* MODIFIEREFFECT_H_ */
