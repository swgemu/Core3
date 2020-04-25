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

TransactionLog::TransactionLog(SceneObject* src, SceneObject* dst, SceneObject* subject, TrxCode code, bool exportSubject,
	const char* file, const char* function, int line)
{
	if (!isEnabled()) {
		return;
	}

	initializeCommon(src, dst, code, file, function, line);

	mContext["type"] = "transfer";

	if (subject != nullptr) {
		mTransaction["subject"] = subject->getObjectID();

		if (exportSubject || mDebug) {
			addRelatedObject(subject->getObjectID());
		}

		addStateCreditBalances("subject", "Before", subject);
		addStateObjectName("subjectObjectName", subject);
		addState("subjectClass", subject->_getClassName());
	} else {
		mTransaction["subject"] = 0;
	}
}

TransactionLog::TransactionLog(SceneObject* src, SceneObject* dst, TrxCode code, int amount, bool isCash,
	const char* file, const char* function, int line)
{
	if (!isEnabled()) {
		return;
	}

	initializeCommon(src, dst, code, file, function, line);
	initializeCreditsCommon(src, dst, code, amount, isCash);
}

TransactionLog::TransactionLog(uint64 srcObjectID, TrxCode code, uint amount, bool isCash,
	const char* file, const char* function, int line)
{
	if (!isEnabled()) {
		return;
	}

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

TransactionLog::TransactionLog(CreditObject* creditObject, SceneObject* dst, TrxCode code, int amount, bool isCash,
	const char* file, const char* function, int line)
{
	if (!isEnabled()) {
		return;
	}

	initializeCommon(nullptr, dst, code, file, function, line);
	initializeCreditsCommon(nullptr, dst, code, amount, isCash);

	mTransaction["src"] = creditObject->_getObjectID();

	addStateCreditBalances("src", "Before");
}

TransactionLog::~TransactionLog() {
	if (!isEnabled()) {
		return;
	}

	if (mAborted) {
		writeLog();
		return;
	}

	if (!mCommitted) {
		if (mAutoCommit) {
			commit();
		} else {
			abort() << "Transaction ended without commit!";
			writeLog();
		}
	}
}

void TransactionLog::commit() {
	if (!isEnabled()) {
		return;
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
			// Force a copy of trx because dtor will destroy (this) before we're done
			Core::getTaskManager()->executeTask([trx = *this] {
				auto tp = const_cast<TransactionLog*>(&trx);
				tp->exportRelated();
				tp->writeLog();
			}, "TransactionLogExport", "slowQueue");
			return;
		}
	}

	mTransaction["msCommit"] = mStartTime.miliDifference();
	writeLog();
}

void TransactionLog::addRelatedObject(uint64 oid, bool trackChildren) {
	if (!isEnabled() || oid == 0) {
		return;
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

	scno->getChildrenRecursive(mChildObjects, 50, true, true);
}

void TransactionLog::exportRelated() {
	if (mRelatedObjects.size() <= 0) {
		return;
	}

	JSONSerializationType exportMap = JSONSerializationType::object();
	auto server = ServerCore::getZoneServer();

	if (server == nullptr) {
		errorMessage() << "unable to getZoneServer in exportRelated";
		return;
	}

	Time exportStartTime;
	auto logMsg = "TransactionLog trxId: " + getTrxID();

	for (int i = 0;i < mRelatedObjects.size(); ++i) {
		auto oid = mRelatedObjects.get(i);
		auto obj = server->getObject(oid);

		if (obj == nullptr) {
			errorMessage() << "failed to getObject(" << oid << ")";
			continue;
		}

		auto pruneCreo = getPruneCreatureObjects() && obj->isStructureObject();

		exportMap[String::valueOf(oid)] = obj->exportJSON(logMsg, 50, pruneCreo, getPruneCraftedComponents());
	}

	mState["exports"] = exportMap;
	mTransaction["msExport"] = mStartTime.miliDifference();
}

StringBuffer& TransactionLog::abort() {
	mAborted = true;
	mTransaction["aborted"] = mAborted;

	if (!mError.length()) {
		mError << "; ";
	}

	mError << "Transaction Aborted: ";
	return mError;
}

StringBuffer& TransactionLog::errorMessage() {
	if (!mError.length()) {
		mError << "; ";
	}

	return mError;
}

const String TransactionLog::getErrorMessage() {
	return mError.toString();
}

bool TransactionLog::isCreditTransaction() {
	return mContext["type"] == "credits";
}

String TransactionLog::toStringData() const {
	return composeLogEntry();
}

void TransactionLog::addContextFromLua(lua_State* L) {
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

void TransactionLog::addState(const String& key, const String& value) {
	catchAndLog(__FUNCTION__, [&]() -> void {
		mState[key] = value;
	});
}

void TransactionLog::addState(const String& key, float value) {
	catchAndLog(__FUNCTION__, [&]() -> void {
		mState[key] = value;
	});
}

void TransactionLog::addState(const String& key, double value) {
	catchAndLog(__FUNCTION__, [&]() -> void {
		mState[key] = value;
	});
}

void TransactionLog::addState(const String& key, int value) {
	catchAndLog(__FUNCTION__, [&]() -> void {
		mState[key] = value;
	});
}

void TransactionLog::addState(const String& key, uint value) {
	catchAndLog(__FUNCTION__, [&]() -> void {
		mState[key] = value;
	});
}

void TransactionLog::addState(const String& key, int64 value) {
	catchAndLog(__FUNCTION__, [&]() -> void {
		mState[key] = value;
	});
}

void TransactionLog::addState(const String& key, uint64 value) {
	catchAndLog(__FUNCTION__, [&]() -> void {
		mState[key] = value;
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
	} catch(...) {
#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
		errorMessage() << __FILE__ << ":" << functioName << " unexpected exception: " << __cxxabiv1::__cxa_current_exception_type()->name();
#else
		errorMessage() << __FILE__ << ":" << functioName << " unexpected exception";
#endif
		Logger::console.error() << errorMessage() << " " << *this;
	}
}

Logger& TransactionLog::getLogger() {
	static AtomicBoolean setup{false};
	static Logger log;
	static Mutex mutex;

	if (!setup.get()) {
		setup.set(true);

		auto logLevel = ConfigManager::instance()->getInt("Core3.TransactionLog.LogLevel", (int)Logger::DEBUG);

		log.setLoggingName("TransactionLog");
		log.setGlobalLogging(false);
		log.setFileLogger("log/transaction.log", true, ConfigManager::instance()->getRotateLogAtStart());
		log.setLogLevelToFile(false);
		log.setLogToConsole(false);
		log.setRotateLogSizeMB(ConfigManager::instance()->getInt("Core3.TransactionLog.RotateLogSizeMB", ConfigManager::instance()->getRotateLogSizeMB()));
		log.setLogLevel(static_cast<Logger::LogLevel>(logLevel));
		log.setLoggerCallback([&] (Logger::LogLevel level, const char* msg) -> int {
				Locker guard(&mutex);
				auto logFile = log.getFileLogger();
				StringBuffer logLine;
				logLine << msg << endl;
				(*logFile) << logLine;logLine;
				logFile->flush();
				return Logger::DONTLOG;
		});
	}

	return log;
};

bool TransactionLog::checkDebug(SceneObject* obj) {
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

const String TransactionLog::shortFilename(const char* file) {
	auto ep = file;

	while (*ep) {
		ep++;
	}

	for (auto cp = file;cp < ep - 8;cp++) {
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
		addStateObjectName(key + "ObjectName", obj);
		return;
	}
	
	auto player = creo->getPlayerObject();

	if (player != nullptr) {
		mTransaction[key + "AccountId"] = player->getAccountID();
		return;
	}

	addStateObjectName(key + "ObjectName", obj);
	addState(key + "Class", obj->_getClassName());
}

void TransactionLog::initializeCommon(SceneObject* src, SceneObject* dst, TrxCode code,
		const char* file, const char* function, int line) {

	mTransaction["trxId"] = getNewTrxID();

	mTransaction["code"] = trxCodeToString(code);

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

	auto currentThread = Thread::getCurrentThread();

	if (currentThread != nullptr) {
		mContext["thread"] = currentThread->getName();
	}

	auto scno = src != nullptr ? src : dst;

	if (scno != nullptr) {
		auto pos = scno->getWorldPosition();
		addState("worldPositionX", (int)pos.getX());
		addState("worldPositionZ", (int)pos.getZ());
		addState("worldPositionY", (int)pos.getY());

		auto zone = scno->getZone();
		addState("zone", zone != nullptr ? zone->getZoneName() : "null");
	}
}

void TransactionLog::initializeCreditsCommon(SceneObject* src, SceneObject* dst, TrxCode code, int amount, bool isCash) {
	mContext["type"] = "credits";
	mTransaction["isCash"] = isCash;
	mTransaction["amount"] = amount;

	addStateCreditBalances("src", "Before", src);
	addStateCreditBalances("dst", "Before", dst);
}

void TransactionLog::addStateObjectName(const String& key, SceneObject* obj) {
	if (obj != nullptr) {
		addState(key, obj->getObjectNameStringIdFile() + "." + obj->getObjectNameStringIdName());
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
		Locker lock(obj);
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

	if (mError.length() > 0) {
		logEntry["error"] = mError.toString();
	}

	return logEntry.dump();
}

void TransactionLog::writeLog() {
	mState["relatedObjects"] = mRelatedObjects;

	JSONSerializationType children = JSONSerializationType::object();

	for (int i = 0;i < mChildObjects.size(); ++i) {
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

		auto objName = scno->getObjectNameStringIdFile() + "." + scno->getObjectNameStringIdName();

		if (objName == ".") {
			objName = scno->_getClassName();
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

	getLogger().info() << composeLogEntry();
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
	static String version;

	if (version.isEmpty()) {
		auto revision = ConfigManager::instance()->getRevision();
		auto i = revision.indexOf(" ");

		if (i != -1) {
			version = revision.subString(1, i);
		} else {
			version = revision;
		}
	}

	return version;
}

#define CONFIG_CACHED_BOOL_GETTER(name, defaultValue) \
	bool TransactionLog::get ##name () { \
		static Mutex mutex; \
		Locker guard(&mutex); \
		static bool cachedValue = defaultValue; \
		static uint64 cachedVersion = 0; \
		auto configVersion = ConfigManager::instance()->getConfigVersion(); \
		if (configVersion > cachedVersion) { \
			cachedVersion = configVersion; \
			cachedValue = ConfigManager::instance()->getBool("Core3.TransactionLog." #name, defaultValue); \
		} \
		return cachedValue; \
	}

CONFIG_CACHED_BOOL_GETTER(Enabled, false)

CONFIG_CACHED_BOOL_GETTER(AsyncExport, false)

CONFIG_CACHED_BOOL_GETTER(Verbose, false)

CONFIG_CACHED_BOOL_GETTER(PruneCreatureObjects, true)

CONFIG_CACHED_BOOL_GETTER(PruneCraftedComponents, true)

CONFIG_CACHED_BOOL_GETTER(CheckPlayerDebug, true)

const String TransactionLog::trxCodeToString(TrxCode code) {
	switch(code) {
	case  0: return "unknown";             // Unknown
	case  1: return "charactercreation";   // Character Creation   
	case  2: return "newbietutorial";      // Newbie Tutorial   
	case  3: return "customerservice";     // Customer Service   
	case  4: return "missionsystemdynamic";// Dynamic Mission System  
	case  5: return "missionsystemplayer"; // Player Mission System  
	case  6: return "bountysystem";        // Bounty System   
	case  7: return "cloningsystem";       // Cloning System   
	case  8: return "insurancesystem";     // Insurance System   
	case  9: return "travelsystem";        // the Galactic Travel Commission 
	case 10: return "shippingsystem";      // the Galactic Shipping Commission 
	case 11: return "bazaarsystem";        // the Galactic Trade Commission 
	case 12: return "dispensersystem";     // Dispenser System   
	case 13: return "skilltrainingsystem"; // Skill Training Union  
	case 14: return "rebelfaction";        // Rebellion    
	case 15: return "imperialfaction";     // the Empire   
	case 16: return "jabbaspalace";        // Jabba the Hutt  
	case 17: return "poisystem";           // POI System   
	case 18: return "corpseexpiration";    // Corpse Expiration Tracking  
	case 19: return "testaccount";         // Testing    
	case 20: return "structuremaintanence";// Structure Maintenance   
	case 21: return "tipsurcharge";        // Tip Surcharge   
	case 22: return "vendormaintanence";   // Vendor Wages   
	case 23: return "npcloot";             // NPC Loot   
	case 24: return "junkdealer";          // Junk Dealer   
	case 25: return "cantinadrink";        // Cantina Drink   
	case 26: return "betatest";            // Beta Test Fund  
	case 27: return "badgroupcoinsplit";   // Group Split Error Account 
	case 28: return "gamblingslotstandard";// Standard Slot Machine Account 
	case 29: return "gamblingroulette";    // Roulette Account   
	case 30: return "gamblingcardsabacc";  // Sabacc Account   
	case 31: return "vehiclerepairs";      // Vehicle Repair System  
	case 32: return "relicdealer";         // Relic Dealer   
	case 33: return "newplayerquests";     // New Player Quests  
	case 34: return "fines";               // Contraband Scanning Fines  
	case 35: return "bank";                // bank    

	// SWGEmu Specific Codes
	case 100: return "transferstruct";     // Transfer Structure
	case 101: return "playertip";          // Player tip
	case 102: return "cityincometax";      // City Income Tax
	case 104: return "characterbuilder";   // Character Builder
	case 105: return "citytreasury";       // City Treasury
	case 106: return "auctionsalesfee";    // Auction Sales Fee
	case 107: return "instantbuy";         // Instant Buy
	case 108: return "citysalestax";       // City Sales Tax
	case 109: return "playertrade";        // Player Trade
	case 110: return "accessfee";          // Access Fee
	case 111: return "luascript";          // LUA Script
	case 112: return "lotterydroid";       // Lottery Droid
	case 113: return "auctionbid";         // Auction Bid Escrow
	case 114: return "npclootclaim";       // NPC Loot Claimed
	case 115: return "imagedesign";        // Image Design Fees
	case 116: return "transferitemmisc";   // /transferitemmisc command
	case 117: return "veteranreward";      // /claimveteranreward command
	}

	StringBuffer buf;
	buf << "TrxCode(" << (int)(code) << ")";
	return buf.toString();
}
