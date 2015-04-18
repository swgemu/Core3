/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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

class RadialMenuItem : public Object {
	uint8 radialID;
	uint8 callback;
	UnicodeString text;

	RadialMenuItem* parent;

	Vector<Reference<RadialMenuItem*> > children;

	int itemIndex;

public:
	RadialMenuItem(int itemidx, RadialMenuItem* parent, uint8 radialid, uint8 callback, const UnicodeString& text = "") {
		setRadialID(radialid);
		setCallback(callback);
		setText(text);

		RadialMenuItem::parent = parent;

		itemIndex = itemidx;
	}

	RadialMenuItem() {
		radialID = 0;
		callback = 0;

		itemIndex = 0;

		parent = NULL;
	}

	~RadialMenuItem() {
		/*for (int i = 0; i < children.size(); ++i)
			delete children.get(i);*/

		//children.removeAll();
	}

	void addRadialMenuItem(int itemidx, uint8 radialid, uint8 callback, const UnicodeString& text = "") {
		RadialMenuItem* menuitem = new RadialMenuItem(itemidx, this, radialid, callback, text);
		children.add(menuitem);
	}

	RadialMenuItem* getItem(int index) {
		RadialMenuItem* returnItem = NULL;

		for (int i = 0; i < children.size(); ++i) {
			RadialMenuItem* item = children.get(i);

			if (item->getItemIndex() == index)
				return item;
			else {
				returnItem = item->getItem(index);

				if (returnItem != NULL)
					return returnItem;
			}
		}

		return returnItem;
	}

	RadialMenuItem* getItemByRadialID(uint8 index) {
		RadialMenuItem* returnItem = NULL;

		for (int i = 0; i < children.size(); ++i) {
			RadialMenuItem* item = children.get(i);

			if (item->getRadialID() == index)
				return item;
			else {
				returnItem = item->getItemByRadialID(index);

				if (returnItem != NULL)
					return returnItem;
			}
		}

		return returnItem;
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

	inline void setParent(RadialMenuItem* item) {
		parent = item;
	}

	inline void setItemIndex(int idx) {
		itemIndex = idx;
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

	inline RadialMenuItem* getChild(int idx) {
		return children.get(idx);
	}

	inline RadialMenuItem* getParent() {
		return parent;
	}

	inline bool hasChildren() {
		return children.size() > 0;
	}

	inline int getChildrenSize() {
		return children.size();
	}

	inline int getParentIndex() {
		if (parent != NULL) {
			return parent->getItemIndex();
		} else
			return 0;
	}

	inline int getItemIndex() {
		return itemIndex;
	}
};

#endif /* RADIALMENUITEM_H_ */
