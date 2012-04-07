/*
Copyright (C) 2007 <SWGEmu>
 
This File is part of Core3.
 
This program is free software; you can redistribute 
it and/or modify it under the terms of the GNU Lesser 
General Public License as published by the Free Software
Foundation; either version 2 of the License, 
or (at your option) any later version.
 
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for
more details.
 
You should have received a copy of the GNU Lesser General 
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
Linking Engine3 statically or dynamically with other modules 
is making a combined work based on Engine3. 
Thus, the terms and conditions of the GNU Lesser General Public License 
cover the whole combination.
 
In addition, as a special exception, the copyright holders of Engine3 
give you permission to combine Engine3 program with free software 
programs or libraries that are released under the GNU LGPL and with 
code included in the standard release of Core3 under the GNU LGPL 
license (or modified versions of such code, with unchanged license). 
You may copy and distribute such a system following the terms of the 
GNU LGPL for Engine3 and the licenses of the other code concerned, 
provided that you include the source code of that other code when 
and as the GNU LGPL requires distribution of source code.
 
Note that people who make modified versions of Engine3 are not obligated 
to grant this special exception for their modified versions; 
it is their choice whether to do so. The GNU Lesser General Public License 
gives permission to release a modified version without this exception; 
this exception also makes it possible to release a modified version 
which carries forward this exception.
*/

#ifndef LOGINCLIENT_H_
#define LOGINCLIENT_H_

#include "engine/engine.h"

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
			if (session == NULL)
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

		void sendMessage(Message* msg) {
			session->sendPacket(cast<BasePacket*>(msg));
		}
	
		void sendErrorMessage(const String& title, const String& text, bool fatal = false) {
			ErrorMessage* errorMessage = new ErrorMessage(title, text, fatal);

			sendMessage(errorMessage);
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
