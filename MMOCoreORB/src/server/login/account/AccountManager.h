/*
 * AccountManager.h
 *
 *  Created on: Oct 13, 2010
 *      Author: crush
 */

#ifndef ACCOUNTMANAGER_H_
#define ACCOUNTMANAGER_H_

#include "engine/engine.h"

#include "Account.h"

namespace server {
	namespace login {

		class LoginServer;
		class LoginClient;

		namespace account {

			class Account;

			class AccountManager : public Singleton<AccountManager>, public Logger, public Object {
				ManagedReference<LoginServer*> loginServer;

				String requiredVersion;

				bool autoRegistration;

				uint32 maxOnlineCharacters;

				String dbSecret;

			public:
				AccountManager(LoginServer* loginserv);
				~AccountManager();

				void loginAccount(LoginClient* client, Message* packet);

				Account* validateAccountCredentials(LoginClient* client, const String& username, const String& password);

				Account* createAccount(const String& username, const String& password, String& passwordStored);

				void updateHash(const String& username, const String& password);

				//These lookup an account on the mysql database...
				//Account* lookupAccount(uint32 accountID);
				//Account* lookupAccount(uint64 characterID);
				//Account* lookupAccount(const String& username);

				inline void setMaxOnlineCharacters(uint32 maxonline) {
					maxOnlineCharacters = maxonline;
				}

				inline uint32 getMaxOnlineCharacters() {
					return maxOnlineCharacters;
				}

				inline void setRequiredVersion(const String& version) {
					requiredVersion = version;
				}

				inline void setAutoRegistrationEnabled(bool enabled) {
					autoRegistration = enabled;
				}

				inline void setDBSecret(const String& secret) {
					dbSecret = secret;
				}

				inline bool isRequiredVersion(const String& version) {
					if (requiredVersion.isEmpty())
						return true;

					return (requiredVersion == version);
				}

				inline bool isAutoRegistrationEnabled() {
					return autoRegistration;
				}

				Account* getAccount(uint32 accountID);

				Account* getAccount(uint32 accountID, String& passwordStored);

			private:

				Account* getAccount(String query, String& passwordStored);

			};
		}
	}
}

using namespace server::login::account;

#endif /* ACCOUNTMANAGER_H_ */
