/*
 * RequestCategoriesResponseMessage.h
 *
 *  Created on: Nov 25, 2008
 *      Author: swgemu
 */

#ifndef REQUESTCATEGORIESRESPONSEMESSAGE_H_
#define REQUESTCATEGORIESRESPONSEMESSAGE_H_

class RequestCategoriesResponseMessage : public BaseMessage {
	int mainCategoryCount;

public:
   RequestCategoriesResponseMessage() : BaseMessage() {
	    mainCategoryCount = 0;
		insertShort(0x03);
		insertInt(0x61148FD4);  // CRC

		insertInt(0); //??

		insertInt(0); //Main Category Count

   }

   void addMainCategory(const UnicodeString& mCategory, uint32 categoryId, int subCatCount, byte flag1, byte flag2) {

		    insertUnicode(mCategory);
			insertInt(categoryId);

			if (subCatCount > 0) {
				insertInt(subCatCount);
				//Here is where we need to add in Sub-Categories.
				//TODO: Put code here.
				addSubCategory("test", 0xB90B, 0x01, 0x01);
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
#endif /* REQUESTCATEGORIESRESPONSEMESSAGE_H_ */
