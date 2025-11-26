/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : SWGRealmsAPI.cpp
 * @created     : Fri Nov 29 10:04:14 UTC 2019
 */

#ifdef WITH_SWGREALMS_API

#define SWGREALMS_API_VERSION 1004

#include "SWGRealmsAPI.h"

#include "server/login/account/Account.h"
#include "server/zone/ZoneClientSession.h"
#include "server/login/objects/GalaxyBanEntry.h"
#include "server/login/objects/CharacterListEntry.h"
#include "server/login/objects/GalaxyList.h"
#include "server/zone/managers/player/CharacterNameMap.h"

#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <pplx/threadpool.h>

// Workaround for googletest conflict
// See https://github.com/Microsoft/cpprestsdk/blob/master/Release/include/cpprest/details/basic_types.h#L95
#ifndef U
#define U(x) _XPLATSTR(x)
#endif

#ifdef WITH_SWGREALMS_CALLSTATS
#define API_TRACE(result, key) result->trace(key)
#else
#define API_TRACE(result, key) // NOOP
#endif // WITH_SWGREALMS_CALLSTATS

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;

namespace server {
namespace login {

// Result class definitions (moved from header to avoid circular includes)

// Account-specific result (account data, ban status, etc.)
class AccountResult : public SWGRealmsAPIResult {
private:
	Reference<account::Account*> account;
	uint32 accountID;
	bool accountIDOnly;

public:
	AccountResult(Reference<account::Account*> acc);
	AccountResult();

	bool parse() override;

	inline uint32 getAccountID() const {
		return accountID;
	}

	inline Reference<account::Account*> getAccount() const {
		return account;
	}
};

// Simple result for operations that just return success/failure
class SimpleResult : public SWGRealmsAPIResult {
public:
	SimpleResult() {}
	bool parse() override { return true; }
};

} // namespace login
} // namespace server

using namespace server::login;

SWGRealmsAPI::SWGRealmsAPI() {
	trxCount = 0;

	// Separate log file to avoid spamming the console
	setLoggingName("SWGRealmsAPI");
	setFileLogger("log/session_api.log", true, ConfigManager::instance()->getRotateLogAtStart());
	setLogSynchronized(true);
	setRotateLogSizeMB(ConfigManager::instance()->getInt("Core3.Login.API.RotateLogSizeMB", ConfigManager::instance()->getRotateLogSizeMB()));
	setLogToConsole(false);
	setGlobalLogging(false);
	setLogging(true);

	auto config = ConfigManager::instance();

	debugLevel = config->getInt("Core3.Login.API.DebugLevel", 0);

	setLogLevel(static_cast<Logger::LogLevel>(debugLevel));

	galaxyID = config->getZoneGalaxyID();

	dryRun = config->getBool("Core3.Login.API.DryRun", false);

	baseURL = config->getString("Core3.Login.API.BaseURL", "");

	if (baseURL.length() == 0) {
		warning() << "Missing Core3.Login.API.BaseURL, Sessions API disabled.";
		apiEnabled = false;
		return;
	} else {
		apiEnabled = true;
	}

	apiToken = config->getString("Core3.Login.API.APIToken", "");

	if (apiToken.length() == 0) {
		warning() << "Missing Core3.Login.API.APIToken, Sessions API disabled.";
		apiEnabled = false;
		return;
	}

	failOpen = config->getBool("Core3.Login.API.FailOpen", false);

	apiTimeoutMs = config->getInt("Core3.Login.API.Timeout", 30) * 1000;

	// Create persistent HTTP client for connection reuse
	web::http::client::http_client_config client_config;
	client_config.set_validate_certificates(false);
	client_config.set_timeout(utility::seconds(apiTimeoutMs / 1000));

	httpClient = new http_client(baseURL.toCharArray(), client_config);

	streamer = new SWGRealmsStreamer(baseURL, apiToken, galaxyID, debugLevel);

	info(true) << "Starting " << toString();
}

SWGRealmsAPI::~SWGRealmsAPI() {
	// Stop the cpprest threadpool's io_service and shut down resolver threads
	auto& ioService = crossplat::threadpool::shared_instance().service();
	ioService.stop();

	// Notify fork_prepare to stop and join the resolver service worker threads
	// This must be done before deleting clients that might spawn new resolver work
	ioService.notify_fork(boost::asio::execution_context::fork_prepare);

	if (streamer != nullptr) {
		delete streamer;
		streamer = nullptr;
	}

	if (httpClient != nullptr) {
		delete httpClient;
		httpClient = nullptr;
	}

	info(true) << "Shutdown";
}

String SWGRealmsAPI::toStringData() const {
	return toString();
}

String SWGRealmsAPI::toString() const {
	StringBuffer buf;

	buf << "SWGRealmsAPI " << this << " ["
		<< "apiEnabled: " << apiEnabled << ", "
		<< "trxCount: " << trxCount << ", "
		<< "errCount: " << errCount << ", "
		<< "failOpen: " << failOpen << ", "
		<< "dryRun: " << dryRun << ", "
		<< "debugLevel: " << debugLevel << ", "
		<< "baseURL: " << baseURL << "]"
		;

	return buf.toString();
}

void SWGRealmsAPI::apiCall(Reference<SWGRealmsAPIResult*> result, const String& src, const String& path, const String& method, const String& body) {
	// If not enabled just return ALLOW all the time
	if (!apiEnabled) {
		result->setAction(SWGRealmsAPIResult::ApprovalAction::ALLOW);
		result->setTitle("");
		result->setMessage("");
		result->setDetails("API Not enabled.");
		result->setDebugValue("trx_id", "api-disabled");

		Core::getTaskManager()->executeTask([result]() {
			result->invokeCallback();
		}, "SWGRealmsAPIResult-nop-" + src, "slowQueue");
		return;
	}

	Time startTime;

	incrementTrxCount();

	String apiPath = path;

	if (dryRun) {
		apiPath = path + (path.indexOf("?") == -1 ? "?" : "&") + "debug=1&dryrun=1";
	}

	debug() << src << " START apiCall [path=" << apiPath << "]";

	API_TRACE(result, "apiCall_start");

	web::http::method httpMethod;

	if (method == "GET") {
		httpMethod = methods::GET;
	} else if (method == "POST") {
		httpMethod = methods::POST;
	} else if (method == "PUT") {
		httpMethod = methods::PUT;
	} else if (method == "DELETE") {
		httpMethod = methods::DEL;
	} else {
		warning() << "Unknown HTTP method: " << method << " - defaulting to GET";
		httpMethod = methods::GET;
	}

	http_request req(httpMethod);

	String authHeader = "Bearer " + apiToken;

	req.headers().add(U("Authorization"), authHeader.toCharArray());

	req.set_request_uri(apiPath.toCharArray());

	if (!body.isEmpty()) {
		req.set_body(body.toCharArray(), "application/json");
	}

	API_TRACE(result, "http_request_sent");

	httpClient->request(req)
		.then([this, src, apiPath, result](pplx::task<http_response> task) {
			http_response resp;
			bool failed = false;

			try {
				resp = task.get();
				API_TRACE(result, "http_response_received");
			} catch (const http_exception& e) {
				error() << src << " " << apiPath << " HTTP Exception caught: " << e.what();
				failed = true;
			}

			if (failed || resp.status_code() != 200) {
				incrementErrorCount();

				error() << src << " HTTP Status " << resp.status_code() << " returned.";

				auto json_err = json::value();

				json_err[U("action")] = json::value::string(U("TEMPFAIL"));
				json_err[U("title")] = json::value::string(U("Temporary Server Error"));
				json_err[U("message")] = json::value::string(U("If the error continues please contact support and mention error code = N"));

				StringBuffer buf;

				if (failed) {
					buf << "Exception caught handling request, ";
				}

				buf << "http_response.status_code() == " << resp.status_code();

				json_err[U("details")] = json::value::string(U(buf.toString().toCharArray()));

				return pplx::task_from_result(json_err);
			}

			return resp.extract_json();
		}).then([this, src, method, apiPath, result, startTime](pplx::task<json::value> task) {
			auto logPrefix = result->getClientTrxId() + " " + src + ": ";
			auto result_json = json::value();
			bool failed = false;

			try {
				result_json = task.get();
			} catch (const http_exception& e) {
				error() << logPrefix << " " << apiPath << " HTTP Exception caught reading body: " << e.what();
				failed = true;
			}

			if (result_json.is_null()) {
				incrementErrorCount();
				error() << logPrefix << "Null JSON result from server.";
				result->setAction(SWGRealmsAPIResult::ApprovalAction::TEMPFAIL);
				result->setTitle("Temporary Server Error");
				result->setMessage("If the error continues please contact support and mention error code = K");
			} else {
				result->setJSONObject(result_json);

				if (result_json.has_field("action")) {
					result->setAction(String(result_json[U("action")].as_string().c_str()));
				} else if (failOpen) {
					warning() << logPrefix << "Missing action from result, failing to ALLOW: JSON: " << result_json.serialize().c_str();
					result->setAction(SWGRealmsAPIResult::ApprovalAction::ALLOW);
				} else {
					incrementErrorCount();
					result->setAction(SWGRealmsAPIResult::ApprovalAction::TEMPFAIL);
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

					if (debug.has_field("req_time_ms")) {
						result->setDebugValue("req_time_ms", String::valueOf(debug[U("req_time_ms")].as_integer()));
					}
				}

				// Call subclass parse() to extract type-specific fields
				result->parse();
				API_TRACE(result, "json_parsed");
			}

			result->setElapsedTimeMS(startTime.miliDifference());

			if (result->getElapsedTimeMS() > 500)
				warning() << "Slow API Call: " << result->toString();

			if (dryRun) {
				debug() << logPrefix << "DryRun: original result = " << *result;

				result->setAction(SWGRealmsAPIResult::ApprovalAction::ALLOW);
				result->setTitle("");
				result->setMessage("");
				result->setDetails("");
				result->setDebugValue("trx_id", "dry-run-trx-id");
			}

			debug() << logPrefix << "END apiCall " << method << " [path=" << apiPath << "] result = " << *result;

			API_TRACE(result, "queue_scheduled");
			Core::getTaskManager()->executeTask([result] {
				API_TRACE(result, "callback_invoked");
				result->invokeCallback();
			}, "SWGRealmsAPIResult-" + src, "slowQueue");
		});
}

void SWGRealmsAPI::apiNotify(const String& src, const String& basePath) {
	Reference<SessionApprovalResult*> result = new SessionApprovalResult([this, src](const SessionApprovalResult& r) {
		if (!r.isActionAllowed()) {
			error() << src << " unexpected failure: " << r;
		}
	});

	apiCall(result.castTo<SWGRealmsAPIResult*>(), src, basePath);
}

void SWGRealmsAPI::notifyGalaxyStart(uint32 galaxyID) {
	StringBuffer path;

	// Save for later
	this->galaxyID = galaxyID;

	path << "/v1/core3/galaxy/" << galaxyID << "/start?client_version=" << SWGREALMS_API_VERSION;

	apiNotify(__FUNCTION__, path.toString());
}

void SWGRealmsAPI::notifyGalaxyShutdown() {
	StringBuffer path;

	path << "/v1/core3/galaxy/" << galaxyID << "/shutdown?client_version=" << SWGREALMS_API_VERSION;

	apiNotify(__FUNCTION__, path.toString());
}

void SWGRealmsAPI::createSession(const String& username, const String& password, const String& clientVersion, const String& clientEndpoint, const SessionAPICallback& resultCallback) {
	Reference<SessionApprovalResult*> result = new SessionApprovalResult(resultCallback);

	if (!apiEnabled) {
		result->setAction(SWGRealmsAPIResult::ApprovalAction::REJECT);
		result->setTitle("Temporary Server Error");
		result->setMessage("If the error continues please contact support and mention error code = S");
		result->setDetails("SWGRealms API required for authentication but not configured");
		result->setDebugValue("trx_id", "api-disabled-auth");

		Core::getTaskManager()->executeTask([result]() mutable {
			result->invokeCallback();
		}, "SWGRealmsAPIResult-nop-createSession", "slowQueue");

		return;
	}

	auto requestBody = json::value::object();
	requestBody[U("username")] = json::value::string(U(username.toCharArray()));
	requestBody[U("password")] = json::value::string(U(password.toCharArray()));
	requestBody[U("client_version")] = json::value::string(U(clientVersion.toCharArray()));
	requestBody[U("client_ip")] = json::value::string(U(clientEndpoint.toCharArray()));
	requestBody[U("galaxy_id")] = json::value::number(galaxyID);

	apiCall(result.castTo<SWGRealmsAPIResult*>(), __FUNCTION__, "/v1/core3/account/login", "POST", String(requestBody.serialize().c_str()));
}

void SWGRealmsAPI::approveNewSession(const String& ip, uint32 accountID, const SessionAPICallback& resultCallback) {
	Reference<SessionApprovalResult*> result = new SessionApprovalResult(resultCallback);

	StringBuffer path;
	path << "/v1/core3/account/" << accountID << "/galaxy/" << galaxyID << "/session/ip/" << ip << "/approval";

	apiCall(result.castTo<SWGRealmsAPIResult*>(), __FUNCTION__, path.toString());
}

void SWGRealmsAPI::validateSession(const String& sessionID, uint32 accountID, const String& ip, const SessionAPICallback& resultCallback) {
	Reference<SessionApprovalResult*> result = new SessionApprovalResult(resultCallback);

	StringBuffer path;
	path << "/v1/core3/account/" << accountID
		<< "/galaxy/" << galaxyID
		<< "/session/ip/" << ip
		<< "/sessionHash/" << sessionID
		<< "/isvalidsession";

	apiCall(result.castTo<SWGRealmsAPIResult*>(), __FUNCTION__, path.toString(), "GET", "");
}

void SWGRealmsAPI::notifySessionStart(const String& ip, uint32 accountID) {
	StringBuffer path;

	path << "/v1/core3/account/" << accountID << "/galaxy/" << galaxyID << "/session/ip/" << ip << "/start";

	apiNotify(__FUNCTION__, path.toString());
}

void SWGRealmsAPI::notifyDisconnectClient(const String& ip, uint32 accountID, uint64_t characterID, String eventType) {
	StringBuffer path;

	path << "/v1/core3/account/" << accountID << "/galaxy/" << galaxyID << "/session/ip/" << ip << "/player/" << characterID << "/disconnect"
		<< "?eventType=" << eventType;

	apiNotify(__FUNCTION__, path.toString());
}

void SWGRealmsAPI::approvePlayerConnect(const String& ip, uint32 accountID, uint64_t characterID,
		const ArrayList<uint32>& loggedInAccounts, const SessionAPICallback& resultCallback) {
	Reference<SessionApprovalResult*> result = new SessionApprovalResult(resultCallback);

	StringBuffer path;
	path << "/v1/core3/account/" << accountID << "/galaxy/" << galaxyID << "/session/ip/" << ip << "/player/" << characterID << "/approval";

	if (loggedInAccounts.size() > 0) {
		path << "?loggedin_accounts";

		for (int i = 0; i < loggedInAccounts.size(); ++i) {
			path << (i == 0 ? "=" : ",") << loggedInAccounts.get(i);
		}
	}

	apiCall(result.castTo<SWGRealmsAPIResult*>(), __FUNCTION__, path.toString(), "GET", "");
}

void SWGRealmsAPI::notifyPlayerOnline(const String& ip, uint32 accountID, uint64_t characterID,
		const SessionAPICallback& resultCallback) {
	StringBuffer path;
	path << "/v1/core3/account/" << accountID << "/galaxy/" << galaxyID << "/session/ip/" << ip << "/player/" << characterID << "/online";

	if (resultCallback != nullptr) {
		Reference<SessionApprovalResult*> result = new SessionApprovalResult(resultCallback);
		apiCall(result.castTo<SWGRealmsAPIResult*>(), __FUNCTION__, path.toString(), "GET", "");
	} else {
		apiNotify(__FUNCTION__, path.toString());
	}
}

void SWGRealmsAPI::notifyPlayerOffline(const String& ip, uint32 accountID, uint64_t characterID) {
	StringBuffer path;

	path << "/v1/core3/account/" << accountID << "/galaxy/" << galaxyID << "/session/ip/" << ip << "/player/" << characterID << "/offline";

	apiNotify(__FUNCTION__, path.toString());
}

bool SWGRealmsAPI::consoleCommand(const String& arguments) {
	StringTokenizer tokenizer(arguments);

	String subcmd;

	if (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(subcmd);
		subcmd = subcmd.toLowerCase();
	}

	if (subcmd == "help") {
		System::out << "Available swgrealms commands:" << endl
			<< "\thelp - This command" << endl
			<< "\tenable - Enable SWGRealms API" << endl
			<< "\tdisable - Disable SWGRealms API" << endl
			<< "\tstatus - SWGRealms API status" << endl
			<< "\tdryrun {off} - Control dry run setting" << endl
			<< "\tdebug {level} - Set debug logLevel (0-5)" << endl
			;
		return true;
	} else if (subcmd == "enable") {
		if (baseURL.length() == 0 || apiToken.length() == 0) {
			info(true) << "SWGRealmsAPI can not be enabled without Core3.Login.API.BaseURL and Core3.Login.API.APIToken.";
		} else {
			apiEnabled = true;
			info(true) << "SWGRealmsAPI enabled.";
		}
		return true;
	} else if (subcmd == "disable") {
		apiEnabled = false;
		info(true) << "SWGRealmsAPI disabled.";
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
			info(true) << "SWGRealmsAPI set to dry run, api calls continue but results are ignored.";
		} else {
			info(true) << "SWGRealmsAPI set to run, api results will be honored by the server.";
		}

		return true;
	} else if (subcmd == "debug" || subcmd == "debuglevel" || subcmd == "loglevel") {
		int newDebugLevel = 5;

		if (tokenizer.hasMoreTokens()) {
			newDebugLevel = tokenizer.getIntToken();
		}

		debugLevel = newDebugLevel;

		setLogLevel(static_cast<Logger::LogLevel>(debugLevel));

		if (streamer != nullptr) {
			streamer->setLogLevel(static_cast<Logger::LogLevel>(debugLevel));
		}

		info(true) << "DebugLevel set to " << debugLevel << " by console command.";

		return true;
	}

	if (subcmd == "stats") {
		auto stats = getStatsAsJSON();
		auto latency = stats["latency"];

		info(true) << "SWGRealms API Statistics:";
		info(true) << "  Total transactions: " << stats["trxCount"].get<int>();
		info(true) << "  Errors: " << stats["errCount"].get<int>();
		info(true) << "  Outstanding blocking calls: " << stats["outstandingBlockingCalls"].get<int>();
		info(true) << "  Peak concurrent calls: " << stats["peakConcurrentCalls"].get<int>();
		info(true) << "  Total blocking calls: " << stats["totalBlockingCalls"].get<int>();
		info(true) << "  Avg round-trip: " << stats["avgRoundTripMs"].get<int>() << "ms";
		info(true) << "  Avg ig-88a request: " << stats["avgRequestMs"].get<int>() << "ms";
		info(true) << "  Avg Core3 overhead: " << stats["avgProcessMs"].get<int>() << "ms";
		info(true) << "  Latency 0-10ms: " << latency["0-10ms"].get<int>();
		info(true) << "  Latency 10-50ms: " << latency["10-50ms"].get<int>();
		info(true) << "  Latency 50-100ms: " << latency["50-100ms"].get<int>();
		info(true) << "  Latency 100-500ms: " << latency["100-500ms"].get<int>();
		info(true) << "  Latency 500ms+: " << latency["500ms+"].get<int>();

		return true;
	}

	info(true) << "Unknown swgrealms subcommand: " << subcmd;

	return false;
}

JSONSerializationType SWGRealmsAPI::getStatsAsJSON() const {
	JSONSerializationType stats;

	stats["trxCount"] = trxCount.get();
	stats["errCount"] = errCount.get();
	stats["outstandingBlockingCalls"] = outstandingBlockingCalls.get();
	stats["peakConcurrentCalls"] = peakConcurrentCalls.get();
	stats["totalBlockingCalls"] = totalBlockingCalls.get();

	// Calculate averages
	int total = totalBlockingCalls.get();
	if (total > 0) {
		stats["avgRoundTripMs"] = (int)(totalRoundTripMs.get() / total);
		stats["avgRequestMs"] = (int)(totalRequestMs.get() / total);
		stats["avgProcessMs"] = (int)((totalRoundTripMs.get() - totalRequestMs.get()) / total);
	} else {
		stats["avgRoundTripMs"] = 0;
		stats["avgRequestMs"] = 0;
		stats["avgProcessMs"] = 0;
	}

	JSONSerializationType latency;
	latency["0-10ms"] = latency_0_10ms.get();
	latency["10-50ms"] = latency_10_50ms.get();
	latency["50-100ms"] = latency_50_100ms.get();
	latency["100-500ms"] = latency_100_500ms.get();
	latency["500ms+"] = latency_500plus.get();

	stats["latency"] = latency;
	stats["apiEnabled"] = apiEnabled;
	stats["galaxyID"] = galaxyID;
	stats["failOpen"] = failOpen;
	stats["dryRun"] = dryRun;
	stats["debugLevel"] = debugLevel;

	// Add streaming stats if enabled
	if (streamer != nullptr) {
		stats["streaming"] = streamer->getStatsAsJSON();
	}

	return stats;
}

SWGRealmsAPIResult::SWGRealmsAPIResult() {
	API_TRACE(this, "ctor");

	// Generate simple code for log tracing
	uint64 trxid = (System::getMikroTime() << 8) | System::random(255);

	resultClientTrxId = String::hexvalueOf(trxid);
	resultAction = ApprovalAction::UNKNOWN;
	resultElapsedTimeMS = 0ull;
	blockingReceived = false;

	resultDebug.setNullValue("<not set>");
}

SWGRealmsAPIResult::~SWGRealmsAPIResult() {
#ifdef WITH_SWGREALMS_CALLSTATS
	if (callTrace.size() > 0) {
		SWGRealmsAPI::instance()->info(true) << "TRACE [" << resultClientTrxId << "]: " << dumpTrace();
	}
#endif
}

#ifdef WITH_SWGREALMS_CALLSTATS
void SWGRealmsAPIResult::trace(const String& tag) {
	Time now;
	now.updateToCurrentTime();
	callTrace.add(Pair<String, Time>(tag, now));
}

String SWGRealmsAPIResult::dumpTrace() const {
	if (callTrace.size() == 0) {
		return "No trace data";
	}

	StringBuffer output;
	const Time& baseline = callTrace.get(0).second;
	Time previous = baseline;

	for (int i = 0; i < callTrace.size(); ++i) {
		const Pair<String, Time>& entry = callTrace.get(i);
		const String& tag = entry.first;
		const Time& timestamp = entry.second;

		uint64 totalMs = baseline.miliDifference(timestamp);
		uint64 deltaMs = previous.miliDifference(timestamp);

		if (i > 0) {
			output << ", ";
		}

		output << tag << ": +" << deltaMs << "ms (total: " << totalMs << "ms)";
		previous = timestamp;
	}

	return output.toString();
}
#endif // WITH_SWGREALMS_CALLSTATS

String SWGRealmsAPIResult::toStringData() const {
	return toString();
}

String SWGRealmsAPIResult::toString() const {
	StringBuffer buf;

	buf << TypeInfo<SWGRealmsAPIResult>::getClassName(this) << " " << this << " ["
		<< "clientTrxId: " << getClientTrxId() << ", "
		<< "trxId: " << getTrxId() << ", "
		<< "action: " << actionToString(getAction()) << ", "
		<< "title: '" << getTitle() << "', "
		<< "message: '" << getMessage() << "', "
		<< "details: '" << getDetails() << "'"
		;

	if (!jsonData.is_null()) {
		buf << ", JSON: '" << getRawJSON() << "'";
	}

	buf << ", elapsedTimeMS: " << getElapsedTimeMS();

#ifdef WITH_SWGREALMS_CALLSTATS
	if (callTrace.size() > 0) {
		buf << ", trace: [" << dumpTrace() << "]";
	}
#endif

	buf << "]";

	return buf.toString();
}

String SWGRealmsAPIResult::getLogMessage() const {
	int debugLevel = SWGRealmsAPI::instance()->getDebugLevel();

	StringBuffer buf;

	buf << TypeInfo<SWGRealmsAPIResult>::getClassName(this) << " " << this << " ["
		<< "clientTrxId: " << getClientTrxId() << ", "
		<< "trxId: " << getTrxId() << ", "
		<< "action: " << actionToString(getAction()) << ", "
		;

	if (debugLevel == Logger::DEBUG) {
		buf << "message: '" << getMessage() << "', ";
	}

	buf << "details: '" << getDetails() << "'" ;

	if (debugLevel == Logger::DEBUG && !jsonData.is_null()) {
		buf << ", JSON: '" << getRawJSON() << "'";
	}

	buf << ", elapsedTimeMS: " << getElapsedTimeMS() << "]";

	return buf.toString();
}

SessionApprovalResult::SessionApprovalResult() {
	resultAccountID = 0;
	resultStationID = 0;
}

SessionApprovalResult::SessionApprovalResult(const SessionAPICallback& resultCallback) {
	resultAccountID = 0;
	resultStationID = 0;
	callback = [this, resultCallback]() {
		resultCallback(*this);
	};
}

bool SessionApprovalResult::parse() {
	// Parse session-specific fields from jsonData
	if (jsonData.is_null()) {
		return true; // Nothing to parse
	}

	try {
		if (jsonData.has_field(U("eip"))) {
			resultEncryptedIP = conversions::to_utf8string(jsonData[U("eip")].as_string());
		}

		if (jsonData.has_field(U("session_id"))) {
			resultSessionID = conversions::to_utf8string(jsonData[U("session_id")].as_string());
		}

		if (jsonData.has_field(U("account_id"))) {
			auto field = jsonData[U("account_id")];
			if (field.is_number()) {
				resultAccountID = (uint32)field.as_number().to_uint32();
			}
		}

		if (jsonData.has_field(U("station_id"))) {
			auto field = jsonData[U("station_id")];
			if (field.is_number()) {
				resultStationID = (uint32)field.as_number().to_uint32();
			}
		}

		return true;
	} catch (const web::json::json_exception&) {
		// Parsing error - return false but don't log here (apiCall will handle)
		return false;
	}
}

AccountResult::AccountResult(Reference<Account*> acc) {
	account = acc;
	accountID = 0;
	accountIDOnly = false;
}

AccountResult::AccountResult() {
	account = nullptr;
	accountID = 0;
	accountIDOnly = true;  // This is for getAccountID() calls
}

bool AccountResult::parse() {
	// Parse account data from jsonData
	if (jsonData.is_null()) {
		return false;
	}

	try {
		// Check if this is just an ID lookup or full account data
		if (!jsonData.has_field(U("account"))) {
			return false;
		}

		auto accountObj = jsonData[U("account")];

		if (!accountObj.has_field(U("account_id"))) {
			return false;
		}

		accountID = accountObj[U("account_id")].as_integer();

		// If this is accountID-only lookup, we're done
		if (accountIDOnly || account == nullptr) {
			return true;
		}

		// Parse full account data into Account object
		if (!accountObj.has_field(U("station_id")) || !accountObj.has_field(U("username")) ||
		    !accountObj.has_field(U("active"))) {
			return false;
		}

		uint32 stationID = accountObj[U("station_id")].as_integer();
		String username = conversions::to_utf8string(accountObj[U("username")].as_string());
		bool active = accountObj[U("active")].as_bool();
		uint32 adminLevel = accountObj.has_field(U("admin_level")) ? accountObj[U("admin_level")].as_integer() : 0;
		uint32 created = accountObj.has_field(U("created")) ? accountObj[U("created")].as_integer() : 0;

		// Ban fields
		uint32 banExpires = 0;
		String banReason = "";
		uint32 banAdmin = 0;

		if (accountObj.has_field(U("ban_expires"))) {
			banExpires = accountObj[U("ban_expires")].as_integer();
		}

		if (accountObj.has_field(U("ban_reason"))) {
			banReason = conversions::to_utf8string(accountObj[U("ban_reason")].as_string());
		}

		if (accountObj.has_field(U("ban_admin"))) {
			banAdmin = accountObj[U("ban_admin")].as_integer();
		}

		// Parse valid_until for caching
		Time validUntil;
		if (jsonData.has_field(U("valid_until"))) {
			if (jsonData[U("valid_until")].is_number()) {
				uint64 timestamp = jsonData[U("valid_until")].as_number().to_uint64();
				validUntil = Time((uint32)timestamp);
			} else if (jsonData[U("valid_until")].is_string()) {
				String isoTimestamp = conversions::to_utf8string(jsonData[U("valid_until")].as_string());
				validUntil = Time::fromISO8601(isoTimestamp);
			}
		}

		// Update account object
		Locker locker(account);
		account->setAccountID(accountID);
		account->setStationID(stationID);
		account->setUsername(username);
		account->setActive(active);
		account->setAdminLevel(adminLevel);
		account->setTimeCreated(created);
		account->setBanExpires(banExpires);
		account->setBanReason(banReason);
		account->setBanAdmin(banAdmin);
		account->setAccountDataValidUntil(validUntil);

		// Set default TTL if none provided
		if (account->getAccountDataValidUntil()->getTime() == 0) {
			Time defaultTTL;
			defaultTTL.addMiliTime(300000); // 5 minute default
			account->setAccountDataValidUntil(defaultTTL);
		}

		return true;

	} catch (const web::json::json_exception&) {
		return false;
	} catch (const std::exception&) {
		return false;
	}
}

bool SWGRealmsAPI::apiCallBlocking(Reference<SWGRealmsAPIResult*> result, const String& path, const String& method,
                                    const String& body, String& errorMessage) {
	if (!apiEnabled) {
		errorMessage = "SWGRealms API is not enabled";
		return false;
	}

	// Track blocking call statistics
	Time startTime;
	outstandingBlockingCalls.increment();
	totalBlockingCalls.increment();

	// Update peak if needed
	int current = outstandingBlockingCalls.get();
	int peak = peakConcurrentCalls.get();
	while (current > peak) {
		if (peakConcurrentCalls.compareAndSet(peak, current)) {
			break;
		}
		peak = peakConcurrentCalls.get();
	}

	// Reset blocking state
	result->blockingReceived = false;

	// Set callback that signals completion
	result->callback = [result]() {
		Locker lock(&result->blockingMutex);
		result->blockingReceived = true;
		result->blockingCondition.broadcast();
	};

	// Make API call - result will be populated and callback invoked
	apiCall(result, "apiCallBlocking", path, method, body);

	// Wait for result with timeout using result's members
	Locker lock(&result->blockingMutex);
	if (!result->blockingReceived) {
		Time timeout;
		timeout.addMiliTime(apiTimeoutMs);

		if (result->blockingCondition.timedWait(&result->blockingMutex, &timeout) != 0) {
			errorMessage = "Timeout waiting for API response";
			return false;
		}
	}

	// Update statistics before return
	outstandingBlockingCalls.decrement();

	uint64 elapsed = startTime.miliDifference();
	totalRoundTripMs.add(elapsed);

	// Extract ig-88a's req_time_ms if available
	String reqTimeStr = result->getDebugValue("req_time_ms");
	if (!reqTimeStr.isEmpty()) {
		try {
			int reqTime = Integer::valueOf(reqTimeStr);
			totalRequestMs.add(reqTime);
		} catch (...) {
			// Ignore parse errors
		}
	}

	// Latency histogram
	if (elapsed < 10) {
		latency_0_10ms.increment();
	} else if (elapsed < 50) {
		latency_10_50ms.increment();
	} else if (elapsed < 100) {
		latency_50_100ms.increment();
	} else if (elapsed < 500) {
		latency_100_500ms.increment();
	} else {
		latency_500plus.increment();
	}

	// Check result status
	if (!result->isActionAllowed()) {
		errorMessage = result->getMessage(true);
		return false;
	}

	return true;
}

void SWGRealmsAPI::updateClientIPAddress(ZoneClientSession* client, const SessionApprovalResult& result) {
	if (client != nullptr && !result.getEncryptedIP().isEmpty()) {
		auto oldIP = client->getIPAddress();

		Locker lock(client);
		client->setIPAddress(result.getEncryptedIP());
	}
}

bool SWGRealmsAPI::parseAccountFromJSON(const String& jsonStr, Reference<Account*> account, String& errorMessage) {
	if (account == nullptr) {
		errorMessage = "Account reference is null";
		return false;
	}

	try {
		auto rootJson = json::value::parse(conversions::to_string_t(jsonStr.toCharArray()));

		if (!rootJson.is_object()) {
			errorMessage = "Response is not a JSON object";
			return false;
		}

		// Extract the "account" field from the root response
		if (!rootJson.has_field(U("account"))) {
			errorMessage = "Missing 'account' field in JSON response";
			return false;
		}

		auto jsonValue = rootJson[U("account")];

		// Parse required fields from account object
		if (!jsonValue.has_field(U("account_id")) || !jsonValue.has_field(U("station_id")) ||
		    !jsonValue.has_field(U("username")) || !jsonValue.has_field(U("active"))) {
			errorMessage = "Missing required fields in account object";
			return false;
		}

		uint32 accountID = jsonValue[U("account_id")].as_integer();
		uint32 stationID = jsonValue[U("station_id")].as_integer();
		String username = conversions::to_utf8string(jsonValue[U("username")].as_string());
		bool active = jsonValue[U("active")].as_bool();

		// Optional fields with defaults
		uint32 adminLevel = jsonValue.has_field(U("admin_level")) ? jsonValue[U("admin_level")].as_integer() : 0;
		uint32 created = jsonValue.has_field(U("created")) ? jsonValue[U("created")].as_integer() : 0;

		// Ban fields
		uint32 banExpires = 0;
		String banReason = "";
		uint32 banAdmin = 0;

		if (jsonValue.has_field(U("ban_expires"))) {
			banExpires = jsonValue[U("ban_expires")].as_integer();
		}

		if (jsonValue.has_field(U("ban_reason"))) {
			banReason = conversions::to_utf8string(jsonValue[U("ban_reason")].as_string());
		}

		if (jsonValue.has_field(U("ban_admin"))) {
			banAdmin = jsonValue[U("ban_admin")].as_integer();
		}

		// Parse valid_until for caching (supports both Unix timestamp and ISO 8601)
		Time validUntil;
		if (rootJson.has_field(U("valid_until"))) {
			if (rootJson[U("valid_until")].is_number()) {
				uint64 timestamp = rootJson[U("valid_until")].as_number().to_uint64();
				validUntil = Time((uint32)timestamp);
			} else if (rootJson[U("valid_until")].is_string()) {
				// ISO 8601 timestamp (e.g., "2025-10-03T10:25:30Z")
				String isoTimestamp = conversions::to_utf8string(rootJson[U("valid_until")].as_string());
				validUntil = Time::fromISO8601(isoTimestamp);

				if (validUntil.getTime() == 0) {
					error() << "Failed to parse ISO 8601 timestamp: " << isoTimestamp;
				}
			}
		}

		// Update account object
		Locker locker(account);

		account->setAccountID(accountID);
		account->setStationID(stationID);
		account->setUsername(username);
		account->setActive(active);
		account->setAdminLevel(adminLevel);
		account->setTimeCreated(created);
		account->setBanExpires(banExpires);
		account->setBanReason(banReason);
		account->setBanAdmin(banAdmin);
		account->setAccountDataValidUntil(validUntil);

		return true;

	} catch (const json::json_exception& e) {
		errorMessage = String("JSON parsing error: ") + e.what();
		return false;
	} catch (const std::exception& e) {
		errorMessage = String("Exception parsing account JSON: ") + e.what();
		return false;
	}
}

bool SWGRealmsAPI::getAccountDataBlocking(uint32 accountID, Reference<Account*> account, String& errorMessage) {
	if (account == nullptr) {
		errorMessage = "Account reference is null";
		return false;
	}

	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/account/" << accountID;

	Reference<AccountResult*> result = new AccountResult(account);
	return apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "GET", "", errorMessage);
}

uint32 SWGRealmsAPI::getAccountID(const String& username, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/account/" << username;

	Reference<AccountResult*> result = new AccountResult();  // accountID-only mode
	if (!apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "GET", "", errorMessage)) {
		return 0;
	}

	return result->getAccountID();
}

bool SWGRealmsAPI::parseAccountBanStatusFromJSON(const String& jsonStr, Reference<Account*> account, String& errorMessage) {
	if (account == nullptr) {
		errorMessage = "Account reference is null";
		return false;
	}

	try {
		auto jsonValue = json::value::parse(conversions::to_string_t(jsonStr.toCharArray()));

		if (!jsonValue.is_object()) {
			errorMessage = "Response is not a JSON object";
			return false;
		}

		// Check isbanned flag - optimization to avoid parsing when not banned
		if (!jsonValue.has_field(U("isbanned"))) {
			errorMessage = "Missing isbanned field in response";
			return false;
		}

		bool isBanned = jsonValue[U("isbanned")].as_bool();

		if (!isBanned) {
			// No ban data to parse, success with no updates
			return true;
		}

		// Parse ban data (only present when isbanned=true)
		if (!jsonValue.has_field(U("active")) || !jsonValue.has_field(U("admin_level"))) {
			errorMessage = "Missing required fields in ban status JSON response";
			return false;
		}

		bool active = jsonValue[U("active")].as_bool();
		uint32 adminLevel = jsonValue[U("admin_level")].as_integer();

		// Ban fields (required when isbanned=true)
		uint32 banExpires = 0;
		String banReason = "";
		uint32 banAdmin = 0;

		if (jsonValue.has_field(U("ban_expires"))) {
			banExpires = jsonValue[U("ban_expires")].as_integer();
		}

		if (jsonValue.has_field(U("ban_reason"))) {
			banReason = conversions::to_utf8string(jsonValue[U("ban_reason")].as_string());
		}

		if (jsonValue.has_field(U("ban_admin"))) {
			banAdmin = jsonValue[U("ban_admin")].as_integer();
		}

		// Update account object with ban status
		Locker locker(account);

		account->setActive(active);
		account->setAdminLevel(adminLevel);
		account->setBanExpires(banExpires);
		account->setBanReason(banReason);
		account->setBanAdmin(banAdmin);

		return true;

	} catch (const json::json_exception& e) {
		errorMessage = String("JSON parsing error: ") + e.what();
		return false;
	} catch (const std::exception& e) {
		errorMessage = String("Exception parsing ban status JSON: ") + e.what();
		return false;
	}
}

bool SWGRealmsAPI::getAccountBanStatusBlocking(uint32 accountID, Reference<Account*> account, String& errorMessage) {
	if (account == nullptr) {
		errorMessage = "Account reference is null";
		return false;
	}

	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/account/" << accountID << "/isbanned";

	// TODO: Create BanStatusResult or reuse AccountResult for ban status parsing
	// For now, keep using parseAccountBanStatusFromJSON until we refactor
	Reference<SimpleResult*> result = new SimpleResult();
	if (!apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "GET", "", errorMessage)) {
		return false;
	}

	// Parse ban status from result's jsonData
	return parseAccountBanStatusFromJSON(result->getRawJSON(), account, errorMessage);
}

bool SWGRealmsAPI::banAccountBlocking(uint32 accountID, uint32 issuerID, uint64 expiresTimestamp,
                                       const String& reason, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/account/" << accountID << "/ban";

	auto jsonBody = json::value::object();
	jsonBody[U("issuer_id")] = json::value::number(issuerID);
	jsonBody[U("expires")] = json::value::number(static_cast<double>(expiresTimestamp));
	jsonBody[U("reason")] = json::value::string(U(reason.toCharArray()));

	Reference<SimpleResult*> result = new SimpleResult();
	return apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "POST", String(jsonBody.serialize().c_str()), errorMessage);
}

bool SWGRealmsAPI::unbanAccountBlocking(uint32 accountID, const String& reason, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/account/" << accountID << "/unban";

	auto jsonBody = json::value::object();
	jsonBody[U("reason")] = json::value::string(U(reason.toCharArray()));

	Reference<SimpleResult*> result = new SimpleResult();
	return apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "PUT", String(jsonBody.serialize().c_str()), errorMessage);
}

bool SWGRealmsAPI::parseGalaxyBansFromJSON(const String& jsonStr, VectorMap<uint32, Reference<GalaxyBanEntry*>>& galaxyBans, String& errorMessage) {
	try {
		auto jsonValue = json::value::parse(conversions::to_string_t(jsonStr.toCharArray()));

		if (!jsonValue.is_object()) {
			errorMessage = "Response is not a JSON object";
			return false;
		}

		// Check for bans array
		if (!jsonValue.has_field(U("bans"))) {
			errorMessage = "Missing bans field in response";
			return false;
		}

		auto bansArray = jsonValue[U("bans")];
		if (!bansArray.is_array()) {
			errorMessage = "bans field is not an array";
			return false;
		}

		// Clear existing bans
		galaxyBans.removeAll();

		// Parse each ban entry
		for (auto& banValue : bansArray.as_array()) {
			if (!banValue.is_object()) {
				continue; // Skip invalid entries
			}

			Reference<GalaxyBanEntry*> entry = new GalaxyBanEntry();

			if (banValue.has_field(U("account_id"))) {
				entry->setAccountID(banValue[U("account_id")].as_integer());
			}

			if (banValue.has_field(U("issuer_id"))) {
				entry->setBanAdmin(banValue[U("issuer_id")].as_integer());
			}

			if (banValue.has_field(U("galaxy_id"))) {
				entry->setGalaxyID(banValue[U("galaxy_id")].as_integer());
			}

			if (banValue.has_field(U("created"))) {
				Time bancreated(banValue[U("created")].as_integer());
				entry->setCreationDate(bancreated);
			}

			if (banValue.has_field(U("expires"))) {
				Time banexpires(banValue[U("expires")].as_integer());
				entry->setBanExpiration(banexpires);
			}

			if (banValue.has_field(U("reason"))) {
				String reason = conversions::to_utf8string(banValue[U("reason")].as_string());
				entry->setBanReason(reason);
			}

			// Add to map keyed by galaxy_id
			galaxyBans.put(entry->getGalaxyID(), entry);
		}

		return true;

	} catch (const json::json_exception& e) {
		errorMessage = String("JSON parse error: ") + e.what();
		return false;
	} catch (const Exception& e) {
		errorMessage = String("Error parsing galaxy bans: ") + e.getMessage();
		return false;
	}
}

bool SWGRealmsAPI::getGalaxyBansBlocking(uint32 accountID, VectorMap<uint32, Reference<GalaxyBanEntry*>>& galaxyBans, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/account/" << accountID << "/galaxybans";

	Reference<SimpleResult*> result = new SimpleResult();
	if (!apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "GET", "", errorMessage)) {
		return false;
	}

	// Parse galaxy bans from result's jsonData
	return parseGalaxyBansFromJSON(result->getRawJSON(), galaxyBans, errorMessage);
}

bool SWGRealmsAPI::banFromGalaxyBlocking(uint32 accountID, uint32 targetGalaxyID, uint32 issuerID, uint64 expiresTimestamp,
                                          const String& reason, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/account/" << accountID << "/galaxyban";

	auto jsonBody = json::value::object();
	jsonBody[U("galaxy_id")] = json::value::number(targetGalaxyID);
	jsonBody[U("issuer_id")] = json::value::number(issuerID);
	jsonBody[U("expires")] = json::value::number(static_cast<double>(expiresTimestamp));
	jsonBody[U("reason")] = json::value::string(U(reason.toCharArray()));

	Reference<SimpleResult*> result = new SimpleResult();
	return apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "POST", String(jsonBody.serialize().c_str()), errorMessage);
}

bool SWGRealmsAPI::unbanFromGalaxyBlocking(uint32 accountID, uint32 targetGalaxyID, const String& reason, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/account/" << accountID << "/galaxyban/" << targetGalaxyID;

	auto jsonBody = json::value::object();
	jsonBody[U("reason")] = json::value::string(U(reason.toCharArray()));

	Reference<SimpleResult*> result = new SimpleResult();
	return apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "PUT", String(jsonBody.serialize().c_str()), errorMessage);
}

bool SWGRealmsAPI::parseCharacterBansFromJSON(const String& jsonStr, VectorMap<String, Reference<CharacterListEntry*>>& characterBans, String& errorMessage) {
	try {
		auto jsonValue = json::value::parse(conversions::to_string_t(jsonStr.toCharArray()));

		if (!jsonValue.is_object()) {
			errorMessage = "Response is not a JSON object";
			return false;
		}

		// Check for bans array
		if (!jsonValue.has_field(U("bans"))) {
			errorMessage = "Missing bans field in response";
			return false;
		}

		auto bansArray = jsonValue[U("bans")];
		if (!bansArray.is_array()) {
			errorMessage = "bans field is not an array";
			return false;
		}

		// Clear existing bans
		characterBans.removeAll();

		// Parse each ban entry
		for (auto& banValue : bansArray.as_array()) {
			if (!banValue.is_object()) {
				continue; // Skip invalid entries
			}

			Reference<CharacterListEntry*> entry = new CharacterListEntry();

			uint32 galaxyID = 0;
			String characterName;

			if (banValue.has_field(U("account_id"))) {
				entry->setAccountID(banValue[U("account_id")].as_integer());
			}

			if (banValue.has_field(U("issuer_id"))) {
				entry->setBanAdmin(banValue[U("issuer_id")].as_integer());
			}

			if (banValue.has_field(U("galaxy_id"))) {
				galaxyID = banValue[U("galaxy_id")].as_integer();
				entry->setGalaxyID(galaxyID);
			}

			if (banValue.has_field(U("name"))) {
				characterName = conversions::to_utf8string(banValue[U("name")].as_string());
				entry->setFirstName(characterName);
			}

			if (banValue.has_field(U("expires"))) {
				Time banexpires(banValue[U("expires")].as_integer());
				entry->setBanExpiration(banexpires);
			}

			if (banValue.has_field(U("reason"))) {
				String reason = conversions::to_utf8string(banValue[U("reason")].as_string());
				entry->setBanReason(reason);
			}

			// Build key as "galaxyID:name"
			StringBuffer keyBuffer;
			keyBuffer << galaxyID << ":" << characterName;
			characterBans.put(keyBuffer.toString(), entry);
		}

		return true;

	} catch (const json::json_exception& e) {
		errorMessage = String("JSON parse error: ") + e.what();
		return false;
	} catch (const Exception& e) {
		errorMessage = String("Error parsing character bans: ") + e.getMessage();
		return false;
	}
}

bool SWGRealmsAPI::getCharacterBansBlocking(uint32 accountID, VectorMap<String, Reference<CharacterListEntry*>>& characterBans, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/account/" << accountID << "/characterbans";

	Reference<SimpleResult*> result = new SimpleResult();
	if (!apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "GET", "", errorMessage)) {
		return false;
	}

	// Parse character bans from result's jsonData
	return parseCharacterBansFromJSON(result->getRawJSON(), characterBans, errorMessage);
}

bool SWGRealmsAPI::banCharacterBlocking(uint32 accountID, uint32 targetGalaxyID, const String& name, uint32 issuerID,
                                         uint64 expiresTimestamp, const String& reason, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/account/" << accountID << "/characterban";

	auto jsonBody = json::value::object();
	jsonBody[U("galaxy_id")] = json::value::number(targetGalaxyID);
	jsonBody[U("name")] = json::value::string(U(name.toCharArray()));
	jsonBody[U("issuer_id")] = json::value::number(issuerID);
	jsonBody[U("expires")] = json::value::number(static_cast<double>(expiresTimestamp));
	jsonBody[U("reason")] = json::value::string(U(reason.toCharArray()));

	Reference<SimpleResult*> result = new SimpleResult();
	return apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "POST", String(jsonBody.serialize().c_str()), errorMessage);
}

bool SWGRealmsAPI::unbanCharacterBlocking(uint32 accountID, uint32 targetGalaxyID, const String& name, const String& reason, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/account/" << accountID << "/characterban/";

	// URL-encode name for path
	String escapedName = name;
	Database::escapeString(escapedName);
	pathBuffer << escapedName;

	auto jsonBody = json::value::object();
	jsonBody[U("galaxy_id")] = json::value::number(targetGalaxyID);
	jsonBody[U("reason")] = json::value::string(U(reason.toCharArray()));

	Reference<SimpleResult*> result = new SimpleResult();
	return apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "PUT", String(jsonBody.serialize().c_str()), errorMessage);
}

// ============================================================================
// Character Operations
// ============================================================================

bool SWGRealmsAPI::createCharacterBlocking(uint64 characterOID, uint32 accountID, uint32 galaxyID,
                                            const String& firstname, const String& surname,
                                            uint32 race, uint32 gender, const String& templatePath,
                                            const String& reservationID, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/account/" << accountID << "/characters";

	auto jsonBody = json::value::object();
	jsonBody[U("character_oid")] = json::value::number(static_cast<double>(characterOID));
	jsonBody[U("account_id")] = json::value::number(accountID);
	jsonBody[U("galaxy_id")] = json::value::number(galaxyID);
	jsonBody[U("firstname")] = json::value::string(U(firstname.toCharArray()));
	jsonBody[U("surname")] = json::value::string(U(surname.toCharArray()));
	jsonBody[U("race")] = json::value::number(race);
	jsonBody[U("gender")] = json::value::number(gender);
	jsonBody[U("template")] = json::value::string(U(templatePath.toCharArray()));

	if (!reservationID.isEmpty()) {
		jsonBody[U("reservation_id")] = json::value::string(U(reservationID.toCharArray()));
	}

	Reference<SimpleResult*> result = new SimpleResult();
	return apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "POST", String(jsonBody.serialize().c_str()), errorMessage);
}

bool SWGRealmsAPI::parseCharacterListFromJSON(const String& jsonStr, Vector<CharacterListEntry>& characters, String& errorMessage) {
	try {
		auto jsonValue = json::value::parse(conversions::to_string_t(jsonStr.toCharArray()));

		if (!jsonValue.is_object()) {
			errorMessage = "Response is not a JSON object";
			return false;
		}

		if (!jsonValue.has_field(U("characters"))) {
			errorMessage = "Missing characters field in response";
			return false;
		}

		auto charactersArray = jsonValue[U("characters")];
		if (!charactersArray.is_array()) {
			errorMessage = "characters field is not an array";
			return false;
		}

		characters.removeAll();

		for (auto& charValue : charactersArray.as_array()) {
			if (!charValue.is_object()) {
				continue;
			}

			CharacterListEntry entry;

			if (charValue.has_field(U("character_oid"))) {
				entry.setObjectID(charValue[U("character_oid")].as_number().to_uint64());
			}

			if (charValue.has_field(U("account_id"))) {
				entry.setAccountID(charValue[U("account_id")].as_integer());
			}

			if (charValue.has_field(U("galaxy_id"))) {
				entry.setGalaxyID(charValue[U("galaxy_id")].as_integer());
			}

			if (charValue.has_field(U("firstname"))) {
				entry.setFirstName(conversions::to_utf8string(charValue[U("firstname")].as_string()));
			}

			if (charValue.has_field(U("surname"))) {
				entry.setSurName(conversions::to_utf8string(charValue[U("surname")].as_string()));
			}

			if (charValue.has_field(U("gender"))) {
				entry.setGender(charValue[U("gender")].as_integer());
			}

			if (charValue.has_field(U("template"))) {
				String templateStr = conversions::to_utf8string(charValue[U("template")].as_string());
				entry.setRace(templateStr.hashCode());
			}

			if (charValue.has_field(U("creation_date"))) {
				Time createdTime((uint32)charValue[U("creation_date")].as_number().to_uint64());
				entry.setCreationDate(createdTime);
			}

			if (charValue.has_field(U("galaxy_name"))) {
				entry.setGalaxyName(conversions::to_utf8string(charValue[U("galaxy_name")].as_string()));
			}

			characters.add(entry);
		}

		return true;

	} catch (const json::json_exception& e) {
		errorMessage = String("JSON parse error: ") + e.what();
		return false;
	} catch (const Exception& e) {
		errorMessage = String("Error parsing character list: ") + e.getMessage();
		return false;
	}
}

bool SWGRealmsAPI::getCharacterListBlocking(uint32 accountID, Vector<CharacterListEntry>& characters, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/account/" << accountID << "/characters";

	Reference<SimpleResult*> result = new SimpleResult();
	if (!apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "GET", "", errorMessage)) {
		return false;
	}

	return parseCharacterListFromJSON(result->getRawJSON(), characters, errorMessage);
}

JSONSerializationType SWGRealmsAPI::getCharacterBlocking(uint64 characterOID, uint32 galaxyID, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/characters/" << characterOID;

	Reference<SimpleResult*> result = new SimpleResult();
	if (!apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "GET", "", errorMessage)) {
		return JSONSerializationType::object();  // Return empty object on API failure
	}

	// Parse raw JSON string into nlohmann JSONSerializationType
	try {
		JSONSerializationType response = JSONSerializationType::parse(result->getRawJSON().toCharArray());

		if (response.contains("character") && !response["character"].is_null()) {
			return response["character"];  // Return character object
		}

		errorMessage = "No character field in response";
		return JSONSerializationType::object();  // Not found
	} catch (const std::exception& e) {
		errorMessage = String("JSON parse error: ") + e.what();
		return JSONSerializationType::object();
	}
}

bool SWGRealmsAPI::beginCharactersCommitBlocking(uint32 galaxyID, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/characters?filter=dirty";

	Reference<SimpleResult*> result = new SimpleResult();
	return apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "GET", "", errorMessage);
}

bool SWGRealmsAPI::commitCharactersBlocking(uint32 galaxyID, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/characters/commit";

	Reference<SimpleResult*> result = new SimpleResult();
	return apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "PUT", "", errorMessage);
}

bool SWGRealmsAPI::updateCharacterFirstNameBlocking(uint64 characterOID, uint32 galaxyID,
                                                     const String& firstname, String& errorMessage) {
	// Validate that firstname is not empty - we should never allow blank firstnames
	if (firstname.isEmpty()) {
		errorMessage = "First name cannot be empty";
		return false;
	}

	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/characters/" << characterOID;

	auto jsonBody = json::value::object();
	jsonBody[U("firstname")] = json::value::string(U(firstname.toCharArray()));

	Reference<SimpleResult*> result = new SimpleResult();
	return apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "PUT", String(jsonBody.serialize().c_str()), errorMessage);
}

bool SWGRealmsAPI::updateCharacterSurNameBlocking(uint64 characterOID, uint32 galaxyID,
                                                   const String& surname, String& errorMessage) {
	// Always send surname value, even if empty - this allows CSRs to blank out surnames
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/characters/" << characterOID;

	auto jsonBody = json::value::object();
	jsonBody[U("surname")] = json::value::string(U(surname.toCharArray()));

	Reference<SimpleResult*> result = new SimpleResult();
	return apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "PUT", String(jsonBody.serialize().c_str()), errorMessage);
}

bool SWGRealmsAPI::deleteCharacterBlocking(uint64 characterOID, uint32 accountID, uint32 galaxyID, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/account/" << accountID << "/characters/" << characterOID;

	Reference<SimpleResult*> result = new SimpleResult();
	return apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "DELETE", "", errorMessage);
}

bool SWGRealmsAPI::rollbackCharactersBlocking(uint32 galaxyID, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/characters/rollback";

	Reference<SimpleResult*> result = new SimpleResult();
	return apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "DELETE", "", errorMessage);
}

bool SWGRealmsAPI::beginPurgeBatchBlocking(uint32 galaxyID, uint32 limit, Vector<uint64>& characterOIDs,
                                            String& batchID, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/characters?filter=deleted&limit=" << limit;

	Reference<SimpleResult*> result = new SimpleResult();
	if (!apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "GET", "", errorMessage)) {
		return false;
	}

	// Parse response to get batch_id and character OIDs
	try {
		auto jsonValue = json::value::parse(conversions::to_string_t(result->getRawJSON().toCharArray()));

		if (!jsonValue.is_object()) {
			errorMessage = "Response is not a JSON object";
			return false;
		}

		if (jsonValue.has_field(U("batch_id"))) {
			auto batchIdValue = jsonValue[U("batch_id")];
			if (batchIdValue.is_null()) {
				// No deleted characters to purge
				batchID = "";
				characterOIDs.removeAll();
				return true;
			}
			batchID = conversions::to_utf8string(batchIdValue.as_string());
		} else {
			errorMessage = "Missing batch_id in response";
			return false;
		}

		if (!jsonValue.has_field(U("characters"))) {
			errorMessage = "Missing characters field in response";
			return false;
		}

		auto charactersArray = jsonValue[U("characters")];
		if (!charactersArray.is_array()) {
			errorMessage = "characters field is not an array";
			return false;
		}

		characterOIDs.removeAll();

		for (auto& charValue : charactersArray.as_array()) {
			if (!charValue.is_object()) {
				continue;
			}

			if (charValue.has_field(U("character_oid"))) {
				uint64 oid = charValue[U("character_oid")].as_number().to_uint64();
				characterOIDs.add(oid);
			}
		}

		return true;

	} catch (const json::json_exception& e) {
		errorMessage = String("JSON parse error: ") + e.what();
		return false;
	} catch (const Exception& e) {
		errorMessage = String("Error parsing begin purge response: ") + e.getMessage();
		return false;
	}
}

bool SWGRealmsAPI::commitPurgeBatchBlocking(uint32 galaxyID, const String& batchID, String& errorMessage) {
	String escapedBatchID = batchID;
	Database::escapeString(escapedBatchID);

	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/characters/purge?batch_id=" << escapedBatchID;

	Reference<SimpleResult*> result = new SimpleResult();
	return apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "PUT", "", errorMessage);
}

bool SWGRealmsAPI::loadCharacterNamesBlocking(uint32 galaxyID, CharacterNameMap& nameMap, String& errorMessage) {
	Time startTime;
	startTime.updateToCurrentTime();

	const uint32 pageSize = 10000;
	uint32 offset = 0;
	bool hasMore = true;
	uint32 totalLoaded = 0;

	while (hasMore) {
		StringBuffer pathBuffer;
		pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/characters/names?limit=" << pageSize << "&offset=" << offset;

		Reference<SimpleResult*> result = new SimpleResult();
		if (!apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "GET", "", errorMessage)) {
			return false;
		}

		// Parse response
		try {
			auto jsonValue = json::value::parse(conversions::to_string_t(result->getRawJSON().toCharArray()));

			if (!jsonValue.is_object()) {
				errorMessage = "Response is not a JSON object";
				return false;
			}

			if (!jsonValue.has_field(U("names"))) {
				errorMessage = "Missing names field in response";
				return false;
			}

			auto namesArray = jsonValue[U("names")];
			if (!namesArray.is_array()) {
				errorMessage = "names field is not an array";
				return false;
			}

			uint32 pageCount = 0;

			for (auto& nameValue : namesArray.as_array()) {
				// Compact tuple format: [character_oid, firstname]
				if (!nameValue.is_array() || nameValue.size() < 2) {
					continue;
				}

				uint64 oid = nameValue[0].as_number().to_uint64();
				String firstname = conversions::to_utf8string(nameValue[1].as_string());

				if (!nameMap.put(firstname.toLowerCase(), oid)) {
					error("error colliding name: " + firstname.toLowerCase());
				}

				pageCount++;
			}

			totalLoaded += pageCount;
			hasMore = (pageCount == pageSize);
			offset += pageSize;

		} catch (const json::json_exception& e) {
			errorMessage = String("JSON parse error: ") + e.what();
			return false;
		} catch (const Exception& e) {
			errorMessage = String("Error parsing character names: ") + e.getMessage();
			return false;
		}
	}

	Time endTime;
	endTime.updateToCurrentTime();
	uint64 elapsed = startTime.miliDifference(endTime);

	float namesPerSec = totalLoaded > 0 ? (totalLoaded / (elapsed / 1000.0f)) : 0;

	info(true) << "Loaded " << totalLoaded << " character names via API in " << elapsed << "ms (" << (int)namesPerSec << " names/s)";
	return true;
}

bool SWGRealmsAPI::reserveCharacterNameBlocking(uint32 galaxyID, const String& firstname, const String& surname,
                                                 String& reservationID, String& errorMessage) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID << "/characters/names";

	auto jsonBody = json::value::object();
	jsonBody[U("firstname")] = json::value::string(U(firstname.toCharArray()));

	if (!surname.isEmpty()) {
		jsonBody[U("surname")] = json::value::string(U(surname.toCharArray()));
	}

	Reference<SimpleResult*> result = new SimpleResult();
	if (!apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "POST", String(jsonBody.serialize().c_str()), errorMessage)) {
		return false;
	}

	// Parse reservation_id from response
	try {
		auto jsonValue = json::value::parse(conversions::to_string_t(result->getRawJSON().toCharArray()));

		if (!jsonValue.is_object()) {
			errorMessage = "Response is not a JSON object";
			return false;
		}

		if (jsonValue.has_field(U("reservation_id"))) {
			reservationID = conversions::to_utf8string(jsonValue[U("reservation_id")].as_string());
			return true;
		} else {
			errorMessage = "Missing reservation_id in response";
			return false;
		}

	} catch (const json::json_exception& e) {
		errorMessage = String("JSON parse error: ") + e.what();
		return false;
	} catch (const Exception& e) {
		errorMessage = String("Error parsing name reservation: ") + e.getMessage();
		return false;
	}
}

bool SWGRealmsAPI::parseGalaxyListFromJSON(const String& jsonStr, Vector<Galaxy>& galaxies, String& errorMessage) {
	try {
		auto jsonValue = json::value::parse(conversions::to_string_t(jsonStr.toCharArray()));

		if (!jsonValue.is_object()) {
			errorMessage = "Response is not a JSON object";
			return false;
		}

		if (!jsonValue.has_field(U("galaxies"))) {
			errorMessage = "Missing galaxies field in response";
			return false;
		}

		auto galaxiesArray = jsonValue[U("galaxies")];
		if (!galaxiesArray.is_array()) {
			errorMessage = "galaxies field is not an array";
			return false;
		}

		galaxies.removeAll();

		for (auto& galaxyObj : galaxiesArray.as_array()) {
			if (!galaxyObj.is_object()) {
				continue;
			}

			uint32 galaxyID = 0;

			if (galaxyObj.has_field(U("galaxy_id"))) {
				galaxyID = galaxyObj[U("galaxy_id")].as_integer();
			} else {
				errorMessage = "missing galaxy_id in result";
				return false;
			}

			Galaxy galaxy(galaxyID);

			if (galaxyObj.has_field(U("name"))) {
				galaxy.setName(conversions::to_utf8string(galaxyObj[U("name")].as_string()));
			}
			if (galaxyObj.has_field(U("address"))) {
				galaxy.setAddress(conversions::to_utf8string(galaxyObj[U("address")].as_string()));
			}
			if (galaxyObj.has_field(U("port"))) {
				galaxy.setPort(galaxyObj[U("port")].as_integer());
			}
#ifdef USE_RANDOM_EXTRA_PORTS
			if (galaxyObj.has_field(U("extra_ports"))) {
				try {
					String extraPortStrings = conversions::to_utf8string(galaxyObj[U("extra_ports")].as_string());

					if (!extraPortStrings.isEmpty()) {
						int numPorts = 0;
						StringTokenizer tokenizer(extraPortStrings);
						tokenizer.setDelimiter(",");

						while (tokenizer.hasMoreTokens() && numPorts < 256) {
							try {
								uint32 newPort = tokenizer.getIntToken();

								if (newPort != 0) {
									galaxy.addPort(newPort);
									numPorts++;
								}
							} catch (Exception e) {
								// Do nothing
							}
						}
					}
				} catch (Exception e) {
					// Do Nothing
				}
			}
#endif // USE_RANDOM_EXTRA_PORTS
			if (galaxyObj.has_field(U("pingport"))) {
				galaxy.setPingPort(galaxyObj[U("pingport")].as_integer());
			}
			if (galaxyObj.has_field(U("population"))) {
				galaxy.setPopulation(galaxyObj[U("population")].as_integer());
			}

			galaxies.add(galaxy);
		}

		return true;

	} catch (const json::json_exception& e) {
		errorMessage = String("JSON parse error: ") + e.what();
		return false;
	}
}

Optional<Galaxy> SWGRealmsAPI::parseGalaxyFromJSON(const String& jsonStr) {
	try {
		auto jsonValue = json::value::parse(conversions::to_string_t(jsonStr.toCharArray()));

		if (!jsonValue.is_object() || !jsonValue.has_field(U("galaxy"))) {
			return Optional<Galaxy>();
		}

		auto galaxyObj = jsonValue[U("galaxy")];
		if (!galaxyObj.is_object()) {
			return Optional<Galaxy>();
		}

		uint32 galaxyID = 0;

		if (galaxyObj.has_field(U("galaxy_id"))) {
			galaxyID = galaxyObj[U("galaxy_id")].as_integer();
		} else {
			return Optional<Galaxy>();
		}

		Galaxy galaxy(galaxyID);

		if (galaxyObj.has_field(U("name"))) {
			galaxy.setName(conversions::to_utf8string(galaxyObj[U("name")].as_string()));
		}
		if (galaxyObj.has_field(U("address"))) {
			galaxy.setAddress(conversions::to_utf8string(galaxyObj[U("address")].as_string()));
		}
		if (galaxyObj.has_field(U("port"))) {
			galaxy.setPort(galaxyObj[U("port")].as_integer());
		}
		if (galaxyObj.has_field(U("pingport"))) {
			galaxy.setPingPort(galaxyObj[U("pingport")].as_integer());
		}
		if (galaxyObj.has_field(U("population"))) {
			galaxy.setPopulation(galaxyObj[U("population")].as_integer());
		}

		return Optional<Galaxy>(galaxy);

	} catch (const json::json_exception& e) {
		error() << "JSON parse error in parseGalaxyFromJSON: " << e.what();
		return Optional<Galaxy>();
	}
}

Vector<Galaxy> SWGRealmsAPI::getAuthorizedGalaxies(uint32 accountID) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/account/" << accountID << "/galaxies";

	String errorMessage;
	Reference<SimpleResult*> result = new SimpleResult();
	Vector<Galaxy> galaxies;

	if (apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "GET", "", errorMessage)) {
		parseGalaxyListFromJSON(result->getRawJSON(), galaxies, errorMessage);
	} else {
		error() << "getGalaxyList failed for account " << accountID << ": " << errorMessage;
	}

	return galaxies;
}

Optional<Galaxy> SWGRealmsAPI::getGalaxyEntry(uint32 galaxyID) {
	StringBuffer pathBuffer;
	pathBuffer << "/v1/core3/galaxy/" << galaxyID;

	String errorMessage;
	Reference<SimpleResult*> result = new SimpleResult();
	if (!apiCallBlocking(result.castTo<SWGRealmsAPIResult*>(), pathBuffer.toString(), "GET", "", errorMessage)) {
		error() << "getGalaxyEntry failed for galaxy " << galaxyID << ": " << errorMessage;
		return Optional<Galaxy>();
	}

	return parseGalaxyFromJSON(result->getRawJSON());
}

// Streaming API proxy methods

void SWGRealmsAPI::publish(const String& channel, const String& key, const String& payloadJson) {
	if (streamer != nullptr) {
		streamer->publish(channel, key, payloadJson);
	}
}

void SWGRealmsAPI::publishTrxLog(const String& trxId, const String& payloadJson) {
	if (streamer != nullptr) {
		streamer->publish("trxlog", trxId, payloadJson);
	}
}

bool SWGRealmsAPI::isStreamConnected() const {
	return streamer != nullptr && streamer->isConnected();
}

int SWGRealmsAPI::getStreamPendingCount() const {
	return streamer != nullptr ? streamer->getPendingCount() : 0;
}

// Metrics publishing

#include "server/zone/managers/statistics/StatisticsManager.h"

/**
 * Periodic task to publish server metrics via SWGRealms streaming API.
 * Config: Core3.Login.API.MetricsInterval (seconds, default 600, 0 = disabled)
 */
class SWGRealmsMetricsTask : public Task, public Logger {
private:
	int intervalMs;

public:
	SWGRealmsMetricsTask(int intervalSec) : Task(), Logger("SWGRealmsMetricsTask") {
		intervalMs = intervalSec * 1000;
	}

	void run() {
		if (intervalMs <= 0) {
			return;
		}

		auto api = SWGRealmsAPI::instance();
		if (api == nullptr) {
			reschedule(intervalMs);
			return;
		}

		try {
			auto statsManager = StatisticsManager::instance();
			if (statsManager != nullptr) {
				// Build metrics JSON
				JSONSerializationType metrics = statsManager->getAsJSON();

				Time now;
				metrics["@timestamp"] = now.getFormattedTimeFull();
				metrics["@timestampMs"] = now.getMiliTime();
				metrics["swgrealms"] = api->getStatsAsJSON();

				// Generate unique key (microseconds, hex)
				uint64 microTime = now.getMikroTime();
				char keyBuf[32];
				snprintf(keyBuf, sizeof(keyBuf), "%014llx", (unsigned long long)microTime);

				api->publish("metrics", String(keyBuf), String(metrics.dump()));
			}
		} catch (Exception& e) {
			error() << "Failed to publish metrics: " << e.getMessage();
		}

		reschedule(intervalMs);
	}
};

const TaskQueue* SWGRealmsAPI::getCustomQueue() {
	static auto customQueue = []() {
		return Core::getTaskManager()->initializeCustomQueue("SWGRealmsWorker", 1);
	}();

	return customQueue;
}

void SWGRealmsAPI::scheduleMetricsPublish() {
	int intervalSec = ConfigManager::instance()->getInt("Core3.Login.API.MetricsInterval", 600);

#ifndef NDEBUG
	// Check range if not a debug / development build
	if (intervalSec < 30) {
		intervalSec = 30; // Can't be faster than this
	}

	if (intervalSec > 3600) {
		intervalSec = 3600; // Can't be longer than this
	}
#endif

	if (streamer == nullptr) {
		info(true) << "Metrics publishing disabled (streaming not enabled)";
		return;
	}

	Reference<SWGRealmsMetricsTask*> task = new SWGRealmsMetricsTask(intervalSec);
	task->setCustomTaskQueue(getCustomQueue()->getName());
	task->schedule(intervalSec * 1000);

	info(true) << "Scheduled metrics publishing every " << intervalSec << " seconds";
}

// ============================================================================
// SWGRealmsStreamer Implementation
// ============================================================================

using namespace engine::db::berkeley;
using namespace web::websockets::client;

constexpr uint64 SWGRealmsStreamer::MAX_WAL_SIZE;
constexpr uint64 SWGRealmsStreamer::GC_AFTER_HOURS;

SWGRealmsStreamer::SWGRealmsStreamer(const String& baseURL, const String& token, int galaxy, int debugLevel) : walDatabase() {
	setLoggingName("SWGRealmsStreamer");
	setFileLogger("log/swgrealms_stream.log", true, ConfigManager::instance()->getRotateLogAtStart());
	setLogSynchronized(true);
	setRotateLogSizeMB(ConfigManager::instance()->getRotateLogSizeMB());
	setLogToConsole(false);
	setGlobalLogging(false);
	setLogging(true);
	setLogLevel(static_cast<Logger::LogLevel>(debugLevel));

	apiToken = token;
	galaxyID = galaxy;

	if (apiToken.beginsWith("Bearer ")) {
		apiToken = apiToken.subString(7);
	}

	wsURL = "";
	if (!baseURL.isEmpty()) {
		String url = baseURL;
		if (url.endsWith("/")) {
			url = url.subString(0, url.length() - 1);
		}
		if (url.beginsWith("https://")) {
			wsURL = "wss://" + url.subString(8) + "/v1/core3/stream?galaxy_id=" + String::valueOf(galaxyID);
		} else if (url.beginsWith("http://")) {
			wsURL = "ws://" + url.subString(7) + "/v1/core3/stream?galaxy_id=" + String::valueOf(galaxyID);
		}
	}

	wsURL = ConfigManager::instance()->getString("Core3.Login.API.StreamURL", wsURL);
	enabled = !wsURL.isEmpty() && !apiToken.isEmpty();

	wsClient = nullptr;
	connected = false;
	reconnectDelay = 1;
	reconnectScheduled = false;
	walPendingCount = 0;
	publishedCount = 0;
	ackedCount = 0;
	errorCount = 0;
	inFlightCount = 0;

	if (!enabled) {
		warning() << "WebSocket URL or API token not configured, streaming disabled";
		return;
	}

	info(true) << "Streaming to " << wsURL << " (galaxy " << galaxyID << ")";

	walEnvPath = "log/wal";
	walDbPath = "stream_wal.db";

	try {
		File walDir(walEnvPath);
		if (!walDir.exists()) {
			if (!walDir.mkdir()) {
				throw Exception("Failed to create WAL directory: " + walEnvPath);
			}
		}

		EnvironmentConfig envConfig;
		envConfig.setAllowCreate(true);
		envConfig.setInitializeLocking(true);
		envConfig.setInitializeLogging(true);
		envConfig.setInitializeCache(true);
		envConfig.setThreaded(true);
		envConfig.setThreadCount(64);
		envConfig.setLogAutoRemove(true);
		envConfig.setMaxLogFileSize(10 * 1024 * 1024);
		envConfig.setTransactional(true);
		envConfig.setPrivate(false);
		envConfig.setRecover(true);
		envConfig.setRegister(false);

		walEnvironment = new Environment(walEnvPath, envConfig);
		info() << "WAL environment created: " << walEnvPath;

		DatabaseConfig dbConfig;
		dbConfig.setAllowCreate(true);
		dbConfig.setType(DatabaseType::HASH);

		auto initDb = walEnvironment->openDatabase(nullptr, walDbPath, "", dbConfig);
		info() << "WAL database initialized: " << walDbPath;

		try {
			auto cursor = initDb->openCursor(nullptr);
			DatabaseEntry key, value;
			int count = 0;
			while (cursor->getNext(&key, &value, LockMode::DEFAULT) == 0) {
				count++;
			}
			cursor->close();
			delete cursor;
			walPendingCount.set(count);
			if (count > 0) {
				warning() << "WAL has " << count << " pending events from previous run";
			}
		} catch (Exception& e) {
			info() << "WAL is empty (first run)";
		}

		initDb->close(false);
		delete initDb;

	} catch (Exception& e) {
		error() << "Failed to create WAL environment: " << e.getMessage();
		enabled = false;
		return;
	}

	try {
		websocket_client_config wsConfig;
		wsConfig.headers().add(U("Authorization"), U(("Bearer " + apiToken).toCharArray()));
		wsConfig.set_validate_certificates(false);

		wsClient = new websocket_callback_client(wsConfig);

		wsClient->set_message_handler([this](const websocket_incoming_message& msg) {
			this->onMessage(msg);
		});

		wsClient->set_close_handler([this](websocket_close_status status, const utility::string_t& reason, const std::error_code& ec) {
			this->onClose(status, reason, ec);
		});

		connectWebSocket();

	} catch (std::exception& e) {
		error() << "Failed to initialize WebSocket client: " << e.what();
		enabled = false;
		return;
	}

	info() << "SWGRealms Streamer initialized: " << wsURL << " (galaxy " << galaxyID << ")";
}

SWGRealmsStreamer::~SWGRealmsStreamer() {
	enabled = false;

	if (wsClient != nullptr) {
		try {
			// Initiate close but don't wait - this breaks the epoll_wait in the ws thread
			wsClient->close();
			// Brief sleep to let the close propagate to the io_service thread
			Thread::sleep(100);
			// DON'T delete wsClient - cpprestsdk's destructor calls close().wait()
			// which hangs forever. Intentionally leak; _exit() will clean up.
			wsClient = nullptr;
		} catch (std::exception& e) {
			error() << "Error closing WebSocket: " << e.what();
		}
	}

	// Close thread-local database handle if open on this thread
	auto db = walDatabase.get();
	if (db != nullptr) {
		try {
			db->close(false);
			delete db;
			walDatabase.set(nullptr);
		} catch (...) {
			// Ignore errors during shutdown
		}
	}

	if (walEnvironment != nullptr) {
		walEnvironment->close();
		delete walEnvironment;
		walEnvironment = nullptr;
	}

	info() << "Shutdown: published=" << publishedCount.get() << ", acked=" << ackedCount.get()
	       << ", pending=" << walPendingCount.get();
}

BerkeleyDatabase* SWGRealmsStreamer::getWALHandle() {
	auto db = walDatabase.get();

	if (db == nullptr) {
		DatabaseConfig config;
		config.setAllowCreate(true);
		config.setType(DatabaseType::HASH);

		try {
			db = walEnvironment->openDatabase(nullptr, walDbPath, "", config);
			walDatabase.set(db);
			auto currentThread = Thread::getCurrentThread();
			if (currentThread != nullptr) {
				debug() << "Opened WAL database handle for thread " << currentThread->getName();
			} else {
				debug() << "Opened WAL database handle";
			}
		} catch (const Exception& e) {
			error() << "Failed to open WAL database";
			throw;
		} catch (const std::exception& e) {
			error() << "Failed to open WAL database: " << e.what();
			throw;
		} catch (...) {
			error() << "Failed to open WAL database (unknown exception)";
			throw;
		}
	}

	return db;
}

void SWGRealmsStreamer::publish(const String& channel, const String& key, const String& payloadJson) {
	if (!enabled) {
		return;
	}

	try {
		appendToWAL(channel, key, payloadJson);
		if (connected) {
			sendMessage(channel, key, payloadJson);
		} else {
			debug() << "WebSocket disconnected, event buffered: " << channel << ":" << key;
		}
	} catch (Exception& e) {
		error() << "Failed to publish event " << channel << ":" << key << ": " << e.getMessage();
		errorCount.increment();
	}
}

void SWGRealmsStreamer::appendToWAL(const String& channel, const String& key, const String& payloadJson) {
	try {
		String compositeKey = channel + ":" + key;
		DatabaseEntry dbKey((uint8*)compositeKey.toCharArray(), compositeKey.length());
		DatabaseEntry dbValue((uint8*)payloadJson.toCharArray(), payloadJson.length());
		getWALHandle()->put(nullptr, &dbKey, &dbValue);
		getWALHandle()->sync();
		walPendingCount.increment();
	} catch (Exception& e) {
		error() << "WAL append failed for " << channel << ":" << key << ": " << e.getMessage();
		throw;
	}
}

void SWGRealmsStreamer::removeFromWAL(const String& channel, const String& key) {
	try {
		String compositeKey = channel + ":" + key;
		DatabaseEntry dbKey((uint8*)compositeKey.toCharArray(), compositeKey.length());
		int ret = getWALHandle()->del(nullptr, &dbKey);
		if (ret == 0) {
			walPendingCount.decrement();
			getWALHandle()->sync();
		}
	} catch (Exception& e) {
		error() << "WAL remove failed for " << channel << ":" << key << ": " << e.getMessage();
	}
}

Vector<Pair<String, String>> SWGRealmsStreamer::getAllPendingFromWAL() {
	Locker lock(&syncMutex);
	Vector<Pair<String, String>> result;

	try {
		auto cursor = getWALHandle()->openCursor(nullptr);
		DatabaseEntry key, value;
		while (cursor->getNext(&key, &value, LockMode::DEFAULT) == 0) {
			String compositeKey((char*)key.getData(), key.getSize());
			String payload((char*)value.getData(), value.getSize());
			result.add(Pair<String, String>(compositeKey, payload));
		}
		cursor->close();
		delete cursor;
	} catch (Exception& e) {
		error() << "WAL iteration failed: " << e.getMessage();
	}

	return result;
}

void SWGRealmsStreamer::garbageCollect() {
	Locker lock(&syncMutex);
	Time cutoff;
	cutoff.addMiliTime(-GC_AFTER_HOURS * 3600 * 1000);
	int removedCount = 0;

	try {
		auto cursor = getWALHandle()->openCursor(nullptr);
		DatabaseEntry key, value;

		while (cursor->getNext(&key, &value, LockMode::DEFAULT) == 0) {
			String compositeKey((char*)key.getData(), key.getSize());
			int colonPos = compositeKey.indexOf(':');
			if (colonPos < 0) continue;

			String keyPart = compositeKey.subString(colonPos + 1);
			uint64 trxMikroTime = parseTimestampFromKey(keyPart);

			if (trxMikroTime < cutoff.getMikroTime()) {
				cursor->del();
				walPendingCount.decrement();
				removedCount++;
			}
		}

		cursor->close();
		delete cursor;

		if (removedCount > 0) {
			warning() << "WAL GC: Removed " << removedCount << " events older than " << GC_AFTER_HOURS << " hours";
		}
	} catch (Exception& e) {
		error() << "WAL GC failed: " << e.getMessage();
	}
}

uint64 SWGRealmsStreamer::parseTimestampFromKey(const String& key) {
	if (key.length() < 14) {
		return 0;
	}
	String hexStr = key.subString(0, 14);
	return strtoull(hexStr.toCharArray(), nullptr, 16);
}

void SWGRealmsStreamer::connectWebSocket() {
	if (!enabled) {
		return;
	}

	{
		Locker lock(&reconnectMutex);
		reconnectScheduled = false;
	}

	try {
		if (wsClient != nullptr) {
			delete wsClient;
			wsClient = nullptr;
		}

		websocket_client_config wsConfig;
		wsConfig.headers().add(U("Authorization"), U(("Bearer " + apiToken).toCharArray()));
		wsConfig.set_validate_certificates(false);

		wsClient = new websocket_callback_client(wsConfig);

		wsClient->set_message_handler([this](const websocket_incoming_message& msg) {
			this->onMessage(msg);
		});

		wsClient->set_close_handler([this](websocket_close_status status, const utility::string_t& reason, const std::error_code& ec) {
			this->onClose(status, reason, ec);
		});

		info() << "WebSocket connecting to " << wsURL;

		wsClient->connect(U(wsURL.toCharArray())).then([this]() {
			this->onOpen();
		}).then([this](pplx::task<void> task) {
			try {
				task.wait();
			} catch (std::exception& e) {
				this->onFail(e);
			}
		});

	} catch (std::exception& e) {
		error() << "WebSocket connect failed: " << e.what();
		scheduleReconnect();
	}
}

void SWGRealmsStreamer::disconnectWebSocket() {
	if (wsClient != nullptr && connected) {
		try {
			wsClient->close().wait();
		} catch (std::exception& e) {
			error() << "WebSocket disconnect failed: " << e.what();
		}
	}
}

void SWGRealmsStreamer::sendMessage(const String& channel, const String& key, const String& payloadJson) {
	if (!connected || wsClient == nullptr) {
		return;
	}

	try {
		StringBuffer msg;
		msg << channel << "\t" << key << "\t" << payloadJson << "\n";

		websocket_outgoing_message outMsg;
		outMsg.set_utf8_message(msg.toString().toCharArray());

		wsClient->send(outMsg).then([this, channel, key](pplx::task<void> task) {
			try {
				task.wait();
				publishedCount.increment();
				inFlightCount.increment();
				int inFlight = inFlightCount.get();
				if (inFlight > 1000) {
					warning() << "High in-flight count: " << inFlight << " (slow ACKs or network issue)";
				} else if (inFlight > 100 && inFlight % 100 == 0) {
					info() << "In-flight count: " << inFlight;
				}
			} catch (std::exception& e) {
				error() << "WebSocket send failed for " << channel << ":" << key << ": " << e.what();
				errorCount.increment();
			}
		});

	} catch (std::exception& e) {
		error() << "WebSocket send failed for " << channel << ":" << key << ": " << e.what();
		errorCount.increment();
	}
}

void SWGRealmsStreamer::scheduleReconnect() {
	if (!enabled) {
		return;
	}

	Locker lock(&reconnectMutex);

	if (reconnectScheduled) {
		debug() << "Reconnect already scheduled, skipping";
		return;
	}

	reconnectScheduled = true;
	reconnectDelay = Math::min(reconnectDelay * 2, 60);

	warning() << "Scheduling reconnect in " << reconnectDelay << " seconds";

	Core::getTaskManager()->scheduleTask([this]() {
		connectWebSocket();
	}, "WebSocketReconnect", reconnectDelay * 1000);
}

void SWGRealmsStreamer::replayWAL() {
	auto pending = getAllPendingFromWAL();

	if (pending.size() == 0) {
		info() << "WAL replay: no pending events";
		return;
	}

	info() << "WAL replay: sending " << pending.size() << " pending events";

	for (int i = 0; i < pending.size(); i++) {
		const auto& pair = pending.get(i);
		const String& compositeKey = pair.first;
		const String& payload = pair.second;

		int colonPos = compositeKey.indexOf(':');
		if (colonPos < 0) {
			warning() << "  Skipping malformed WAL key: " << compositeKey;
			continue;
		}

		String channel = compositeKey.subString(0, colonPos);
		String key = compositeKey.subString(colonPos + 1);

		info() << "  Replaying [" << (i+1) << "/" << pending.size() << "]: " << compositeKey;
		sendMessage(channel, key, payload);
	}

	info() << "WAL replay complete: sent " << pending.size() << " events";
}

void SWGRealmsStreamer::onOpen() {
	info() << "WebSocket connected to " << wsURL;

	connected = true;
	reconnectDelay = 1;

	{
		Locker lock(&reconnectMutex);
		reconnectScheduled = false;
	}

	Core::getTaskManager()->executeTask([this]() {
		replayWAL();
	}, "WALReplay", "slowQueue");
}

void SWGRealmsStreamer::onClose(websocket_close_status status, const utility::string_t& reason, const std::error_code& ec) {
	warning() << "WebSocket closed: " << reason.c_str() << " (code " << ec.value() << ")";
	connected = false;
	scheduleReconnect();
}

void SWGRealmsStreamer::onFail(const std::exception& e) {
	error() << "WebSocket connection failed: " << e.what();
	connected = false;
	scheduleReconnect();
}

void SWGRealmsStreamer::onMessage(const websocket_incoming_message& msg) {
	try {
		if (msg.message_type() != websocket_message_type::text_message) {
			const char* typeNames[] = {"open", "close", "ping", "pong", "message", "upgrade", "noop"};
			int type = (int)msg.message_type();
			const char* typeName = (type >= 0 && type <= 6) ? typeNames[type] : "unknown";
			debug() << "Ignoring WebSocket " << typeName << " frame (type " << type << ")";
			return;
		}

		msg.extract_string().then([this](pplx::task<std::string> task) {
			try {
				std::string payload = task.get();

				if (payload.empty() || payload == "[]") {
					debug() << "Received keep-alive (empty payload)";
					return;
				}

				web::json::value ackJson;
				try {
					ackJson = web::json::value::parse(utility::conversions::to_string_t(payload));
				} catch (web::json::json_exception& e) {
					error() << "Failed to parse ACK JSON: " << e.what() << " - Payload: [" << payload.c_str() << "]";
					return;
				}

				if (!ackJson.has_field(U("channel")) || !ackJson.has_field(U("key")) || !ackJson.has_field(U("status"))) {
					error() << "Invalid ACK format (missing channel, key or status): " << payload.c_str();
					return;
				}

				String channel = utility::conversions::to_utf8string(ackJson[U("channel")].as_string()).c_str();
				String key = utility::conversions::to_utf8string(ackJson[U("key")].as_string()).c_str();
				String status = utility::conversions::to_utf8string(ackJson[U("status")].as_string()).c_str();

				if (status == "ok" || status == "duplicate_ok") {
					removeFromWAL(channel, key);
					ackedCount.increment();
					inFlightCount.decrement();
					debug() << "ACK received for " << channel << ":" << key << " (status: " << status << ")";
				} else {
					String errorMsg = "";
					if (ackJson.has_field(U("message"))) {
						errorMsg = utility::conversions::to_utf8string(ackJson[U("message")].as_string()).c_str();
					}
					error() << "Event rejected: " << channel << ":" << key << " status=" << status << " message=" << errorMsg;
				}

			} catch (Exception& e) {
				error() << "Failed to parse ACK: " << e.getMessage();
			} catch (std::exception& e) {
				error() << "Failed to parse ACK: " << e.what();
			}
		});

	} catch (std::exception& e) {
		error() << "Failed to extract message: " << e.what();
	}
}

JSONSerializationType SWGRealmsStreamer::getStatsAsJSON() const {
	JSONSerializationType stats;
	stats["enabled"] = enabled;
	stats["connected"] = connected;
	stats["wsURL"] = wsURL.toCharArray();
	stats["galaxyID"] = galaxyID;
	stats["walPending"] = walPendingCount.get();
	stats["published"] = publishedCount.get();
	stats["acked"] = ackedCount.get();
	stats["inFlight"] = inFlightCount.get();
	stats["errors"] = errorCount.get();
	stats["reconnectDelay"] = reconnectDelay;
	return stats;
}

String SWGRealmsStreamer::toString() const {
	StringBuffer buf;
	buf << "SWGRealmsStreamer " << this << " ["
	    << "enabled: " << enabled << ", "
	    << "connected: " << connected << ", "
	    << "wsURL: " << wsURL << ", "
	    << "galaxyID: " << galaxyID << ", "
	    << "walPending: " << walPendingCount << ", "
	    << "inFlight: " << inFlightCount << ", "
	    << "published: " << publishedCount << ", "
	    << "acked: " << ackedCount << ", "
	    << "errors: " << errorCount << "]";
	return buf.toString();
}

#endif // WITH_SWGREALMS_API
