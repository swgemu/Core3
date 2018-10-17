/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef ROW_H_
#define ROW_H_

#include <mysql.h>

namespace server {
  namespace db {
    namespace mysql {

	class Row {
		MYSQL_ROW row;

	public:
		Row() {
		}

	};

    } // namespace mysql
  } // namespace db
} // namespace engine

using namespace engine::db::mysql;

#endif /*ROW_H_*/
