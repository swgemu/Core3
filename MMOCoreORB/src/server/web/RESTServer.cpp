/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : theanswer (theanswer@Victors-MacBook-Pro.local)
 * @file        : RESTServer
 * @created     : Sunday Nov 11, 2018 11:31:08 CET
 */

#ifdef WITH_REST_API

#include "RESTServer.h"
#include "server/ServerCore.h"
#include "conf/ConfigManager.h"

#include "RESTEndpoint.h"
#include "APIRequest.h"
#include "APIProxyPlayerManager.h"
#include "APIProxyChatManager.h"
#include "APIProxyObjectManager.h"
#include "APIProxyGuildManager.h"
#include "APIProxyConfigManager.h"
#include "APIProxyStatisticsManager.h"

using namespace server::web3;

RESTServer::RESTServer() {
	setLoggingName("RESTServer");
	setFileLogger("log/core3_api.log", true, ConfigManager::instance()->getRotateLogAtStart());
	setLogSynchronized(true);
	setRotateLogSizeMB(ConfigManager::instance()->getInt("Core3.RESTServer.RotateLogSizeMB", ConfigManager::instance()->getRotateLogSizeMB()));
	setLogToConsole(false);
	setGlobalLogging(false);
	setLogging(true);
	doRun.set(true);
}

RESTServer::~RESTServer() {
}

#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <pplx/threadpool.h>

#include <map>
#include <set>
#include <string>
#include <memory>
#include <chrono>
#include <regex>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

using namespace std;

namespace server {
namespace web3 {
	UniqueReference<http_listener*> restListener;
}
}

void RESTServer::registerEndpoints() {
	const auto addEndpoint = [this](auto endpoint) {
		mAPIEndpoints.add(endpoint);
		info() << "Registered " << endpoint;
	};

	info() << "Registering mAPIEndpoints...";

	addEndpoint(RESTEndpoint("GET:/v1/version/", {}, [this] (APIRequest& apiRequest) -> void {
		auto result = JSONSerializationType::object();

		result["api_version"] = 1;

		StringTokenizer revLines(ConfigManager::instance()->getRevision());
		revLines.setDelimeter("\n");

		if (revLines.hasMoreTokens()) {
			String revFirstLine;
			revLines.getStringToken(revFirstLine);
			result["core3_version"] = revFirstLine;
		}

		apiRequest.success(result);
	}));

	addEndpoint(RESTEndpoint("(?:GET|DELETE):/v1/object/(?:(\\d*)/|)", {"oid"}, [this] (APIRequest& apiRequest) -> void {
		mObjectManagerProxy->handle(apiRequest);
	}));

	addEndpoint(RESTEndpoint("(?:PUT):/v1/object/(\\d+)/(\\w+)/(\\w+)/", {"oid", "class", "property"}, [this] (APIRequest& apiRequest) -> void {
		mObjectManagerProxy->handle(apiRequest);
	}));

	addEndpoint(RESTEndpoint("(?:GET|POST|PUT):/v1/admin/config/(?:(.*)/|)", {"key"}, [this] (APIRequest& apiRequest) -> void {
		mConfigManagerProxy->handle(apiRequest);
	}));

	addEndpoint(RESTEndpoint("(?:GET|PUT):/v1/admin/stats/", {}, [this] (APIRequest& apiRequest) -> void {
		mStatisticsManager->handle(apiRequest);
	}));

	addEndpoint(RESTEndpoint("POST:/v1/admin/console/(\\w+)/", {"command"}, [this] (APIRequest& apiRequest) -> void {
		StringBuffer buf;

		buf << apiRequest.getPathFieldString("command");

		if (apiRequest.hasQueryField("args")) {
			buf << " " << apiRequest.getQueryFieldString("args");
		}

		auto consoleCommand = buf.toString().trim();

		info(true) << "REMOTE CONSOLE COMMAND: " << consoleCommand;

		ServerCore::getInstance()->queueConsoleCommand(consoleCommand);

		JSONSerializationType result;

		result["console_command"] = consoleCommand;

		apiRequest.success(result);
	}));

	addEndpoint(RESTEndpoint("POST:/v1/admin/account/(\\d+)/galaxy/(\\d+)/character/(\\d+)/", {"accountID", "galaxyID", "characterID"}, [this] (APIRequest& apiRequest) -> void {
		mPlayerManagerProxy->handle(apiRequest);
	}));

	addEndpoint(RESTEndpoint("POST:/v1/admin/account/(\\d+)/", {"accountID"}, [this] (APIRequest& apiRequest) -> void {
		mPlayerManagerProxy->handle(apiRequest);
	}));

	addEndpoint(RESTEndpoint("GET:/v1/(find|lookup)/character/", {"mode"}, [this] (APIRequest& apiRequest) -> void {
		mPlayerManagerProxy->lookupCharacter(apiRequest);
	}));

	addEndpoint(RESTEndpoint("GET:/v1/(find|lookup)/guild/", {"mode"}, [this] (APIRequest& apiRequest) -> void {
		mGuildManagerProxy->lookupGuild(apiRequest);
	}));

	addEndpoint(RESTEndpoint("POST:/v1/chat/(mail|message|galaxy)/", {"msgType"}, [this] (APIRequest& apiRequest) -> void {
		mChatManagerProxy->handle(apiRequest);
	}));

	info() << "Registered " << mAPIEndpoints.size() << " endpoint(s)";
}

void RESTServer::routeRequest(http_request& request) {
	const auto& uri = request.relative_uri();

	String endpointKey = request.method() + ":" + uri::decode(uri.path());

	if (!endpointKey.endsWith("/")) {
		endpointKey += "/";
	}

	if (!checkAuth(request)) {
		warning() << "AUTHFAIL " << endpointKey;
		request.reply(status_codes::Forbidden, U("Invalid API Token"));
		return;
	}

	try {
		RESTEndpoint hitEndpoint;

		for (auto endpoint : mAPIEndpoints) {
			if (endpoint.isMatch(endpointKey) && endpoint.getWeight() > hitEndpoint.getWeight()) {
				hitEndpoint = endpoint;
			}
		}

		if (hitEndpoint.getWeight() == 0) {
			request.reply(status_codes::NotFound, U("Invalid resource"));
			return;
		}

		if (getLogLevel() >= Logger::DEBUG) {
			auto msg = debug();
			auto pathFields = hitEndpoint.getPathFields(endpointKey);

			msg << "HIT: " << hitEndpoint;

			auto pathFieldIter = pathFields.iterator();

			while (pathFieldIter.hasNext()) {
				String fieldName, fieldValue;
				pathFieldIter.getNextKeyAndValue(fieldName, fieldValue);

				msg << " " << fieldName << "=[" << fieldValue << "]";
			}

			msg.flush();
		}

		Core::getTaskManager()->executeTask([=] {
			try {
				auto apiRequest = APIRequest(request, endpointKey, *this);

				debug() << "START REQUEST: " << apiRequest;

				try {
					hitEndpoint.handle(apiRequest);
				} catch (http_exception const & e) {
					apiRequest.fail("Failed to parse request.", "Exception handling request: " + String(e.what()));
				}

				info() << "REQUEST: " << apiRequest;

				if (apiRequest.getElapsedTimeMS() > 500) {
					warning() << "SLOW API CALL: " << apiRequest;
				}
			} catch (Exception& e) {
				error() << "Unexpected exception in RESTAPITask: " << e.getMessage();
				request.reply(status_codes::BadGateway, U("Unexpected exception handling request."));
			} catch (JSONSerializationType::exception& e) {
				error() << "Unexpected JSON exception in RESTAPITask: " << e.what();
				request.reply(status_codes::BadGateway, U("Unexpected JSON exception handling request."));
			} catch (...) {
#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
				error() << endpointKey << ": Uncaptured exception in RESTAPITask: " << __cxxabiv1::__cxa_current_exception_type()->name();
#else
				error() << endpointKey << ": Uncaptured exception in RESTAPITask";
#endif
				request.reply(status_codes::BadGateway, U("Uncaptured exception handling request"));
			}
		}, "RESTAPITask-" + hitEndpoint.toString(), "RESTServerWorker");
	} catch (Exception& e) {
		error() << endpointKey << ": Unexpected exception in request router: " + e.getMessage();
		request.reply(status_codes::BadGateway, U("Unexpected exception in request router"));
	}
}

bool RESTServer::checkAuth(http_request& request) {
	if (mAuthHeader.isEmpty()) {
		return false;
	}

	auto headers = request.headers();

	if (request.headers().find(header_names::authorization) == headers.end())
		return false;

	auto requestToken = String(headers[header_names::authorization]);

	return requestToken == mAuthHeader;
}

void RESTServer::createProxies() {
	destroyProxies();

	mPlayerManagerProxy = new APIProxyPlayerManager();

	if (mPlayerManagerProxy == nullptr) {
		throw OutOfMemoryError();
	}

	mChatManagerProxy = new APIProxyChatManager();

	if (mChatManagerProxy == nullptr) {
		throw OutOfMemoryError();
	}

	mObjectManagerProxy = new APIProxyObjectManager();

	if (mObjectManagerProxy == nullptr) {
		throw OutOfMemoryError();
	}

	mGuildManagerProxy = new APIProxyGuildManager();

	if (mGuildManagerProxy == nullptr) {
		throw OutOfMemoryError();
	}

	mConfigManagerProxy = new APIProxyConfigManager();

	if (mConfigManagerProxy == nullptr) {
		throw OutOfMemoryError();
	}

	mStatisticsManager = new APIProxyStatisticsManager();

	if (mStatisticsManager == nullptr) {
		throw OutOfMemoryError();
	}
}

void RESTServer::destroyProxies() {
	if (mPlayerManagerProxy != nullptr) {
		delete mPlayerManagerProxy;
		mPlayerManagerProxy = nullptr;
	}

	if (mChatManagerProxy != nullptr) {
		delete mChatManagerProxy;
		mChatManagerProxy = nullptr;
	}

	if (mObjectManagerProxy != nullptr) {
		delete mObjectManagerProxy;
		mObjectManagerProxy = nullptr;
	}

	if (mGuildManagerProxy != nullptr) {
		delete mGuildManagerProxy;
		mGuildManagerProxy = nullptr;
	}

	if (mConfigManagerProxy != nullptr) {
		delete mConfigManagerProxy;
		mConfigManagerProxy = nullptr;
	}

	if (mStatisticsManager != nullptr) {
		delete mStatisticsManager;
		mStatisticsManager = nullptr;
	}
}

void RESTServer::start() {
	auto logLevel = ConfigManager::instance()->getInt("Core3.RESTServer.LogLevel", (int)Logger::INFO);
	auto numberOfThreads = ConfigManager::instance()->getInt("Core3.RESTServer.WorkerThreads", 4);

	const auto static initialized = Core::getTaskManager()->initializeCustomQueue("RESTServerWorker", numberOfThreads);

	setLogLevel(static_cast<Logger::LogLevel>(logLevel));

	if (restListener != nullptr) {
		info() << "shutting down previous listener";
		restListener->close().wait();
	}

	port = ConfigManager::instance()->getRESTPort();

	if (port == 0) {
		info() << "disabled, RESTPort not set";
		doRun.set(false);
		return;
	}

	auto apiAuthToken = ConfigManager::instance()->getString("Core3.RESTServer.APIToken", "");

	if (apiAuthToken.length() == 0) {
		error() << "Core3.RESTServer.APIToken not set, refusing to authorize API calls";
	} else if (apiAuthToken.length() < 15) {
		error() << "Core3.RESTServer.APIToken too short, must be at least 15 characters, refusing to authorize API calls";
	} else {
		mAuthHeader = "Bearer " + apiAuthToken;
	}

	createProxies();

	registerEndpoints();

	http_listener_config serverConfig;

	serverConfig.set_ssl_context_callback([this](boost::asio::ssl::context& ctx) {
		auto sslKeyFilename = ConfigManager::instance()->getString("Core3.RESTServer.SSLKeyFile", "");

		if (sslKeyFilename.length() == 0) {
			error() << "missing Core3.RESTServer.SSLKeyFile";
			return;
		}

		auto sslCrtFilename = ConfigManager::instance()->getString("Core3.RESTServer.SSLCertFile", "");

		if (sslCrtFilename.length() == 0) {
			error() << "missing Core3.RESTServer.SSLCertFile";
			return;
		}

		ctx.set_options(boost::asio::ssl::context::default_workarounds);

		boost::system::error_code err;

		ctx.use_certificate_chain_file(sslCrtFilename.toCharArray(), err);

		if (err) {
			error() << "load ssl cert failed: " << err.message();
			return;
		}

		ctx.use_private_key_file(sslKeyFilename.toCharArray(), boost::asio::ssl::context::pem, err);

		if (err) {
			error() << "load ssl key failed: " << err.message();
			return;
		}
	});

	restListener = new http_listener(("https://0.0.0.0:" + String::valueOf(port)).toCharArray(), serverConfig);

	restListener->support([this](http_request request) { routeRequest(request); });

	try {
		restListener->open()
			.then([this] {
			info(true) << "listening on port " << port;
		}).wait();
	} catch (exception const & e) {
		error() << e.what();
	}
}

void RESTServer::stop() {
	doRun.set(false);

	if (restListener != nullptr) {
		info() << "Stopping listener.";

		restListener->close().wait();
		restListener = nullptr;
	}

	destroyProxies();

	crossplat::threadpool::shared_instance().service().stop();

	info(true) << "shut down thread pool";
}

#endif // WITH_REST_API
