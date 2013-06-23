#include "packetfunctions.h"
#include "packets.h"
#include "CoreServer.h"
#include <string.h>
#include "log.h"
#include "math.h"
#include <fstream>
#include <sys/stat.h>

#include <iostream>

extern client_object oclient;
extern cSpawn spawny;

void send_dynamic_pkt(ServerSocket *Server,char *filename,bool comp);

void rawload(ServerSocket *Server, char *filename)
{
struct stat results;

    if (stat(filename, &results) == 0) {
    //cout << "Packet Size: " << results.st_size << "\n";
    char buffer[results.st_size];
    std::ifstream pFile (filename, std::ios::in | std::ios::binary);
    pFile.read (buffer, results.st_size);
    
    //hex_print(buffer, sizeof(buffer));
    
    bool comp = false;
    if(results.st_size > 149) { comp = true; }; // it think thats the compress size?
    send_hardcode_pkt(Server, buffer, results.st_size, comp);
}
else { 
Log( LOG_PRINT | LOG_CORE_SERVER, NULL, "An error occured when trying to open/read teh raw packet\n");
}

}


//RECV HANDLERS//////////////////////////////////////////////////////////////////

void recv_session_key(ServerSocket *Server)
{
 send_hardcode_pkt(Server,char_options,sizeof(char_options),false);
}

void recv_charID(ServerSocket *Server, cSpawn spawn)
{
 float f;
 send_OK_packet(Server);
 send_hardcode_pkt(Server,unkbyteflag,sizeof(unkbyteflag),false);
 send_hardcode_pkt(Server,unkint900,sizeof(unkint900),false);
 //send_hardcode_pkt(Server,new_mail_notice,sizeof(new_mail_notice),false);
 //send_hardcode_pkt(Server,mail_pkt,sizeof(mail_pkt),true);


 int diff = spawn.location.length() - 8;
 char *pCustomTerrain = new char[sizeof(load_terrain_pkt)+diff];
 memcpy(pCustomTerrain,load_terrain_pkt,39);
 memcpy(pCustomTerrain+32,spawn.location.c_str(),spawn.location.length());
 memcpy(pCustomTerrain+40+diff,load_terrain_pkt+40,sizeof(load_terrain_pkt)-40);
 //*(unsigned short*)(pCustomTerrain+6) = *(unsigned short*)(pCustomTerrain+6) + diff;
 *(unsigned short*)(pCustomTerrain+22) = *(unsigned short*)(pCustomTerrain+22) + diff;
 //Server->hex_print(pCustomTerrain,sizeof(load_terrain_pkt)+diff);
 send_hardcode_pkt(Server,pCustomTerrain,sizeof(load_terrain_pkt)+diff,true);

// send_hardcode_pkt(Server,abilities_list_tmr,sizeof(abilities_list_tmr),false);
send_hardcode_pkt(Server,create_gild_obj,sizeof(create_gild_obj),false);
 send_hardcode_pkt(Server,gild_obj_type3,sizeof(gild_obj_type3),true);
 send_hardcode_pkt(Server,gild_obj_type6_close,sizeof(gild_obj_type6_close),false);

 f = (float)spawn.x;
 memcpy(player_creo_create+34,&f,4);
 f = (float)spawn.y;
 memcpy(player_creo_create+42,&f,4);
 f = (float)spawn.z;
 memcpy(player_creo_create+38,&f,4);

 //OUR SECOND PLAYER
 send_hardcode_pkt(Server,player_creo_create2,sizeof(player_creo_create2),false);
 send_hardcode_pkt(Server,creo_update_type32,sizeof(creo_update_type32),true);
 send_hardcode_pkt(Server,creo_update_type62,sizeof(creo_update_type62),true);
 send_hardcode_pkt(Server,creo_close2,sizeof(creo_close2),true);
 



 send_hardcode_pkt(Server,player_creo_create,sizeof(player_creo_create),false);
 send_hardcode_pkt(Server,creo_update_type1,sizeof(creo_update_type1),true);
 send_hardcode_pkt(Server,creo_update_type3,sizeof(creo_update_type3),true);
 send_hardcode_pkt(Server,creo_update_type4,sizeof(creo_update_type4),true);
 send_hardcode_pkt(Server,creo_update_type6,sizeof(creo_update_type6),true);
 send_hardcode_pkt(Server,creo_8_9_and_crt_play_lnk_play_creo_play_3_6,sizeof(creo_8_9_and_crt_play_lnk_play_creo_play_3_6),true);
 send_hardcode_pkt(Server,play_update_type8,sizeof(play_update_type8),true);
 send_hardcode_pkt(Server,play_update_type9,sizeof(play_update_type9),true);
 send_hardcode_pkt(Server,play_cls_hair_all,sizeof(play_cls_hair_all),true);
 //send_hardcode_pkt(Server,weao_unk_all,sizeof(weao_unk_all),true);
 send_hardcode_pkt(Server,tano_bank_all,sizeof(tano_bank_all),true);
 send_hardcode_pkt(Server,tano_datapad_all,sizeof(tano_datapad_all),true);
 send_hardcode_pkt(Server,tano_mission_bag_all,sizeof(tano_mission_bag_all),true);
 send_hardcode_pkt(Server,tano_inventory_start,sizeof(tano_inventory_start),true);
 send_hardcode_pkt(Server,tano_shirt_all,sizeof(tano_shirt_all),true);
 send_hardcode_pkt(Server,tano_pants_all,sizeof(tano_pants_all),true);
 send_hardcode_pkt(Server,tano_shoes_all,sizeof(tano_shoes_all),true);
 send_hardcode_pkt(Server,tano_vest_all,sizeof(tano_vest_all),true);
 send_hardcode_pkt(Server,tano_crafttool_all,sizeof(tano_crafttool_all),true);
 send_hardcode_pkt(Server,tano_mellon_all_close,sizeof(tano_mellon_all_close),true);
 send_hardcode_pkt(Server,creo_close,sizeof(creo_close),true);

 send_hardcode_pkt(Server,player_schematics,sizeof(player_schematics),true);
 send_hardcode_pkt(Server,resource_spawn,sizeof(resource_spawn),true);
 send_hardcode_pkt(Server,resource_spawn2,sizeof(resource_spawn2),true);
 send_hardcode_pkt(Server,resource_spawn3,sizeof(resource_spawn3),true);
 send_hardcode_pkt(Server,resource_attributes,sizeof(resource_attributes),true);
 send_hardcode_pkt(Server,resource_attributes2,sizeof(resource_attributes2),true);
 send_hardcode_pkt(Server,resource_attributes3,sizeof(resource_attributes3),true);

 send_hardcode_pkt(Server,craft_finish2,sizeof(craft_finish2),true);
 send_hardcode_pkt(Server,inv_pwrhandler,sizeof(inv_pwrhandler),true);

// send_hardcode_pkt(Server,spawnswoop,sizeof(spawnswoop),true);
 //send_hardcode_pkt(Server,mountswoop,sizeof(mountswoop),true);
 //send_hardcode_pkt(Server,mountswoop2,sizeof(mountswoop2),true);




 send_hardcode_pkt(Server,mob_create_new,sizeof(mob_create_new),false);
 send_hardcode_pkt(Server,mob_creo3_new,sizeof(mob_creo3_new),true);
 send_hardcode_pkt(Server,mob_creo6_new,sizeof(mob_creo6_new),true);
 send_hardcode_pkt(Server,mob_preclose,sizeof(mob_preclose),false);
 send_hardcode_pkt(Server,mob_close,sizeof(mob_close),false);

// send_hardcode_pkt(Server,addswooptodatapad,sizeof(addswooptodatapad),true);

 send_hardcode_pkt(Server,player1_test,sizeof(player1_test),true);
 send_hardcode_pkt(Server,player2_test,sizeof(player2_test),true);
 send_hardcode_pkt(Server,mob_test,sizeof(mob_test),true);

 send_hardcode_pkt(Server,house2,sizeof(house2),true);
 send_hardcode_pkt(Server,house2_2,sizeof(house2_2),true);

 send_hardcode_pkt(Server,station_spawn,sizeof(station_spawn),true);

 //send_hardcode_pkt(Server,house22,sizeof(house2),true);
 //send_hardcode_pkt(Server,house2_22,sizeof(house2_2),true);
 
}

void recv_load_done(ServerSocket *Server)
{
 send_hardcode_pkt(Server,load_done_return,sizeof(load_done_return),true);
}

void recv_pos(ServerSocket *Server, float x, float z, float y, signed short dir)
{
 signed short a,b,c;
 a = (int)(x*4);
 b = (int)(y*4);
 c = (int)(z * 4);
 printf("movement x:%f z:%f y:%f a:%i c:%i b:%i\n",x,z,y,a,c,b);

 memcpy(mob_pos+18,&a,2);
 memcpy(mob_pos+20,&c,2);
 memcpy(mob_pos+22,&b,2);
 a = *(unsigned short*)(mob_pos+24)+1; //count
 b = 0; //no idea
 //dir = dir; / 4; //I DONT FUCKING KNOW =)
 printf("count:%i unk:%i dir:%i\n",a,b,dir);
 memcpy(mob_pos+24,&a,2);

 memcpy(mob_pos+26,&b,2);
 memcpy(mob_pos+29,&dir,1);
 //Server->hex_print(mob_pos,sizeof(mob_pos));
 send_hardcode_pkt(Server,mob_pos,sizeof(mob_pos),false);


}



void send_text(ServerSocket *Server, wchar_t *pData, unsigned short nLength)
{

 char *pChatReply = new char [sizeof(player_chat_response_head) + sizeof(player_chat_response_foot) + nLength];
 memcpy(pChatReply, player_chat_response_head, sizeof(player_chat_response_head));
 *(unsigned short*)(pChatReply+46) = nLength/2;
 memcpy(pChatReply+50, pData, nLength);
 memcpy(pChatReply+50+nLength, player_chat_response_foot, sizeof(player_chat_response_foot));
 send_hardcode_pkt(Server,pChatReply,sizeof(player_chat_response_head) + sizeof(player_chat_response_foot) + nLength,true);
 delete [] pChatReply;

}

int startmove = 0;

void recv_chat(ServerSocket *Server, char *pData, unsigned short nLength)
{
 send_OK_packet(Server);
 int offset;
 if ((nLength % 2) == 0) offset = 70; else offset = 69;
 unsigned short textsize = nLength - offset;
 if ((textsize > 1) && (textsize < 513)) {
   //Server->hex_print(pData,nLength);

   wchar_t *U_text = new wchar_t[(textsize/2)+1];
   memcpy(U_text, pData+66, textsize);
   //printf("str[%i]:%s\n",textsize,U_text);
   send_text(Server,U_text,textsize);

   //admin command checking crap:
  char *A_text = new char[(textsize/2)];

  for(int i=0; i < (textsize/2); i++)  A_text[i] = U_text[i];

  A_text[(textsize/2)] = char(0x00);

  if (strncmp(A_text,"@",1) == 0) {
    int cmd_size = 5;
    int max_cmds = 28;
    static char cmd_list[][7] = { "@disc","@relo","@npcc","@warp","@zone","@test","@load", "@file", "@t2", "@t3", "@t4", "@t5", "@t6", "@t7", "@t8", "@t9", "@t10", "@t11", "@t12", "@t13", "@t14", "@t15", "@t16", "@t17", "@t18", "@t19", "@t20","@t21"};
    int c = 255;
    for (int n=0;n<max_cmds;n++)
      if (strncmp(cmd_list[n],A_text,cmd_size) == 0)
      {
          c = n;
          n = max_cmds;
      }

    string str_command(A_text);
    printf("str[%i]:%s\n",str_command.length(),str_command.c_str());
    int x;
    int y;
    int z;
    
    char *file;

    switch(c) {
      case 0 :
        printf("disconnect requested\n");
        send_disconnect(Server);
        break;
      case 1 :
        printf("reload requested\n");
        recv_charID(Server,spawny);
        break;
      case 2 :
        printf("npc chatting requested\n");
       // send_hardcode_pkt(Server, npc_nub_chat, sizeof(npc_nub_chat), true);
       // send_hardcode_pkt(Server,player_stand_update,sizeof(player_stand_update),true);
       // send_hardcode_pkt(Server,player_stand_update2,sizeof(player_stand_update2),true);
       // send_hardcode_pkt(Server,player_stand_update3,sizeof(player_stand_update3),true);
       //send_hardcode_pkt(Server, weao_update1, sizeof(weao_update1), true);
       send_hardcode_pkt(Server, statechange, sizeof(statechange), true);
      // send_hardcode_pkt(Server, equip2, sizeof(equip2), true);
       //send_hardcode_pkt(Server, spawnswoop2, sizeof(spawnswoop2), true);
        break;
      case 3 :
        x = str_command.find(" ",0);
        y = str_command.find(" ",x+1);
        z = str_command.length();
        if ((x && y) > 0) {
          x = atoi(str_command.substr(x+1,y-x).c_str());
          y = atoi(str_command.substr(y+1,z-y).c_str());
          printf("warping to %i,%i\n",x,y);
          spawny.x = x;
          spawny.y = y;
          recv_charID(Server,spawny);
        }
        break;
      case 4 :
        printf("changing planets...\n");
        x = str_command.find(" ",0);
        y = str_command.length();
        if ((x && y) > 0) {
            printf("x:%i y:%i s:%s\n",x,y,str_command.c_str());
            str_command = str_command.substr(x+1,y-x);
            strcpy(A_text,str_command.c_str());
            char option[5] = "list";
            if (strncmp(A_text,option,4) == 0) {
              wchar_t list[195] = L"creature_test rivertest otoh_gunga godclient_test\ntaanab endor_asommers dungeon1 10 09 11\ncinco_city_test_m5 test_wearables\nrori yavin4 dantooine lok\ntalus endor tatooine\ndathomir corellia naboo";
              send_text(Server,list,194*2);
            } else {
              printf("respawning to %s[%i]\n",str_command.c_str(),str_command.length());
              str_command = str_command.c_str();
              spawny.location = str_command;
              recv_charID(Server,spawny);
            }
        }
        break;
      case 5 :
      send_hardcode_pkt(Server, finalanimation3, sizeof(finalanimation3), true);
      
      break;
      
      case 6:
      A_text+=6;
      rawload(Server, A_text);
      break;
      case 7: //t1
            printf("file command\n");
            x = str_command.find(" ",0);
            str_command = str_command.substr(x+1,str_command.length());
            strcpy(A_text,str_command.c_str());
            
           //send_hardcode_pkt(Server, giveexp, sizeof(test1_combatanimation), true);
           send_dynamic_pkt(Server,A_text,false);
           break;
      case 8: //t2
           //send_hardcode_pkt(Server,spawnhouse,sizeof(spawnhouse),true);

           send_hardcode_pkt(Server,mountswoop,sizeof(mountswoop),true);
           break;
      case 9:
           send_hardcode_pkt(Server,mountswoop2,sizeof(mountswoop2),true);
           //send_hardcode_pkt(Server, test3_UpdateTarget, sizeof(test3_UpdateTarget), true);//3
           break;
      case 10: //t4
           /*send_hardcode_pkt(Server,loot_inventory_start,sizeof(loot_inventory_start),true);
           send_hardcode_pkt(Server,loot_inventory_finish,sizeof(loot_inventory_finish),true);*/
           send_hardcode_pkt(Server,loot_mellon,sizeof(loot_mellon),true);

           /*send_hardcode_pkt(Server,craft1,sizeof(craft1),true);
           send_hardcode_pkt(Server,craft2,sizeof(craft2),true);
           send_hardcode_pkt(Server,craft3,sizeof(craft3),true);
           send_hardcode_pkt(Server,craft4,sizeof(craft4),true);*/

           break;
      case 11: //t5
           send_hardcode_pkt(Server,craft2_add_resource4,sizeof(craft2_add_resource4),true);
           send_hardcode_pkt(Server,craft2_add_resource5,sizeof(craft2_add_resource5),true);

           //send_hardcode_pkt(Server, test4_LinkDead, sizeof(test4_LinkDead), true);
           break;
     case 12: //t6
           send_hardcode_pkt(Server,vendortestlistitems1,sizeof(vendortestlistitems1),true);
           send_hardcode_pkt(Server,vendortestlistitems2,sizeof(vendortestlistitems2),true);

           /*send_hardcode_pkt(Server,craft_add_resource2_1,sizeof(craft_add_resource2_1),true);
           send_hardcode_pkt(Server,craft_add_resource2_2,sizeof(craft_add_resource2_2),true);
           send_hardcode_pkt(Server,craft_add_resource_3,sizeof(craft_add_resource_3),true);
           send_hardcode_pkt(Server,craft_add_resource_4,sizeof(craft_add_resource_4),true);
           send_hardcode_pkt(Server,craft_add_resource_5,sizeof(craft_add_resource_5),true);
           send_hardcode_pkt(Server,craft_add_resource_6,sizeof(craft_add_resource_6),true);*/

           //send_hardcode_pkt(Server,craft_create_ingreedients1,sizeof(craft_create_ingreedients1),true);
           /*send_hardcode_pkt(Server,house22,sizeof(house22),true);
           send_hardcode_pkt(Server,house2_22,sizeof(house2_22),true);*/

           //send_hardcode_pkt(Server, test5_SpawnTravelTerminal, sizeof(test5_SpawnTravelTerminal), true);
           break;
      case 13: //t7
           send_hardcode_pkt(Server,craft2_create_ingreedients2,sizeof(craft2_create_ingreedients2),true);

           /*send_hardcode_pkt(Server,craft14,sizeof(craft14),true);
           send_hardcode_pkt(Server,craft15,sizeof(craft15),true);
           send_hardcode_pkt(Server,craft16,sizeof(craft16),true);*/

           //send_hardcode_pkt(Server, test6_CreateMission, sizeof(test6_CreateMission), true);
           break;
      case 14: // t8
           /*if (startmove == 1) startmove = -1;
           else if (startmove == -1) startmove = 1;
           else startmove = 1;*/
           break;
      case 15: // t9
           startmove = 0;
           //send_hardcode_pkt(Server, test_unknown1, sizeof(test_unknown1), true);//9
           break;
      case 16:
           send_hardcode_pkt(Server, test_unknown2, sizeof(test_unknown2), true);//10
           break;
      case 17:
           send_hardcode_pkt(Server, test_unknown3, sizeof(test_unknown3), true);//11
           break;
      case 18:
           send_hardcode_pkt(Server, test_unknown4, sizeof(test_unknown4), true);//12
           break;
      case 19:
           send_hardcode_pkt(Server, test_unknown5, sizeof(test_unknown5), true);//13
           break;
      case 20:
           send_hardcode_pkt(Server, test_unknown6, sizeof(test_unknown6), true);//14
           break;
      case 21:
           send_hardcode_pkt(Server, test_unknown7, sizeof(test_unknown7), true);//15
           break;
            case 22:
           send_hardcode_pkt(Server, test_unknown8, sizeof(test_unknown8), true);//16
           break;
      case 23:
           send_hardcode_pkt(Server, test_unknown9, sizeof(test_unknown9), true);//17
           break;
      case 24:
           send_hardcode_pkt(Server, test_unknown10, sizeof(test_unknown10), true);//18
           break;
      case 25:
           send_hardcode_pkt(Server, test_unknown11, sizeof(test_unknown11), true);//19
           break;
      case 26:
           send_hardcode_pkt(Server, colortool, sizeof(colortool), true);
           break;
      case 27:
           send_hardcode_pkt(Server, test3_UpdateTarget3, sizeof(test3_UpdateTarget3), true);
           break;
           
      
     }
    }
  } else printf("skipped due to textxsize of %i\n",textsize);
};

void recv_emote(ServerSocket *Server, char *pData)
{
 send_OK_packet(Server);
 //Server->hex_print(pData,60);
 unsigned short emote_type_size = *(char*)(pData+42);
 string emote_type(emote_type_size+1,0x0);
 for(int x=0;x<=emote_type_size;++x) {
     emote_type[x] = *(char*)(pData+(46+(x*2)));
 }
 //printf("emote: %i %s\n",emote_type_size,emote_type.c_str());

 int x = emote_type.find(" ",0);
 int y = emote_type.find(" ",x+1);
 emote_type = emote_type.substr(x,y-x);
 char s_emote_type[255];
 strcpy(s_emote_type,emote_type.c_str());

 char *pEmoteReply = new char [sizeof(player_emote_base)];
 memcpy(pEmoteReply, player_emote_base, sizeof(player_emote_base));


 *(unsigned short*)(pEmoteReply+46) = atoi(s_emote_type);

 send_hardcode_pkt(Server,pEmoteReply,sizeof(player_emote_base),true);
 Server->hex_print(pEmoteReply,sizeof(player_emote_base));
 delete [] pEmoteReply;
};

void recv_cmd_sit(ServerSocket *Server)
{       
//send_hardcode_pkt(Server,player_sit_update,sizeof(player_sit_update),true);
send_hardcode_pkt(Server,statechange,sizeof(statechange),true);
send_hardcode_pkt(Server,sit_chair,sizeof(sit_chair),true);


 send_OK_packet(Server);
}

void recv_cmd_stand(ServerSocket *Server)
{
 //send_hardcode_pkt(Server,player_stand_update,sizeof(player_stand_update),true);
 send_OK_packet(Server);
}



void recv_cmd_prone(ServerSocket *Server)
{
 send_hardcode_pkt(Server,player_prone_update,sizeof(player_prone_update),true);
 send_OK_packet(Server);
}
void recv_cmd_kneel(ServerSocket *Server)
{
 send_hardcode_pkt(Server,player_kneel_update,sizeof(player_kneel_update),true);
 send_OK_packet(Server);
};

void recv_attack(ServerSocket *Server, char *pData)
{
send_OK_packet(Server);
send_hardcode_pkt(Server,statechange,sizeof(statechange),true);
send_hardcode_pkt(Server,statechange2,sizeof(statechange2),true);
send_hardcode_pkt(Server, finalanimation3, sizeof(finalanimation3), true);

  
//send_hardcode_pkt(Server,creo_update_type32combat,sizeof(creo_update_type32combat),true);
//send_hardcode_pkt(Server,creo_update_type3combat,sizeof(creo_update_type3combat),true);
//send_hardcode_pkt(Server,player2_testupdate,sizeof(player2_testupdate),true);
};

void recv_unknown(ServerSocket *Server, char *pData)
{
 send_OK_packet(Server);
};

void recv_tell(ServerSocket *Server, char *pData)
{
//send_hardcode_pkt(Server,player_tell,sizeof(player_tell),true);
send_hardcode_pkt(Server,player_not_online,sizeof(player_not_online),true);
};

void recv_peace(ServerSocket *Server, char *pData)
{
send_hardcode_pkt(Server, butterfly_die, sizeof(butterfly_die), true);
send_hardcode_pkt(Server, butterfly_die2, sizeof(butterfly_die2), true);
send_hardcode_pkt(Server,creo_update_type32,sizeof(creo_update_type32),true);
send_hardcode_pkt(Server,creo_update_type3,sizeof(creo_update_type3),true);
send_hardcode_pkt(Server,player2_test,sizeof(player2_test),true);
};


void recv_burstrun(ServerSocket *Server, char *pData)
{
 send_hardcode_pkt(Server,player_burstrun,sizeof(player_burstrun),true);
 send_hardcode_pkt(Server,player_burstrun2,sizeof(player_burstrun2),true);
}


//SOE_FUNCTIONS//////////////////////////////////////////////////////////////////

void ping_reply(ServerSocket *Server)
{
 char *pPing = new char [sizeof(ping)];
 memcpy(pPing,ping,sizeof(ping));
 unsigned short size = sizeof(ping);
 Server->SendSWG(pPing,size,true, false, true);
 delete [] pPing;
}

void send_netstat(ServerSocket *Server, unsigned short tick)
{
 char *pNet = new char [sizeof(netstat)];
 unsigned short *pTick = (unsigned short*)(netstat+2);
 *pTick = tick;
 memcpy(pNet, netstat, sizeof(netstat));
 unsigned short size = sizeof(netstat);
 Server->SendSWG(pNet,size,true,true,false);
 delete [] pNet;
}

void send_sesresp(ServerSocket *Server)
{
 char *pSesRep = session_response;
 unsigned int *pInt = (unsigned int*)(pSesRep+2);
 *pInt = oclient.connection_id;
 pInt = (unsigned int*)(pSesRep+6);
 *pInt = htonl(oclient.CrcSeed);
 unsigned short size = sizeof(session_response);
 Server->SendSWG( pSesRep,size,false,false,false);

 //now send connectionserver packets
 send_hardcode_pkt(Server,connection_server,sizeof(connection_server),false);
}


void send_ack(ServerSocket *Server,unsigned short sequence)
{
 char *pAck = new char [sizeof(disconnect)];
 memcpy(pAck,ack,sizeof(ack));
 unsigned short *pSeq = (unsigned short*)(pAck+2);
 *pSeq = sequence;
 unsigned short size = sizeof(ack);

 Server->SendSWG(pAck,size,true);
 delete [] pAck;
}

void send_ack_ok(ServerSocket *Server, unsigned short sequence)
{
 char *pAckok = new char [sizeof(ackok)];
 memcpy(pAckok,ackok,sizeof(ackok));
 unsigned short *pSeq = (unsigned short*)(pAckok+5);
 *pSeq = sequence;
 unsigned short size = sizeof(ackok);
 Server->SendSWG(pAckok,size,true);
 delete [] pAckok;
};


void send_disconnect(ServerSocket *Server)
{
  char *pDis = new char [sizeof(disconnect)];
  memcpy(pDis,disconnect,sizeof(disconnect));
  unsigned int *pConID = (unsigned int*)(pDis+2);
  *pConID = oclient.connection_id;
  unsigned short size = sizeof(disconnect);
  Server->SendSWG(pDis,size,true);
  delete [] pDis;
}





//CLIENT_SERVER_PACKETS//////////////////////////////////////////////////////////
/* BRUTE FORCE ALGO
void send_weao_6(ServerSocket *Server)
{
 static int append = 28;
 Log( LOG_PRINT | LOG_CORE_SERVER, NULL, "\nAPPENDED: %d",append);
 unsigned short size = sizeof(weao_6_header) + sizeof(weao_6_body);
 char *packet = new char [size  + sizeof(footer) + append];
 memcpy(packet,weao_6_header,sizeof(weao_6_header));
 memcpy(packet+sizeof(weao_6_header),weao_6_body,sizeof(weao_6_body));
 for(int i = 0; i < append;i++)
 {
  packet[size+i] = 0x00;
 }
 size += append + sizeof(footer);
 memcpy(packet+size-sizeof(footer),footer,sizeof(footer));
 *(unsigned short*)(packet+2) =  (unsigned short)htons(oclient.server_sequence);
 *(unsigned int*)(packet+sizeof(weao_6_header)- sizeof(unsigned int)) = (unsigned int)(sizeof(weao_6_body) + append);
 Server->SendSWG(packet,size,true);
 delete [] packet;
 append++;
}
*/
void send_OK_packet(ServerSocket *Server)
{
     char *pOK = new char [sizeof(OK_packet)];
     memcpy(pOK,OK_packet,sizeof(OK_packet));
     Server->SendSWG(pOK,sizeof(OK_packet),true);
     delete [] pOK;
}

void send_hardcode_pkt(ServerSocket *Server,char *pkt,unsigned short size,bool comp)
{
     char *packet = new char [size];
     memcpy(packet,pkt,size);
     *(unsigned short*)(packet+2) =  (unsigned short)htons(oclient.server_sequence);
     Server->SendSWG(packet,size,true,comp,true);
     delete [] packet;
     oclient.server_sequence+=1;
}


//CHAR CREATION///////////////////////////////////////////////////////////////////


void recv_char_iff(ServerSocket *Server, char *pData, unsigned short nLength)
{
     unsigned short iff_size = *(unsigned short*)(pData+6);
     char *char_iff = new char[iff_size];
     memcpy(char_iff, pData+8, iff_size);
     char name1[] = "omfg";
     char name2[] = "swgemu.com";
     char name3[] = "dummyZone>all";
     char name4[] = "ImRonBurgandy?";
     char defaultname[] = "uhoh";


//Dlos25 Changed this because time wasn't a function found in VC++ 2005
#if defined(_WIN32) || defined(_WIN32_WCE) || defined(__WIN32__)
     srand(1234);
#else
	 srand((unsigned)time(0));
#endif
     int random_integer;
     for(int index=0; index<4; index++){
     random_integer = (rand()%4);
     }

     unsigned short namesize;



switch(random_integer)
{
     case 1:
          namesize = sizeof(name1);
          send_validate_char_name(Server, char_iff, iff_size, name1, namesize);
     break;

     case 2:
          namesize = sizeof(name2);
          send_validate_char_name(Server, char_iff, iff_size, name2, namesize);
     break;

     case 3:
          namesize = sizeof(name3);
          send_validate_char_name(Server, char_iff, iff_size, name3, namesize);
     break;

     case 4:
          namesize = sizeof(name4);
          send_validate_char_name(Server, char_iff, iff_size, name4, namesize);
     break;

     default:
          namesize = sizeof(defaultname);
          send_validate_char_name(Server, char_iff, iff_size, defaultname, namesize);
     break;
     }

}

void send_validate_char_name(ServerSocket *Server, char *char_iff, unsigned short iff_size, char *name, unsigned short namesize)
{
     unsigned short *pSeq = (unsigned short*)(character_statvalid_header+2);
     *pSeq = htons(oclient.server_sequence);
     namesize--; //remove teh null from the sizecount

     *(unsigned short*)(character_statvalid_header+10) = (unsigned short)iff_size; //copy the size to the header
     *(unsigned int*)character_statvalid_namesize = (unsigned int)namesize;
     namesize = namesize*2; //multiply by 2, for unicode

     wchar_t *u_name = new wchar_t[namesize/2];
     Server->ascii_to_unicode(u_name, name, namesize/2); //convert teh name to unicode

     unsigned short status_str_size = *(unsigned short*)character_statvalid_midfoot+8; //size of the namestatus string(
     status_str_size = sizeof(namestatus_name_approved);

     unsigned short packetsize = 29+iff_size+namesize+status_str_size; //total size of the packet.

     char *pNamePacket = new char [packetsize];

     memcpy(pNamePacket, character_statvalid_header, 12); //copy header
     memcpy(pNamePacket+12, char_iff, iff_size); //copy iff string
     memcpy(pNamePacket+12+iff_size, character_statvalid_namesize, 4); //copy the namesize (4 bytes)
     memcpy(pNamePacket+16+iff_size, u_name, namesize); //copy (unicode) name
     memcpy(pNamePacket+16+iff_size+namesize, character_statvalid_midfoot, 10); //copy ui+status_str_size
     memcpy(pNamePacket+26+iff_size+namesize, namestatus_name_approved, status_str_size); //copy namestatus approved. temporary!
     memcpy(pNamePacket+packetsize - 3, footer, 3); //copy those last 3 bytes

     Server->SendSWG(pNamePacket, packetsize, true);
     delete [] pNamePacket;
     oclient.server_sequence+=1;
}


void send_assign_char_id(ServerSocket *Server)
{
   static long long new_charID;
   new_charID = 1111111111;
     char *new_charid_pkt = new char[sizeof(assign_char_id_pkt)];
     memcpy(new_charid_pkt, assign_char_id_pkt, sizeof(assign_char_id_pkt));

     unsigned short *pSeq = (unsigned short*)(new_charid_pkt+2);
     *pSeq = htons(oclient.server_sequence);

     *(unsigned long long*)(new_charid_pkt+10) = (unsigned long long)new_charID;
     unsigned short size = sizeof(assign_char_id_pkt);

     Server->SendSWG(new_charid_pkt,size,true, false, true);

     delete [] new_charid_pkt;
     new_charID += 111111;
     oclient.server_sequence+=1;

}

void send_craft(ServerSocket *Server) {
     printf("crafting stared..\n");

     send_hardcode_pkt(Server,craft_start,sizeof(craft_start),true);
     send_hardcode_pkt(Server,craft_toolstart,sizeof(craft_toolstart),true);

}

void send_craft_stage1(ServerSocket *Server) {
     printf("1st crafting stage\n");

     send_hardcode_pkt(Server,craft2_create_ingreedients1,sizeof(craft2_create_ingreedients1),true);
     send_hardcode_pkt(Server,craft2_create_ingreedients2,sizeof(craft2_create_ingreedients2),true);
     send_hardcode_pkt(Server,craft2_create_ingreedients2_2,sizeof(craft2_create_ingreedients2_2),true);

     int ctime = time(0);
     while ( time(0) < ctime + 5);

     send_hardcode_pkt(Server,craft2_create_ingreedientslist1,sizeof(craft2_create_ingreedientslist1),true);
     send_hardcode_pkt(Server,craft2_create_ingreedientslist2,sizeof(craft2_create_ingreedientslist2),true);
     send_hardcode_pkt(Server,craft2_create_ingreedientslist3,sizeof(craft2_create_ingreedientslist3),true);
}

int slotcount = 0;

void send_craft_updateschems(ServerSocket *Server) {
     printf("ingreedients from datapad updated\n");

     send_hardcode_pkt(Server,craft2_update_schematic1,sizeof(craft2_update_schematic1),true);
     send_hardcode_pkt(Server,craft2_update_schematic2,sizeof(craft2_update_schematic2),true);
     
     slotcount = 0;
}

void send_insert_resource(ServerSocket *Server, unsigned long long *resId, unsigned int *slot, unsigned char* scount) {
     /*if (slotcount == 0) {
        ++slotcount;

        *((unsigned long long *)(craft_add_resource+13)) = *resId;
        *((unsigned char *)(craft_add_resource+66)) = slotcount;

        send_hardcode_pkt(Server,craft_add_resource,sizeof(craft_add_resource),true);

        printf("resource added to slot [%i]\n", slotcount);           
        send_hardcode_pkt(Server,craft_add_resource2_1,sizeof(craft_add_resource2_1),true);
        send_hardcode_pkt(Server,craft_add_resource2_2,sizeof(craft_add_resource2_2),true);
     } else {
        ++slotcount;

        *((unsigned char *)(craft_add_resource_3+0x42)) = slotcount;

        send_hardcode_pkt(Server,craft_add_resource_3,sizeof(craft_add_resource_3),true);

     }*/

     if (slotcount == 0) {
           send_hardcode_pkt(Server,craft2_add_resource1_1,sizeof(craft2_add_resource1_1),true);
           send_hardcode_pkt(Server,craft2_add_resource1_2,sizeof(craft2_add_resource1_2),true);
           send_hardcode_pkt(Server,craft2_add_resource1_3,sizeof(craft2_add_resource1_3),true);
     } else if (slotcount == 1) {
           send_hardcode_pkt(Server,craft2_add_resource2,sizeof(craft2_add_resource2),true);
     } else if (slotcount == 2) {
           send_hardcode_pkt(Server,craft2_add_resource3,sizeof(craft2_add_resource3),true);
     } else if (slotcount == 3) {
           send_hardcode_pkt(Server,craft2_add_resource4,sizeof(craft2_add_resource4),true);
     } else if (slotcount == 4) {
           send_hardcode_pkt(Server,craft2_add_resource5,sizeof(craft2_add_resource5),true);
     }

     *((unsigned char *)(craft2_add_resource1_4+38)) = *scount;
     send_hardcode_pkt(Server,craft2_add_resource1_4,sizeof(craft2_add_resource1_4),true);

     ++slotcount;
}

void send_insert_updateres(ServerSocket *Server) {
     //send_hardcode_pkt(Server,resource_attributes2,sizeof(resource_attributes2),true);
     send_hardcode_pkt(Server,craft_test1,sizeof(craft_test1),true);
     send_hardcode_pkt(Server,craft_test2,sizeof(craft_test2),true);
     send_hardcode_pkt(Server,craft_test3,sizeof(craft_test3),true);
}

int assembled = 0;

void send_craft_assemble(ServerSocket *Server) {
     if (assembled == 0) {
          printf("assembling\n");
     
          send_hardcode_pkt(Server,craft2_preassemble,sizeof(craft2_preassemble),true);
          send_hardcode_pkt(Server,craft2_assemble,sizeof(craft2_assemble),true);
          send_hardcode_pkt(Server,craft_assemble_finish,sizeof(craft_assemble_finish),true);
     
          assembled = 1;
     } else {
          printf("finishing experiment\n");

          send_hardcode_pkt(Server,craft2_assemble2,sizeof(craft2_assemble2),true);
     }
}

void send_craft_experiment(ServerSocket *Server) {
     send_hardcode_pkt(Server,craft2_experiment_start,sizeof(craft2_experiment_start),true);
}

void send_craft_createobj(ServerSocket *Server) {
     printf("creating object\n");

     send_hardcode_pkt(Server,craft2_createobj1,sizeof(craft2_createobj1),true);
     send_hardcode_pkt(Server,craft_createobj2,sizeof(craft_createobj2),true);
}

int craft_on = 0;

void send_craft_finish(ServerSocket *Server) {
     printf("finishing crafting\n");

     send_hardcode_pkt(Server,craft_finish1,sizeof(craft_finish1),true);

     craft_on = 18;
}

void send_craft_updatetooltime(ServerSocket *Server) {
     *((unsigned int *)(craft_update_tooltime+34)) = craft_on;

     send_hardcode_pkt(Server,craft_update_tooltime,sizeof(craft_update_tooltime),true);
}

void send_craft_finish2(ServerSocket *Server) {
     send_hardcode_pkt(Server,craft_finishmsg,sizeof(craft_finishmsg),true);
     send_hardcode_pkt(Server,craft2_finish2,sizeof(craft2_finish2),true);
}

void send_loot_open(ServerSocket *Server) {
     send_hardcode_pkt(Server,loot_inventory_start,sizeof(loot_inventory_start),true);
     send_hardcode_pkt(Server,loot_mellon,sizeof(loot_mellon),true);
     send_hardcode_pkt(Server,loot_inventory_finish,sizeof(loot_inventory_finish),true);
}

void send_loot_pearl(ServerSocket *Server) {
     send_hardcode_pkt(Server,pick_pearl,sizeof(pick_pearl),true);
}

void send_radial_confirm(ServerSocket *Server, char* pData, unsigned short nLength) {
     char resp[nLength+7];
     memcpy(resp+4,pData,nLength);
     *(unsigned short*)resp = (unsigned short)0x900;
     *(unsigned int*)(resp+10) = (unsigned int)0x0B;
     *(unsigned int*)(resp+14) = (unsigned int)0x147;

     //*(unsigned int*)(resp+50) = (unsigned int) 0x03240001;
     /**(unsigned int*)(resp+50+8) = (unsigned int) 0x03230102;
     *(unsigned int*)(resp+50+16) = (unsigned int) 0x01070003;*/
     //*(unsigned char*)(resp+53) = (unsigned char)0x03;
     send_hardcode_pkt(Server,resp,nLength+7,true);
     //send_hardcode_pkt(Server,radial_resp,sizeof(radial_resp),true);
     
/*     Server->hex_print(resp, 4);
     Server->hex_print(resp+4, nLength+7);
     Server->hex_print(resp+nLength+4, 3);*/
}


void send_dynamic_pkt(ServerSocket *Server,char *filename,bool comp)
{    
    std::ifstream file;
    file.open(filename,std::ios::in);
    char pkt[496];
    char bytebuffer[3] = {0,0,0};
    unsigned int byte = 0;
    char waste = 0;
    unsigned short counter = 0;
    if(!file.is_open())
    {
        std::cout << "Error Opening file: " << filename << std::endl;
        std::cout << "Cannot Send Dynamic Packet\\n";
        return;
    }
    while(!file.eof())
    {
        file >> bytebuffer[0];
        
        if (bytebuffer[0] == '-') {
           std::cout << "packet size: " << counter;
           send_hardcode_pkt(Server,pkt,counter,comp);
           
           counter = 0;
           continue;
        } else if (bytebuffer[0] == '/') {
           std::string line;
           getline (file,line);

           continue;
        }
        
        file >> bytebuffer[1];
        sscanf(bytebuffer,"%X",&byte);
        pkt[counter] = (unsigned char)byte;
        counter++;
        if(file.eof())
            break;
    }
    //file.close();
    counter--;
    std::cout << "packet size: " << counter;
    send_hardcode_pkt(Server,pkt,counter,comp);
}
