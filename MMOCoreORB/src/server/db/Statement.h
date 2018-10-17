/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef STATEMENT_H_
#define STATEMENT_H_

#include "system/lang.h"

namespace server {
  namespace db {
    namespace mysql {

	#define quote '\''

  	class Statement {
  		char* data;

  	public:
  		Statement();

	};

    } // namespace mysql
  } // namespace db
} // namespace engine

#endif /*STATEMENT_H_*/
