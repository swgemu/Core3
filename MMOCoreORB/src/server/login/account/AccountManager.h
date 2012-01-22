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
#include "AccountMap.h"

namespace server {
	namespace login {

		class LoginServer;
		class LoginClient;
		class AccountMap;

		namespace account {

			class Account;

			class AccountManager : public Singleton<AccountManager>, public Logger, public Object {
				ManagedReference<LoginServer*> loginServer;

				AccountMap* accountMap;

				String requiredVersion;

				bool autoRegistration;

				uint32 maxOnlineCharacters;

				String dbSecret;

			public:
				AccountManager(LoginServer* loginserv);
				~AccountManager();

				void loginAccount(LoginClient* client, Message* packet);

				Account* validateAccountCredentials(LoginClient* client, const String& username, const String& password);

				Account* createAccount(const String& username, const String& password);

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

				Account* getAccount(uint32 accountID) {
					Locker lock(accountMap);
					return accountMap->get(accountID);
				}

				int addAccount(Account* account) {
					Locker lock(accountMap);
					info("Adding account " + account->getUsername() + " to the accounts map.");

					return accountMap->put(account->getAccountID(), account);
				}

				inline void dropAccount(uint32 accountID) {
					Locker lock(accountMap);
					if (!accountMap->contains(accountID))
						return;

					info("Dropping account " + accountMap->get(accountID)->getUsername() + " to the accounts map.");

					accountMap->drop(accountID);
				}

				inline bool containsAccount(uint32 accountID) {
					Locker lock(accountMap);
					return accountMap->contains(accountID);
				}

				inline int getTotalAccountsOnline() {
					Locker lock(accountMap);
					return accountMap->size();
				}
			};
		}
	}
}

using namespace server::login::account;

#endif /* ACCOUNTMANAGER_H_ */
