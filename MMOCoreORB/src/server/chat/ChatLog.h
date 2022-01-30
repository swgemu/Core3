/*
        Copyright <SWGEmu>
    See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : ChatLog.h
 * @created     : Sat Jan 29 16:03:45 UTC 2022
 */

#pragma once

#include "engine/engine.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/chat/room/ChatRoom.h"

namespace server {
 namespace chat {
	class ChatLogEntry {
		Time m_TimeStamp;
		uint64 m_QueueDelay;
		String m_GalaxyName;
		String m_SenderName;
		uint64 m_SenderID;
		String m_ReceiverName;
		uint64 m_ReceiverID;
		String m_ChatType;
		uint32 m_Mood;
		UnicodeString m_Message;
		Vector3 m_WorldPosition;
		String m_Zone;
	public:
		ChatLogEntry(const String& galaxyName, CreatureObject* sender, const CreatureObject* receiver, const String& chatType, uint32 moodType, const UnicodeString& message);

		ChatLogEntry(const String& galaxyName, CreatureObject* sender, const ChatRoom* room, const UnicodeString& message);

		String toStringData() const;

		void updateQueueDelay() {
			Time now;
			m_QueueDelay = now.getNanoTime() - m_TimeStamp.getNanoTime();
		};

		friend class ChatLog;
	};

	class ChatLog : public Singleton<ChatLog>, public Object, public Logger {
		Mutex mutex;

		String galaxyName;

		SynchronizedVector<ChatLogEntry*>queue;

		void queueLogEntry(ChatLogEntry* entry);

		bool isEnabled();

		void logMessage(const String& message, int logLevel = Logger::INFO);

		void processQueue();

	public:
		ChatLog();
		~ChatLog();

		void instantMessage(CreatureObject* sender, const CreatureObject* receiver, const UnicodeString& message);

		void roomMessage(CreatureObject* sender, const ChatRoom* room, const UnicodeString& message);

		void spatialMessage(CreatureObject* sender, const CreatureObject* receiver, const String& chatType, uint32 moodType, uint32 chatFlags, const UnicodeString& message);

		void spatialMessage(CreatureObject* sender, const CreatureObject* receiver, const String& chatType, uint32 moodType, uint32 chatFlags, const StringIdChatParameter& stringIdMessage);
	};
 }
}
