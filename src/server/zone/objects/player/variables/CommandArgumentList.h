/*
 * COMMANDARGUMENTLIST.h
 *
 *  Created on: 23/08/2010
 *      Author: victor
 */

#ifndef COMMANDARGUMENTLIST_H_
#define COMMANDARGUMENTLIST_H_

#include "engine/engine.h"

class CommandArgumentList : public VectorMap<String, SortedVector<String> > {
public:
	void addArgument(const String& command, const String& arg) {
		String lowCaseCommand = command.toLowerCase();
		String lowCaseArg = arg.toLowerCase();

		if (contains(lowCaseCommand)) {
			SortedVector<String>* vec = &get(lowCaseCommand);
			vec->setNoDuplicateInsertPlan();
			vec->put(lowCaseArg);
		} else {
			SortedVector<String> args;
			args.add(lowCaseArg);

			put(lowCaseCommand, args);
		}
	}

	void dropArgument(const String& command, const String& arg) {
		String lowCaseCommand = command.toLowerCase();
		String lowCaseArg = arg.toLowerCase();

		if (contains(lowCaseCommand)) {
			SortedVector<String>* vec = &get(lowCaseCommand);
			vec->setNoDuplicateInsertPlan();
			vec->drop(lowCaseArg);

			if (vec->size() == 0)
				drop(lowCaseCommand);
		}
	}

	bool containsArgument(const String& command, const String& arg) {
		String lowCaseCommand = command.toLowerCase();
		String lowCaseArg = arg.toLowerCase();

		if (!contains(lowCaseCommand))
			return false;

		SortedVector<String>* vec = &get(lowCaseCommand);
		vec->setNoDuplicateInsertPlan();

		return vec->contains(lowCaseArg);
	}
};

#endif /* COMMANDARGUMENTLIST_H_ */
