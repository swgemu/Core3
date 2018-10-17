/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef ENGINE_DB_MYSQL_RESULTSET_H_
#define ENGINE_DB_MYSQL_RESULTSET_H_

#include <mysql.h>

#include "system/lang/Long.h"

#include "engine/db/ResultSet.h"

namespace server {
  namespace db {
    namespace mysql {

	class ResultSet : public engine::db::ResultSet {
		MYSQL *mysql;

		MYSQL_RES *result;
		MYSQL_ROW row;

	public:
		ResultSet(MYSQL* db, MYSQL_RES *res) : row(nullptr) {
			mysql = db;
			result = res;
		}

		virtual ~ResultSet() {
			mysql_free_result(result);
		}

		bool next() {
			return (row = mysql_fetch_row(result)) != nullptr;
		}

		bool getBoolean(int index) {
			return atoi(row[index]);
		}

		int getInt(int index) {
			return atoi(row[index]);
		}

		sys::uint32 getUnsignedInt(int index) {
			return (sys::uint32) strtoul(row[index], nullptr, 0);
		}

		sys::int64 getLong(int index) {
			return Long::valueOf(row[index]);
		}

		sys::uint64 getUnsignedLong(int index) {
			return Long::unsignedvalueOf(row[index]);
		}

		float getFloat(int index) {
			return atof(row[index]);
		}

		char* getString(int index) {
			return row[index];
		}

		sys::uint64 getRowsAffected() {
			return mysql_affected_rows(mysql);
		}

		sys::uint64 getLastAffectedRow() {
			return mysql_insert_id(mysql);
		}

		inline sys::uint64 size() {
			return mysql_num_rows(result);
		}
	};

    } // namespace mysql
  } // namespace db
} // namespace engine

#endif /*ENGINE_DB_MYSQL_RESULTSET_H_*/
