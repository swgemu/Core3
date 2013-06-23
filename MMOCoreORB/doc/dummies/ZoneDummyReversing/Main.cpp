//
//Main.cpp
//(C) SWGEmu 2006
//
//The main part. Where everything is called.
//

#include <cstdio>
#include "CoreServer.h"



int main()
{
    printf("SWGEmu Dummy Zone Server Version ALPHA\n\n");
    int Port;
    bool Protocol;

    //Load the config
    ServerSocket Server;
    Log( LOG_PRINT | LOG_CORE_SERVER, NULL, "Loading Server Configuration...");
    ConfigFile config("conf\\zoneserver.conf");
    config.readInto( Port, "ZonePort" );
    config.readInto( Protocol, "Protocol" );
    Log( LOG_PRINT | LOG_CORE_SERVER, NULL, "Server Config Loaded!");
#ifdef WIN32

    Server.InitSocket(); //Init WSA on windows only.
#endif
    Server.StartServer(Port, Protocol); //The StartServer function. Perameters: (Port, Protocol. 1/0. 1=TCP 0=UDP)
    Server.RecvLoop(Protocol); //The Recv Loop function.

    //If the RecvLoop stops, then close the server:
    Server.CloseSocket();
    return 0;
}


