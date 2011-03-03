/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "zone/Zone.h"
#include "zone/managers/object/ObjectManager.h"

#include "ClientCore.h"
#include "login/LoginSession.h"

ClientCore::ClientCore(int instances) : Core("log/core3client.log"), Logger("CoreClient") {
	ClientCore::instances = instances;
}

void ClientCore::initialize() {
	info("starting up client..");
}

void ClientCore::run() {
	for (int i = 0; i < instances; ++i) {
		LoginSession loginSession(i);
		loginSession.run();

		uint32 selectedCharacter = loginSession.getSelectedCharacter();
		uint64 objid = 0;

		if (selectedCharacter != -1) {
			objid = loginSession.getCharacterObjectID(selectedCharacter);

			info("trying to login " + String::valueOf(objid), true);
		}

		uint32 acc = loginSession.getAccountID();
		uint32 session = loginSession.getSessionID();

		Zone* zone = new Zone(i, objid, acc, session);
		zone->start();

		zones.add(zone);

		Thread::sleep(2000);
	}

	info("initialized", true);

	handleCommands();

	/*delete zone;
	zone = NULL;*/
}

void ClientCore::handleCommands() {
	while (true) {
		try {
			String command;

			Thread::sleep(500);

			continue;

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

		} catch (...) {
			System::out << "[ClientCore] unreported Exception caught\n";

			throw;
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
	} catch (...) {
		System::out << "unreported exception caught main()\n";
	}

	return 0;
}
