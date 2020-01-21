/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : SessionAPIClient.h
 * @created     : Fri Nov 29 10:04:14 UTC 2019
 */

#ifdef WITH_SESSION_API
#pragma once

#include "engine/engine.h"
#include "system/thread/atomic/AtomicInteger.h"
#include "server/login/account/Account.h"
#include "server/login/LoginClient.h"

namespace server {
	namespace login {
		class SessionApprovalResult {
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

		private:
			String resultTrxId;
			String resultClientTrxId;
			ApprovalAction resultAction;
			String resultTitle;
			String resultMessage;
			String resultDetails;
			String resultRawJSON;
			uint64 resultElapsedTimeMS;
			HashTable<String, String> resultDebug;

		public:
			SessionApprovalResult();

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

			inline void setTrxId(const String& trxId) {
				resultDebug.put("trx_id", trxId);
			}

			inline const String& getTrxId() const {
				return resultDebug.get("trx_id");
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

			inline const String& getRawJSON() const {
				return resultRawJSON;
			}

			inline void setRawJSON(const String& json) {
				resultRawJSON = json;
			}
		};

		using SessionAPICallback = Function<void(SessionApprovalResult)>;

		class SessionAPIClient : public Logger, public Singleton<SessionAPIClient>, public Object {
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

		public:
			SessionAPIClient();
			~SessionAPIClient();

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

			String toString() const;
			String toStringData() const;

			// Hook for console "sessionapi" command
			bool consoleCommand(const String& arguments);

			// API Helpers
			void apiCall(const String& src, const String& basePath, const SessionAPICallback& resultCallback);
			void apiNotify(const String& src, const String& basePath);

			// Calls in general order of execution
			void notifyGalaxyStart(uint32 galaxyID);
			void notifyGalaxyShutdown();
			void approveNewSession(const String& ip, uint32 accountID, const SessionAPICallback& resultCallback);
			void notifySessionStart(const String& ip, uint32 accountID);
			void notifyDisconnectClient(const String& ip, uint32 accountID, uint64_t characterID, String eventType);
			void approvePlayerConnect(const String& ip, uint32 accountID, uint64_t characterID,
					const ArrayList<uint32>& loggedInAccounts, const SessionAPICallback& resultCallback);
			void notifyPlayerOnline(const String& ip, uint32 accountID, uint64_t characterID);
			void notifyPlayerOffline(const String& ip, uint32 accountID, uint64_t characterID);
		};
	}
}

using namespace server::login;

#endif // WITH_SESSION_API
