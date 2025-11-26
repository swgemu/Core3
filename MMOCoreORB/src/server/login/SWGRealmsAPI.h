/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : SWGRealmsAPI.h
 * @created     : Fri Nov 29 10:04:14 UTC 2019
 */

#ifndef _SWGREALMSAPI_H
#define _SWGREALMSAPI_H

#ifdef WITH_SWGREALMS_API

#include "engine/engine.h"
#include "system/thread/atomic/AtomicInteger.h"
#include "server/login/objects/Galaxy.h"
#include "engine/db/berkeley/BerkeleyDatabase.h"
#include "engine/db/berkeley/Environment.h"

#define _TURN_OFF_PLATFORM_STRING
#include <cpprest/json.h>
#include <cpprest/ws_client.h>

// Forward declarations
class GalaxyBanEntry;
class CharacterListEntry;
class CharacterNameMap;

namespace web {
	namespace http {
		namespace client {
			class http_client;
		}
	}
}

namespace server {
	namespace zone {
		class ZoneClientSession;
	}
	namespace login {
		namespace account {
			class Account;
		}

		// Forward declarations
		class SWGRealmsAPI;

		// Base class for all SWGRealms API results
		class SWGRealmsAPIResult : public Object {
			friend class SWGRealmsAPI;

		public:
			enum ApprovalAction {
				UNKNOWN = -2,
				TEMPFAIL = -1,
				ALLOW = 0,
				WARN = 1,
				REJECT = 2,
				BAN = 3,
				DEBUG = 4
			};

		protected:
			web::json::value jsonData;
			String resultClientTrxId;
			ApprovalAction resultAction;
			String resultTitle;
			String resultMessage;
			String resultDetails;
			uint64 resultElapsedTimeMS;
			HashTable<String, String> resultDebug;

			// Blocking call synchronization
			Mutex blockingMutex;
			Condition blockingCondition;
			bool blockingReceived;

#ifdef WITH_SWGREALMS_CALLSTATS
			// Call trace for detailed profiling (maintains insertion order)
			Vector<Pair<String, Time>> callTrace;
#endif

		public:
			Function<void()> callback;

			SWGRealmsAPIResult();
			virtual ~SWGRealmsAPIResult();

			// Parse from JSON - implemented by subclasses
			virtual bool parse() = 0;

			// Invoke the callback if set
			inline void invokeCallback() {
				if (callback) {
					callback();
				}
			}

#ifdef WITH_SWGREALMS_CALLSTATS
			// Call tracing for profiling
			void trace(const String& tag);
			String dumpTrace() const;
#endif

			String toString() const;
			String toStringData() const;
			String getLogMessage() const;

			String actionToString(ApprovalAction action) const {
				switch (action) {
				case ApprovalAction::UNKNOWN:	return String("UNKNOWN");
				case ApprovalAction::TEMPFAIL:	return String("TEMPFAIL");
				case ApprovalAction::ALLOW:		return String("ALLOW");
				case ApprovalAction::WARN:		return String("WARN");
				case ApprovalAction::REJECT:	return String("REJECT");
				case ApprovalAction::BAN:		return String("BAN");
				case ApprovalAction::DEBUG:		return String("DEBUG");
				}

				return String("UNKOWN(" + String::valueOf((int)action) + ")");
			}

			void setAction(const String& stringAction) {
				if (stringAction == "TEMPFAIL") {
					resultAction = ApprovalAction::TEMPFAIL;
					return;
				}

				if (stringAction == "ALLOW") {
					resultAction = ApprovalAction::ALLOW;
					return;
				}

				if (stringAction == "WARN") {
					resultAction = ApprovalAction::WARN;
					return;
				}

				if (stringAction == "REJECT") {
					resultAction = ApprovalAction::REJECT;
					return;
				}

				if (stringAction == "BAN") {
					resultAction = ApprovalAction::BAN;
					return;
				}

				if (stringAction == "DEBUG") {
					resultAction = ApprovalAction::DEBUG;
					return;
				}

				resultAction = ApprovalAction::UNKNOWN;
			}

			inline void setJSONObject(const web::json::value& json) {
				jsonData = json;
			}

			inline const web::json::value& getJSONObject() const {
				return jsonData;
			}

			inline String getRawJSON() const {
				if (jsonData.is_null()) return "";
				return String(jsonData.serialize().c_str());
			}

			inline void setClientTrxId(const String& clientTrxId) {
				resultClientTrxId = clientTrxId;
			}

			inline const String& getClientTrxId() const {
				return resultClientTrxId;
			}

			inline void setAction(ApprovalAction action) {
				resultAction = action;
			}

			inline ApprovalAction getAction() const {
				return resultAction;
			}

			inline bool isActionTemporaryFailure() const {
				return resultAction == ApprovalAction::TEMPFAIL;
			}

			inline bool isActionAllowed() const {
				return resultAction == ApprovalAction::ALLOW || resultAction == ApprovalAction::DEBUG;
			}

			inline bool isActionWarning() const {
				return resultAction == ApprovalAction::WARN;
			}

			inline bool isActionRejected() const {
				return resultAction == ApprovalAction::REJECT;
			}

			inline bool isActionBan() const {
				return resultAction == ApprovalAction::BAN;
			}

			inline bool isActionDebug() const {
				return resultAction == ApprovalAction::DEBUG;
			}

			inline void setTitle(const String& title) {
				resultTitle = title;
			}

			inline const String& getTitle() const {
				return resultTitle;
			}

			inline void setMessage(const String& message) {
				resultMessage = message;
			}

			inline String getMessage(bool appendTrxId = false) const {
				auto entry = resultDebug.getEntry("trx_id");

				if (!appendTrxId || !entry) {
					return resultMessage;
				}

				return resultMessage + "\n\ntrx_id: " + entry->getValue();
			}

			inline void setDetails(const String& details) {
				resultDetails = details;
			}

			inline const String& getDetails() const {
				return resultDetails;
			}

			inline void setElapsedTimeMS(uint64 elapsedTimeMS) {
				resultElapsedTimeMS = elapsedTimeMS;
			}

			inline uint64 getElapsedTimeMS() const {
				return resultElapsedTimeMS;
			}

			inline void setDebugValue(const String& key, const String& value) {
				resultDebug.put(key, value);
			}

			inline const String& getDebugValue(const String& key) const {
				auto entry = resultDebug.getEntry(key);

				if (entry) {
					return entry->getValue();
				} else {
					const static String empty;
					return empty;
				}
			}

			inline const HashTable<String, String>& getDebugHashTable() const {
				return resultDebug;
			}

			inline void setTrxId(const String& trxId) {
				resultDebug.put("trx_id", trxId);
			}

			inline const String& getTrxId() const {
				return resultDebug.get("trx_id");
			}
		};

		// Forward declare for SessionApprovalResult constructor
		class SessionApprovalResult;
		using SessionAPICallback = Function<void(SessionApprovalResult)>;

		// Session-specific result (login, session validation, etc.)
		class SessionApprovalResult : public SWGRealmsAPIResult {
		private:
			String resultEncryptedIP;
			String resultSessionID;
			uint32 resultAccountID;
			uint32 resultStationID;

		public:
			SessionApprovalResult();
			SessionApprovalResult(const SessionAPICallback& resultCallback);

			// Implement virtual parse() method
			bool parse() override;

			// Session-specific methods
			inline void setEncryptedIP(const String& eip) {
				resultEncryptedIP = eip;
			}

			inline const String& getEncryptedIP() const {
				return resultEncryptedIP;
			}

			inline void setSessionID(const String& newSessionID) {
				resultSessionID = newSessionID;
			}

			inline const String& getSessionID() const {
				return resultSessionID;
			}

			inline void setAccountID(uint32 newAccountID) {
				resultAccountID = newAccountID;
			}

			inline uint32 getAccountID() const {
				return resultAccountID;
			}

			inline void setStationID(uint32 newStationID) {
				resultStationID = newStationID;
			}

			inline uint32 getStationID() const {
				return resultStationID;
			}
		};

		// Result classes defined in SWGRealmsAPI.cpp to avoid circular includes
		class AccountResult;
		class SimpleResult;

		/**
		 * WebSocket streaming client with BerkeleyDB WAL for durability.
		 *
		 * Wire Protocol:
		 *   Send: channel\tkey\tpayload\n
		 *   ACK:  {"channel":"...","key":"...","status":"ok"|"error"}
		 */
		class SWGRealmsStreamer : public Logger, public Object {
		private:
			web::websockets::client::websocket_callback_client* wsClient;
			bool connected;
			String wsURL;
			String apiToken;
			int galaxyID;
			bool enabled;

			ThreadLocal<engine::db::berkeley::BerkeleyDatabase*> walDatabase;
			engine::db::berkeley::Environment* walEnvironment;
			String walDbPath;
			String walEnvPath;

			Mutex syncMutex;
			Mutex reconnectMutex;

			AtomicInteger walPendingCount;
			AtomicInteger publishedCount;
			AtomicInteger ackedCount;
			AtomicInteger errorCount;
			AtomicInteger inFlightCount;

			int reconnectDelay;
			bool reconnectScheduled;

			static constexpr uint64 MAX_WAL_SIZE = 100 * 1024 * 1024;
			static constexpr uint64 GC_AFTER_HOURS = 48;

		public:
			SWGRealmsStreamer(const String& baseURL, const String& token, int galaxy, int debugLevel);
			~SWGRealmsStreamer();

			void publish(const String& channel, const String& key, const String& payloadJson);
			void garbageCollect();
			JSONSerializationType getStatsAsJSON() const;
			String toString() const;

			inline bool isConnected() const { return connected; }
			inline int getPendingCount() const { return walPendingCount.get(); }

		private:
			engine::db::berkeley::BerkeleyDatabase* getWALHandle();
			void appendToWAL(const String& channel, const String& key, const String& payloadJson);
			void removeFromWAL(const String& channel, const String& key);
			Vector<Pair<String, String>> getAllPendingFromWAL();
			uint64 parseTimestampFromKey(const String& key);

			void connectWebSocket();
			void disconnectWebSocket();
			void sendMessage(const String& channel, const String& key, const String& payloadJson);
			void replayWAL();
			void scheduleReconnect();

			void onOpen();
			void onClose(web::websockets::client::websocket_close_status status,
			            const utility::string_t& reason, const std::error_code& ec);
			void onFail(const std::exception& e);
			void onMessage(const web::websockets::client::websocket_incoming_message& msg);
		};

		class SWGRealmsAPI : public Logger, public Singleton<SWGRealmsAPI>, public Object {
		protected:
			AtomicInteger trxCount = 0;
			AtomicInteger errCount = 0;
			bool apiEnabled = false;
			int galaxyID = 0;
			int debugLevel = 0;
			String apiToken = "";
			String baseURL = "";
			bool dryRun = false;
			bool failOpen = false;
			int apiTimeoutMs = 30000;

			// Persistent HTTP client for connection reuse (thread-safe)
			web::http::client::http_client* httpClient = nullptr;

			// WebSocket streaming client (owned, nullable if disabled)
			SWGRealmsStreamer* streamer = nullptr;

			// Blocking call statistics
			AtomicInteger outstandingBlockingCalls = 0;
			AtomicInteger peakConcurrentCalls = 0;
			AtomicInteger totalBlockingCalls = 0;

			// Latency histogram (milliseconds)
			AtomicInteger latency_0_10ms = 0;
			AtomicInteger latency_10_50ms = 0;
			AtomicInteger latency_50_100ms = 0;
			AtomicInteger latency_100_500ms = 0;
			AtomicInteger latency_500plus = 0;

			// Timing breakdown (for averaging)
			AtomicLong totalRoundTripMs = 0;
			AtomicLong totalRequestMs = 0;

		public:
			SWGRealmsAPI();
			~SWGRealmsAPI();

			inline void incrementTrxCount() {
				trxCount.increment();
			}

			inline void incrementErrorCount() {
				errCount.increment();
			}

			inline void setDebugLevel(int newDebugLevel) {
				debugLevel = newDebugLevel;
			}

			inline int getDebugLevel() const {
				return debugLevel;
			}

			inline bool getFailOpen() const {
				return failOpen;
			}

			String toString() const;
			String toStringData() const;

			// Statistics
			JSONSerializationType getStatsAsJSON() const;

			// Hook for console "swgrealms" command
			bool consoleCommand(const String& arguments);

		private:
			// API Helpers
			void apiCall(Reference<SWGRealmsAPIResult*> result, const String& src, const String& path,
					const String& method = "GET", const String& body = "");
			void apiNotify(const String& src, const String& basePath);

			bool parseAccountFromJSON(const String& jsonStr, Reference<account::Account*> account, String& errorMessage);
			bool parseAccountBanStatusFromJSON(const String& jsonStr, Reference<account::Account*> account, String& errorMessage);
			bool parseGalaxyBansFromJSON(const String& jsonStr, VectorMap<uint32, Reference<GalaxyBanEntry*>>& galaxyBans, String& errorMessage);
			bool parseCharacterBansFromJSON(const String& jsonStr, VectorMap<String, Reference<CharacterListEntry*>>& characterBans, String& errorMessage);
			bool parseCharacterListFromJSON(const String& jsonStr, Vector<CharacterListEntry>& characters, String& errorMessage);
			bool parseGalaxyListFromJSON(const String& jsonStr, Vector<Galaxy>& galaxies, String& errorMessage);
			Optional<Galaxy> parseGalaxyFromJSON(const String& jsonStr);

			// Generic blocking API call helper - eliminates boilerplate
			bool apiCallBlocking(Reference<SWGRealmsAPIResult*> result, const String& path, const String& method,
			                     const String& body, String& errorMessage);

		public:
			// Account Data Retrieval
			bool getAccountDataBlocking(uint32 accountID, Reference<account::Account*> account, String& errorMessage);
			uint32 getAccountID(const String& username, String& errorMessage);
			bool getAccountBanStatusBlocking(uint32 accountID, Reference<account::Account*> account, String& errorMessage);

			// Account Ban Operations
			bool banAccountBlocking(uint32 accountID, uint32 issuerID, uint64 expiresTimestamp,
			                        const String& reason, String& errorMessage);
			bool unbanAccountBlocking(uint32 accountID, const String& reason, String& errorMessage);

			// Galaxy Ban Operations
			bool getGalaxyBansBlocking(uint32 accountID, VectorMap<uint32, Reference<GalaxyBanEntry*>>& galaxyBans,
			                           String& errorMessage);
			bool banFromGalaxyBlocking(uint32 accountID, uint32 galaxyID, uint32 issuerID, uint64 expiresTimestamp,
			                           const String& reason, String& errorMessage);
			bool unbanFromGalaxyBlocking(uint32 accountID, uint32 galaxyID, const String& reason, String& errorMessage);

			// Character Ban Operations
			bool getCharacterBansBlocking(uint32 accountID, VectorMap<String, Reference<CharacterListEntry*>>& characterBans,
			                              String& errorMessage);
			bool banCharacterBlocking(uint32 accountID, uint32 galaxyID, const String& name, uint32 issuerID,
			                          uint64 expiresTimestamp, const String& reason, String& errorMessage);
			bool unbanCharacterBlocking(uint32 accountID, uint32 galaxyID, const String& name, const String& reason,
			                            String& errorMessage);

			// Character Operations
			bool createCharacterBlocking(uint64 characterOID, uint32 accountID, uint32 galaxyID,
			                             const String& firstname, const String& surname,
			                             uint32 race, uint32 gender, const String& templatePath,
			                             const String& reservationID, String& errorMessage);
			bool getCharacterListBlocking(uint32 accountID, Vector<CharacterListEntry>& characters, String& errorMessage);
			JSONSerializationType getCharacterBlocking(uint64 characterOID, uint32 galaxyID, String& errorMessage);
			bool loadCharacterNamesBlocking(uint32 galaxyID, CharacterNameMap& nameMap, String& errorMessage);
			bool reserveCharacterNameBlocking(uint32 galaxyID, const String& firstname, const String& surname,
			                                  String& reservationID, String& errorMessage);
			bool beginCharactersCommitBlocking(uint32 galaxyID, String& errorMessage);
			bool commitCharactersBlocking(uint32 galaxyID, String& errorMessage);
			bool updateCharacterFirstNameBlocking(uint64 characterOID, uint32 galaxyID,
			                                      const String& firstname, String& errorMessage);
			bool updateCharacterSurNameBlocking(uint64 characterOID, uint32 galaxyID,
			                                    const String& surname, String& errorMessage);
			bool deleteCharacterBlocking(uint64 characterOID, uint32 accountID, uint32 galaxyID, String& errorMessage);
			bool rollbackCharactersBlocking(uint32 galaxyID, String& errorMessage);
			bool beginPurgeBatchBlocking(uint32 galaxyID, uint32 limit, Vector<uint64>& characterOIDs,
			                             String& batchID, String& errorMessage);
			bool commitPurgeBatchBlocking(uint32 galaxyID, const String& batchID, String& errorMessage);

			// Galaxy Metadata Operations
			Vector<Galaxy> getAuthorizedGalaxies(uint32 accountID);
			Optional<Galaxy> getGalaxyEntry(uint32 galaxyID);

			// EIP Helper
			static void updateClientIPAddress(server::zone::ZoneClientSession* client, const SessionApprovalResult& result);

			// Calls in general order of execution
			void notifyGalaxyStart(uint32 galaxyID);
			void notifyGalaxyShutdown();
			void createSession(const String& username, const String& password, const String& clientVersion, const String& clientEndpoint,
					const SessionAPICallback& resultCallback);
			void approveNewSession(const String& ip, uint32 accountID, const SessionAPICallback& resultCallback);
			void validateSession(const String& sessionID, uint32 accountID, const String& ip, const SessionAPICallback& resultCallback);
			void notifySessionStart(const String& ip, uint32 accountID);
			void notifyDisconnectClient(const String& ip, uint32 accountID, uint64_t characterID, String eventType);
			void approvePlayerConnect(const String& ip, uint32 accountID, uint64_t characterID,
					const ArrayList<uint32>& loggedInAccounts, const SessionAPICallback& resultCallback);
			void notifyPlayerOnline(const String& ip, uint32 accountID, uint64_t characterID,
					const SessionAPICallback& resultCallback = nullptr);
			void notifyPlayerOffline(const String& ip, uint32 accountID, uint64_t characterID);

			// Streaming API proxy methods
			void publish(const String& channel, const String& key, const String& payloadJson);
			void publishTrxLog(const String& trxId, const String& payloadJson);
			bool isStreamConnected() const;
			int getStreamPendingCount() const;

			// Metrics publishing
			static const TaskQueue* getCustomQueue();
			void scheduleMetricsPublish();
		};
	}
}

using namespace server::login;

#endif // WITH_SWGREALMS_API

#endif // _SWGREALMSAPI_H
