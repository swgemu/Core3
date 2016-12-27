/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef OBJECTMENURESPONSE_H_
#define OBJECTMENURESPONSE_H_

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

	Reference<RadialMenuItem*> root;

	/*Reference<SceneObject*> player;

	uint64 target;*/

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

		/*this->player = player;
		this->target = target;*/

		insertInt(0); // size

		listSize = 0;
		count = counter;

		indexCount = 0;

		root = new RadialMenuItem();
	}

	/*ObjectMenuResponse* cloneMenuResponse() {
		ObjectMenuResponse* resp = new ObjectMenuResponse(player, target, count);
		resp->player = player;
		resp->listSize = listSize;
		resp->indexCount = indexCount;
		resp->root = root;
	}*/

	~ObjectMenuResponse() {
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
			throw Exception("error: null parent radial menu (id = " + String::valueOf(parentid) + ") specified. radialid = " + String::valueOf(radialid));
		}

		parent->addRadialMenuItem(++indexCount, radialid, callback, text);
	}

	/**
	 * Adds an object menu item to the specified parent radial id, not parent index with callback
	 */
	void addRadialMenuItemToRadialID(uint8 parentRadialID, uint8 newRadialID, uint8 callback, const UnicodeString& text = "") {
		RadialMenuItem* parent = getRadialItemByRadialID(parentRadialID);

		if (parent == NULL) {
			throw Exception("error: parent radial id (" + String::valueOf(parentRadialID) + ") menu item null. newRadialID = " + String::valueOf(newRadialID));
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
