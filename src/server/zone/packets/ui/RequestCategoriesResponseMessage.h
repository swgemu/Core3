/*
 * RequestCategoriesResponseMessage.h
 *
 *  Created on: Nov 25, 2008
 *      Author: swgemu
 */

#ifndef REQUESTCATEGORIESRESPONSEMESSAGE_H_
#define REQUESTCATEGORIESRESPONSEMESSAGE_H_

class BugCategory : public Object {
public:
	UnicodeString name;
	int id;
	byte unk1;
	byte unk2;

	Vector<BugCategory> children;

	BugCategory() {
		id = 0;
		unk1 = 1;
		unk2 = 1;
	}

	BugCategory(const UnicodeString& n, int i, byte u1, byte u2) {
		name = n;
		id = i;
		unk1 = u1;
		unk2 = u2;
	}

	BugCategory(const BugCategory& bc) : Object() {
		name = bc.name;
		id = bc.id;
		unk1 = bc.unk1;
		unk2 = bc.unk2;
	}

	BugCategory& operator= (const BugCategory& bc) {
		name = bc.name;
		id = bc.id;
		unk1 = bc.unk1;
		unk2 = bc.unk2;

		return *this;
	}

	inline void insertToMessage(BaseMessage* message) {
		message->insertUnicode(name);
		message->insertInt(id);

		message->insertInt(1);
		message->insertUnicode("None");
		message->insertInt(0);
		message->insertInt(0);
		message->insertByte(1);
		message->insertByte(1);

		message->insertByte(unk1);
		message->insertByte(unk2);
	}

	inline void addSubCategory(BugCategory category) {
		children.add(category);
	}

	inline int getCount() {
		return children.size();
	}
};

class RequestCategoriesResponseMessage : public BaseMessage {
	int mainCategoryCount;

public:
   RequestCategoriesResponseMessage(Vector<BugCategory>* categories) : BaseMessage() {
	    mainCategoryCount = 0;
		insertShort(0x03);
		insertInt(0x61148FD4);  // CRC

		insertInt(0); //??
		insertInt(categories->size());

		for (int i = 0; i < categories->size(); ++i) {
			BugCategory* category = &categories->get(i);

			if (category == NULL)
				continue;

			category->insertToMessage(this);
		}
   }

   void addMainCategory(const UnicodeString& mCategory, uint32 categoryId, int subCatCount, byte flag1, byte flag2) {

		    insertUnicode(mCategory);
			insertInt(categoryId);

			if (subCatCount > 0) {
				insertInt(subCatCount);
				//Here is where we need to add in Sub-Categories.
				//TODO: Put code here.
				addSubCategory("test", 0xB90B, 0x01, 0x01);
				addSubCategory("test2", 0xB90B, 0x01, 0x01);
			} else {
				insertInt(0); //Set the sub category count to 0.
			}
			insertByte(flag1); //?? seen 0 and 1
			insertByte(flag2); //?? seen 0 and 1
			updateMainCategoryCount();

   }

   void addSubCategory(const UnicodeString& sCategory, uint32 categoryId, byte flag1, byte flag2){
						insertUnicode(sCategory);
						insertInt(categoryId);

						insertInt(0); //List of more subcategories. CUT IT OFF HERE. SEND 0.
						insertByte(flag1);
						insertByte(flag2);
   }

   void updateMainCategoryCount() {
	   insertInt(14, ++mainCategoryCount);
   }

};

class RequestCategoriesMessageCallback : public MessageCallback {
	String language;

public:
	RequestCategoriesMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		message->parseAscii(language);
	}

	void run() {
		Vector<BugCategory> categories;
		BugCategory test1("Test1", 1, 1, 1);
		BugCategory test2("Test2", 3, 1, 1);

		categories.add(test1);
		categories.add(test2);

		RequestCategoriesResponseMessage* rcrm = new RequestCategoriesResponseMessage(&categories);
		client->info(rcrm->toStringData(), true);
		client->sendMessage(rcrm);

		//RequestCategoriesResponseMessage* rcrm2 = new RequestCategoriesResponseMessage();
		//rcrm2->addMainCategory("Account/Billing", 0xB808, 1, 1, 1);
		//client->sendMessage(rcrm2);
	}
};

#endif /* REQUESTCATEGORIESRESPONSEMESSAGE_H_ */
