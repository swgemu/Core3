/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef MYSQLDATABASE_H_
#define MYSQLDATABASE_H_

#include "system/lang.h"

#include <mysql.h>

#include "engine/log/Logger.h"

#include "engine/db/Database.h"

#include "Statement.h"
#include "ResultSet.h"

namespace server {
  namespace db {
    namespace mysql {

    class MySqlDatabase : public Database, public Mutex, public Logger {
		MYSQL mysql;
		String host;

		uint32 queryTimeout;
		uint32 writeQueryTimeout;

	private:
		static int createDatabaseThread();
		static const char* mysqlThreadName;

	public:
		MySqlDatabase(const String& s);
		MySqlDatabase(const String& s, const String& host);

		~MySqlDatabase();

		void connect(const String& dbname, const String& user, const String& passw, int port);

		void executeStatement(const char* statement);
		void executeStatement(const String& statement);
		void executeStatement(const StringBuffer& statement);

		void doExecuteStatement(const String& statement);

		//sync
		engine::db::ResultSet* executeQuery(const char* statement);
		engine::db::ResultSet* executeQuery(const String& statement);
		engine::db::ResultSet* executeQuery(const StringBuffer& statement);

#ifdef CXX11_COMPILER
		//async
		void executeQuery(const char* query, Function<void(engine::db::ResultSet*)>&& callback);
#endif

		void commit();

		void rollback();

		void autocommit(bool doCommit);

		void close();

		void error();
		void error(const char* query);

		static void finalizeLibrary();
		static void initializeLibrary();
		static void onThreadStart();
		static void onThreadEnd();

		int compareTo(const Database* database) const final {
			if (this < database)
				return 1;
			else if (this > database)
				return -1;
			else
				return 0;
		}

	};

    } // namespace mysql
  } // namespace db
} // namespace engine

#endif /*MYSQLDATABASE_H_*/
