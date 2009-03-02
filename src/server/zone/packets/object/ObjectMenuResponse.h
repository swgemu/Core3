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

#ifndef OBJECTMENURESPONSE_H_
#define OBJECTMENURESPONSE_H_

#include "engine/engine.h"

#include "ObjectControllerMessage.h"
#include "../../objects/player/Player.h"

#include "RadialMenuItem.h"

class ObjectMenuResponse : public ObjectControllerMessage {
	int listSize;
	uint8 count;

	Vector<RadialMenuParent*> radials;

	/**
	 * This method is used to write the radial objects to the packet.
	 * \param parentid The parentid of the radial option.
	 * \param radialid The radial id to be handled by the client and radialmanager.
	 * \param callback The callback type for the radial.
	 * \param text The text to label the radial choice.
	 */
	void addRadialOption(uint8 parentid, uint8 radialid, uint8 callback, const UnicodeString& text = "") {
		insertByte((uint8) ++listSize);
		insertByte(parentid);
		insertByte(radialid);
		insertByte(callback);
		insertUnicode(text);
	}

public:
	ObjectMenuResponse(Player* player, uint64 target, uint8 counter)
	   		: ObjectControllerMessage(player->getObjectID(), 0x0B, 0x147) {
		insertLong(target);
		insertLong(player->getObjectID());

		insertInt(0); // size

		listSize = 0;
		count = counter;
	}

	~ObjectMenuResponse() {
		for (int i = 0; i < radials.size(); i++)
			delete radials.get(i);

		radials.removeAll();
	}

	/**
	 * Adds a radial item to the radials Vector.
	 * These radials will be appended to the packet when finish() is called.
	 * \param menuitem The RadialMenuParent to add.
	 */
	void addRadialParent(RadialMenuParent* menuitem) {
		radials.add(menuitem);

		//We add the parents immediately upon being added to the list.
		addRadialOption(0, menuitem->getRadialID(), menuitem->getCallback(), menuitem->getText());
	}

	/**
	 * Adds a radial menu parent object to the ObjectMenuResponse message.
	 * \param radialid The radial id to be handled when the radial option is clicked.
	 * \param callback The callback type to be initiated when the radial option is clicked.
	 * \param text The text to display on the radial menu.
	 */
	void addRadialParent(uint8 radialid, uint8 callback, const UnicodeString& text = "") {
		addRadialParent(new RadialMenuParent(radialid, callback, text));
	}

	void finish() {
		//Loop through the radials and add their children now.
		for (int i = 0; i < radials.size(); i++) {
			RadialMenuParent* rmp = radials.get(i);
			for (int j = 0; j < rmp->children.size(); j++) {
				RadialMenuItem* rmi = rmp->children.get(j);
				addRadialOption(i + 1, rmi->getRadialID(), rmi->getCallback(), rmi->getText());
			}
		}

		insertInt(46, listSize);
		insertByte(count);
	}

	inline void setCounter(uint8 counter) {
		count = counter;
	}
};

#endif

