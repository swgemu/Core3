/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SEARCHKNOWLEDGEBASERESPONSEMESSAGE_H_
#define SEARCHKNOWLEDGEBASERESPONSEMESSAGE_H_

class SearchKnowledgebaseResponseMessage : public BaseMessage {
	int articleCount;
public:
   SearchKnowledgebaseResponseMessage(bool success) : BaseMessage() {
	    articleCount = 0;
		insertShort(0x03);
		insertInt(0x7CBC8F67);  // CRC

		if (success == true)
			insertInt(0); //option.  1 = found nothing. 0 = found.
		else
			insertInt(1);


		insertInt(0); //List count articles found.



   }

   void addArticle(const UnicodeString& title, const String& articleid) {
		    insertUnicode(title);
	   		insertAscii(articleid);
	   		insertShort(0);

	   		updateCount();
   }

   void updateCount() {
	   insertInt(14, ++articleCount);
   }

   void updateFound(bool found) {
	   if (found == true) {
		   insertInt(10, 0);
	   } else {
		   insertInt(10, 1);
	   }

   }


};

#endif /*SEARCHKNOWLEDGEBASERESPONSEMESSAGE_H_*/

