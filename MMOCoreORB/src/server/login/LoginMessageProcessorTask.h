/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LOGINMESSAGEPROCESSORTASK_H_
#define LOGINMESSAGEPROCESSORTASK_H_

#include "LoginPacketHandler.h"

namespace server {
	namespace login {

		class LoginMessageProcessorTask : public Task {
			Reference<Message*> message;

			LoginPacketHandler* packetHandler;

		public:
			LoginMessageProcessorTask(Message* msg, LoginPacketHandler* handler) {
				message = msg;

				packetHandler = handler;
			}

			~LoginMessageProcessorTask() {
			}

			void run() {
				static Logger logger("LoginMessageProcessorTask", Logger::INFO);

				try {
					message->reset();

					packetHandler->handleMessage(message);
				} catch (const PacketIndexOutOfBoundsException& e) {
					logger.error() << e.getMessage();

					logger.debug() << "incorrect packet - " << *message;
				} catch (const Exception& e) {
					logger.error() << e.getMessage();

					logger.debug() << "incorrect packet - " << *message;
				}
			}

		};

	} // namespace login
} // namespace server

using namespace server::login;

#endif /*LOGINMESSAGEPROCESSORTASK_H_*/
