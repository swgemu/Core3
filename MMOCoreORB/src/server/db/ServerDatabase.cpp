/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ServerDatabase.h"

Vector<Database*>* ServerDatabase::databases = NULL;
AtomicInteger ServerDatabase::currentDB;
