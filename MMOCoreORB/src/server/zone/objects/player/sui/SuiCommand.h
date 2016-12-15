/*
 * SuiCommand.h
 *
 *  Created on: Nov 7, 2013
 *      Author: crush
 */

#ifndef SUICOMMAND_H_
#define SUICOMMAND_H_

#include "engine/engine.h"

class SuiCommand : public Object {
public:
	static const int SCT_none = 0x00;
	static const int SCT_clearDataSource = 0x01;
	static const int SCT_addChildWidget = 0x02;
	static const int SCT_setProperty = 0x03;
	static const int SCT_addDataItem = 0x04;
	static const int SCT_subscribeToEvent = 0x05;
	static const int SCT_addDataSourceContainer = 0x06;
	static const int SCT_clearDataSourceContainer = 0x07;
	static const int SCT_addDataSource = 0x08;

private:
	byte commandType;
	Vector<UnicodeString> wideParameters;
	Vector<String> narrowParameters;

public:
	SuiCommand() : Object() {
		this->commandType = 0;
	}

	SuiCommand(const byte& commandType) : Object() {
		this->commandType = commandType;
	}

	inline byte getCommandType() {
		return commandType;
	}

	void addNarrowParameter(const String& param) {
		narrowParameters.add(param);
	}

	String getNarrowParameter(int index) {
		return narrowParameters.get(index);
	}

	void addWideParameter(const UnicodeString& param) {
		wideParameters.add(param);
	}

	UnicodeString& getWideParameter(int index) {
		return wideParameters.get(index);
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		stream->writeByte(commandType);
		stream->writeInt(wideParameters.size());

		for (int i = 0; i < wideParameters.size(); ++i)
			wideParameters.get(i).toBinaryStream(stream);

		stream->writeInt(narrowParameters.size());

		for (int i = 0; i < narrowParameters.size(); ++i)
			narrowParameters.get(i).toBinaryStream(stream);

		return true;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		commandType = stream->readInt();

		int size = stream->readInt();

		for (int i = 0; i < size; ++i) {
			UnicodeString param;
			param.parseFromBinaryStream(stream);
			wideParameters.add(param);
		}

		size = stream->readInt();

		for (int i = 0; i < size; ++i) {
			String param;
			param.parseFromBinaryStream(stream);
			narrowParameters.add(param);
		}

		return true;
	}
};

#endif /* SUICOMMAND_H_ */
