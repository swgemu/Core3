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

	setLogLevel(static_cast<Logger::LogLevel>(debugLevel));

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

	// TODO: Make this a config option?
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

void SessionAPIClient::apiCall(const String src, int debugLevel, const String basePath, const SessionAPICallback& resultCallback) {
	incrementTrxCount();

	String path = basePath;

	if (dryRun) {
		path = basePath + (basePath.indexOf("?") == -1 ? "?" : "&") + "debug=1&dryrun=1";
	}

	debug() << src << " START apiCall [path=" << path << "]";

	web::http::client::http_client_config client_config;

	client_config.set_validate_certificates(false);

	http_client client(baseURL.toCharArray(), client_config);

	http_request req(methods::GET);

	req.headers().add(U("Authorization"), apiToken.toCharArray());

	req.set_request_uri(path.toCharArray());

	client.request(req)
		.then([this, src](http_response resp) {
			if (resp.status_code() != 200) {
				error() << src << "Response status code " << resp.status_code() << " returned.";
			}

			return resp.extract_json();
		}).then([this, src, debugLevel, path, resultCallback](json::value result_json) {
			SessionApprovalResult result;

			auto logPrefix = result.getClientTrxId() + " " + src + ": ";

			if (result_json.is_null()) {
				error() << logPrefix << "Null JSON result from server.";
				result.setAction(SessionApprovalResult::ApprovalAction::TEMPFAIL);
				result.setTitle("Temporary Server Error");
				result.setMessage("If the error continues please contact support and mention error code = K");
			} else {
				result.setRawJSON(String(result_json.serialize().c_str()));

				if (result_json.has_field("action")) {
					result.setAction(String(result_json[U("action")].as_string().c_str()));
				} else if (failOpen) {
					warning() << logPrefix << "Missing action from result, failing to ALLOW: JSON: " << result_json.serialize().c_str();
					result.setAction(SessionApprovalResult::ApprovalAction::ALLOW);
				} else {
					result.setAction(SessionApprovalResult::ApprovalAction::TEMPFAIL);
					result.setTitle("Temporary Server Error");
					result.setMessage("If the error continues please contact support and mention error code = L");
					result.setDetails("Missing action field from server");
				}

				if (result_json.has_field("title")) {
					result.setTitle(String(result_json[U("title")].as_string().c_str()));
				}

				if (result_json.has_field("message")) {
					result.setMessage(String(result_json[U("message")].as_string().c_str()));
				}

				if (result_json.has_field("details")) {
					result.setDetails(String(result_json[U("details")].as_string().c_str()));
				}

				if (result_json.has_field("debug")) {
					auto debug = result_json[U("debug")];

					if (debug.has_field("trx_id")) {
						result.setDebugValue("trx_id", String(debug[U("trx_id")].as_string().c_str()));
					}
				}
			}

			if (dryRun) {
				debug() << logPrefix << "DryRun: original result = " << result.toString();

				result.setAction(SessionApprovalResult::ApprovalAction::ALLOW);
				result.setTitle("");
				result.setMessage("");
				result.setDetails("");
				result.setDebugValue("trx_id", "dry-run-trx-id");
			}

			debug() << logPrefix << "END apiCall [path=" << path << "] result = " << result.toString();

			Core::getTaskManager()->executeTask([resultCallback, result] {
				resultCallback(result);
			}, "SessionAPIClientResult", "slowQueue");
		});
}

void SessionAPIClient::apiNotify(String src, int debugLevel, const String basePath) {
	apiCall(src, 2, basePath, [=](SessionApprovalResult result) {
		if (!result.isActionAllowed()) {
			error() << src << " unexpected failure: " << result.toString();
		}
	});
}

void SessionAPIClient::approveNewSession(const String ip, uint32 accountID, const SessionAPICallback& resultCallback) {
	StringBuffer path;

	path << "/v1/core3/account/" << accountID << "/session/" << ip << "/approval";

	apiCall(__FUNCTION__, 1, path.toString(), resultCallback);
}

void SessionAPIClient::notifySessionStart(const String ip, uint32 accountID) {
	StringBuffer path;

	path << "/v1/core3/account/" << accountID << "/session/" << ip << "/start";

	apiNotify(__FUNCTION__, 1, path.toString());
}

void SessionAPIClient::notifyDisconnectClient(const String ip, uint32 accountID, uint64_t characterID, String eventType) {
	StringBuffer path;

	path << "/v1/core3/account/" << accountID << "/session/" << ip << "/player/" << characterID << "/disconnect" << "?eventType=" << eventType;

	apiNotify(__FUNCTION__, 2, path.toString());
}

void SessionAPIClient::approvePlayerConnect(const String ip, uint32 accountID, uint64_t characterID, const SessionAPICallback& resultCallback) {
	StringBuffer path;

	path << "/v1/core3/account/" << accountID << "/session/" << ip << "/player/" << characterID << "/approval";

	apiCall(__FUNCTION__, 1, path.toString(), resultCallback);
}

void SessionAPIClient::notifyPlayerOnline(const String ip, uint32 accountID, uint64_t characterID) {
	StringBuffer path;

	path << "/v1/core3/account/" << accountID
		<< "/session/" << ip
		<< "/player/" << characterID
		<< "/online"
		;

	apiNotify(__FUNCTION__, 1, path.toString());
}

void SessionAPIClient::notifyPlayerOffline(const String ip, uint32 accountID, uint64_t characterID) {
	StringBuffer path;

	path << "/v1/core3/account/" << accountID
		<< "/session/" << ip
		<< "/player/" << characterID
		<< "/offline"
		;

	apiNotify(__FUNCTION__, 1, path.toString());
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

	if (debugLevel == Logger::DEBUG) {
		buf << "message: '" << getMessage() << "', ";
	}

	buf << "details: '" << getDetails() << "'" ;

	if (debugLevel == Logger::DEBUG && getRawJSON().length() > 0) {
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
