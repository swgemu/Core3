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
#include "server/zone/objects/scene/SceneObject.h"

#include "RadialMenuItem.h"

namespace server {
namespace zone {
namespace packets {
namespace object {


class ObjectMenuResponse : public ObjectControllerMessage {
	int listSize;
	uint8 count;

	RadialMenuItem* root;

	int indexCount;
	/**
	 * This method is used to write the radial objects to the packet.
	 * \param parentid The parentid of the radial option.
	 * \param radialid The radial id to be handled by the client and radialmanager.
	 * \param callback The callback type for the radial.
	 * \param text The text to label the radial choice.
	 */
	void addRadialOption(RadialMenuItem* item) {
		insertByte(item->getItemIndex());
		insertByte(item->getParentIndex());
		insertByte(item->getRadialID());
		insertByte(item->getCallback());
		insertUnicode(item->getText());

		/*System::out << "inserting item idx:" << item->getItemIndex() << " parent: " << item->getParentIndex()
					<< " radialid: " << item->getRadialID() << "\n";*/

		++listSize;
	}

public:
	ObjectMenuResponse(SceneObject* player, uint64 target, uint8 counter)
	   		: ObjectControllerMessage(player->getObjectID(), 0x0B, 0x147) {
		insertLong(target);
		insertLong(player->getObjectID());

		insertInt(0); // size

		listSize = 0;
		count = counter;

		indexCount = 0;

		root = new RadialMenuItem();
	}

	~ObjectMenuResponse() {
		delete root;
		root = NULL;
	}

	RadialMenuItem* getRadialItem(int index) {
		if (index == 0)
			return root;
		else
			return root->getItem(index);
	}

	RadialMenuItem* getRadialItemByRadialID(uint8 id) {
		if (id == root->getRadialID())
			return root;
		else
			return root->getItemByRadialID(id);
	}

	void addRadialMenuItem(uint8 parentid, uint8 radialid, uint8 callback, const UnicodeString& text = "") {
		RadialMenuItem* parent = getRadialItem(parentid);

		if (parent == NULL) {
			System::out << "error parent radial menu item null" << "\n";
			throw Exception("null parent radial menu specified");
		}

		parent->addRadialMenuItem(++indexCount, radialid, callback, text);
	}

	/**
	 * Adds an object menu item to the specified parent radial id, not parent index with callback
	 */
	void addRadialMenuItemToRadialID(uint8 parentRadialID, uint8 newRadialID, uint8 callback, const UnicodeString& text = "") {
		RadialMenuItem* parent = getRadialItemByRadialID(parentRadialID);

		if (parent == NULL) {
			System::out << "error parent radial id menu item null" << "\n";
			throw Exception("error parent radial id menu item null");
		}

		parent->addRadialMenuItem(++indexCount, newRadialID, callback, text);
	}

	void addRadialMenuItem(uint8 radialid, uint8 callback, const UnicodeString& text = "") {
		root->addRadialMenuItem(++indexCount, radialid, callback, text);
	}

	void finish() {
		insertRadialItemToMessage(root);

		insertInt(46, listSize);
		insertByte(count);
	}

	void insertRadialItemToMessage(RadialMenuItem* item) {
		for (int i = 0; i < item->getChildrenSize(); ++i) {
			RadialMenuItem* child = item->getChild(i);
			addRadialOption(child);

			insertRadialItemToMessage(child);
		}
	}

	inline void setCounter(uint8 counter) {
		count = counter;
	}

	inline RadialMenuItem* getRootMenuItem() {
		return root;
	}
};


}
}
}
}

using namespace server::zone::packets::object;

#endif
