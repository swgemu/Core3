/*
 * BugCategory.h
 *
 *  Created on: Nov 22, 2010
 *      Author: crush
 */

#ifndef BUGCATEGORY_H_
#define BUGCATEGORY_H_

#include "engine/engine.h"

class BugCategory : public Object {
	UnicodeString categoryName;
	uint32 categoryId;
	byte unk1;
	byte unk2;

	Vector<BugCategory> children;

public:
	BugCategory() {
		categoryId = 0;
		unk1 = 0;
		unk2 = 0;
	}

	BugCategory(const UnicodeString& name, uint32 id, byte u1 = 1, byte u2 = 1) {
		categoryName = name;
		categoryId = id;
		unk1 = u1;
		unk2 = u2;
	}

	BugCategory(const BugCategory& cat) : Object() {
		categoryName = cat.categoryName;
		categoryId = cat.categoryId;
		unk1 = cat.unk1;
		unk2 = cat.unk2;

		children = cat.children;
	}

	BugCategory& operator= (const BugCategory& cat) {
		if (this == &cat)
			return *this;

		categoryName = cat.categoryName;
		categoryId = cat.categoryId;
		unk1 = cat.unk1;
		unk2 = cat.unk2;

		children = cat.children;

		return *this;
	}

	void addCategory(const BugCategory& cat) {
		children.add(cat);
	}

	int compareTo(const BugCategory& cat) const {
		if (categoryId < cat.categoryId)
			return 1;
		else if (categoryId > cat.categoryId)
			return -1;
		else
			return 0;
	}

	void insertToMessage(Message* message) {
		message->insertUnicode(categoryName);
		message->insertInt(categoryId);

		message->insertInt(children.size());

		for (int i = 0; i < children.size(); ++i) {
			BugCategory* category = &children.get(i);

			if (category == NULL)
				continue;

			category->insertToMessage(message);
		}

		message->insertByte(unk1);
		message->insertByte(unk2);
	}

	inline void setCategoryName(const UnicodeString& name) {
		categoryName = name;
	}

	inline void setCategoryId(uint32 id) {
		categoryId = id;
	}

	inline void setUnk1(byte u1) {
		unk1 = u1;
	}

	inline void setUnk2(byte u2) {
		unk2 = u2;
	}
};

#endif /* BUGCATEGORY_H_ */
