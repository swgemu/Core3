/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "client/zone/Zone.h"
#include "client/zone/managers/object/ObjectManager.h"
#include "conf/ConfigManager.h"
#include "templates/manager/DataArchiveStore.h"
#include "templates/manager/TemplateManager.h"
#include "client/ClientCore.h"


#include "client/login/LoginSession.h"


ClientCore::ClientCore(int instances) : Core("log/core3client.log"), Logger("CoreClient") {
	ClientCore::instances = instances;

	setInfoLogLevel();
}

void ClientCore::initialize() {
	renderer = NULL;
	info("starting up client..");
	
	ConfigManager::instance()->loadConfigData();
	DataArchiveStore::instance()->loadTres(ConfigManager::instance()->getTrePath(), ConfigManager::instance()->getTreFiles());
	TemplateManager *manager = TemplateManager::instance();//new TemplateManager();
	
	manager->loadLuaTemplates();
}

int connectCount = 0, disconnectCount = 0;

void ClientCore::run() {
	for (int i = 0; i < instances; ++i) {
		zones.add(NULL);
	}
//	viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);
//	viewer.setCameraManipulator(new osgGA::TrackballManipulator());
//	viewer.setUpThreading();
//	viewer.realize();
//
//	
//	renderer->run();
	
	viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);
	viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	viewer.setUpThreading();
	viewer.realize();
	
	Zone *zone = new Zone(this, 0, 0, 0, 0);
	zone->name = "tatooine";
	
	renderer = ClientRenderer::instance();
	renderer->initialize(this, zone, Vector3(-131, -4723, 0), &viewer);
	renderer->run();
	while(true) {
		if(renderer)
			renderer->frame();
	}

	info("initialized", true);

	int rounds = 0;

	ClientCore* cCore = this;
	Core::getTaskManager()->executeTask([=] {
		loginCharacter(0);
		
		handleCommands();

	}, "input");
	

//	for (int i = 0; i < instances; ++i) {
//		Zone* zone = zones.get(i);
//		if (zone != NULL)
//			zone->disconnect();
//	}
//
//	Thread::sleep(10000);
}

void ClientCore::loginCharacter(int index) {
	try {
		Zone* zone = zones.get(index);
		if (zone != NULL)
			return;

		Reference<LoginSession*> loginSession = new LoginSession(index);
		loginSession->run();

		uint32 selectedCharacter = loginSession->getSelectedCharacter();
		uint64 objid = 0;

		if (selectedCharacter != -1) {
			objid = loginSession->getCharacterObjectID(selectedCharacter);

			info("trying to login " + String::valueOf(objid));
		}

		uint32 acc = loginSession->getAccountID();
		uint32 session = loginSession->getSessionID();

		zone = new Zone(this, index, objid, acc, session);
		zone->start();

		zones.set(index, zone);

		connectCount++;
	} catch (Exception& e) {

	}
}

void ClientCore::logoutCharacter(int index) {
	Zone* zone = zones.get(index);
	if (zone == NULL || !zone->isStarted())
		return;

	zones.set(index, NULL);

	zone->disconnect();

	disconnectCount++;

	delete zone;
}

void ClientCore::handleCommands() {
	while (true) {
		try {
			String command;

			Thread::sleep(500);

			System::out << "> ";

			char line[256];
			fgets(line, sizeof(line), stdin);

			command = line;
			command = command.replaceFirst("\n", "");

			StringTokenizer tokenizer(command);
			String firstToken;
			tokenizer.getStringToken(firstToken);

			if (firstToken == "exit") {
				for (int i = 0; i < zones.size(); ++i)
					zones.get(i)->disconnect();

				return;
			} else if (firstToken == "follow") {
				String name;
				tokenizer.finalToken(name);

				for (int i = 0; i < zones.size(); ++i)
					zones.get(i)->follow(name);

			} else if (firstToken == "stopFollow") {
				for (int i = 0; i < zones.size(); ++i)
					zones.get(i)->stopFollow();
			} else if (firstToken == "lurk") {
				for (int i = 0; i < zones.size(); ++i)
					zones.get(i)->lurk();
			} else if (firstToken == "render") {
//				ClientRenderer renderer(NULL, NULL);
//				
//				renderer.start();
			} else if (firstToken == "info") {
				for (int i = 0; i < zones.size(); ++i) {
					uint32 size = zones.get(i)->getObjectManager()->getObjectMapSize();
					StringBuffer msg;
					msg << "[ObjectManager" << i << "] size: " << size;

					info(msg.toString(), true);
				}

			} else {
				String args;
				if (tokenizer.hasMoreTokens())
					tokenizer.finalToken(args);

				for (int i = 0; i < zones.size(); ++i)
					if (!zones.get(i)->doCommand(firstToken, args))
						Logger::console.error("unknown command");
			}
		} catch (SocketException& e) {
			System::out << "[ClientCore] " << e.getMessage();
		} catch (ArrayIndexOutOfBoundsException& e) {
			System::out << "[ClientCore] " << e.getMessage() << "\n";
			e.printStackTrace();

		} catch (Exception& e) {
			StringBuffer msg;
			msg << "[ClientCore] Exception caught";
			error(msg.toString());
			error(e.getMessage());
			e.printStackTrace();

		}
	}
}

int main(int argc, char* argv[]) {
	try {
		Vector<String> arguments;
		for (int i = 1; i < argc; ++i) {
			arguments.add(argv[i]);
		}

		StackTrace::setBinaryName("core3client");

		int instances = 1;

		if (argc > 1)
			instances = Integer::valueOf(arguments.get(0));
		
		ClientCore core(instances);
		core.start();
		
		

	} catch (Exception& e) {
		System::out << e.getMessage() << "\n";
		e.printStackTrace();
	}

	return 0;
}
