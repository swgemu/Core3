/*
		Copyright <SWGEmu>
	See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : TransactionLog.h
 * @created     : Wed Apr 15 21:49:41 UTC 2020
 */

#pragma once

#include "engine/engine.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/credits/CreditObject.h"

enum TrxCode {
	// From string/en/money/acct_n.stf
	UNKNOWN              =  0, // Unknown
	CHARACTERCREATION    =  1, // Character Creation
	NEWBIETUTORIAL       =  2, // Newbie Tutorial
	CUSTOMERSERVICE      =  3, // Customer Service
	MISSIONSYSTEMDYNAMIC =  4, // Dynamic Mission System
	MISSIONSYSTEMPLAYER  =  5, // Player Mission System
	BOUNTYSYSTEM         =  6, // Bounty System
	CLONINGSYSTEM        =  7, // Cloning System
	INSURANCESYSTEM      =  8, // Insurance System
	TRAVELSYSTEM         =  9, // the Galactic Travel Commission
	SHIPPINGSYSTEM       = 10, // the Galactic Shipping Commission
	BAZAARSYSTEM         = 11, // the Galactic Trade Commission
	DISPENSERSYSTEM      = 12, // Dispenser System
	SKILLTRAININGSYSTEM  = 13, // Skill Training Union
	REBELFACTION         = 14, // Rebellion
	IMPERIALFACTION      = 15, // the Empire
	JABBASPALACE         = 16, // Jabba the Hutt
	POISYSTEM            = 17, // POI System
	CORPSEEXPIRATION     = 18, // Corpse Expiration Tracking
	TESTACCOUNT          = 19, // Testing
	STRUCTUREMAINTANENCE = 20, // Structure Maintenance
	TIPSURCHARGE         = 21, // Tip Surcharge
	VENDORMAINTANENCE    = 22, // Vendor Wages
	NPCLOOT              = 23, // NPC Loot
	JUNKDEALER           = 24, // Junk Dealer
	CANTINADRINK         = 25, // Cantina Drink
	BETATEST             = 26, // Beta Test Fund
	BADGROUPCOINSPLIT    = 27, // Group Split Error Account
	GAMBLINGSLOTSTANDARD = 28, // Standard Slot Machine Account
	GAMBLINGROULETTE     = 29, // Roulette Account
	GAMBLINGCARDSABACC   = 30, // Sabacc Account
	VEHICLEREPAIRS       = 31, // Vehicle Repair System
	RELICDEALER          = 32, // Relic Dealer
	NEWPLAYERQUESTS      = 33, // New Player Quests
	FINES                = 34, // Contraband Scanning Fines
	BANK                 = 35, // bank

	// SWGEmu Specific Codes
	ACCESSFEE            = 100, // Access Fee
	AUCTIONADDSALE,             // addSaleItem()
	AUCTIONBID,                 // Auction Bid Escrow
	AUCTIONRETRIEVE,            // retrieveItem()
	CHARACTERBUILDER,           // Character Builder
	CITYINCOMETAX,              // City income taxes
	CITYSALESTAX,               // City Sales taxes
	CITYTREASURY,               // City Treasury
	IMAGEDESIGN,                // Image Design Fees
	INSTANTBUY,                 // Instant Buy
	LOTTERYDROID,               // Lottery Droid
	LUASCRIPT,                  // LUA Script
	NPCLOOTCLAIM,               // NPC Loot Claimed
	PLAYERTIP,                  // sui Tip
	PLAYERTRADE,                // Player Trade
	TRANSFERITEMMISC,           // /transferitemmisc command
	TRANSFERSTRUCT,             // Transfer Structure
	VETERANREWARD,              // /claimveteranreward command
};

class TransactionLog {
	Time mStartTime;
	bool mEnabled = true;
	bool mAutoCommit = true;
	bool mDebug = false;
	bool mCommitted = false;
	bool mAborted = false;
	bool mExportRelated = false;
	StringBuffer mError;
	Vector<uint64> mRelatedObjects;
	SortedVector<uint64> mChildObjects;
	JSONSerializationType mState = JSONSerializationType::object();
	JSONSerializationType mContext = JSONSerializationType::object();
	JSONSerializationType mTransaction = JSONSerializationType::object();

public:
	TransactionLog(SceneObject* src, SceneObject* dst, SceneObject* subject, TrxCode code, bool exportSubject = false,
		const char* file = __builtin_FILE(), const char* function = __builtin_FUNCTION(), int line = __builtin_LINE());

	TransactionLog(SceneObject* src, SceneObject* dst, TrxCode code, int amount, bool isCash = true,
		const char* file = __builtin_FILE(), const char* function = __builtin_FUNCTION(), int line = __builtin_LINE());

	TransactionLog(TrxCode code, SceneObject* dst, SceneObject* subject, bool exportSubject = false,
		const char* file = __builtin_FILE(), const char* function = __builtin_FUNCTION(), int line = __builtin_LINE())
		: TransactionLog((SceneObject*)nullptr, dst, subject, code, exportSubject)
	{
	}

	TransactionLog(SceneObject* src, TrxCode code, uint amount, bool isCash = true,
		const char* file = __builtin_FILE(), const char* function = __builtin_FUNCTION(), int line = __builtin_LINE())
		: TransactionLog(src, nullptr, code, amount, isCash, file, function, line)
	{
	}

	TransactionLog(TrxCode code, SceneObject* dst, uint amount, bool isCash = true,
		const char* file = __builtin_FILE(), const char* function = __builtin_FUNCTION(), int line = __builtin_LINE())
		: TransactionLog((SceneObject*)nullptr, dst, code, amount, isCash, file, function, line)
	{
	}

	TransactionLog(uint64 srcObjectID, TrxCode code, uint amount, bool isCash = true,
		const char* file = __builtin_FILE(), const char* function = __builtin_FUNCTION(), int line = __builtin_LINE());

	TransactionLog(CreditObject* creditObject, SceneObject* dst, TrxCode code, int amount, bool isCash = true,
		const char* file = __builtin_FILE(), const char* function = __builtin_FUNCTION(), int line = __builtin_LINE());

	~TransactionLog();

	TransactionLog(const TransactionLog& rhs) {
		*this = rhs;
	}

	TransactionLog& operator=(const TransactionLog& rhs) {
		if (this == &rhs) {
			return *this;
		}

		mStartTime = rhs.mStartTime;
		mEnabled = rhs.mEnabled;
		mDebug = rhs.mDebug;
		mCommitted = rhs.mCommitted;
		mAborted = rhs.mAborted;
		mExportRelated = rhs.mExportRelated;
		mError << rhs.mError;
		mRelatedObjects = rhs.mRelatedObjects;
		mChildObjects = rhs.mChildObjects;
		mState = rhs.mState;
		mContext = rhs.mContext;
		mTransaction = rhs.mTransaction;

		return *this;
	}

	void commit();

	StringBuffer& abort();

	StringBuffer& errorMessage();

	const String getErrorMessage();

	bool isEnabled() {
		return getEnabled() && mEnabled;
	}

	void setEnabled(bool enabled) {
		mEnabled = enabled;
	}

	void setWriteLog(bool enabled) {
		mEnabled = enabled;
	}

	bool isCreditTransaction();

	void setExportRelatedObjects(bool exportRelated) {
		mExportRelated = exportRelated;
	}

	bool getExportRealtedObjects() {
		return mExportRelated;
	}

	static const String getTrxGroup() {
		return "G" + getNewTrxID().toUpperCase();
	}

	const String getTrxGroup(TransactionLog& trx) {
		if (mTransaction["trxGroup"].is_null()) {
			mTransaction["trxGroup"] = getTrxGroup();
		}

		return String(mTransaction["trxGroup"].get<std::string>());
	}

	void setTrxGroup(const String& groupTrxId) {
		mTransaction["trxGroup"] = groupTrxId;
	}

	void setTrxGroup(const TransactionLog& leadTrx) {
		mTransaction["trxGroup"] = leadTrx.getTrxGroup();
	}

	void setAutoCommit(bool autocommit) {
		mAutoCommit = autocommit;
	}

	bool getAutoCommit() {
		return mAutoCommit;
	}

	void setDebug(bool debug) {
		mDebug = debug;
	}

	bool getDebug() {
		return mDebug;
	}

	bool isVerbose() {
		return getVerbose();
	}

	const String getTrxID() const {
		return String(mTransaction["trxId"].get<std::string>());
	}

	String toStringData() const;

	void addContextFromLua(lua_State* L);

	void addRelatedObject(uint64 oid, bool trackChildren = false);

	void addState(const String& key, const String& value);

	void addState(const String& key, float value);

	void addState(const String& key, double value);

	void addState(const String& key, int value);

	void addState(const String& key, uint value);

	void addState(const String& key, int64 value);

	void addState(const String& key, uint64 value);

	static const String getNewTrxID();

	static bool getVerbose();

	static SceneObject* getTrxParticipant(SceneObject* obj, SceneObject* defaultValue);

private:
	static AtomicInteger exportBacklog;

	void catchAndLog(const char* functioName, Function<void()> function);

	static Logger& getLogger();

	static const String& getVersion();

	static const TaskQueue& getCustomQueue();

	static bool getAsyncExport();

	static bool getEnabled();

	static bool getPruneCreatureObjects();

	static bool getPruneCraftedComponents();

	static bool getCheckPlayerDebug();

	bool checkDebug(SceneObject* obj);

	const String shortFilename(const char* file);

	void initializeCommon(SceneObject* src, SceneObject* dst, TrxCode code,
			const char* file = __builtin_FILE(), const char* function = __builtin_FUNCTION(), int line = __builtin_LINE());

	void initializeCommonSceneObject(const String& key, SceneObject* obj);

	void initializeCreditsCommon(SceneObject* src, SceneObject* dst, TrxCode code, int amount, bool isCash);

	void addStateObjectName(const String& key, SceneObject* obj);

	void addStateCreditBalances(const String& key, const String& when);

	void addStateCreditBalances(const String& who, const String& when, SceneObject* obj);

	const String composeLogEntry() const;

	void writeLog();

	void exportRelated();

	static const String trxCodeToString(TrxCode code);
};
