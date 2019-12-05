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
		uint32 accountID;

	public:
		LoginClient(BaseClientProxy* session) {
			LoginClient::session = session;
			accountID = -1;
		}

		virtual ~LoginClient() {
		}
		
		void disconnect(bool doLock = true) {
			if (session == nullptr)
				return;

			if (session->isDisconnected())
				return;
	
			String time;
			Logger::getTime(time);
	
			StringBuffer msg;
			msg << time << " [LoginServer] disconnecting client \'" << session->getIPAddress() << "\'\n";
			Logger::console.log(msg);

			session->disconnect(doLock);
			accountID = -1;
		}

		String getIPAddress() const {
			if (session == nullptr)
				return "null-session";

			return session->getIPAddress();
		}

		void sendMessage(Message* msg) {
			session->sendPacket(cast<BasePacket*>(msg));
		}
	
		void sendErrorMessage(const String& title, const String& text, bool fatal = false, bool sendDisconnect = true) {
			ErrorMessage* errorMessage = new ErrorMessage(title, text, fatal);

			sendMessage(errorMessage);

			if (sendDisconnect) {
				session->sendPacket(new DisconnectMessage(session));
			}
		}

		void info(const String& msg, bool doLog = true) {
			session->info(msg, doLog);
		}

		ServiceClient* getSession() {
			return session;
		}

		uint32 getAccountID() {
			return accountID;
		}

		void setAccountID(uint32 account) {
			LoginClient::accountID = account;
		}

		bool hasAccount() {
			return (accountID != -1);
		}
	};

  } // namespace login
} // namespace server

using namespace server::login;

#endif /*LOGINCLIENT_H_*/
