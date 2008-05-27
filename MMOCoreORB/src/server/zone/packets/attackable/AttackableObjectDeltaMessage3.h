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

#ifndef ATTACKABLEOBJECTDELTAMESSAGE3_H_
#define ATTACKABLEOBJECTDELTAMESSAGE3_H_

#include "../../packets/DeltaMessage.h"

#include "../../objects/attackable/AttackableObject.h"

class AttackableObjectDeltaMessage3 : public DeltaMessage {
	AttackableObject* tano;
	
public:
	AttackableObjectDeltaMessage3(AttackableObject* ta)
			: DeltaMessage(ta->getObjectID(), 0x54414E4F, 3) {
		tano = ta;
	}
	
	void updateCustomizationString() {
		string app;
		tano->getCustomizationString(app);
		addAsciiUpdate(4, app);
	}
	
	void updateName(string name) {
		addUnicodeUpdate(2, name);
	}
	
	void updateConditionDamage() {
		addIntUpdate(8, tano->getConditionDamage());
	}
	
	void updateMaxCondition() {
		addIntUpdate(9, tano->getMaxCondition());
	}
	
	void update06Operand(uint32 value) {
		addIntUpdate(0x06, value);
	}

	/*
	void updateState() {
		addLongUpdate(0x10, creo->getStateBitmask());
	}
	*/
};

#endif /*ATTACKABLEOBJECTDELTAMESSAGE3_H_*/
