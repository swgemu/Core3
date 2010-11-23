/*
 * MantisDatabase.cpp
 *
 *  Created on: Nov 22, 2010
 *      Author: crush
 */


#include "MantisDatabase.h"

Vector<Database*>* MantisDatabase::databases = NULL;
AtomicInteger MantisDatabase::currentDB;
String MantisDatabase::tablePrefix;
