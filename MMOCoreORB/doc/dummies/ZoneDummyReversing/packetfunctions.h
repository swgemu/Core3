#ifndef PACKET_FUNCTIONS_H
#define PACKET_FUNCTIONS_H
#include <string>

class ServerSocket;

struct cSpawn {
    bool initalized;
    int x;
    int y;
    int z;
    std::string location;
};

void rawload(ServerSocket *Server, char *filename);

//RECV HANDLERS
void recv_session_key(ServerSocket *Server);
void recv_charID(ServerSocket *Server, cSpawn spawn);
void recv_load_done(ServerSocket *Server);
void recv_chat(ServerSocket *Server, char *pData, unsigned short nLength);
void recv_cmd_sit(ServerSocket *Server);
void recv_cmd_stand(ServerSocket *Server);
void recv_cmd_prone(ServerSocket *Server);
void recv_cmd_kneel(ServerSocket *Server);
void recv_emote(ServerSocket *Server, char *pData);
void recv_pos(ServerSocket *Server, float x, float z, float y, signed short dir);
void recv_attack(ServerSocket *Server, char *pData);
void recv_peace(ServerSocket *Server, char *pData);
void recv_tell(ServerSocket *Server, char *pData);
void recv_burstrun(ServerSocket *Server, char *pData);
void recv_unknown(ServerSocket *Server, char *pData);



//SOE_FUNCTIONS
void ping_reply(ServerSocket *Server);
void send_netstat(ServerSocket *Server,unsigned short tick);
void send_sesresp(ServerSocket *Server);
void send_ack(ServerSocket *Server,unsigned short sequence);
void send_ack_ok(ServerSocket *Server,unsigned short sequence);
void send_disconnect(ServerSocket *Server);


//CLIENT_SERVER_FUNCTIONS
void recv_char_iff(ServerSocket *Server,char *pData,unsigned short nLength);
void send_validate_char_name(ServerSocket *Server, char *char_iff, unsigned short iff_size, char *name, unsigned short namesize);
void send_approve_char_name(ServerSocket *Server,char *iff,unsigned short size);
void send_loot_open(ServerSocket *Server);
void send_loot_pearl(ServerSocket *Server);
void send_radial_confirm(ServerSocket *Server, char* pData,unsigned short nLength);
void send_assign_char_id(ServerSocket *Server);
void send_OK_packet(ServerSocket *Server);
void send_hardcode_pkt(ServerSocket *Server,char *pkt,unsigned short size,bool comp = true);

void send_craft(ServerSocket *Server);
void send_craft_stage1(ServerSocket *Server);
void send_craft_updateschems(ServerSocket *Server);
void send_insert_resource(ServerSocket *Server, unsigned long long *resId, unsigned int *slot, unsigned char* scount);
void send_insert_updateres(ServerSocket *Server);


void send_craft_assemble(ServerSocket *Server);
void send_craft_experiment(ServerSocket *Server);

void send_craft_createobj(ServerSocket *Server);
void send_craft_finish(ServerSocket *Server);
void send_craft_updatetooltime(ServerSocket *Server);
void send_craft_finish2(ServerSocket *Server);

#endif
