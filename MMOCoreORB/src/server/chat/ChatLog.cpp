/*
        Copyright <SWGEmu>
    See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : ChatLog.cpp
 * @created     : Sat Jan 29 16:03:45 UTC 2022
 */

#include "ChatLog.h"

#include "conf/ConfigManager.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/ServerCore.h"

namespace server {
namespace chat {

ChatLogEntry::ChatLogEntry(const String& galaxyName, CreatureObject* sender, const CreatureObject* receiver, const String& chatType, uint32 moodType, const UnicodeString& message) {
	m_TimeStamp.updateToCurrentTime();
	m_GalaxyName = galaxyName;

	if (sender != nullptr) {
		auto zone = sender->getZone();

		m_SenderID = sender->_getObjectID();
		m_SenderName = sender->getFirstName();
		m_WorldPosition = sender->getWorldPosition();
		m_Zone = zone != nullptr ? zone->getZoneName() : "<unknown>";
	} else {
		m_SenderID = 0;
		m_SenderName = "<unknown>";
	}

	if (receiver != nullptr) {
		m_ReceiverID = receiver->_getObjectID();
		m_ReceiverName = receiver->getFirstName();
	} else {
		m_ReceiverID = 0;
		m_ReceiverName = "<unknown>";
	}

	m_ChatType = chatType;
	m_Mood = moodType;
	m_Message = message;
}

ChatLogEntry::ChatLogEntry(const String& galaxyName, CreatureObject* sender, const ChatRoom* room, const UnicodeString& message) {
	m_TimeStamp.updateToCurrentTime();
	m_GalaxyName = galaxyName;

	if (sender != nullptr) {
		auto zone = sender->getZone();

		m_SenderID = sender->_getObjectID();
		m_SenderName = sender->getFirstName();
		m_WorldPosition = sender->getWorldPosition();
		m_Zone = zone != nullptr ? zone->getZoneName() : "<unknown>";
	} else {
		m_SenderID = 0;
		m_SenderName = "<unknown>";
	}

	if (room != nullptr) {
		m_ReceiverID = room->_getObjectID();
		m_ReceiverName = room->getFullPath();
	} else {
		m_ReceiverID = 0;
		m_ReceiverName = "<unknown>";
	}

	m_ChatType = "room";
	m_Mood = 0;
	m_Message = message;
}

String ChatLogEntry::toStringData() const {
	JSONSerializationType json;

	json["@timestamp"] = m_TimeStamp.getFormattedTimeFull().toCharArray();
	json["type"] = "chatLog";
	json["galaxyName"] = m_GalaxyName;
	json["worldX"] = int(m_WorldPosition.getX());
	json["worldY"] = int(m_WorldPosition.getY());
	json["zone"] = m_Zone;
	json["senderName"] = m_SenderName;
	json["senderID"] = m_SenderID;
	json["receiverName"] = m_ReceiverName;
	json["receiverID"] = m_ReceiverID;
	json["mood"] = m_Mood;
	json["chatType"] = m_ChatType;
	json["message"] = m_Message;
	json["queueDelayNs"] = m_QueueDelay;

	return json.dump().c_str();
}

ChatLog::ChatLog() {
	auto zoneServer = ServerCore::getZoneServer();

	galaxyName = zoneServer != nullptr ? zoneServer->getGalaxyName() : "<unknown>";

	auto logLevel = ConfigManager::instance()->getInt("Core3.ChatLog.LogLevel", (int)Logger::DEBUG);

	setLoggingName("ChatLog");

	if (logLevel < Logger::DEBUG) {
		setGlobalLogging(false);
		setFileLogger("log/chat.log", true, ConfigManager::instance()->getRotateLogAtStart());
		setLogLevelToFile(false);
		setLogToConsole(false);
		setRotateLogSizeMB(ConfigManager::instance()->getInt("Core3.ChatLog.RotateLogSizeMB", ConfigManager::instance()->getRotateLogSizeMB()));

		setLoggerCallback([=](Logger::LogLevel level, const char* msg) -> int {
			static Mutex logWriteMutext;
			auto logFile = getFileLogger();

			if (logFile == nullptr) {
				Logger::console.error() << "ChatLog logfile is nullptr!";
				return Logger::DONTLOG;
			}

			StringBuffer logLine;

			logLine << msg << endl;

			Locker guard(&logWriteMutext);
			(*logFile) << logLine;
			logFile->flush();

			return Logger::DONTLOG;
		});
	}

	setLogLevel(static_cast<Logger::LogLevel>(logLevel));

	processQueue();
}

ChatLog::~ChatLog() {
	logMessage("Shutting down");
}

bool ChatLog::isEnabled() {
	static AtomicInteger cachedVersion = 0;
	static bool cachedValue;
	auto currentVersion = ConfigManager::instance()->getConfigVersion();

	if (currentVersion > cachedVersion.get()) {
		Locker guard(&mutex);
		cachedValue = ConfigManager::instance()->getBool("Core3.ChatLog.Enabled", false);
		cachedVersion.set(currentVersion);
		StringBuffer buf;
		buf << "Core3.ChatLog.Enabled=" << cachedValue;
		logMessage(buf.toString());
	}

	return cachedValue;
}

void ChatLog::logMessage(const String& message, int logLevel) {
	if (logLevel > getLogLevel()) {
		return;
	}

	JSONSerializationType json;

	Time now;
	json["@timestamp"] = now.getFormattedTimeFull().toCharArray();
	json["type"] = "logMessage";
	json["level"] = Logger::getLogType(static_cast<Logger::LogLevel>(logLevel));
	json["logMessage"] = message;

	log() << json.dump().c_str();
}

void ChatLog::queueLogEntry(ChatLogEntry* entry) {
	queue.add(entry);
}

void ChatLog::processQueue() {
	while (!queue.isEmpty()) {
		auto entry = queue.remove(0);

		entry->updateQueueDelay();

		log() << *entry;

		delete entry;
	}

	Core::getTaskManager()->scheduleTask([=]{
			processQueue();
	}, "chatLogQueue", 10);
}

void ChatLog::instantMessage(CreatureObject* sender, const CreatureObject* receiver, const UnicodeString& message) {
	if (!isEnabled() || sender == nullptr || receiver == nullptr || message.isEmpty()) {
		return;
	}

	queueLogEntry(new ChatLogEntry(galaxyName, sender, receiver, "im", 0, message));
}

void ChatLog::roomMessage(CreatureObject* sender, const ChatRoom* room, const UnicodeString& message) {
	if (!isEnabled() || sender == nullptr || room == nullptr || message.isEmpty()) {
		return;
	}


	queueLogEntry(new ChatLogEntry(galaxyName, sender, room, message));
}

void ChatLog::spatialMessage(CreatureObject* sender, const CreatureObject* receiver, const String& chatType, uint32 moodType, uint32 chatFlags, const UnicodeString& message) {
	if (!isEnabled() || sender == nullptr || receiver == nullptr || message.isEmpty()) {
		return;
	}

	queueLogEntry(new ChatLogEntry(galaxyName, sender, receiver, chatType, moodType, message));

}

void ChatLog::spatialMessage(CreatureObject* sender, const CreatureObject* receiver, const String& chatType, uint32 moodType, uint32 chatFlags, const StringIdChatParameter& stringIdMessage) {
	if (!isEnabled()) {
		return;
	}

	spatialMessage(sender, receiver, chatType, moodType, chatFlags, UnicodeString(stringIdMessage.toString()));
}

}
}
