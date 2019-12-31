/**
 * @author      : theanswer (theanswer@Victors-MacBook-Pro.local)
 * @file        : RESTServer
 * @created     : Sunday Nov 11, 2018 11:31:08 CET
 */

#include "server/ServerCore.h"
#include "RESTServer.h"

using namespace server::web3;

Logger server::web3::RESTServer::logger("RESTServer");

RESTServer::RESTServer(uint16 port) : doRun(true), port(port) {

}

RESTServer::~RESTServer() {
}

#ifdef COMPILE_CORE3_REST
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <pplx/threadpool.h>

#include <map>
#include <set>
#include <string>
#include <memory>
#include <chrono>

#include "engine/engine.h"
#include "conf/ConfigManager.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

using namespace std;

namespace server {
namespace web3 {
	// simple API Authtoken check
	bool check_auth(http_request request) {
		auto apiAuthToken = ConfigManager::instance()->getString("Core3.RESTServer.APIToken", "");

		if (apiAuthToken.length() == 0) {
			RESTServer::logger.error() << "Core3.RESTServer.APIToken not set, refusing to authorize API call.";
			return false;
		}

		if (apiAuthToken.length() < 15) {
			RESTServer::logger.error() << "Core3.RESTServer.APIToken too short, must be at least 15 characters, refusing to authorize API call.";
			return false;
		}

		auto headers = request.headers();

		if (request.headers().find(header_names::authorization) == headers.end())
			return false;

		auto authHeader = "Bearer " + apiAuthToken;
		auto requestToken = String(headers[header_names::authorization].c_str());

		if (requestToken == authHeader)
			return true;

		return false;
	}

	void error_response(http_request request, const utility::string_t error) {
		const auto& uri = request.absolute_uri();

		RESTServer::logger.error()
			<< error.c_str()
			<< " - " << request.method().c_str()
			<< " " << uri.to_string().c_str()
			;

		auto result = json::value();

		result[U("status")] = json::value::string(U("ERROR"));
		result[U("error")] = json::value::string(U(error));

		http_response response(status_codes::Accepted);

		response.set_status_code(status_codes::NotFound);

		response.set_body(result);

		request.reply(response);
	}

	void handle_get_object(http_request request) {
		auto start = chrono::steady_clock::now();

		const auto& uri = request.relative_uri();

		auto fragments = uri::split_path(uri.to_string());

		// Skip resource path
		fragments.erase(fragments.begin());
		fragments.erase(fragments.begin());

		nlohmann::json responses = nlohmann::json::array();

		for (const auto& frag : fragments) {
			try {
				uint64 oid = UnsignedLong::valueOf(frag.c_str());

				auto obj = Core::lookupObject(oid).castTo<ManagedObject*>();

				if (obj != nullptr) {
					ReadLocker lock(obj);

					nlohmann::json jsonData;
					obj->writeJSON(jsonData);

					nlohmann::json entry;
					entry[frag] = jsonData;

					responses.push_back(entry);
				}
			} catch (const Exception& e) {
				RESTServer::logger.error() << e.getMessage();
			}
		}

		http_response response(status_codes::Accepted);
		response.headers()[U("Access-Control-Allow-Origin")] = U("*");

		if (responses.empty()) {
			response.set_status_code(status_codes::NotFound);
		} else {
			response.set_status_code(status_codes::OK);

			response.set_body(json::value::parse(responses.dump()));
		}

		auto end = chrono::steady_clock::now();
		auto diff = end - start;

		response.headers()[U("ms")] = String::valueOf(chrono::duration <double, milli> (diff).count()).toCharArray();

		request.reply(response);
	}

	void handle_get_version(http_request request) {
		auto result = json::value();

		result[U("status")] = json::value::string(U("OK"));
		result[U("api_version")] = json::value::number(1);

		http_response response(status_codes::Accepted);

		response.set_status_code(status_codes::OK);

		response.set_body(result);

		request.reply(response);
	}

	void handle_post_admin(http_request request) {
		const auto& uri = request.relative_uri();

		RESTServer::logger.info(true) << "REMOTE ADMIN COMMAND: " << uri.to_string().c_str();

		auto fragments = uri::split_path(uri.path());

		// Skip resource path
		fragments.erase(fragments.begin());
		fragments.erase(fragments.begin());

		http_response response(status_codes::Accepted);

		if (fragments.size() <= 0) {
			response.set_status_code(status_codes::NotFound);
			request.reply(response);
		}

		auto subCommand = fragments.front();

		response.set_status_code(status_codes::OK);

		auto result = json::value();

		result[U("status")] = json::value::string(U("OK"));
		result[U("subcommand")] = json::value::string(subCommand);

		if (subCommand == "console") {
			fragments.erase(fragments.begin());

			if (fragments.size() <= 0) {
				error_response(request, "Missing console command");
				return;
			}

			StringBuffer buf;

			for (const auto& part : fragments) {
				buf << " " << part.c_str();
			}

			auto get_vars = uri::split_query(uri.query());

			auto find_args = get_vars.find(U("args"));

			if (find_args != get_vars.end()) {
				buf << " " << uri::decode(find_args->second).c_str();
			}

			auto consoleCommand = buf.toString().trim();

			result[U("console_command")] = json::value::string(consoleCommand.toCharArray());

			RESTServer::logger.info(true) << "REMOTE CONSOLE COMMAND: " << consoleCommand;
			ServerCore::getInstance()->queueConsoleCommand(consoleCommand);
		}

		response.set_body(result);

		request.reply(response);
	}

	// Simple routers

	void handle_get(http_request request) {
		if (!check_auth(request)) {
			request.reply(status_codes::Forbidden, U("Invalid API Token"));
			return;
		}

		const auto& uri = request.relative_uri();

		if (uri.path() == "/v1/version") {
			handle_get_version(request);
			return;
		}

		if (uri.path().rfind("/v1/object/", 0) == 0) {
			handle_get_object(request);
			return;
		}

		error_response(request, "Invalid resource");
	}

	void handle_post(http_request request) {
		if (!check_auth(request)) {
			request.reply(status_codes::Forbidden, U("Invalid API Token"));
			return;
		}

		const auto& uri = request.relative_uri();

		if (uri.path().rfind("/v1/admin/", 0) == 0) {
			handle_post_admin(request);
			return;
		}

		error_response(request, "Invalid resource");
	}

	UniqueReference<http_listener*> restListener;
}
}

void RESTServer::start() {
	logger.setLogLevel(Logger::DEBUG);

	if (restListener != nullptr) {
		logger.info() << "shutting down previous listener";
		restListener->close().wait();
	}

	http_listener_config serverConfig;

	serverConfig.set_ssl_context_callback([&](boost::asio::ssl::context& ctx) {
		auto sslKeyFilename = ConfigManager::instance()->getString("Core3.RESTServer.SSLKeyFile", "");

		if (sslKeyFilename.length() == 0) {
			logger.error() << "missing Core3.RESTServer.SSLKeyFile";
			return;
		}

		auto sslCrtFilename = ConfigManager::instance()->getString("Core3.RESTServer.SSLCertFile", "");

		if (sslCrtFilename.length() == 0) {
			logger.error() << "missing Core3.RESTServer.SSLCertFile";
			return;
		}

		ctx.set_options(boost::asio::ssl::context::default_workarounds);

		boost::system::error_code error;

		ctx.use_certificate_chain_file(sslCrtFilename.toCharArray(), error);

		if (error) {
			logger.error() << "load ssl cert failed: " << error.message().c_str();
			return;
		}

		ctx.use_private_key_file(sslKeyFilename.toCharArray(), boost::asio::ssl::context::pem, error);

		if (error) {
			logger.error() << "load ssl key failed: " << error.message().c_str();
			return;
		}
	});

	restListener = new http_listener(("https://0.0.0.0:" + String::valueOf(port)).toCharArray(), serverConfig);

	restListener->support(methods::GET, handle_get);
	restListener->support(methods::POST, handle_post);
	//listener.support(methods::PUT, handle_put);
	//listener.support(methods::DEL, handle_del);

	try {
		restListener->open()
			.then([this] {
			logger.info(true) << "listening to port " << port;
		}).wait();
	} catch (exception const & e) {
		logger.error() << e.what();
	}
}

void RESTServer::stop() {
	doRun.set(false);

	if (restListener != nullptr) {
		restListener->close().wait();
		restListener = nullptr;
	}

	crossplat::threadpool::shared_instance().service().stop();
	logger.info(true) << "shut down thread pool";
}

#else

void RESTServer::start() {
	logger.error() << "disabled, server compiled without rest support";
}

void RESTServer::stop() {
	doRun.set(false);
}

#endif
