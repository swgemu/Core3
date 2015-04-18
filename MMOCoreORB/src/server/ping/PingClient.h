/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PINGCLIENT_H_
#define PINGCLIENT_H_

#include "engine/engine.h"

class PingClient : public BaseClientProxy {
public:
	PingClient(DatagramServiceThread* serv, Socket* sock, SocketAddress& addr) : BaseClientProxy(sock, addr) {
		setLoggingName("PingClient " + ip);
		setLogging(false);

		init(serv);
	}

	virtual ~PingClient() {
	}

	void disconnect(bool doLock = true) {
		if (isDisconnected())
			return;

		String time;
		Logger::getTime(time);

		StringBuffer msg;
		msg << time << " [PingServer] disconnecting client \'" << ip << "\'\n";
		Logger::console.log(msg);

		BaseClientProxy::disconnect(doLock);
	}

	void sendMessage(Message* msg) {
		BaseClientProxy::sendPacket(cast<BasePacket*>(msg));
	}
};

#endif /* PINGCLIENT_H_ */
