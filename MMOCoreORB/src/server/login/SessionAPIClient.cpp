/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : SessionAPIClient.cpp
 * @created     : Fri Nov 29 10:04:14 UTC 2019
 */

#ifdef WITH_SESSION_API

#include "SessionAPIClient.h"

#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <pplx/threadpool.h>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;

SessionAPIClient::SessionAPIClient() {
	trxCount = 0;

	// Separate log file to avoid spamming the console
	setLoggingName("SessionAPIClient");
	setFileLogger("log/session_api.log", true);
	setLogToConsole(false);
	setGlobalLogging(false);
	setLogging(true);

	debugLevel = ConfigManager::instance()->getInt("Core3.Login.API.DebugLevel", 0);

	dryRun = ConfigManager::instance()->getBool("Core3.Login.API.DryRun", false);

	apiToken = ConfigManager::instance()->getString("Core3.Login.API.APIToken", "");

	if (apiToken.length() == 0) {
		warning() << "Missing Core3.Login.API.APIToken, Sessions API disabled.";
		dryRun = true;
		return;
	}

	baseURL = ConfigManager::instance()->getString("Core3.Login.API.BaseURL", "");

	if (baseURL.length() == 0) {
		warning() << "Missing Core3.Login.API.BaseURL, Sessions API disabled.";
		dryRun = true;
		return;
	}

	failOpen = ConfigManager::instance()->getBool("Core3.Login.API.FailOpen", false);

	info(true) << "Starting " << toString();

	// crossplat::threadpool::initialize_with_threads(8);
}

SessionAPIClient::~SessionAPIClient() {
	crossplat::threadpool::shared_instance().service().stop();
	info(true) << "Shutdown";
}

String SessionAPIClient::toString() {
	StringBuffer buf;

	buf << "SessionAPIClient " << this << " ["
		<< "trxCount: " << trxCount << ", "
		<< "failOpen: " << failOpen << ", "
		<< "dryRun: " << dryRun << ", "
		<< "debugLevel: " << debugLevel << ", "
		<< "baseURL: " << baseURL << "]"
		;

	return buf.toString();
}

SessionApprovalResult& SessionAPIClient::apiCall(String src, int debugLevel, const String basePath) {
	incrementTrxCount();

	web::http::client::http_client_config client_config;

	client_config.set_validate_certificates(false);

	http_client client(baseURL.toCharArray(), client_config);

	http_request req(methods::GET);

	req.headers().add(U("Authorization"), apiToken.toCharArray());

	String path = basePath;

	if (dryRun) {
		path = basePath + (basePath.indexOf("?") == -1 ? "?" : "&") + "debug=1";
	}

	req.set_request_uri(path.toCharArray());

	auto result = new SessionApprovalResult();

	auto logPrefix = result->getClientTrxId() + " " + src + ": ";

	if (getDebugLevel() > debugLevel) {
		info() << logPrefix << "START apiCall [path=" << path << "]";
	}

	client.request(req)
		.then([=](http_response resp) {
			if (resp.status_code() != 200) {
				error() << logPrefix << "Response status code " << resp.status_code() << " returned.";
				result->setDetails("Call failed, status_code: " + String::valueOf(resp.status_code()));
			}

			return resp.extract_json();
		}).then([=](json::value result_json) {
			if (result_json.is_null()) {
				error() << logPrefix << "Null JSON result from server.";
				result->setAction(SessionApprovalResult::ApprovalAction::TEMPFAIL);
				result->setTitle("Temporary Server Error");
				result->setMessage("If the error continues please contact support and mention error code = K");
				return;
			}

			result->setRawJSON(String(result_json.serialize().c_str()));

			if (result_json.has_field("action")) {
				result->setAction(String(result_json[U("action")].as_string().c_str()));
			} else if (failOpen) {
				warning() << logPrefix << "Missing action from result, failing to ALLOW: JSON: " << result_json.serialize().c_str();
				result->setAction(SessionApprovalResult::ApprovalAction::ALLOW);
			} else {
				result->setAction(SessionApprovalResult::ApprovalAction::TEMPFAIL);
				result->setTitle("Temporary Server Error");
				result->setMessage("If the error continues please contact support and mention error code = L");
				result->setDetails("Missing action field from server");
			}

			if (result_json.has_field("title")) {
				result->setTitle(String(result_json[U("title")].as_string().c_str()));
			}

			if (result_json.has_field("message")) {
				result->setMessage(String(result_json[U("message")].as_string().c_str()));
			}

			if (result_json.has_field("details")) {
				result->setDetails(String(result_json[U("details")].as_string().c_str()));
			}

			if (result_json.has_field("debug")) {
				auto debug = result_json[U("debug")];

				if (debug.has_field("trx_id")) {
					result->setDebugValue("trx_id", String(debug[U("trx_id")].as_string().c_str()));
				}
			}
		})

	.wait();

	if (dryRun) {
		if (getDebugLevel() > 0) {
			info() << logPrefix << "DryRun: original result = " << result->toString();
		}

		result->setAction(SessionApprovalResult::ApprovalAction::ALLOW);
		result->setTitle("");
		result->setMessage("");
		result->setDetails("");
		result->setDebugValue("trx_id", "dry-run-trx-id");
	}

	if (getDebugLevel() >= debugLevel) {
		info() << logPrefix << "END apiCall [path=" << path << "] result = " << result->toString();
	}

	return *result;
}

void SessionAPIClient::apiNotify(String src, int debugLevel, const String basePath) {
	auto result = apiCall(__func__, 2, basePath);

	if (getDebugLevel() > 0 && !result.isActionAllowed()) {
		error() << __func__ << " unexpected failure: " << result.toString();
	}
}

SessionApprovalResult& SessionAPIClient::approveNewSession(LoginClient* client, Account* account) {
	StringBuffer path;

	path << "/v1/core3/account/" << account->getAccountID()
		<< "/session/" << client->getIPAddress()
		<< "/approval"
		;

	return apiCall(__func__, 1, path.toString());
}

SessionApprovalResult& SessionAPIClient::startNewSession(LoginClient* client, Account* account) {
	StringBuffer path;

	path << "/v1/core3/account/" << account->getAccountID()
		<< "/session/" << client->getIPAddress()
		<< "/start"
		;

	return apiCall(__func__, 1, path.toString());
}

void SessionAPIClient::notifyDisconnectClient(const String ip, uint32 accountID, uint64_t characterID, String eventType) {
	StringBuffer path;

	path << "/v1/core3/account/" << accountID
		<< "/session/" << ip
		<< "/player/" << characterID
		<< "/disconnect"
		<< "?eventType=" << eventType
		;

	apiNotify(__func__, 2, path.toString());
}

SessionApprovalResult& SessionAPIClient::approvePlayerConnect(const String ip, uint32 accountID, uint64_t characterID) {
	StringBuffer path;

	path << "/v1/core3/account/" << accountID
		<< "/session/" << ip
		<< "/player/" << characterID
		<< "/approval"
		;

	return apiCall(__func__, 1, path.toString());
}

void SessionAPIClient::notifyPlayerOnline(const String ip, uint32 accountID, uint64_t characterID) {
	StringBuffer path;

	path << "/v1/core3/account/" << accountID
		<< "/session/" << ip
		<< "/player/" << characterID
		<< "/online"
		;

	apiNotify(__func__, 1, path.toString());
}

void SessionAPIClient::notifyPlayerOffline(const String ip, uint32 accountID, uint64_t characterID) {
	StringBuffer path;

	path << "/v1/core3/account/" << accountID
		<< "/session/" << ip
		<< "/player/" << characterID
		<< "/offline"
		;

	apiNotify(__func__, 1, path.toString());
}

bool SessionAPIClient::consoleCommand(String arguments) {
	StringTokenizer tokenizer(arguments);

	String subcmd;

	if (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(subcmd);
		subcmd = subcmd.toLowerCase();
	}

	if (subcmd == "help") {
		System::out << "Available sessionapi commands:" << endl
			<< "\thelp - This command" << endl
			<< "\tstatus - Session API status" << endl
			<< "\tdryrun {off} - Control session dry run setting" << endl
			<< "\tdebug {level} - Set debug level for session API" << endl
			;
		return true;
	} else if (subcmd == "status") {
		System::out << "Status for " << toString() << endl;
		return true;
	} else if (subcmd == "dryrun") {
		bool newDryRun = true;

		if (tokenizer.hasMoreTokens()) {
			String arg1;
			tokenizer.getStringToken(arg1);

			if (arg1.toLowerCase() == "off") {
				newDryRun = false;
			}
		}

		dryRun = newDryRun;

		if (dryRun) {
			info(true) << "SessionAPIClient set to dry run, api calls continue but results are ignored.";
		} else {
			info(true) << "SessionAPIClient set to run, api results will be honored by the server.";
		}

		return true;
	} else if (subcmd == "debug" || subcmd == "debuglevel") {
		int newDebugLevel = 9;

		if (tokenizer.hasMoreTokens()) {
			newDebugLevel = tokenizer.getIntToken();
		}

		debugLevel = newDebugLevel;

		info(true) << "DebugLevel set to " << debugLevel << " by console command.";

		return true;
	}

	info(true) << "Unknown sessionapi subcommand: " << subcmd;

	return false;
}

String SessionApprovalResult::toString() const {
	StringBuffer buf;

	buf << "SessionApprovalResult " << this << " ["
		<< "clientTrxId: " << getClientTrxId() << ", "
		<< "trxId: " << getTrxId() << ", "
		<< "action: " << actionToString(getAction()) << ", "
		<< "title: '" << getTitle() << "', "
		<< "message: '" << getMessage() << "', "
		<< "details: '" << getDetails() << "'"
		;

	if (getRawJSON().length() > 0) {
		buf << ", JSON: '" << getRawJSON() << "'";
	}
	
	buf << "]";

	return buf.toString();
}

String SessionApprovalResult::getLogMessage() const {
	int debugLevel = SessionAPIClient::instance()->getDebugLevel();

	StringBuffer buf;

	buf << "SessionApprovalResult " << this << " ["
		<< "clientTrxId: " << getClientTrxId() << ", "
		<< "trxId: " << getTrxId() << ", "
		<< "action: " << actionToString(getAction()) << ", "
		;

	if (debugLevel > 0) {
		buf << "message: '" << getMessage() << "', ";
	}

	buf << "details: '" << getDetails() << "'" ;

	if (debugLevel > 0 && getRawJSON().length() > 0) {
		buf << ", JSON: '" << getRawJSON() << "'";
	}
	
	buf << "]";

	return buf.toString();
}

SessionApprovalResult::SessionApprovalResult() {
	// Generate simple code for log tracing
	uint64 trxid = (System::getMikroTime() << 8) | System::random(255);
	StringBuffer buf;
	buf << hex << trxid;
	resultClientTrxId = buf.toString();

	resultTrxId = "";
	resultAction = ApprovalAction::UNKNOWN;
	resultTitle = "";
	resultMessage = "";
	resultDetails = "";
	resultRawJSON = "";
}

#endif // WITH_SESSION_API
