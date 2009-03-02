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

#ifndef RADIALMENUITEM_H_
#define RADIALMENUITEM_H_

#include "engine/engine.h"


/**
 * Please see Radial in the wiki for a list of client side radial id's.
 * Also, please note that radial id's are handled in RadialManager.cpp and most have already been defined.
 * Try to find one suitable to your purpose, or piggy back the SERVER_MENUX ones which
 * Call an objects associated virtual method.
 *
 * Callback Types known:
 *  0x01 = Default
 *  0x03 = Callback
 */

class RadialMenuItem {
	uint8 radialID;
	uint8 callback;
	UnicodeString text;

public:
	RadialMenuItem(uint8 radialid, uint8 callback, const UnicodeString& text = "") {
		setRadialID(radialid);
		setCallback(callback);
		setText(text);
	}

	~RadialMenuItem() {

	}

	//Setters
	inline void setRadialID(uint8 radialid) {
		radialID = radialid;
	}

	inline void setCallback(uint8 cback) {
		callback = cback;
	}

	inline void setText(const UnicodeString& txt) {
		text = txt;
	}

	//Getters
	inline uint8 getRadialID() {
		return radialID;
	}

	inline uint8 getCallback() {
		return callback;
	}

	inline UnicodeString& getText() {
		return text;
	}
};

class RadialMenuParent : public RadialMenuItem {
	Vector<RadialMenuItem*> children;

public:
	RadialMenuParent(uint8 radialid, uint8 callback, const UnicodeString& text = "") :
		RadialMenuItem(radialid, callback, text) {
	}

	~RadialMenuParent() {
		for (int i = 0; i < children.size(); i++)
			delete children.get(i);

		children.removeAll();
	}

	/**
	 * This method adds a sub menu radial item
	 * \param menuitem The tadial menu item to add.
	 */
	inline void addRadialMenuItem(RadialMenuItem* menuitem) {
		children.add(menuitem);
	}

	/**
	 * This method adds a sub menu radial item
	 * \param radialid What radial id will the new radial menu item return.
	 * \param callback What sort of callback is produced by this radial menu item.
	 * \param text The text of the radial item. Preferrably the stf string.
	 */
	inline void addRadialMenuItem(uint8 radialid, uint8 callback, const UnicodeString& text = "") {
		RadialMenuItem* menuitem = new RadialMenuItem(radialid, callback, text);
		children.add(menuitem);
	}

	/**
	 * Removes a child radial menu item from the submenu.
	 * \param menuitem RadialMenuItem pointer to remove from the list.
	 */
	inline void removeRadialMenuItem(RadialMenuItem* menuitem) {
		int index = getRadialMenuItemIndex(menuitem);

		if (index > -1)
			children.remove(index);
	}

	///Returns if this radial parent has any children associated with it.
	inline bool hasChildren() {
		return children.size() > 0;
	}

	///Returns the index of the menuitem if it exists, or -1 if it doesn't
	inline int getRadialMenuItemIndex(RadialMenuItem* menuitem) {
		for (int i = 0; i < children.size(); i++) {
			if (children.get(i) == menuitem)
				return i;
		}

		return -1;
	}

	friend class ObjectMenuResponse;
};

#endif /* RADIALMENUITEM_H_ */
