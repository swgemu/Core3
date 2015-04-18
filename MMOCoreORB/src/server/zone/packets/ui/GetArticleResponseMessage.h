/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETARTICLERESPONSEMESSAGE_H_
#define GETARTICLERESPONSEMESSAGE_H_

class GetArticleResponseMessage : public BaseMessage {
public:
   GetArticleResponseMessage(bool success) : BaseMessage() {
		insertShort(0x03);
		insertInt(0x934BAEE0);  // CRC

		if (success == true)
			insertInt(0); //option.  1 = couldnt retrieve. 0 = show article.
		else {
			insertInt(1);
			insertInt(0); //Blank Unicode string.
		}

		setCompression(true);
   }

   void insertArticle(const UnicodeString& article) {
	   insertUnicode(article);
   }
};

#endif /*GETARTICLERESPONSEMESSAGE_H__*/

