/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LOGINCLIENT_H_
#define LOGINCLIENT_H_

#include "engine/engine.h"
#include "engine/service/proto/packets/DisconnectMessage.h"

#include "packets/ErrorMessage.h"

namespace server {
namespace login {

	class LoginClient : public Object {
		Reference<BaseClientProxy*> session;
		uint32 accountID = -1;

	public:
		LoginClient(BaseClientProxy* session) : session(session) {
		}

		~LoginClient() {
		}

		void disconnect(bool doLock = true) {
			if (session == nullptr)
				return;

			if (session->isDisconnected())
				return;

			String time;
			Logger::getTime(time);

			Logger::console.log() << time << " [LoginServer] disconnecting client \'" << session->getIPAddress() << "\'\n";

			session->disconnect(doLock);
			accountID = -1;
		}

		String getIPAddress() const {
			if (session == nullptr)
				return "null-session";

			return session->getIPAddress();
		}

		void sendMessage(BasePacket* msg) {
			session->sendPacket(msg);
		}

		void sendErrorMessage(const String& title, const String& text, bool fatal = false, bool sendDisconnect = true) {
			ErrorMessage* errorMessage = new ErrorMessage(title, text, fatal);
			sendMessage(errorMessage);

			constexpr auto disconnectDelay = 500;

			if (sendDisconnect) {
				Core::getTaskManager()->scheduleTask([session = WeakReference<BaseClientProxy*>(this->session)] {
					auto strongRef = session.get();

					if (strongRef) {
						strongRef->disconnect();
					}
				}, "disconnectErrorTask", disconnectDelay);
			}
		}

		void info(const String& msg, bool doLog = true) const {
			session->info(msg, doLog);
		}

		auto error() const {
			return session->error();
		}

		auto info(bool val) const {
			return session->info(val);
		}

		auto warning() const {
			return session->warning();
		}

		auto debug() const {
			return session->debug();
		}

		ServiceClient* getSession() {
			return session;
		}

		const ServiceClient* getSession() const {
			return session;
		}

		uint32 getAccountID() const {
			return accountID;
		}

		void setAccountID(uint32 account) {
			LoginClient::accountID = account;
		}

		bool hasAccount() const {
			return (accountID != -1);
		}
	};

  } // namespace login
} // namespace server

using namespace server::login;

#endif /*LOGINCLIENT_H_*/
