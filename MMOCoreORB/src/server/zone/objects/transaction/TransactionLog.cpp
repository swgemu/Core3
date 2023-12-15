/*
		Copyright <SWGEmu>
	See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : TransactionLog.h
 * @created     : Wed Apr 15 21:49:41 UTC 2020
 */

#include "TransactionLog.h"
#include "server/ServerCore.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "engine/engine.h"
#include "system/thread/atomic/AtomicBoolean.h"
#include "system/thread/atomic/AtomicInteger.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/tangible/deed/structure/StructureDeed.h"
#include "server/zone/managers/credit/CreditManager.h"
#include "server/zone/objects/tangible/eventperk/LotteryDroid.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"

#define TRXLOG_FORMAT_VERSION 2

AtomicInteger TransactionLog::exportBacklog;

TransactionLog::TransactionLog(SceneObject* src, SceneObject* dst, SceneObject* subject, TrxCode code, bool exportSubject, CAPTURE_CALLER_ARGS) {
	if (!isEnabled()) {
		return;
	}

	setType("transfer");

	initializeCommon(src, dst, code, file, function, line);

	setSubject(subject, exportSubject);
}

TransactionLog::TransactionLog(SceneObject* src, SceneObject* dst, TrxCode code, int amount, bool isCash, CAPTURE_CALLER_ARGS) {
	if (!isEnabled()) {
		return;
	}

	setType("credits");

	initializeCommon(src, dst, code, file, function, line);
	initializeCreditsCommon(src, dst, code, amount, isCash);
}

TransactionLog::TransactionLog(uint64 srcObjectID, TrxCode code, uint amount, bool isCash, CAPTURE_CALLER_ARGS) {
	if (!isEnabled()) {
		return;
	}

	setType("credits");

	auto server = ServerCore::getZoneServer();

	if (server == nullptr) {
		errorMessage() << "failed to getZoneServer to lookup oid: " << srcObjectID;
		return;
	}

	auto src = server->getObject(srcObjectID);

	if (src != nullptr) {
		Locker lock(src);
		initializeCommon(src, nullptr, code, file, function, line);
		initializeCreditsCommon(src, nullptr, code, amount, isCash);
	} else {
		mTransaction["src"] = srcObjectID;
		initializeCommon(nullptr, nullptr, code, file, function, line);
		initializeCreditsCommon(nullptr, nullptr, code, amount, isCash);
	}
}

TransactionLog::TransactionLog(CreditObject* creditObject, SceneObject* dst, TrxCode code, int amount, bool isCash, CAPTURE_CALLER_ARGS) {
	if (!isEnabled()) {
		return;
	}

	setType("credits");

	initializeCommon(nullptr, dst, code, file, function, line);
	initializeCreditsCommon(nullptr, dst, code, amount, isCash);

	mTransaction["src"] = creditObject->_getObjectID();

	addStateCreditBalances("src", "Before");
}

TransactionLog::~TransactionLog() {
	if (!isEnabled()) {
		return;
	}

	if (!mCommitted) {
		if (mAborted) {
			writeLog();
			return;
		}

		if (mAutoCommit) {
			commit();
		} else {
			abort() << "Transaction ended without commit!";
			writeLog();
		}
	}
}

void TransactionLog::commit(bool discardEmpty) {
	if (!isEnabled()) {
		return;
	}

	if (discardEmpty) {
		uint64 subjectID = mTransaction.contains("subject") ? mTransaction["subject"].get<uint64>() : 0ull;

		if (subjectID == 0ull && mRelatedObjects.size() == 0) {
			mEnabled = false;
			return;
		}
	}

	if (mCommitted) {
		getLogger().error() << "Double commit of transaction: " << *this;
		return;
	}

	if (isCreditTransaction()) {
		addStateCreditBalances("src", "After");
		addStateCreditBalances("dst", "After");
	} else {
		addStateCreditBalances("subject", "After");
	}

	if (mDebug) {
		addRelatedObject(mTransaction["src"].get<uint64>());
		addRelatedObject(mTransaction["dst"].get<uint64>());
		mExportRelated = true;
	}

	mCommitted = true;
	mTransaction["msCommit"] = mStartTime.miliDifference();

	if (mExportRelated) {
		if (!getAsyncExport()) {
			exportRelated();
		} else {
			exportBacklog.increment();

			// Force a copy of trx because dtor will destroy (this) before we're done
			Core::getTaskManager()->executeTask(
				[trx = *this] () mutable {
					try {
						trx.exportRelated();
						trx.mTransaction["exportBacklog"] = exportBacklog.get() - 1;
						trx.writeLog();
					} catch (...) {
						getLogger().error() << "unexpected exception in export task: " << trx;
					}

					exportBacklog.decrement();
				},
				"exportRelated-" + getTrxID(), getCustomQueue()->getName());
			return;
		}
	}

	mTransaction["msCommit"] = mStartTime.miliDifference();
	writeLog();
}

void TransactionLog::setSubject(SceneObject* subject, bool exportSubject) {
	if (subject != nullptr) {
		mTransaction["subject"] = subject->getObjectID();

		if (exportSubject || mDebug) {
			addRelatedObject(subject->getObjectID());
		}

		addStateCreditBalances("subject", "Before", subject);
		addStateObjectMetadata("subject", subject);
	} else {
		mTransaction["subject"] = 0;
	}
}

void TransactionLog::setExperience(const String& xpType, int xpAdd, int xpTotal) {
	if (mTransaction.contains("xpAdd")) {
		errorMessage() << "duplicate setExperience call: [" << xpType << "] = [" << xpAdd << "]";
		getLogger().error() << errorMessage() << " " << *this;
		return;
	}

	mTransaction["xpType"] = xpType;
	mTransaction["xpAdd"] = xpAdd;
	mTransaction["xpTotal"] = xpTotal;
}

void TransactionLog::addRelatedObject(uint64 oid, bool trackChildren) {
	if (!isEnabled() || oid == 0) {
		return;
	}

	uint64 subjectID = mTransaction.contains("subject") ? mTransaction["subject"].get<uint64>() : 0ull;

	if (subjectID == 0ull) {
		mTransaction["subject"] = oid;
	}

	if (!mRelatedObjects.contains(oid)) {
		mRelatedObjects.add(oid);
	}

	if (!trackChildren) {
		return;
	}

	auto scno = Core::getObjectBroker()->lookUp(oid).castTo<SceneObject*>();

	if (scno == nullptr) {
		return;
	}

	if (mChildObjects.size() == 0) {
		mChildObjects.setAllowOverwriteInsertPlan();
	}

	scno->getChildrenRecursive(mChildObjects, mMaxDepth, true, true);
}

void TransactionLog::addRelatedObject(SceneObject* obj, bool trackChildren) {
	if (obj == nullptr) {
		return;
	}

	uint64 subjectID = mTransaction.contains("subject") ? mTransaction["subject"].get<uint64>() : 0ull;

	if (subjectID == 0ull) {
		setSubject(obj);
	}

	addRelatedObject(obj->getObjectID(), trackChildren);
}

void TransactionLog::exportRelated() {
	if (!isEnabled() || mRelatedObjects.size() <= 0 || mState.contains("exports")) {
		return;
	}

	if (mState.contains("exports")) {
		return;
	}

	JSONSerializationType exportMap = JSONSerializationType::object();
	auto server = ServerCore::getZoneServer();

	if (server == nullptr) {
		errorMessage() << "unable to getZoneServer in exportRelated";
		return;
	}

	Time exportStartTime;
	auto logMsg = "TransactionLog trxId: " + getTrxID() + "; code: " + String(mTransaction["code"]);

	for (int i = 0; i < mRelatedObjects.size(); ++i) {
		auto oid = mRelatedObjects.get(i);
		auto obj = server->getObject(oid);

		if (obj == nullptr) {
			errorMessage() << "failed to getObject(" << oid << ")";
			continue;
		}

		auto pruneCreo = getPruneCreatureObjects() && obj->isStructureObject();

		exportMap[String::valueOf(oid)] = obj->exportJSON(logMsg, mMaxDepth, pruneCreo, getPruneCraftedComponents());
	}

	mState["exports"] = exportMap;
	mTransaction["msExport"] = mStartTime.miliDifference();
}

StringBuffer& TransactionLog::abort(CAPTURE_CALLER_ARGS) {
	mAborted = true;
	mContext["abortFile"] = file;
	mContext["abortFunction"] = function;
	mContext["abortLine"] = line;

	if (mError.length() > 0) {
		mError << "; ";
	}

	mError << "Transaction Aborted: ";
	return mError;
}

StringBuffer& TransactionLog::errorMessage() {
	if (mError.length() > 0) {
		mError << "; ";
	}

	return mError;
}

const String TransactionLog::getErrorMessage() {
	return mError.toString();
}

bool TransactionLog::isCreditTransaction() const {
	return getType() == "credits";
}

String TransactionLog::toStringData() const {
	return composeLogEntry();
}

void TransactionLog::addContextFromLua(lua_State* L) {
	if (!isEnabled()) {
		return;
	}

	catchAndLog(__FUNCTION__, [&]() -> void {
		lua_Debug ar;

		memset(&ar, 0, sizeof(ar));

		if (lua_getstack(L, 0, &ar) && lua_getinfo(L, "n", &ar)) {
			if (ar.name != nullptr) {
				mContext["luaFunction"] = ar.name;
			}

			if (lua_getstack(L, 1, &ar) && lua_getinfo(L, "Sl", &ar)) {
				if (ar.source != nullptr) {
					mContext["luaFile"] = ar.source;
				}

				mContext["luaLine"] = ar.currentline;
			}
		}
	});
}

const String TransactionLog::getNewTrxID() {
	static AtomicInteger incr;
	return String::hexvalueOf((uint64)((System::getMikroTime() << 8)) | (incr.increment() & 0xFF));
}

void TransactionLog::catchAndLog(const char* functioName, Function<void()> function) {
	// Avoid JSON Serialization errors causing game crashes
	try {
		function();
	} catch (...) {
#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
		errorMessage() << __FILE__ << ":" << functioName << " unexpected exception: " << __cxxabiv1::__cxa_current_exception_type()->name();
#else
		errorMessage() << __FILE__ << ":" << functioName << " unexpected exception";
#endif
		getLogger().error() << errorMessage() << " " << *this;
	}
}

Logger& TransactionLog::getLogger() {
	auto static customLogger = [] () {
		Logger log("TransactionLogMessages");

		log.setGlobalLogging(false);
		log.setFileLogger("log/trxlogmsgs.log", true, ConfigManager::instance()->getRotateLogAtStart());
		log.setLogLevelToFile(false);
		log.setLogToConsole(false);
		log.setRotateLogSizeMB(ConfigManager::instance()->getInt("Core3.TransactionLog.RotateLogSizeMB", ConfigManager::instance()->getRotateLogSizeMB()));
		log.setLogLevel(ConfigManager::instance()->getLogLevel("Core3.TransactionLog.LogLevel", Logger::DEBUG));

		return log;
	} ();

	return customLogger;
};

const TaskQueue* TransactionLog::getCustomQueue() {
	auto static customQueue = [] () {
		auto numberOfThreads = ConfigManager::instance()->getInt("Core3.TransactionLog.WorkerThreads", 4);

		return Core::getTaskManager()->initializeCustomQueue("TransactionLogWorker", numberOfThreads);
	}();

	return customQueue;
}

bool TransactionLog::checkDebug(SceneObject* obj) const {
	if (!getCheckPlayerDebug()) {
		return false;
	}

	if (obj != nullptr) {
		auto creo = dynamic_cast<CreatureObject*>(obj);

		if (creo != nullptr) {
			auto ghost = creo->getPlayerObject();

			if (ghost != nullptr) {
				if (ghost->getLogLevel() == Logger::DEBUG) {
					return true;
				}
			}
		}
	}

	return false;
}

const String TransactionLog::shortFilename(const char* file) const {
	auto ep = file;

	while (*ep) {
		ep++;
	}

	for (auto cp = file; cp < ep - 8; cp++) {
		if (strncmp(cp, "src/", 4) == 0) {
			cp += 4;

			if (cp < ep) {
				file = cp;
			}
			break;
		}
	}

	return String(file);
}

void TransactionLog::initializeCommonSceneObject(const String& key, SceneObject* obj) {
	if (obj == nullptr) {
		mTransaction[key] = 0;
		return;
	}

	mTransaction[key] = obj->getObjectID();

	auto creo = obj->asCreatureObject();

	if (creo == nullptr) {
		return;
	}

	if (creo->isNonPlayerCreatureObject()) {
		addStateObjectMetadata(key, obj);
		return;
	}

	auto player = creo->getPlayerObject();

	if (player != nullptr) {
		mTransaction[key + "AccountId"] = player->getAccountID();

		mState[key + "PlayedSeconds"] = (int)(player->getPlayedMiliSecs() / 1000);
		mState[key + "SessionSeconds"] = (int)(player->getSessionMiliSecs() / 1000);
		mState[key + "SessionMovement"] = player->getSessionTotalMovement();
		mState[key + "SessionCredits"] = player->getSessionTotalCredits();

		return;
	}

	addStateObjectMetadata(key, obj);
}

void TransactionLog::initializeCommon(SceneObject* src, SceneObject* dst, TrxCode code, CAPTURE_CALLER_ARGS) {
	mTransaction["trxId"] = getNewTrxID();

	mTransaction["code"] = trxCodeToString(code);

	mMaxDepth = 4;

	if (isStat(code)) {
		mAutoCommit = true;
		mMaxDepth = 1;
		setType("stat");
	} else if (code == TrxCode::HARVESTED) {
		mMaxDepth = 1;
	}

	initializeCommonSceneObject("src", src);
	initializeCommonSceneObject("dst", dst);

	// If either player is being debugged set this transaction to debug
	if (checkDebug(src) || checkDebug(dst)) {
		setDebug(true);
	}

	mContext["file"] = shortFilename(file);
	mContext["function"] = function;
	mContext["line"] = line;
	mContext["ref"] = getVersion();
	mContext["@fmt"] = TRXLOG_FORMAT_VERSION;

	auto currentThread = Thread::getCurrentThread();

	if (currentThread != nullptr) {
		mContext["thread"] = currentThread->getName();
	}

	addStateObjectMetadata("src", src);
	addStateObjectMetadata("dst", dst);
}

void TransactionLog::initializeCreditsCommon(SceneObject* src, SceneObject* dst, TrxCode code, int amount, bool isCash) {
	mTransaction["isCash"] = isCash;
	mTransaction["amount"] = amount;

	addStateCreditBalances("src", "Before", src);
	addStateCreditBalances("dst", "Before", dst);
}

void TransactionLog::addStateObjectMetadata(const String& baseKeyName, SceneObject* obj) {
	if (obj == nullptr) {
		return;
	}

	auto stringIdFile = obj->getObjectNameStringIdFile();
	auto stringIdName = obj->getObjectNameStringIdName();

	if (!stringIdFile.isEmpty() || !stringIdName.isEmpty()) {
		addState(baseKeyName + "ObjectName", stringIdFile + ":" + stringIdName);
	}

	addState(baseKeyName + "Class", obj->_getClassName());

	auto tano = obj->asTangibleObject();

	if (tano != nullptr) {
		auto serial = tano->getSerialNumber();

		if (!serial.isEmpty()) {
			addState(baseKeyName + "ObjectSerial", tano->getSerialNumber());
		}

		if (tano->hasAntiDecayKit()) {
			addState(baseKeyName + "AntiDecayKitObjectID", tano->getAntiDecayKitObjectID());
		}
	}

	auto tmpl = obj->getObjectTemplate();

	if (tmpl != nullptr) {
		auto file = tmpl->getTemplateFileName();

		if (!file.isEmpty()) {
			addState(baseKeyName + "Template", tmpl->getTemplateFileName());
		}
	}

	addWorldPosition(baseKeyName, obj);
}

void TransactionLog::addWorldPosition(String context, SceneObject* scno) {
	if (scno == nullptr || !mWorldPositionContext.isEmpty()) {
		return;
	}

	auto root = scno->getRootParentUnsafe();

	if (root == nullptr || !root->isBuildingObject()) {
		root = scno;
	}

	auto zone = root->getZone();

	if (zone != nullptr) {
		mWorldPositionContext = context;
		mWorldPosition = root->getWorldPosition();
		mZoneName = zone->getZoneName();
		return;
	}
}

void TransactionLog::addStateCreditBalances(const String& key, const String& when) {
	static const auto creditObjectDatabaseID = ObjectDatabaseManager::instance()->getDatabaseID("credits");

	auto server = ServerCore::getZoneServer();

	if (server == nullptr) {
		errorMessage() << "addStateCreditBalances failed to getZoneServer";
		return;
	}

	auto oid = mTransaction[key].get<uint64>();
	auto tableID = (uint16)(oid >> 48);

	// Handle CreditObject special case
	if (tableID == creditObjectDatabaseID) {
		auto creditObject = Core::getObjectBroker()->lookUp(oid).castTo<CreditObject*>();

		if (creditObject != nullptr) {
			Locker lock(creditObject);
			auto owner = creditObject->getOwner().get();
			addState(key + "CreditObjectOwner", owner != nullptr ? owner->getObjectID() : creditObject->getOwnerObjectID());
			addState(key + "Bank" + when, creditObject->getBankCredits());
			addState(key + "Cash" + when, creditObject->getCashCredits());
		}

		return;
	}

	auto obj = server->getObject(oid);

	if (obj != nullptr) {
		addStateCreditBalances(key, when, obj);
	}
}

void TransactionLog::addStateCreditBalances(const String& who, const String& when, SceneObject* obj) {
	if (obj == nullptr) {
		return;
	}

	if (obj->isVendor()) {
		auto data = obj->getDataObjectComponent();

		if (data == nullptr || data->get() == nullptr || !data->get()->isVendorData()) {
			return;
		}

		auto vendorData = dynamic_cast<VendorDataComponent*>(data->get());

		if (vendorData == nullptr) {
			return;
		}

		addState(who + "Maintenance" + when, vendorData->getMaint());
		return;
	}

	if (obj->isStructureObject()) {
		auto sto = dynamic_cast<StructureObject*>(obj);

		if (sto == nullptr) {
			return;
		}

		addState(who + "Maintenance" + when, sto->getSurplusMaintenance());
		addState(who + "Power" + when, sto->getSurplusPower());
		return;
	}

	if (obj->isDeedObject()) {
		auto deed = dynamic_cast<StructureDeed*>(obj);

		if (deed != nullptr) {
			addState(who + "Maintenance" + when, deed->getSurplusMaintenance());
			addState(who + "Power" + when, deed->getSurplusPower());
		}

		return;
	}

	auto lto = dynamic_cast<LotteryDroid*>(obj);

	if (lto != nullptr) {
		addState(who + "Pool" + when, lto->getCreditPool());
		return;
	}

	if (obj->isCreatureObject()) {
		auto creo = dynamic_cast<CreatureObject*>(obj);

		if (creo == nullptr) {
			return;
		}

		Locker lock(creo);

		auto crobj = creo->getCreditObject();

		if (crobj == nullptr) {
			return;
		}

		Locker crLock(crobj);

		addState(who + "Bank" + when, crobj->getBankCredits());
		addState(who + "Cash" + when, crobj->getCashCredits());
		return;
	}
}

const String TransactionLog::composeLogEntry() const {
	JSONSerializationType logEntry = JSONSerializationType::object();

	logEntry["@timestamp"] = mStartTime.getFormattedTimeFull().toCharArray();
	logEntry["context"] = mContext;
	logEntry["state"] = mState;
	logEntry["transaction"] = mTransaction;

	return logEntry.dump();
}

void TransactionLog::writeLog() {
	auto static trxLog = [] () {
		Logger log("TransactionLog");

		log.setGlobalLogging(false);
		log.setFileLogger("log/transaction.log", true, ConfigManager::instance()->getRotateLogAtStart());
		log.setLogLevelToFile(false);
		log.setLogToConsole(false);
		log.setRotateLogSizeMB(ConfigManager::instance()->getInt("Core3.TransactionLog.RotateLogSizeMB", ConfigManager::instance()->getRotateLogSizeMB()));
		log.setLogLevel(ConfigManager::instance()->getLogLevel("Core3.TransactionLog.LogLevel", Logger::DEBUG));
		log.setLoggerCallback([log](Logger::LogLevel level, const char* msg) -> int {
			static Mutex logWriteMutext;
			auto logFile = log.getFileLogger();
			StringBuffer logLine;

			logLine << msg << endl;

			Locker guard(&logWriteMutext);
			(*logFile) << logLine;
			logFile->flush();

			return Logger::DONTLOG;
		});

		return log;
	} ();

	if (mLogged) {
		auto trace = StackTrace();
		getLogger().error() << "Duplicate write for trx " << *this << endl << "STACK: " << trace.toStringData();
		return;
	}

	mLogged = true;

	if (mError.length() > 0) {
		mState["errorMessage"] = mError.toString();
	}

	if (mAborted) {
		mState["aborted"] = mAborted;
	}

	if (!mWorldPositionContext.isEmpty()) {
		addState("worldPositionContext", mWorldPositionContext);
		addState("worldPositionX", (int)mWorldPosition.getX());
		addState("worldPositionZ", (int)mWorldPosition.getZ());
		addState("worldPositionY", (int)mWorldPosition.getY());
		addState("zone", mZoneName);
	}

	mState["relatedObjects"] = mRelatedObjects;

	JSONSerializationType children = JSONSerializationType::object();

	for (int i = 0; i < mChildObjects.size(); ++i) {
		auto oid = mChildObjects.get(i);
		auto scno = Core::getObjectBroker()->lookUp(oid).castTo<SceneObject*>();

		if (scno == nullptr) {
			getLogger().error() << "Failed to find object for child " << oid;
			children[String::valueOf(oid)] = "@error";
			continue;
		}

		if (scno->isContainerObject() && !scno->isAntiDecayKitObject() && !scno->isRecycleToolObject()) {
			continue;
		}

		if (scno->isMissionObject() || scno->isTerminal() || scno->isCellObject() || scno->isSignObject()) {
			continue;
		}

		auto objName = "@" + scno->getObjectNameStringIdFile() + ":" + scno->getObjectNameStringIdName();

		if (objName == "@:") {
			objName = "@c:" + scno->_getClassName();
		}

		children[String::valueOf(oid)] = objName;
	}

	mState["relatedChildren"] = children;

	if (mDebug) {
		mState["debug"] = mDebug;
	}

	if (isVerbose()) {
		mState["verbose"] = true;
	}

	trxLog.info() << composeLogEntry();
}

SceneObject* TransactionLog::getTrxParticipant(SceneObject* obj, SceneObject* defaultValue) {
	auto owner = obj;

	while (owner != nullptr && (owner->isContainerObject() || owner->isCellObject() || owner->isDataPad())) {
		owner = owner->getParent().get();

		if (owner == obj) {
			owner = nullptr;
			break;
		}
	}

	if (owner == nullptr) {
		owner = defaultValue;
	}

	return owner;
}

const String& TransactionLog::getVersion() {
	auto static version = []() {
		auto revision = ConfigManager::instance()->getRevision();
		auto i = revision.indexOf(" ");

		if (i != -1) {
			return revision.subString(1, i);
		}

		return revision;
	}();

	return version;
}

#define CONFIG_CACHED_BOOL_GETTER(name, defaultValue)                                                      \
	bool TransactionLog::get##name() {                                                                     \
		static Mutex mutex;                                                                                \
		Locker guard(&mutex);                                                                              \
		static bool cachedValue = defaultValue;                                                            \
		static uint64 cachedVersion = 0;                                                                   \
		auto configVersion = ConfigManager::instance()->getConfigVersion();                                \
		if (configVersion > cachedVersion) {                                                               \
			cachedVersion = configVersion;                                                                 \
			cachedValue = ConfigManager::instance()->getBool("Core3.TransactionLog." #name, defaultValue); \
		}                                                                                                  \
		return cachedValue;                                                                                \
	}

CONFIG_CACHED_BOOL_GETTER(Enabled, false)

CONFIG_CACHED_BOOL_GETTER(AsyncExport, false)

CONFIG_CACHED_BOOL_GETTER(Verbose, false)

CONFIG_CACHED_BOOL_GETTER(PruneCreatureObjects, true)

CONFIG_CACHED_BOOL_GETTER(PruneCraftedComponents, true)

CONFIG_CACHED_BOOL_GETTER(CheckPlayerDebug, true)

const String TransactionLog::trxCodeToString(TrxCode code) {
	// Regenerate case's with:
	// perl -ne 'if(/enum TrxCode|^\x7d/) { $go=!$go; } elsif($go && m/.*?(\S+)\s*=\s*(\d+).*?\s(.*)/) { printf(qq(\tcase TrxCode::%-25s return %-28s %s\n), $1
	// . ":", q(") . lc $1 . q(";), $3); }' MMOCoreORB/src/server/zone/objects/transaction/TransactionLog.h > /tmp/casecode

	// clang-format off
	switch(code) {
	case TrxCode::UNKNOWN:                  return "unknown";                   // Unknown
	case TrxCode::CHARACTERCREATION:        return "charactercreation";         // Character Creation
	case TrxCode::NEWBIETUTORIAL:           return "newbietutorial";            // Newbie Tutorial
	case TrxCode::CUSTOMERSERVICE:          return "customerservice";           // Customer Service
	case TrxCode::MISSIONSYSTEMDYNAMIC:     return "missionsystemdynamic";      // Dynamic Mission System
	case TrxCode::MISSIONSYSTEMPLAYER:      return "missionsystemplayer";       // Player Mission System
	case TrxCode::BOUNTYSYSTEM:             return "bountysystem";              // Bounty System
	case TrxCode::CLONINGSYSTEM:            return "cloningsystem";             // Cloning System
	case TrxCode::INSURANCESYSTEM:          return "insurancesystem";           // Insurance System
	case TrxCode::TRAVELSYSTEM:             return "travelsystem";              // the Galactic Travel Commission
	case TrxCode::SHIPPINGSYSTEM:           return "shippingsystem";            // the Galactic Shipping Commission
	case TrxCode::BAZAARSYSTEM:             return "bazaarsystem";              // the Galactic Trade Commission
	case TrxCode::DISPENSERSYSTEM:          return "dispensersystem";           // Dispenser System
	case TrxCode::SKILLTRAININGSYSTEM:      return "skilltrainingsystem";       // Skill Training Union
	case TrxCode::REBELFACTION:             return "rebelfaction";              // Rebellion
	case TrxCode::IMPERIALFACTION:          return "imperialfaction";           // the Empire
	case TrxCode::JABBASPALACE:             return "jabbaspalace";              // Jabba the Hutt
	case TrxCode::POISYSTEM:                return "poisystem";                 // POI System
	case TrxCode::CORPSEEXPIRATION:         return "corpseexpiration";          // Corpse Expiration Tracking
	case TrxCode::TESTACCOUNT:              return "testaccount";               // Testing
	case TrxCode::STRUCTUREMAINTANENCE:     return "structuremaintanence";      // Structure Maintenance
	case TrxCode::TIPSURCHARGE:             return "tipsurcharge";              // Tip Surcharge
	case TrxCode::VENDORMAINTANENCE:        return "vendormaintanence";         // Vendor Wages
	case TrxCode::NPCLOOT:                  return "npcloot";                   // NPC Loot
	case TrxCode::JUNKDEALER:               return "junkdealer";                // Junk Dealer
	case TrxCode::CANTINADRINK:             return "cantinadrink";              // Cantina Drink
	case TrxCode::BETATEST:                 return "betatest";                  // Beta Test Fund
	case TrxCode::BADGROUPCOINSPLIT:        return "badgroupcoinsplit";         // Group Split Error Account
	case TrxCode::GAMBLINGSLOTSTANDARD:     return "gamblingslotstandard";      // Standard Slot Machine Account
	case TrxCode::GAMBLINGROULETTE:         return "gamblingroulette";          // Roulette Account
	case TrxCode::GAMBLINGCARDSABACC:       return "gamblingcardsabacc";        // Sabacc Account
	case TrxCode::VEHICLEREPAIRS:           return "vehiclerepairs";            // Vehicle Repair System
	case TrxCode::RELICDEALER:              return "relicdealer";               // Relic Dealer
	case TrxCode::NEWPLAYERQUESTS:          return "newplayerquests";           // New Player Quests
	case TrxCode::FINES:                    return "fines";                     // Contraband Scanning Fines
	case TrxCode::BANK:                     return "bank";                      // bank
	// SWGEmu Specific
	case TrxCode::ACCESSFEE:                return "accessfee";                 // Access Fee
	case TrxCode::ADMINCOMMAND:             return "admincommand";              // From an admin command
	case TrxCode::ADKAPPLY:                 return "adkapply";                  // Apply ADK to an item
	case TrxCode::ADKREMOVE:                return "adkremove";                 // Remove ADK from item
	case TrxCode::APPLYATTACHMENT:          return "applyattachment";           // Apply Attachment to an item
	case TrxCode::AUCTIONADDSALE:           return "auctionaddsale";            // addSaleItem()
	case TrxCode::AUCTIONBID:               return "auctionbid";                // Auction Bid Escrow
	case TrxCode::AUCTIONEXPIRED:           return "auctionexpired";            // Never retrieved and expired
	case TrxCode::AUCTIONRETRIEVE:          return "auctionretrieve";           // retrieveItem()
	case TrxCode::CHARACTERBUILDER:         return "characterbuilder";          // Character Builder
	case TrxCode::CHARACTERDELETE:          return "characterdelete";           // Delete Character
	case TrxCode::CITYINCOMETAX:            return "cityincometax";             // City income taxes
	case TrxCode::CITYSALESTAX:             return "citysalestax";              // City Sales taxes
	case TrxCode::CITYTREASURY:             return "citytreasury";              // City Treasury
	case TrxCode::COMBATSTATS:              return "combatstats";               // Combat Stats
	case TrxCode::CRAFTINGSESSION:          return "craftingsession";           // Crafting Session
	case TrxCode::DATABASECOMMIT:           return "databasecommit";            // Database Commit
	case TrxCode::DESTROYSTRUCTURE:         return "destroystructure";          // Server destroyed structure (maintenance)
	case TrxCode::EXPERIENCE:               return "experience";                // Player experience change
	case TrxCode::EXTRACTCRATE:             return "extractcrate";              // Extract item from crate
	case TrxCode::FACTORYOPERATION:         return "factoryoperation";          // Factory operations
	case TrxCode::FISHING:                  return "fishing";                   // Fishing loot
	case TrxCode::FORAGED:                  return "foraged";                   // Foraged items
	case TrxCode::HARVESTED:                return "harvested";                 // Harvested items
	case TrxCode::IMAGEDESIGN:              return "imagedesign";               // Image Design Fees
	case TrxCode::INSTANTBUY:               return "instantbuy";                // Instant Buy
	case TrxCode::LOTTERYDROID:             return "lotterydroid";              // Lottery Droid
	case TrxCode::LUASCRIPT:                return "luascript";                 // LUA Script
	case TrxCode::LUALOOT:                  return "lualoot";                   // Loot from LUA Script
	case TrxCode::MINED:                    return "mined";                     // Resouces mined by installations
	case TrxCode::MISSIONCOMPLETE:          return "missioncomplete";           // Mission Completed Summary
	case TrxCode::NPCLOOTCLAIM:             return "npclootclaim";              // NPC Loot Claimed
	case TrxCode::PERMISSIONLIST:           return "permissionlist";            // Permission List Changes
	case TrxCode::PLAYERMISCACTION:         return "playermiscaction";          // Misc player action
	case TrxCode::PLAYERTIP:                return "playertip";                 // sui Tip
	case TrxCode::PLAYERTRADE:              return "playertrade";               // Player Trade
	case TrxCode::PLAYERONLINE:             return "playeronline";              // Player Online
	case TrxCode::PLAYEROFFLINE:            return "playeroffline";             // Player Offline
	case TrxCode::PLAYERLINKDEAD:           return "playerlinkdead";            // Player Link Dead
	case TrxCode::PLAYERLOGGINGOUT:         return "playerloggingout";          // Player Logging Out
	case TrxCode::PLAYERDIED:               return "playerdied";                // Player Died
	case TrxCode::RECYCLED:                 return "recycled";                  // Recycled Items
	case TrxCode::SERVERDESTROYOBJECT:      return "serverdestroyobject";       // /serverDestroyObject command
	case TrxCode::SLICECONTAINER:           return "slicecontainer";            // Slicing session on a container
	case TrxCode::STRUCTUREDEED:            return "structuredeed";             // Structure deed trxs
	case TrxCode::TRANSFERITEMMISC:         return "transferitemmisc";          // /transferitemmisc command
	case TrxCode::TRANSFERSTRUCT:           return "transferstruct";            // Transfer Structure
	case TrxCode::VENDORLIFECYCLE:          return "vendorlifecycle";           // Vendor lifecycle (create/destroy)
	case TrxCode::VETERANREWARD:            return "veteranreward";             // /claimveteranreward command
	}
	// clang-format on

	StringBuffer buf;
	buf << "TrxCode(" << (int)(code) << ")";
	return buf.toString();
}
