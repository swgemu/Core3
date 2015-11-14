/*
 * SuiPageData.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: crush
 */


#include "SuiPageData.h"
#include "SuiCommand.h"
#include "server/zone/ZoneClientSession.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/ui/SuiCreatePageMessage.h"

AtomicInteger SuiPageData::lastId;

void SuiPageData::setProperty(const String& widget, const String& property, const UnicodeString& value) {
	SuiCommand* command = new SuiCommand(SuiCommand::SCT_setProperty);
	command->addWideParameter(value);
	command->addNarrowParameter(widget);
	command->addNarrowParameter(property);

	commands.add(command);
}

void SuiPageData::addDataItem(const String& widget, const String& property, const UnicodeString& value) {
	SuiCommand* command = new SuiCommand(SuiCommand::SCT_addDataItem);
	command->addWideParameter(value);
	command->addNarrowParameter(widget);
	command->addNarrowParameter(property);

	commands.add(command);
}

void SuiPageData::clearDataSource(const String& dataSource) {
	SuiCommand* command = new SuiCommand(SuiCommand::SCT_clearDataSource);
	command->addNarrowParameter(dataSource);

	commands.add(command);
}

void SuiPageData::addDataSourceContainer(const String& parent, const String& name) {
	SuiCommand* command = new SuiCommand(SuiCommand::SCT_addDataSourceContainer);
	command->addNarrowParameter(parent);
	command->addNarrowParameter(name);

	commands.add(command);
}

void SuiPageData::clearDataSourceContainer(const String& dataSourceContainer) {
	SuiCommand* command = new SuiCommand(SuiCommand::SCT_clearDataSourceContainer);
	command->addNarrowParameter(dataSourceContainer);

	commands.add(command);
}

void SuiPageData::addChildWidget(const String& parent, const String& type, const String& name) {
	SuiCommand* command = new SuiCommand(SuiCommand::SCT_addChildWidget);
	command->addNarrowParameter(parent);
	command->addNarrowParameter(type);
	command->addNarrowParameter(name);

	commands.add(command);
}

void SuiPageData::subscribeToEvent(const byte& eventType, const String& parent, const String& callback) {
	if (callbacks.contains(eventType)) {
		warning("SuiPageData::addCommand attempt to add duplicate SCT_subscribeToEvent command.");
		return;
	}

	SuiCommand* command = new SuiCommand(SuiCommand::SCT_subscribeToEvent);
	//command->addNarrowParameter(parent);
	command->addNarrowParameter(String::valueOf(eventType));
	command->addNarrowParameter(callback);

	callbacks.put(eventType, command);
	commands.add(command);
}

void SuiPageData::subscribeToPropertyForEvent(const byte& eventType, const String& widget, const String& property) {
	Reference<SuiCommand*> command = callbacks.get(eventType);

	if (command == NULL) {
		warning("Attempted to add properties for event without subscribing a callback first.");
		return;
	}

	command->addNarrowParameter(widget);
	command->addNarrowParameter(property);
}

bool SuiPageData::toBinaryStream(ObjectOutputStream* stream) {
	stream->writeInt(id);
	rootPage.toBinaryStream(stream);
	stream->writeInt(commands.size());

	for (int i = 0; i < commands.size(); ++i)
		commands.get(i)->toBinaryStream(stream);

	stream->writeLong(targetNetworkId);
	stream->writeFloat(forceCloseDistance);
	stream->writeLong(unknownNetworkId);

	return true;
}

bool SuiPageData::parseFromBinaryStream(ObjectInputStream* stream) {
	id = stream->readInt();
	rootPage.parseFromBinaryStream(stream);

	int size = stream->readInt();

	for (int i = 0; i < size; ++i) {
		SuiCommand* command = new SuiCommand();
		command->parseFromBinaryStream(stream);

		if (command->getCommandType() == SuiCommand::SCT_subscribeToEvent) {
			byte eventType = Integer::valueOf(command->getNarrowParameter(0));
			String callback = command->getNarrowParameter(1);
			printf("parseFromBinaryStream subscribe event, type: %i callback: %s", eventType, callback.toCharArray());
			//callbacks.put(); //TODO: Register subscribes again...
		}

		commands.add(command);
	}

	targetNetworkId = stream->readLong();
	forceCloseDistance = stream->readFloat();
	unknownNetworkId = stream->readLong();

	return true;
}

void SuiPageData::sendTo(CreatureObject* creo) {
	creo->getClient()->sendMessage(new SuiCreatePageMessage(this));
}
