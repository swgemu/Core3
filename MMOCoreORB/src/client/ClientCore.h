/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLIENTCORE_H_
#define CLIENTCORE_H_

#include "system/lang.h"
#include "engine/engine.h"
#include "renderer/ClientRenderer.h"

class Zone;
class CmdStartScene;
class ClientCore : public Core, public Logger {
	int instances;
	osgViewer::Viewer viewer;
	Vector<Zone*> zones;
	ClientRenderer *renderer;
public:
	ClientCore(int instances);

	void initialize();

	void run();

	void loginCharacter(int index);
	void logoutCharacter(int index);
	
	void handleStartScene(CmdStartScene *packet);

	void handleCommands();
	
	ClientRenderer* getRenderer() { return renderer; }
	void setRenderer(ClientRenderer* r) { renderer = r; }
	osgViewer::Viewer *getViewer() { return &viewer; }
};

#endif /*CLIENTCORE_H_*/
