/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include <boost/program_options.hpp>
#include <fstream>
#include "engine/util/JSONSerializationType.h"
#include "client/zone/Zone.h"
#include "client/zone/managers/object/ObjectManager.h"

#include "ClientCore.h"

#include "client/login/LoginSession.h"
#include "client/ActionBase.h"
#include "client/ActionManager.h"
#include "server/zone/packets/charcreation/ClientCreateCharacter.h"

int exit_result = 1;

// ClientCoreOptions constructor - does ALL parsing
ClientCoreOptions::ClientCoreOptions(int argc, char** argv) {
	namespace po = boost::program_options;

	// 1. Initialize config with defaults
	config = {
		{"username", ""},
		{"password", ""},
		{"loginHost", "127.0.0.1"},
		{"loginPort", 44453},
		{"clientVersion", "20050408-18:00"},
		{"loginTimeout", 10},
		{"zoneTimeout", 30},
		{"logLevel", static_cast<int>(Logger::INFO)},
		{"characterOid", 0},
		{"characterFirstname", ""},
		{"saveState", ""},
		{"loginOnly", false},
		{"waitAfterZone", 0},
		{"actions", JSONSerializationType::array()}
	};

	// 2. First pass to get --env option
	po::options_description env_desc("Environment");
	env_desc.add_options()
		("env", po::value<std::string>(), "Environment file to load");

	po::variables_map env_vm;
	po::store(po::command_line_parser(argc, argv).options(env_desc).allow_unregistered().run(), env_vm);
	po::notify(env_vm);

	// Load .env files
	if (env_vm.count("env")) {
		loadEnvFile(env_vm["env"].as<std::string>().c_str());
	} else {
		loadEnvFile(".env");
		loadEnvFile(".env-core3client");
	}

	// 3. Quick scan for --options-json (overrides everything)
	bool jsonLoaded = false;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--options-json") == 0 && i+1 < argc) {
			std::ifstream file(argv[i+1]);
			if (file.is_open()) {
				JSONSerializationType json;
				file >> json;

				// Merge JSON into config (JSON takes priority over defaults)
				for (auto it = json.begin(); it != json.end(); ++it) {
					config[it.key()] = it.value();
				}
				jsonLoaded = true;
			}
			break;
		}
	}

	// 4. Parse global options from command line (overrides JSON)
	po::options_description desc("Options");
	desc.add_options()
		("help,h", "Show help message")
		("list-actions", "List all available actions and exit")
		("username,u", po::value<std::string>(), "Username for login")
		("password,p", po::value<std::string>(), "Password for login")
		("login-host", po::value<std::string>(), "Login server hostname")
		("login-port", po::value<int>(), "Login server port")
		("client-version", po::value<std::string>(), "Client version string")
		("login-timeout", po::value<int>(), "Login timeout in seconds")
		("zone-timeout", po::value<int>(), "Zone timeout in seconds")
		("log-level", po::value<std::string>(), "Log level (0-5 or fatal/error/warning/log/info/debug)")
		("character-oid", po::value<uint64>(), "Character object ID to select")
		("character-firstname", po::value<std::string>(), "Character first name to select")
		("save-state", po::value<std::string>(), "Save login state to JSON file")
		("login-only", "Only perform login, skip zone connection")
		("options-json", po::value<std::string>(), "Load options from JSON file")
		("generate-options-json", "Generate default options JSON to stdout and exit")
		("env", po::value<std::string>(), "Environment file to load")
		("wait-after-zone", po::value<int>(), "Seconds to stay connected to zone before shutdown");

	po::variables_map vm;
	auto parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
	po::store(parsed, vm);
	po::notify(vm);

	// Get args that boost didn't recognize (for action parsing)
	std::vector<std::string> unrecognized = po::collect_unrecognized(parsed.options, po::include_positional);
	Vector<String> unrecognizedArgs;
	for (const auto& arg : unrecognized) {
		unrecognizedArgs.add(String(arg.c_str()));
	}

	if (vm.count("help")) {
		std::cout << desc << std::endl;
		std::cout << std::endl;
		std::cout << "Actions:" << std::endl;
		Vector<String> actionNames = ActionManager::listActions();
		for (int i = 0; i < actionNames.size(); i++) {
			ActionBase* action = ActionManager::createAction(actionNames.get(i).toCharArray());
			if (action != nullptr) {
				String helpText = action->getHelpText();
				if (!helpText.isEmpty()) {
					std::cout << "  " << helpText.toCharArray() << std::endl;
				}
				delete action;
			}
		}
		exit(0);
	}

	if (vm.count("list-actions")) {
		std::cout << "Actions:" << std::endl;
		Vector<String> actionNames = ActionManager::listActions();
		for (int i = 0; i < actionNames.size(); i++) {
			ActionBase* action = ActionManager::createAction(actionNames.get(i).toCharArray());
			if (action != nullptr) {
				String helpText = action->getHelpText();
				if (!helpText.isEmpty()) {
					std::cout << "  " << helpText.toCharArray() << std::endl;
				}
				delete action;
			}
		}
		exit(0);
	}

	// Apply environment variables (if not already set by JSON/CLI)
	if (config["username"].get<std::string>().empty()) {
		const char* envUser = getenv("CORE3_CLIENT_USERNAME");
		if (envUser) config["username"] = envUser;
	}
	if (config["password"].get<std::string>().empty()) {
		const char* envPass = getenv("CORE3_CLIENT_PASSWORD");
		if (envPass) config["password"] = resolveFileReference(String(envPass)).toCharArray();
	}
	if (config["loginHost"].get<std::string>() == "127.0.0.1") {
		const char* envHost = getenv("CORE3_CLIENT_LOGINHOST");
		if (envHost) config["loginHost"] = envHost;
	}
	if (config["loginPort"].get<int>() == 44453) {
		const char* envPort = getenv("CORE3_CLIENT_LOGINPORT");
		if (envPort) config["loginPort"] = Integer::valueOf(envPort);
	}

	// Apply command line options (highest priority)
	if (vm.count("username")) config["username"] = vm["username"].as<std::string>();
	if (vm.count("password")) config["password"] = resolveFileReference(String(vm["password"].as<std::string>().c_str())).toCharArray();
	if (vm.count("login-host")) config["loginHost"] = vm["login-host"].as<std::string>();
	if (vm.count("login-port")) config["loginPort"] = vm["login-port"].as<int>();
	if (vm.count("client-version")) config["clientVersion"] = vm["client-version"].as<std::string>();
	if (vm.count("login-timeout")) config["loginTimeout"] = vm["login-timeout"].as<int>();
	if (vm.count("zone-timeout")) config["zoneTimeout"] = vm["zone-timeout"].as<int>();
	if (vm.count("log-level")) config["logLevel"] = parseLogLevel(String(vm["log-level"].as<std::string>().c_str()));
	if (vm.count("character-oid")) config["characterOid"] = vm["character-oid"].as<uint64>();
	if (vm.count("character-firstname")) config["characterFirstname"] = vm["character-firstname"].as<std::string>();
	if (vm.count("save-state")) config["saveState"] = vm["save-state"].as<std::string>();
	if (vm.count("login-only")) config["loginOnly"] = true;
	if (vm.count("wait-after-zone")) config["waitAfterZone"] = vm["wait-after-zone"].as<int>();

	// Handle --generate-options-json after all config is loaded
	if (vm.count("generate-options-json")) {
		JSONSerializationType output = config;
		if (output.contains("password")) {
			output["password"] = "***";
		}
		std::cout << output.dump(2) << std::endl;
		exit(0);
	}

	// Validate required fields
	if (config["username"].get<std::string>().empty()) {
		throw Exception("ERROR: Please provide --username or set CORE3_CLIENT_USERNAME environment variable");
	}
	if (config["password"].get<std::string>().empty()) {
		throw Exception("ERROR: Please provide --password or set CORE3_CLIENT_PASSWORD environment variable");
	}

	// 5. Parse actions - JSON first, then CLI args can add more
	if (jsonLoaded && config.contains("actions") && config["actions"].is_array()) {
		parseJSONIntoActions(config["actions"]);
	}

	// Parse CLI args (can add to JSON actions or provide all actions if no JSON)
	parseArgumentsIntoActions(unrecognizedArgs);

	// Resolve dependencies (auto-insert prerequisites and handle special cases)
	resolveDependencies();

	// Validate we have actions
	if (actions.size() == 0) {
		throw Exception("ERROR: No actions specified. Use --login-only, JSON actions array, or CLI action flags (--create-character, etc.)");
	}
}

ClientCore::ClientCore(const ClientCoreOptions& opts) : Core("log/core3client.log", "client3"), Logger("CoreClient") {
	options = opts;
	zone = nullptr;
	selectedCharacterOid = 0;
	targetCharacterOid = 0;
	targetGalaxyId = 0;

	overallStartTime.updateToCurrentTime();

	Core::initializeProperties("Client3");

	// Fill in missing values from client3.lua properties
	if (options.config["loginHost"].get<std::string>().empty() || options.config["loginHost"].get<std::string>() == "127.0.0.1") {
		String prop = Core::getProperty("Client3.LoginHost", "127.0.0.1");
		if (!prop.isEmpty()) options.config["loginHost"] = prop.toCharArray();
	}
	if (options.config["loginPort"].get<int>() == 0 || options.config["loginPort"].get<int>() == 44453) {
		int prop = Core::getIntProperty("Client3.LoginPort", 44453);
		if (prop != 44453) options.config["loginPort"] = prop;
	}

	// Override properties with user values (higher priority)
	if (!options.config["loginHost"].get<std::string>().empty()) {
		Core::setProperty("Client3.LoginHost", String(options.config["loginHost"].get<std::string>().c_str()));
	}
	if (options.config["loginPort"].get<int>() != 0) {
		Core::setProperty("Client3.LoginPort", String::valueOf(options.config["loginPort"].get<int>()));
	}

	int logLevel = options.get<int>("/logLevel", Logger::INFO);
	setLogLevel(static_cast<LogLevel>(logLevel));
	info(true) << "Log level set to: " << Logger::getLogType(static_cast<LogLevel>(logLevel)) << "(" << logLevel << ")";

	info(true) << "Current options: " << options;
}

void ClientCore::initialize() {
	info(true) << __PRETTY_FUNCTION__ << " start";
}

void ClientCoreOptions::parseJSONIntoActions(const JSONSerializationType& jsonActions) {
	for (auto& actionConfig : jsonActions) {
		if (!actionConfig.contains("action")) {
			System::err << "JSON action missing 'action' field" << endl;
			continue;
		}

		String actionName = String(actionConfig["action"].get<std::string>().c_str());
		ActionBase* action = ActionManager::createAction(actionName.toCharArray());

		if (action == nullptr) {
			System::err << "Unknown action type: " << actionName << endl;
			continue;
		}

		// Parse action-specific config
		action->parseJSON(actionConfig);
		actions.add(action);
	}
}

void ClientCoreOptions::parseArgumentsIntoActions(const Vector<String>& args) {
	for (int i = 0; i < args.size(); ) {
		int consumed = 0;

		// First: Offer arg to existing actions in the array (in order)
		for (int j = 0; j < actions.size(); j++) {
			consumed = actions.get(j)->parseArgs(args, i);
			if (consumed > 0) {
				i += consumed;
				break;
			}
		}

		if (consumed > 0) continue;

		// Second: Try creating new action from registered types
		Vector<String> actionNames = ActionManager::listActions();
		for (int j = 0; j < actionNames.size(); j++) {
			ActionBase* action = ActionManager::createAction(actionNames.get(j).toCharArray());
			if (action == nullptr) continue;

			consumed = action->parseArgs(args, i);

			if (consumed > 0) {
				actions.add(action);
				i += consumed;
				break;
			}

			delete action;
		}

		// Handle unrecognized
		if (consumed == 0) {
			if (args.get(i).charAt(0) == '-') {
				System::err << "ERROR: Unrecognized option: " << args.get(i) << endl;
				System::err << "Use --help to see available options" << endl;
				exit(1);
			}
			i++;
		}
	}
}

void ClientCoreOptions::resolveDependencies() {
	// Special case: --login-only with no actions → add loginAccount
	if (config["loginOnly"].get<bool>() && actions.size() == 0) {
		ActionBase* login = ActionManager::createAction("loginAccount");
		if (login != nullptr) {
			actions.add(login);
		}
	}

	// Walk actions and auto-insert required dependencies
	Vector<ActionBase*> final;
	bool hasLoginAccount = false;
	bool hasSelectContext = false;
	bool hasConnectToZone = false;
	bool hasZoneInCharacter = false;
	bool hasLogoutCharacter = false;
	bool needsLogout = false;

	for (int i = 0; i < actions.size(); i++) {
		ActionBase* action = actions.get(i);

		// Track what we have
		const char* name = action->getName();
		if (strcmp(name, "loginAccount") == 0) hasLoginAccount = true;
		if (strcmp(name, "selectContext") == 0) hasSelectContext = true;
		if (strcmp(name, "connectToZone") == 0) hasConnectToZone = true;
		if (strcmp(name, "zoneInCharacter") == 0) hasZoneInCharacter = true;
		if (strcmp(name, "logoutCharacter") == 0) hasLogoutCharacter = true;

		// Track if we need logout
		if (strcmp(name, "zoneInCharacter") == 0 || strcmp(name, "createCharacter") == 0) {
			needsLogout = true;
		}

		// Auto-insert selectContext before first action needing target
		if (action->needsTarget() && !hasSelectContext) {
			ActionBase* selector = ActionManager::createAction("selectContext");
			if (selector != nullptr) {
				final.add(selector);
				hasSelectContext = true;
			}
		}

		// Auto-insert connectToZone before first zone-needing action
		if (action->needsZone() && !hasConnectToZone) {
			ActionBase* connector = ActionManager::createAction("connectToZone");
			if (connector != nullptr) {
				final.add(connector);
				hasConnectToZone = true;
			}
		}

		final.add(action);
	}

	// Ensure loginAccount at position 0
	if (!hasLoginAccount) {
		ActionBase* login = ActionManager::createAction("loginAccount");
		if (login != nullptr) {
			final.add(0, login);
		}
	}

	// Ensure logoutCharacter at end if we zoned in (for cleanup)
	if (needsLogout && !hasLogoutCharacter) {
		ActionBase* logout = ActionManager::createAction("logoutCharacter");
		if (logout != nullptr) {
			final.add(logout);
		}
	}

	actions = final;
}

void ClientCore::executeActions() {
	for (int i = 0; i < options.actions.size(); i++) {
		ActionBase* action = options.actions.get(i);

		info(true) << "Running action: " << action->getName();
		action->run(*this);

		if (!action->isOK()) {
			error() << action->getName() << " failed: " << action->getError();
			exit_result = 100 + action->getErrorCode();

			// Mark remaining actions as skipped
			for (int j = i + 1; j < options.actions.size(); j++) {
				options.actions.get(j)->setSkipped();
			}

			break;
		}
	}
}

void ClientCore::run() {
	info(true) << "Core3Client starting";

	if (options.actions.size() == 0) {
		error() << "No actions to execute";
		exit_result = 100;
		return;
	}

	executeActions();

	if (exit_result == 1) {
		exit_result = 0;
	}

	int waitAfterZone = options.get<int>("/waitAfterZone", 0);
	if (waitAfterZone > 0 && zone != nullptr && zone->isSceneReady()) {
		info(true) << "Staying connected for " << waitAfterZone << " seconds...";
		Thread::sleep(waitAfterZone * 1000);
		info(true) << "Wait complete, proceeding to shutdown...";
	}

	std::string saveState = options.get<std::string>("/saveState", "");
	if (!saveState.empty()) {
		saveStateToFile(String(saveState.c_str()), loginSession);
	}

	info(true) << "Shutting down...";

	// Cleanup login session if still connected
	if (loginSession != nullptr && loginSession->isConnected()) {
		loginSession->cleanup();
	}

	// Cleanup actions
	for (int i = 0; i < options.actions.size(); i++) {
		delete options.actions.get(i);
	}
}

void ClientCore::saveStateToFile(const String& filename, LoginSession* loginSession) {
	try {
		JSONSerializationType jsonData;

		// Overall timing
		jsonData["totalElapsedMs"] = overallStartTime.miliDifference();

		// Timestamp
		Time now;
		now.updateToCurrentTime();
		jsonData["@timestamp"] = now.getFormattedTimeFull().toCharArray();
		jsonData["time_msecs"] = now.getMiliTime();

		// Exit code
		jsonData["exitCode"] = exit_result;

		// Login stats
		if (loginSession != nullptr) {
			jsonData["loginStats"] = loginSession->collectStats();

			// Account info
			JSONSerializationType account;
			account["id"] = loginSession->getAccountID();
			account["username"] = loginSession->getSessionID().isEmpty() ? "" : loginSession->collectStats()["username"];
			account["sessionId"] = loginSession->getSessionID().toCharArray();
			jsonData["account"] = account;

			// Galaxies - iterate through all galaxies in the map
			JSONSerializationType galaxiesArray = JSONSerializationType::array();
			auto& galaxyMap = loginSession->getGalaxies();
			for (int i = 0; i < galaxyMap.size(); ++i) {
				auto& galaxy = galaxyMap.get(i);
				if (!galaxy.getName().isEmpty()) {
					JSONSerializationType galaxyObj;
					galaxyObj["id"] = galaxy.getID();
					galaxyObj["name"] = galaxy.getName().toCharArray();
					galaxyObj["address"] = galaxy.getAddress().toCharArray();
					galaxyObj["port"] = galaxy.getPort();
					galaxyObj["population"] = galaxy.getPopulation();
					galaxiesArray.push_back(galaxyObj);
				}
			}
			jsonData["galaxies"] = galaxiesArray;

			// Characters from login (may be empty if new account)
			JSONSerializationType charactersArray = JSONSerializationType::array();
			for (int i = 0; i < loginSession->getCharacterListSize(); ++i) {
				const auto& character = loginSession->getCharacterByIndex(i);
				JSONSerializationType charObj;
				charObj["name"] = character.getFirstName().toCharArray();
				charObj["oid"] = character.getObjectID();
				charObj["galaxyId"] = character.getGalaxyID();
				charObj["source"] = "existing";
				charactersArray.push_back(charObj);
			}

		jsonData["characters"] = charactersArray;
	}

		// Zone stats
		if (zone != nullptr) {
			jsonData["zoneStats"] = zone->collectStats();
			jsonData["zoneConnected"] = true;

			// Selected zone info
			JSONSerializationType selectedZone;
			selectedZone["characterId"] = selectedCharacterOid;
			selectedZone["address"] = zone->getGalaxyAddress().toCharArray();
			selectedZone["port"] = zone->getGalaxyPort();
			jsonData["selectedZone"] = selectedZone;
		} else {
			jsonData["zoneConnected"] = false;
		}

		// Success flags
		jsonData["loginSuccess"] = (loginSession != nullptr && loginSession->getAccountID() != 0);
		jsonData["overallSuccess"] = (exit_result == 0);
		jsonData["exitCode"] = exit_result;

		// Selected galaxy (if we got that far)
		if (selectedGalaxy) {
			JSONSerializationType selectedGalaxyJson;
			selectedGalaxyJson["id"] = selectedGalaxy->getID();
			selectedGalaxyJson["name"] = selectedGalaxy->getName().toCharArray();
			selectedGalaxyJson["address"] = selectedGalaxy->getAddress().toCharArray();
			selectedGalaxyJson["port"] = selectedGalaxy->getPort();
			selectedGalaxyJson["population"] = selectedGalaxy->getPopulation();
			jsonData["selectedGalaxy"] = selectedGalaxyJson;
		}

		// Runtime options
		jsonData["runtimeOptions"] = options.getAsJSON();

		// Actions array (new format)
		JSONSerializationType actionsArray = JSONSerializationType::array();
		for (int i = 0; i < options.actions.size(); i++) {
			actionsArray.push_back(options.actions.get(i)->toJSON());
		}
		jsonData["actions"] = actionsArray;

		// Variables map
		if (vars.size() > 0) {
			JSONSerializationType varsObj;
			for (int i = 0; i < vars.size(); i++) {
				varsObj[vars.elementAt(i).getKey().toCharArray()] = vars.elementAt(i).getValue().toCharArray();
			}
			jsonData["variables"] = varsObj;
		}

		// Write to file
		std::ofstream file(filename.toCharArray());
		if (file.is_open()) {
			file << jsonData.dump(2);  // Pretty print with 2-space indent
			file.close();
			info(true) << "State saved to: " << filename;
		} else {
			error() << "Failed to open file for writing: " << filename;
		}

	} catch (Exception& e) {
		error() << "Error saving state: " << e.getMessage();
	}
}

String ClientCoreOptions::resolveFileReference(const String& value) {
	// Check if value starts with '@'
	if (value.isEmpty() || value.charAt(0) != '@') {
		return value;
	}

	// Extract the file path (everything after '@')
	String filePath = value.subString(1);

	// Try to open and read the file
	std::ifstream file(filePath.toCharArray());
	if (!file.is_open()) {
		String errorMsg = "ERROR: Cannot read file referenced by '@': " + filePath;
		System::err << errorMsg << endl;
		throw Exception(errorMsg);
	}

	// Read the entire file content
	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	// Convert to String and trim whitespace
	String result(content.c_str());
	return result.trim();
}

void ClientCoreOptions::loadEnvFile(const String& filename) {
	std::ifstream file(filename.toCharArray());
	if (!file.is_open()) return;

	std::string line;
	while (std::getline(file, line)) {
		String envLine(line.c_str());
		envLine = envLine.trim();
		if (envLine.isEmpty() || envLine.charAt(0) == '#') continue;

		StringTokenizer tokenizer(envLine);
		tokenizer.setDelimeter("=");

		if (tokenizer.hasMoreTokens()) {
			String key = tokenizer.getStringToken();
			if (tokenizer.hasMoreTokens()) {
				String value;
				tokenizer.finalToken(value);
				setenv(key.toCharArray(), value.toCharArray(), 1);
			}
		}
	}
}

int ClientCoreOptions::parseLogLevel(const String& levelStr) {
	String level = levelStr.toLowerCase();

	if (level == "fatal") return Logger::FATAL;
	if (level == "error") return Logger::ERROR;
	if (level == "warning" || level == "warn") return Logger::WARNING;
	if (level == "log") return Logger::LOG;
	if (level == "info") return Logger::INFO;
	if (level == "debug") return Logger::DEBUG;

	// Try to parse as number
	try {
		return Integer::valueOf(levelStr);
	} catch (...) {
		return Logger::INFO; // Default to INFO on parse failure
	}
}

String ClientCoreOptions::toString() const {
	return getAsJSON().dump().c_str();
}

JSONSerializationType ClientCoreOptions::getAsJSON() const {
	// Return a copy with password masked
	JSONSerializationType jsonData = config;
	if (jsonData.contains("password")) {
		jsonData["password"] = "***";
	}
	return jsonData;
}

String ClientCoreOptions::toStringData() const {
	return toString();
}

int main(int argc, char* argv[]) {
	try {
		ClientCoreOptions opts(argc, argv);

		StackTrace::setBinaryName("core3client");

		// Configure engine3
		Core::setProperty("TaskManager.defaultSchedulerThreads", "2");
		Core::setProperty("TaskManager.defaultIOSchedulers", "2");
		Core::setProperty("TaskManager.defaultWorkerQueues", "1");
		Core::setProperty("TaskManager.defaultWorkerThreadsPerQueue", "2");

		ClientCore core(opts);
		core.start();
		System::out << "core.start() returned" << endl;
	} catch (Exception& e) {
		System::out << e.getMessage() << "\n";
		e.printStackTrace();
		exit_result = 100;
	}

	System::out << "exit(" << exit_result << ")" << endl;

	return exit_result;
}
