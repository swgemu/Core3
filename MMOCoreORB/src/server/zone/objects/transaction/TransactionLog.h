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

// clang-format off
enum class TrxCode {
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
	ADMINCOMMAND,               // From an admin command
	ADKAPPLY,                   // Apply and ADK to item
	ADKREMOVE,                  // Remove ADK from item
	APPLYATTACHMENT,            // Apply Attachment to item
	AUCTIONADDSALE,             // addSaleItem()
	AUCTIONBID,                 // Auction Bid Escrow
	AUCTIONEXPIRED,             // Never retrieved and expired
	AUCTIONRETRIEVE,            // retrieveItem()
	CHARACTERBUILDER,           // Character Builder
	CHARACTERDELETE,            // Delete Character
	CITYINCOMETAX,              // City income taxes
	CITYSALESTAX,               // City Sales taxes
	CITYTREASURY,               // City Treasury
	COMBATSTATS,                // Combat Stats
	CRAFTINGSESSION,            // Crafting Session
	DATABASECOMMIT,             // Database Commit
	DESTROYSTRUCTURE,           // Structure destroyed by system (maintenance etc)
	EXPERIENCE,                 // Player experience change
	EXTRACTCRATE,               // Extract item from crate
	FACTORYOPERATION,           // Factory operations
	FISHING,                    // Fishing Loot
	FORAGED,                    // Foraged items
	HARVESTED,                  // Harvested items
	IMAGEDESIGN,                // Image Design Fees
	INSTANTBUY,                 // Instant Buy
	LOTTERYDROID,               // Lottery Droid
	LUASCRIPT,                  // LUA Script
	LUALOOT,                    // Loot from LUA Scripts
	MINED,                      // Resouces mined by installations
	MISSIONCOMPLETE,            // Mission Completed Summary
	NPCLOOTCLAIM,               // NPC Loot Claimed
	PERMISSIONLIST,             // Permission List changes
	PLAYERMISCACTION,           // Misc player action
	PLAYERTIP,                  // sui Tip
	PLAYERTRADE,                // Player Trade
	PLAYERDIED,                 // Player Died
	PLAYERLINKDEAD,             // Player Link Dead
	PLAYERLOGGINGOUT,           // Player Logging Out
	PLAYEROFFLINE,              // Player Offline
	PLAYERONLINE,               // Player Online
	RECYCLED,                   // Recycled Items
	SERVERDESTROYOBJECT,        // /serverDestroyObject command
	SLICECONTAINER,             // Slicing session on a container
	STRUCTUREDEED,              // Structure deed trxs
	TRANSFERITEMMISC,           // /transferitemmisc command
	TRANSFERSTRUCT,             // Transfer Structure
	VENDORLIFECYCLE,            // Vendor lifecycle (create/destroy)
	VETERANREWARD,              // /claimveteranreward command
};
// clang-format on

#if defined(__clang__)
#if __has_builtin(__builtin_FILE)
#define use_builtin_FILE 1
#else
#define use_builtin_FILE 0
#endif
#else
#if defined(__GNUC__) || defined(__GNUG__)
#define use_builtin_FILE 1
#endif
#endif

#if use_builtin_FILE
#define CAPTURE_CALLER_DECLARE const char* file = __builtin_FILE(), const char* function = __builtin_FUNCTION(), int line = __builtin_LINE()
#else
#define CAPTURE_CALLER_DECLARE const char* file = "unknown", const char* function = "unknown", int line = 0
#endif
#define CAPTURE_CALLER_ARGS const char* file, const char* function, int line

class TransactionLog {
	Time mStartTime;
	bool mEnabled = true;
	bool mAutoCommit = true;
	bool mDebug = false;
	bool mCommitted = false;
	bool mAborted = false;
	bool mExportRelated = false;
	bool mLogged = false;
	int mMaxDepth = 4;
	StringBuffer mError;
	Vector3 mWorldPosition;
	String mZoneName;
	String mWorldPositionContext;
	Vector<uint64> mRelatedObjects;
	SortedVector<uint64> mChildObjects;
	JSONSerializationType mState = JSONSerializationType::object();
	JSONSerializationType mContext = JSONSerializationType::object();
	JSONSerializationType mTransaction = JSONSerializationType::object();

public:
	TransactionLog(SceneObject* src, SceneObject* dst, SceneObject* subject, TrxCode code, bool exportSubject = false, CAPTURE_CALLER_DECLARE);

	TransactionLog(SceneObject* src, SceneObject* dst, TrxCode code, int amount, bool isCash = true, CAPTURE_CALLER_DECLARE);

	TransactionLog(SceneObject* src, SceneObject* dst, TrxCode code, bool exportSubject = false, CAPTURE_CALLER_DECLARE)
		: TransactionLog(src, dst, (SceneObject*)nullptr, code, exportSubject, file, function, line) {
			setType("apply");
	}

	TransactionLog(TrxCode code, SceneObject* dst, SceneObject* subject, bool exportSubject = false, CAPTURE_CALLER_DECLARE)
		: TransactionLog((SceneObject*)nullptr, dst, subject, code, exportSubject, file, function, line) {
	}

	TransactionLog(SceneObject* src, TrxCode code, SceneObject* subject, bool exportSubject = false, CAPTURE_CALLER_DECLARE)
		: TransactionLog(src, (SceneObject*)nullptr, subject, code, exportSubject, file, function, line) {
	}

	TransactionLog(TrxCode code, SceneObject* dst, CAPTURE_CALLER_DECLARE)
		: TransactionLog((SceneObject*)nullptr, dst, (SceneObject*)nullptr, code, false, file, function, line) {
			if (!isStat(code)) {
				mAutoCommit = false;
			}
	}

	TransactionLog(SceneObject* src, TrxCode code, uint amount, bool isCash = true, CAPTURE_CALLER_DECLARE)
		: TransactionLog(src, nullptr, code, amount, isCash, file, function, line) {
	}

	TransactionLog(TrxCode code, SceneObject* dst, uint amount, bool isCash = true, CAPTURE_CALLER_DECLARE)
		: TransactionLog((SceneObject*)nullptr, dst, code, amount, isCash, file, function, line) {
	}

	TransactionLog(uint64 srcObjectID, TrxCode code, uint amount, bool isCash = true, CAPTURE_CALLER_DECLARE);

	TransactionLog(CreditObject* creditObject, SceneObject* dst, TrxCode code, int amount, bool isCash = true, CAPTURE_CALLER_DECLARE);

	~TransactionLog();

	TransactionLog(const TransactionLog& rhs) {
		*this = rhs;
	}

	TransactionLog newChild() {
		TransactionLog child;

		// Copy limited properties from parent
		child.mEnabled = mEnabled;
		child.mDebug = mDebug;
		child.mExportRelated = mExportRelated;
		child.mWorldPosition = mWorldPosition;
		child.mWorldPositionContext = mWorldPositionContext;
		child.mZoneName = mZoneName;
		child.mContext = mContext;
		child.mTransaction["trxId"] = getNewTrxID();
		child.mTransaction["trxGroup"] = getTrxGroup();
		child.mTransaction["code"] = mTransaction["code"];
		child.mTransaction["src"] = mTransaction["src"];
		child.mTransaction["dst"] = mTransaction["dst"];
		child.mTransaction["subject"] = mTransaction["subject"];

		return child;
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
		mWorldPosition = rhs.mWorldPosition;
		mWorldPositionContext = rhs.mWorldPositionContext;
		mZoneName = rhs.mZoneName;
		mRelatedObjects = rhs.mRelatedObjects;
		mChildObjects = rhs.mChildObjects;
		mState = rhs.mState;
		mContext = rhs.mContext;
		mTransaction = rhs.mTransaction;

		return *this;
	}

	void commit(bool discardEmpty = false);

	StringBuffer& abort(CAPTURE_CALLER_DECLARE);

	StringBuffer& errorMessage();

	const String getErrorMessage();

	bool isEnabled() const {
		return getEnabled() && mEnabled;
	}

	void setEnabled(bool enabled) {
		mEnabled = enabled;
	}

	void setWriteLog(bool enabled) {
		mEnabled = enabled;
	}

	void discard() {
		mEnabled = false;
	}

	bool isCreditTransaction() const;

	void setExportRelatedObjects(bool exportRelated) {
		mExportRelated = exportRelated;
	}

	bool getExportRealtedObjects() const {
		return mExportRelated;
	}

	static const String getNewTrxGroup() {
		return "G" + getNewTrxID().toUpperCase();
	}

	void setTrxGroup(const String& groupTrxId) {
		mTransaction["trxGroup"] = groupTrxId;
	}

	const String getTrxGroup() {
		if (!mTransaction.contains("trxGroup")) {
			mTransaction["trxGroup"] = getNewTrxGroup();
		}

		return String(mTransaction["trxGroup"]);
	}

	void groupWith(TransactionLog& leadTrx) {
		mTransaction["trxGroup"] = leadTrx.getTrxGroup();
	}

	void setAutoCommit(bool autocommit) {
		mAutoCommit = autocommit;
	}

	void setAmount(int amount, bool isCash = false) {
		mTransaction["isCash"] = isCash;
		mTransaction["amount"] = amount;
	}

	void setType(const String& type) {
		mContext["type"] = type;
	}

	const String getType() const {
		return String(mContext["type"]);
	}

	void setSubject(SceneObject* subject, bool exportSubject = false);

	void setExperience(const String& xpType, int xpAdd, int xpTotal);

	bool getAutoCommit() const {
		return mAutoCommit;
	}

	void setDebug(bool debug) {
		mDebug = debug;
	}

	bool getDebug() const {
		return mDebug;
	}

	bool isAborted() const {
		return mAborted;
	}

	bool isVerbose() const {
		return getVerbose();
	}

	void setMaxDepth(int maxDepth) {
		mMaxDepth = maxDepth;
	}

	int getMaxDepth() const {
		return mMaxDepth;
	}

	const String getTrxID() const {
		if (!isEnabled())
			return "disabled";

		return String(mTransaction["trxId"].get<std::string>());
	}

	String toStringData() const;

	void addContextFromLua(lua_State* L);

	void addRelatedObject(uint64 oid, bool trackChildren = false);

	void addRelatedObject(SceneObject* obj, bool trackChildren = false);

	template<typename T>
	void addState(const String& key, T value) {
		catchAndLog(__FUNCTION__, [&]() -> void { mState[key] = value; });
	}

	void addWorldPosition(String context, SceneObject* scno);

	static const String getNewTrxID();

	static bool getVerbose();

	static SceneObject* getTrxParticipant(SceneObject* obj, SceneObject* defaultValue);

	void exportRelated();

private:
	TransactionLog() {
	};

	static AtomicInteger exportBacklog;

	void catchAndLog(const char* functioName, Function<void()> function);

	static Logger& getLogger();

	static const String& getVersion();

	static const TaskQueue* getCustomQueue();

	static bool getAsyncExport();

	static bool getEnabled();

	static bool getPruneCreatureObjects();

	static bool getPruneCraftedComponents();

	static bool getCheckPlayerDebug();

	bool checkDebug(SceneObject* obj) const;

	const String shortFilename(const char* file) const;

	void initializeCommon(SceneObject* src, SceneObject* dst, TrxCode code, CAPTURE_CALLER_DECLARE);

	void initializeCommonSceneObject(const String& key, SceneObject* obj);

	void initializeCreditsCommon(SceneObject* src, SceneObject* dst, TrxCode code, int amount, bool isCash);

	void addStateObjectMetadata(const String& baseKeyName, SceneObject* obj);

	void addStateCreditBalances(const String& key, const String& when);

	void addStateCreditBalances(const String& who, const String& when, SceneObject* obj);

	const String composeLogEntry() const;

	void writeLog();

	static const String trxCodeToString(TrxCode code);

	static bool isStat(TrxCode code) {
		switch (code) {
			case TrxCode::COMBATSTATS:
			case TrxCode::CORPSEEXPIRATION:
			case TrxCode::CRAFTINGSESSION:
			case TrxCode::DATABASECOMMIT:
			case TrxCode::EXPERIENCE:
			case TrxCode::JABBASPALACE:
			case TrxCode::NEWBIETUTORIAL:
			case TrxCode::PLAYERDIED:
			case TrxCode::PLAYERLINKDEAD:
			case TrxCode::PLAYERLOGGINGOUT:
			case TrxCode::PLAYEROFFLINE:
			case TrxCode::PLAYERONLINE:
			case TrxCode::POISYSTEM:
			case TrxCode::SKILLTRAININGSYSTEM:
			case TrxCode::TESTACCOUNT:
				return true;

			default:
				return false;
		}
	}
};
