/**
 * @author      : theanswer (theanswer@Victors-MacBook-Pro.local)
 * @file        : RESTServer
 * @created     : Sunday Nov 11, 2018 11:31:08 CET
 */

#include <cpprest/http_listener.h>
#include <cpprest/json.h>

#include <iostream>
#include <map>
#include <set>
#include <string>

#include "engine/engine.h"

#include "RESTServer.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

using namespace std;
using namespace server::web3;

RESTServer::RESTServer() : Logger("RESTServer") {

}

RESTServer::~RESTServer() {
}

void handle_get(http_request request) {
	const auto& uri = request.relative_uri();

	auto fragments = uri::split_path(uri.to_string());

	nlohmann::json responses = nlohmann::json::array();

	for (const auto& frag : fragments) {
		uint64 oid = UnsignedLong::valueOf(frag.c_str());

		auto obj = Core::lookupObject(oid).castTo<ManagedObject*>();

		if (obj != nullptr) {
			ReadLocker lock(obj);

			nlohmann::json jsonData;
			obj->writeJSON(jsonData);

			nlohmann::json entry;
			entry[frag] = jsonData;

			//responses[frag] = jsonData;
			responses.push_back(entry);
		}
	}

	if (responses.empty()) {
		request.reply(status_codes::NotFound);
	} else {
		request.reply(status_codes::OK, json::value(responses.dump(2), false));
	}
}

void RESTServer::run() {
	http_listener listener("http://localhost:17632/object");

	listener.support(methods::GET, handle_get);
	//listener.support(methods::POST, handle_post);
	//listener.support(methods::PUT, handle_put);
	//listener.support(methods::DEL, handle_del);

	try {
		listener.open()
			.then([&listener, this]() {
				this->info("listening...", true);
			})
			.wait();

		while (doRun);
	} catch (exception const & e) {
		wcout << e.what() << std::endl;
	}

}

void RESTServer::stop() {
	doRun.set(false);
}
