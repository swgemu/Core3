/**
 * @author      : theanswer (theanswer@Victors-MacBook-Pro.local)
 * @file        : RESTServer
 * @created     : Sunday Nov 11, 2018 11:31:08 CET
 */

#ifdef WITH_REST_API

#include "server/ServerCore.h"
#include "RESTServer.h"

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
	debug() << "Registering apiEndpoints...";

	apiEndpoints.setNoDuplicateInsertPlan();

	apiEndpoints.put("GET:/v1/version/", [this] (http_request request, Vector<String> matches) -> void {
		auto result = json::value();

		result[U("status")] = json::value::string(U("OK"));
		result[U("api_version")] = json::value::number(1);

		StringTokenizer revLines(ConfigManager::instance()->getRevision());
		revLines.setDelimeter("\n");

		if (revLines.hasMoreTokens()) {
			String revFirstLine;
			revLines.getStringToken(revFirstLine);
			result[U("core3_version")] = json::value::string(revFirstLine.toCharArray());
		}

		success_response(request, result);
	});

	apiEndpoints.put("GET:/v1/object/", [this] (http_request request, Vector<String> matches) -> void {
		const auto& uri = request.relative_uri();

		auto get_vars = uri::split_query(uri.query());

		auto find_oids = get_vars.find(U("oids"));

		if (find_oids == get_vars.end()) {
			error_response(request, "missing query field 'oids'");
			return;
		}

		nlohmann::json responses = nlohmann::json::array();

		StringTokenizer oidStrList(uri::decode(find_oids->second));
		oidStrList.setDelimeter(",");

		int countFound = 0;

		while(oidStrList.hasMoreTokens()) {
			try {
				uint64 oid = oidStrList.getUnsignedLongToken();

				debug() << countFound << ") Lookup oid " << oid;

				auto obj = Core::lookupObject(oid).castTo<ManagedObject*>();

				if (obj != nullptr) {
					ReadLocker lock(obj);

					nlohmann::json jsonData;
					obj->writeJSON(jsonData);

					nlohmann::json entry;
					entry[String::valueOf(oid)] = jsonData;

					responses.push_back(entry);
					countFound++;
				}
			} catch (const Exception& e) {
				error() << e.getMessage();
			}
		}

		debug() << "Found " << countFound << " object(s)";

		if (responses.empty()) {
			error_response(request, "Nothing found");
		} else {
			auto result = json::value();

			result[U("objects")] = json::value::parse(responses.dump());

			success_response(request, result);
		}
	});

	apiEndpoints.put("POST:/v1/admin/console/(\\w+)/*(.*)", [this] (http_request request, Vector<String> matches) -> void {
		StringBuffer buf;

		for (int i = 1;i < matches.size();i++) {
			auto match = matches.get(i);

			if (!match.isEmpty()) {
				buf << " " << match;
			}
		}

		const auto& uri = request.relative_uri();

		auto get_vars = uri::split_query(uri.query());

		auto find_args = get_vars.find(U("args"));

		if (find_args != get_vars.end()) {
			buf << " " << uri::decode(find_args->second);
		}

		auto consoleCommand = buf.toString().trim();

		info(true) << "REMOTE CONSOLE COMMAND: " << consoleCommand;

		ServerCore::getInstance()->queueConsoleCommand(consoleCommand);

		auto result = json::value();

		result[U("status")] = json::value::string(U("OK"));
		result[U("console_command")] = json::value::string(consoleCommand.toCharArray());

		success_response(request, result);
	});

	debug() << "Registered " << apiEndpoints.size() << " endpoint(s)";
}

void RESTServer::routeRequest(http_request request) {
	if (!check_auth(request)) {
		request.reply(status_codes::Forbidden, U("Invalid API Token"));
		return;
	}

	const auto& uri = request.relative_uri();

	String endpointKey = request.method() + ":" + uri.path();

	if (!endpointKey.endsWith("/")) {
		endpointKey += "/";
	}

	VectorMapEntry<String, Function<void(http_request request, Vector<String> matches)>> hitEntry;
	int hitLength = 0;
	std::regex hitRegex;

	for (auto entry : apiEndpoints) {
		auto regex = entry.getKey();

		std::regex re(regex.toCharArray());

		if (std::regex_search(endpointKey.toCharArray(), re)) {
			if (regex.length() > hitLength) {
				hitLength = regex.length();
				hitRegex = re;
				hitEntry = entry;
			}
		}
	}

	if (hitLength > 0) {
		// Parse any regex hits for this path
		Vector<String> matches;
		std::cmatch reMatches;

		if (std::regex_match (endpointKey.toCharArray(), reMatches, hitRegex)) {
			for (auto reMatch : reMatches) {
				matches.add(String(reMatch));
			}
		}

		if (getLogLevel() >= Logger::DEBUG) {
			auto msg = debug();

			msg << "HIT: " << hitEntry.getKey();

			if (matches.size() > 0) {
				msg << " Matches: ";
				for (auto match : matches) {
					msg << "[" << match << "]";
				}
			}

			msg.flush();
		}

		hitEntry.getValue()(request, matches);
		return;
	}

	error_response(request, "Invalid resouce");
}

void RESTServer::error_response(http_request request, String errorMessage) {
	const auto& uri = request.absolute_uri();

	error()
		<< request.method()
		<< " " << request.relative_uri()
		<< " error: " << errorMessage
		;

	auto result = json::value();

	result[U("status")] = json::value::string(U("ERROR"));
	result[U("error")] = json::value::string(errorMessage.toCharArray());

	http_response response(status_codes::Accepted);

	response.set_status_code(status_codes::NotFound);

	response.set_body(result);

	request.reply(response);
}

void RESTServer::success_response(http_request request, json::value result) {
	result[U("status")] = json::value::string(U("OK"));

	auto resultStr = String(result.serialize());

	if (resultStr.length() > 255) {
		resultStr = resultStr.subString(0, 252) + "...";
	}

	info(true)
		<< request.method()
		<< " " << request.relative_uri()
		<< " result=" <<  resultStr
		;

	http_response response(status_codes::Accepted);

	response.set_status_code(status_codes::OK);

	response.set_body(result);

	request.reply(response);
}

bool RESTServer::check_auth(http_request request) {
	static String authHeader;

	if (authHeader.isEmpty()) {
		auto apiAuthToken = ConfigManager::instance()->getString("Core3.RESTServer.APIToken", "");

		if (apiAuthToken.length() == 0) {
			error() << "Core3.RESTServer.APIToken not set, refusing to authorize API call.";
			return false;
		}

		if (apiAuthToken.length() < 15) {
			error() << "Core3.RESTServer.APIToken too short, must be at least 15 characters, refusing to authorize API call.";
			return false;
		}

		authHeader = "Bearer " + apiAuthToken;
	}

	auto headers = request.headers();

	if (request.headers().find(header_names::authorization) == headers.end())
		return false;

	auto requestToken = String(headers[header_names::authorization]);

	return requestToken == authHeader;
}

const String RESTServer::getJsonString(json::value jvalue, const String& fieldName, bool required, const String& defaultValue) {
	if (!jvalue.has_field(fieldName)) {
		if (required) {
			throw InvalidRequest("Invalid request, missing field: " + fieldName);
		}

		return defaultValue;
	}

	auto value = jvalue[U(fieldName)];

	if (value.is_string()) {
		return value.as_string();
	}

	throw InvalidRequest("Invalid request, invalid value type for field " + fieldName);
}

uint64_t RESTServer::getJsonUnsignedLong(json::value jvalue, const String& fieldName, bool required, uint64_t defaultValue) {
	if (!jvalue.has_field(fieldName)) {
		if (required) {
			throw InvalidRequest("Invalid request, missing field: " + fieldName);
		}

		return defaultValue;
	}

	auto value = jvalue[U(fieldName)];

	if (value.is_string()) {
		return UnsignedLong::valueOf(value.as_string());
	} else if (value.is_number()) {
		return value.as_number().to_uint64();
	}

	throw InvalidRequest("Invalid request, invalid value type for field " + fieldName);
}

void RESTServer::start() {
	setLogLevel(Logger::DEBUG);

	if (restListener != nullptr) {
		info() << "shutting down previous listener";
		restListener->close().wait();
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

	port = ConfigManager::instance()->getRESTPort();

	restListener = new http_listener(("https://0.0.0.0:" + String::valueOf(port)).toCharArray(), serverConfig);

	restListener->support(methods::GET, [this](http_request request) { routeRequest(request); });
	restListener->support(methods::POST, [this](http_request request) { routeRequest(request); });
	restListener->support(methods::PUT, [this](http_request request) { routeRequest(request); });
	restListener->support(methods::DEL, [this](http_request request) { routeRequest(request); });

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

	crossplat::threadpool::shared_instance().service().stop();
	info(true) << "shut down thread pool";
}
#endif // WITH_REST_API
