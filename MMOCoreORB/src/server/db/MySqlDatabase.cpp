/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#include "engine/db/mysql/MysqlDatabaseManager.h"

#include "engine/engine.h"

#include "engine/core/Task.h"
#include "engine/core/TaskWorkerThread.h"

#include "MySqlDatabase.h"

using namespace server::db::mysql;

class MysqlTask final : public Task {
	MySqlDatabase* database;
	String query;
public:
	MysqlTask(MySqlDatabase* db, const String& q) : database(db), query(q) {
	}

	void run() final {
		try {
			database->doExecuteStatement(query);
		} catch (const Exception& e) {
			database->error(e.getMessage().toCharArray());
		}

	}
};

class MysqlCallback final : public Task {
	engine::db::ResultSet* result;
	Function<void(engine::db::ResultSet*)> callback;

public:
	MysqlCallback(engine::db::ResultSet* res, Function<void(engine::db::ResultSet*)>&& f)
			: result(res), callback(std::move(f)) {
	}

	void run() final {
		callback(result);
	}
};

class MysqlLambda final : public Task {
	MySqlDatabase* database;
	String query;
	Function<void(engine::db::ResultSet*)> function;

public:
	MysqlLambda(MySqlDatabase* db, const char* q,
				Function<void(engine::db::ResultSet*)>&& f): database(db), query(q), function(std::move(f)) {
	}

	void run() final {
		try {
			engine::db::ResultSet* res = database->executeQuery(query);

			MysqlCallback* callback = new MysqlCallback(res, std::move(function));
			callback->execute();
		} catch (const Exception& e) {
			database->error(e.getMessage().toCharArray());
		}
	}
};

using namespace engine::db::mysql;

const char* MySqlDatabase::mysqlThreadName = "mysqlThread";

MySqlDatabase::MySqlDatabase(const String& s) : Mutex("MYSQL DB"), Logger(s) {
	queryTimeout = 5;
	writeQueryTimeout = queryTimeout * 10;

	memset(&mysql, 0, sizeof(mysql));
}

MySqlDatabase::MySqlDatabase(const String& s, const String& host) : Mutex("MYSQL DB"), Logger(s) {
	MySqlDatabase::host = host;

	memset(&mysql, 0, sizeof(mysql));

	queryTimeout = 5;
	writeQueryTimeout = queryTimeout * 1000;

	setLockTracing(false);
}

MySqlDatabase::~MySqlDatabase() {
	close();
}

int MySqlDatabase::createDatabaseThread() {
	Core::getTaskManager()->initializeCustomQueue(mysqlThreadName, 1, false);

	return 0;
}

void MySqlDatabase::connect(const String& dbname, const String& user, const String& passw, int port) {
	Locker locker(this);

	info(true) << "connecting to " << host << ":" << port << "...";

	static int databaseThread = createDatabaseThread();

	fatal(!databaseThread) << "could not create mysql database thread";

	if (!mysql_init(&mysql))
		error();

	mysql_options(&mysql, MYSQL_OPT_READ_TIMEOUT, (char*)&queryTimeout);
	mysql_options(&mysql, MYSQL_OPT_WRITE_TIMEOUT, (char*)&writeQueryTimeout);
	int reconnect = 1;
	mysql_options(&mysql, MYSQL_OPT_RECONNECT, &reconnect);

	if (!mysql_real_connect(&mysql, host.toCharArray(), user.toCharArray(), passw.toCharArray(), dbname.toCharArray(), port, nullptr, 0)) {
		error();
	}

	info(true) << "connected to " << host << ":" << port;

#ifdef WITH_STM
	autocommit(false);
#endif
}

void MySqlDatabase::doExecuteStatement(const String& statement) {
	Locker locker(this);

#ifdef COLLECT_TASKSTATISTICS
	Timer timer(Time::MONOTONIC_TIME);
	timer.start();
#endif

	while (mysql_query(&mysql, statement.toCharArray())) {
		unsigned int errorNumber = mysql_errno(&mysql);

		if (errorNumber != 1205/*ER_LOCK_WAIT_TIMEOUT*/) {
			error(statement.toCharArray());
			break;
		} else
			warning() << "mysql lock wait timeout on statement: " << statement;
	}

#ifdef WITH_STM
	MysqlDatabaseManager::instance()->addModifiedDatabase(this);
#endif

#ifdef COLLECT_TASKSTATISTICS
	uint64 elapsed = timer.stop();

	Thread* thread = Thread::getCurrentThread();
	TaskWorkerThread* worker = thread ? thread->asTaskWorkerThread() : nullptr;

	if (worker) {
		worker->addMysqlStats(statement, elapsed);
	}
#endif

}

void MySqlDatabase::executeStatement(const char* statement) {
	Reference<Task*> task = new MysqlTask(this, statement);
	task->setCustomTaskQueue(mysqlThreadName);
	task->execute();
}

void MySqlDatabase::executeStatement(const String& statement) {
	executeStatement(statement.toCharArray());
}

void MySqlDatabase::executeStatement(const StringBuffer& statement) {
	executeStatement(statement.toString().toCharArray());
}

void MySqlDatabase::executeQuery(const char* query, Function<void(engine::db::ResultSet*)>&& function) {
	Reference<MysqlLambda*> lambda = new MysqlLambda(this, query, std::move(function));
	lambda->setCustomTaskQueue(mysqlThreadName);
	lambda->execute();
}

engine::db::ResultSet* MySqlDatabase::executeQuery(const char* statement) {
	Locker locker(this);

#ifdef COLLECT_TASKSTATISTICS
	Timer timer(Time::MONOTONIC_TIME);
	timer.start();
#endif

	while (mysql_query(&mysql, statement)) {
		unsigned int errorNumber = mysql_errno(&mysql);

		if (errorNumber != 1205/* ER_LOCK_WAIT_TIMEOUT*/) {
			error(statement);
			break;
		} else
			warning() << "mysql lock wait timeout on statement: " << statement;
	}

	MYSQL_RES* result = mysql_store_result(&mysql);

	if (result == nullptr) {
		//TA: insert statements return nullptr result
		//but if the table has auto_increment you can still call mysql_insert_id(mysql) to get the last affected row
		if (mysql_field_count(&mysql) != 0) {
			error(statement);
		}
	}

#ifdef WITH_STM
	MysqlDatabaseManager::instance()->addModifiedDatabase(this);
#endif

#ifdef COLLECT_TASKSTATISTICS
	uint64 elapsed = timer.stop();

	Thread* thread = Thread::getCurrentThread();
	TaskWorkerThread* worker = thread ? thread->asTaskWorkerThread() : nullptr;

	if (worker) {
		worker->addMysqlStats(statement, elapsed);
	}
#endif

	ResultSet* res = new ResultSet(&mysql, result);
	return res;
}

engine::db::ResultSet* MySqlDatabase::executeQuery(const String& statement) {
	return executeQuery(statement.toCharArray());
}

engine::db::ResultSet* MySqlDatabase::executeQuery(const StringBuffer& statement) {
	return executeQuery(statement.toString().toCharArray());
}

void MySqlDatabase::commit() {
	Locker locker(this);

	mysql_commit(&mysql);
}

void MySqlDatabase::rollback() {
	Locker locker(this);

	mysql_rollback(&mysql);
}

void MySqlDatabase::autocommit(bool doCommit) {
	Locker locker(this);

	mysql_autocommit(&mysql, doCommit);
}

void MySqlDatabase::close() {
	mysql_close(&mysql);

	info("disconnected");
}

void MySqlDatabase::error() {
	StringBuffer msg;
	msg << mysql_errno(&mysql) << ": " << mysql_error(&mysql);
	Logger::error(msg);

	throw DatabaseException(msg.toString());
}

void MySqlDatabase::error(const char* query) {
	StringBuffer msg;
	msg << "DatabaseException caused by query: " << query << "\n" << mysql_errno(&mysql) << ": " << mysql_error(&mysql);
	Logger::error(msg);

	throw DatabaseException(msg.toString());
}

void MySqlDatabase::finalizeLibrary() {
	mysql_library_end();
}

void MySqlDatabase::initializeLibrary() {
	mysql_library_init(0, nullptr, nullptr);
}

void MySqlDatabase::onThreadStart() {
	mysql_thread_init();
}

void MySqlDatabase::onThreadEnd() {
	mysql_thread_end();
}
