/*
 * WebCredentials.h
 *
 *  Created on: May 31, 2011
 *      Author: kyle
 */

#ifndef WEBCREDENTIALS_H_
#define WEBCREDENTIALS_H_

class WebCredentials {
private:
	String userName;
	Vector<String> addresses;

public:
	WebCredentials(String user, String ip) {
		userName = user;
		addresses.add(ip);
	}

	~WebCredentials() {

	}

	void addInetAddress(String ip) {
		addresses.add(ip);
	}

	bool contains(String ip) {

		for(int i = 0; i < addresses.size(); ++i) {
			if(addresses.get(i) == ip)
				return true;
		}

		return false;
	}
};

#endif //WEBCREDENTIALS_H_
