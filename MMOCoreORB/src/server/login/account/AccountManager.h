/*
 * AccountManager.h
 *
 *  Created on: Oct 13, 2010
 *      Author: crush
 */

#ifndef ACCOUNTMANAGER_H_
#define ACCOUNTMANAGER_H_

#include "server/login/account/Account.h"

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

				bool enableSessionId;

				uint32 maxOnlineCharacters;

				String dbSecret;

				static ReadWriteLock mutex;

			public:
				AccountManager(LoginServer* loginserv);
				~AccountManager();

				void loginAccount(LoginClient* client, Message* packet);

				bool loginFinalize(LoginClient* client, ManagedReference<Account*> account);

#ifdef WITH_SWGREALMS_API
				void loginApprovedAccount(LoginClient* client, ManagedReference<Account*> account);
#else // !WITH_SWGREALMS_API
				Reference<Account*> validateAccountCredentials(LoginClient* client, const String& username, const String& password);

				// SWG Remastered: delegate auth to the external ticket service. The
				// password field carries a launcher-minted ticket; the service returns
				// the AUTHORITATIVE station_id, which anchors the account.
				Reference<Account*> validateExternalAuth(LoginClient* client, const String& username, const String& ticket);

				// Find-or-create the local account keyed on the authoritative station_id
				// (never System::random), so re-login always maps to the same account
				// and characters are never orphaned.
				Reference<Account*> getOrCreateAccountByStationId(uint32 stationId, const String& username);

				Reference<Account*> createAccount(const String& username, const String& password, String& passwordStored);

				void updateHash(const String& username, const String& password);
#endif // WITH_SWGREALMS_API

				//These lookup an account on the mysql database...
				//Account* lookupAccount(uint32 accountID);
				//Account* lookupAccount(uint64 characterID);
				//Account* lookupAccount(const String& username);

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

#ifndef WITH_SWGREALMS_API
				static void expireSession(Reference<Account*> account, const String& sessionID);
#endif

				static Reference<Account*> getAccount(uint32 accountID, bool forceSqlUpdate = false);

				static Reference<Account*> getAccount(const String& accountName, bool forceSqlUpdate = false);

#ifndef WITH_SWGREALMS_API
				static Reference<Account*> getAccount(uint32 accountID, String& passwordStored, bool forceSqlUpdate = false);

			private:
				static Reference<Account*> getAccount(String query, String& passwordStored, bool forceSqlUpdate = false);
#endif // !WITH_SWGREALMS_API
			};
		}
	}
}

using namespace server::login::account;

#endif /* ACCOUNTMANAGER_H_ */
