/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : theanswer (theanswer@Victors-MacBook-Pro.local)
 * @file        : RESTServer
 * @created     : Sunday Nov 11, 2018 11:31:08 CET
 */

#ifdef WITH_REST_API

#include "server/ServerCore.h"
#include "RESTServer.h"
#include "RESTEndpoint.h"
#include "APIRequest.h"
#include "APIProxyPlayerManager.h"

using namespace server::web3;

RESTServer::RESTServer() {
	setLoggingName("RESTServer");
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

#include "engine/engine.h"
#include "conf/ConfigManager.h"

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
	debug() << "Registering mAPIEndpoints...";

	mAPIEndpoints.add(RESTEndpoint("GET:/v1/version/", {}, [this] (APIRequest& apiRequest) -> void {
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

	mAPIEndpoints.add(RESTEndpoint("GET:/v1/object/", {}, [this] (APIRequest& apiRequest) -> void {
		if (!apiRequest.hasQueryField("oids")) {
			apiRequest.fail("missing query field 'oids'");
			return;
		}

		auto responses = JSONSerializationType::array();

		StringTokenizer oidStrList(apiRequest.getQueryFieldString("oids"));
		oidStrList.setDelimeter(",");

		int countFound = 0;

		while(oidStrList.hasMoreTokens()) {
			try {
				uint64 oid = oidStrList.getUnsignedLongToken();

				debug() << countFound << ") Lookup oid " << oid;

				auto obj = Core::lookupObject(oid).castTo<ManagedObject*>();

				if (obj != nullptr) {
					ReadLocker lock(obj);

					JSONSerializationType jsonData;
					obj->writeJSON(jsonData);

					JSONSerializationType entry;
					entry[String::valueOf(oid)] = jsonData;

					responses.push_back(entry);
					countFound++;
				}
			} catch (const Exception& e) {
				apiRequest.fail("Exception looking up objects", "Exception: " + e.getMessage());
				return;
			}
		}

		debug() << "Found " << countFound << " object(s)";

		if (responses.empty()) {
			apiRequest.fail("Nothing found");
		} else {
			JSONSerializationType result;

			result["objects"] = responses;

			apiRequest.success(result);
		}
	}));

	mAPIEndpoints.add(RESTEndpoint("POST:/v1/admin/console/(\\w+)/", {"command"}, [this] (APIRequest& apiRequest) -> void {
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

	mAPIEndpoints.add(RESTEndpoint("POST:/v1/admin/account/(\\d+)/galaxy/(\\d+)/character/(\\d+)/", {"accountID", "galaxyID", "characterID"}, [this] (APIRequest& apiRequest) -> void {
		try {
			mPlayerManagerProxy->handle(apiRequest);
		} catch (http_exception const & e) {
			apiRequest.fail("Failed to parse request.", "Exception handling request: " + String(e.what()));
		}
	}));

	mAPIEndpoints.add(RESTEndpoint("POST:/v1/admin/account/(\\d+)/", {"accountID"}, [this] (APIRequest& apiRequest) -> void {
		try {
			mPlayerManagerProxy->handle(apiRequest);
		} catch (http_exception const & e) {
			apiRequest.fail("Failed to parse request.", "Exception handling request: " + String(e.what()));
		}
	}));

	debug() << "Registered " << mAPIEndpoints.size() << " endpoint(s)";
}

void RESTServer::routeRequest(http_request& request) {
	if (!checkAuth(request)) {
		request.reply(status_codes::Forbidden, U("Invalid API Token"));
		return;
	}

	const auto& uri = request.relative_uri();

	String endpointKey = request.method() + ":" + uri.path();

	if (!endpointKey.endsWith("/")) {
		endpointKey += "/";
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

			msg << "HIT: " << hitEndpoint.toString();

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
				auto apiRequest = APIRequest(request, endpointKey, getLogLevel());

				hitEndpoint.handle(apiRequest);
			} catch (Exception& e) {
				error() << "Unexpected exception in RESTAPITask: " + e.getMessage();
				request.reply(status_codes::BadGateway, U("Unexpected exception in request router"));
			}
		}, "RESTAPITask-" + hitEndpoint.toString(), "slowQueue");
	} catch (Exception& e) {
		error() << "Unexpected exception in request router: " + e.getMessage();
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

void RESTServer::start() {
	auto logLevel = ConfigManager::instance()->getInt("Core3.RESTServer.LogLevel", (int)Logger::INFO);

	setLogLevel(static_cast<Logger::LogLevel>(logLevel));

	if (restListener != nullptr) {
		info() << "shutting down previous listener";
		restListener->close().wait();
	}

	auto apiAuthToken = ConfigManager::instance()->getString("Core3.RESTServer.APIToken", "");

	if (apiAuthToken.length() == 0) {
		error() << "Core3.RESTServer.APIToken not set, refusing to authorize API calls";
	} else if (apiAuthToken.length() < 15) {
		error() << "Core3.RESTServer.APIToken too short, must be at least 15 characters, refusing to authorize API calls";
	} else {
		mAuthHeader = "Bearer " + apiAuthToken;
	}

	mPlayerManagerProxy = new APIProxyPlayerManager();

	if (mPlayerManagerProxy == nullptr) {
		throw OutOfMemoryError();
	}

	port = ConfigManager::instance()->getRESTPort();

	if (port == 0) {
		info() << "disabled, RESTPort not set";
		doRun.set(false);
		return;
	}

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
			info(true) << "listening to port " << port;
		}).wait();
	} catch (exception const & e) {
		error() << e.what();
	}
}

void RESTServer::stop() {
	doRun.set(false);

	if (restListener != nullptr) {
		restListener->close().wait();
		restListener = nullptr;
	}

	if (mPlayerManagerProxy != nullptr) {
		mPlayerManagerProxy = nullptr;
	}

	crossplat::threadpool::shared_instance().service().stop();
	info(true) << "shut down thread pool";
}

#endif // WITH_REST_API
