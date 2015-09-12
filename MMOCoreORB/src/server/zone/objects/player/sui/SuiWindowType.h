/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SUIWINDOWTYPE_H_
#define SUIWINDOWTYPE_H_

class SuiWindowType {
public:
	enum {
		NONE                               = 0, //This window type can be sent when you don't need to handle a callback.

		//Cloning 1 - 10
		CLONE_REQUEST_DECAY                = 1,
		CLONE_REQUEST                      = 2,
		CLONE_REQUEST_FACTIONAL            = 3,
		CLONE_CONFIRM                      = 10,

		//Entertaining 11 - 20
		MUSIC_START                        = 11,
		MUSIC_CHANGE                       = 12,
		DANCING_START                      = 13,
		DANCING_CHANGE                     = 14,
		BAND_START                         = 15,
		BAND_CHANGE                        = 16,

		//Guilds 21 - 50
		GUILD_CREATE_NAME                  = 21,
		GUILD_CREATE_ABBREV                = 22,
		GUILD_SPONSOR                      = 23,
		GUILD_SPONSOR_VERIFY               = 24,
		GUILD_SPONSORED_LIST               = 25,
		GUILD_SPONSORED_OPTIONS            = 26,
		GUILD_CHANGE_NAME                  = 27,
		GUILD_CHANGE_ABBREV                = 28,
		GUILD_INFORMATION                  = 29,
		GUILD_DISBAND                      = 30,
		GUILD_MEMBER_LIST                  = 31,
		GUILD_MEMBER_OPTIONS               = 32,
		GUILD_MEMBER_REMOVE                = 33,
		GUILD_MEMBER_PERMISSIONS           = 34,
		GUILD_MEMBER_TITLE                 = 35,
		GUILD_TRANSFER_LEADER              = 36,
		GUILD_TRANSFER_LEADER_CONFIRM      = 37,
		GUILD_WAR_LIST                     = 38,
		GUILD_WAR_ENTER_NAME               = 39,
		GUILD_TAKE_LOTS                    = 40,
		GUILD_VOTE                         = 41,
		GUILD_ELECTION_STANDING            = 42,


		//Travel 51 - 60
		TICKET_PURCHASE_MESSAGE            = 51,
		TRAVEL_TICKET_SELECTION            = 52,

		//Color Pickers 61 - 70
		COLOR_PICKER1                      = 61,
		COLOR_PICKER2                      = 62,

		//Bank 71 - 80
		BANK_TRANSFER                      = 71,
		BANK_TIP_CONFIRM                   = 72,

		//Resource 81 - 90
		FREE_RESOURCE                      = 81,
		GIVE_FREE_RESOURCE                 = 82,

		//Factory 91 - 100
		FACTORY_SCHEMATIC2BUTTON           = 91,
		FACTORY_SCHEMATIC3BUTTON           = 92,
		FACTORY_INGREDIENTS                = 93,

		//Insurance 101 - 110
		INSURANCE_MENU                     = 101,
		INSURANCE_CONFIRM_ALL              = 102,

		//City 111 - 140
		CITY_CREATE                        = 111,
		CITY_ENABLE_ZONING                 = 112,
		CITY_SET_NAME                      = 113,
		CITY_MILITIA                       = 114,
		CITY_ADD_MILITIA                   = 115,
		CITY_SPEC                          = 116,
		CITY_SPEC_CONFIRM                  = 117,
		CITY_STATUS_REPORT                 = 118,
		CITY_TREASURY_WITHDRAWAL           = 119,
		CITY_TREASURY_WITHDRAWAL_REASON    = 120,
		CITY_TREASURY_DEPOSIT              = 121,
		CITY_CITIZEN_REPORT                = 122,
		CITY_REMOVE_MILITIA                = 123,
		CITY_TREASURY_REPORT               = 124,
		CITY_ADVANCEMENT                   = 125,
		CITY_REGISTER                      = 126,
		CITY_MAYOR_STANDINGS               = 127,
		CITY_MAYOR_VOTE                    = 128,
		CITY_ADJUST_TAX                    = 129,
		CITY_TAX_PROMPT                    = 130,
		CITY_RENAME                        = 131,
		CITY_ADMIN_FORCE_RANK              = 132,
		CITY_ADMIN_FORCE_UPDATE            = 133,
		CITY_ADMIN_CONFIRM_UPDATE_TYPE     = 134,

		//Structure 141 - 170
		STRUCTURE_STATUS                   = 141,
		STRUCTURE_DESTROY_CODE             = 142,
		STRUCTURE_DESTROY_CONFIRM          = 143,
		STRUCTURE_MANAGE_MAINTENANCE       = 144,
		STRUCTURE_ADD_ENERGY               = 145,
		STRUCTURE_CREATE_VENDOR            = 146,
		STRUCTURE_NAME_VENDOR              = 147,
		STRUCTURE_DESTROY_VENDOR_CONFIRM   = 148,
		STRUCTURE_VENDOR_STATUS            = 149,
		STRUCTURE_VENDOR_REGISTER          = 150,
		STRUCTURE_UNCONDEMN_CONFIRM        = 151,
		STRUCTURE_SET_ACCESS_FEE           = 152,
		STRUCTURE_SET_ACCESS_DURATION      = 153,
		STRUCTURE_CONSENT_PAY_ACCESS_FEE   = 154,
		STRUCTURE_VENDOR_PAY               = 155,
		STRUCTURE_VENDOR_WITHDRAW          = 156,
		STRUCTURE_SELECT_SIGN              = 157,
		STRUCTURE_ASSIGN_DROID             = 158,

		//Admin 171 - 220
		ADMIN_COMMANDS                     = 171,
		ADMIN_BANLIST                      = 172,
		ADMIN_ACCOUNTINFO                  = 173,
		ADMIN_PLAYERINFO                   = 174,
		ADMIN_GUILDLIST                    = 175,
		ADMIN_DESTROY_CONFIRM              = 176,
		ADMIN_BAN_DURATION                 = 177,
		ADMIN_BAN_REASON                   = 178,
		ADMIN_BAN_SUMMARY                  = 179,
		ADMIN_UNBAN_SUMMARY                = 180,
		ADMIN_PLAYER_CREDITS               = 181,
		ADMIN_FIND_OBJECT                  = 182,
		ADMIN_GUILDINFO                    = 183,
		ADMIN_JEDILIST                     = 184,
		ADMIN_LIST                     	   = 185,

		//Teach 221 - 230
		TEACH_SKILL                        = 221,
		TEACH_PLAYER                       = 222,
		TEACH_DENY                         = 223,
		TEACH_OFFER                        = 224,

		//Survey Tool 231 - 240
		SURVEY_TOOL_RANGE                  = 231,
		SURVEY_TOOL_CONCENTRATED_MINIGAME  = 232,
		SURVEY_TOOL_CONCENTRATED_MINIGAME2 = 233,
		// survey droid tool
		SURVERY_DROID_MENU                 = 234,

		//Sample 241 - 250
		SAMPLE_RADIOACTIVE_CONFIRM         = 241,

		//Slicing 251 - 260
		SLICING_MENU                       = 251,

		//Gambling 261 - 270
		GAMBLING_ROULETTE                  = 261,
		GAMBLING_SLOT                      = 262,
		GAMBLING_SLOT_PAYOUT               = 263,

		//Fishing 271 - 280
		FISHING                            = 271,

		//Junk Dealer 281 - 290
		JUNK_DEALER_SELL_LIST              = 281,

		//Medic 291 - 300
		MEDIC_CONSENT                      = 291,
		MEDIC_DIAGNOSE                     = 292,

		//MOTD 301 - 310
		MOTD                               = 301,
		MOTD_SET                           = 302,

		//Character Builder 311 - 320
		CHARACTER_BUILDER_LIST             = 311,

		//
		DELEGATE_TRANSFER                  = 321,

		// Reaction Fines
		REACTION_FINE                      = 331,

		// Growable Plant
		GROWABLE_PLANT					   = 341,

		// Ranger 400 - 401
		RANGER_TRACK_OPTIONS               = 400,
		RANGER_TRACK_RESULTS               = 401,

		// FACTION HQ STRUCTURE
		//HQ_DEFENSE_STATUS = 420,
		//HQ_RESET_VULNERABILITY = 421,
		HQ_TERMINAL                        = 420,
		HQ_TURRET_TERMINAL                 = 421,

		// Firework Show 500-510
		FIREWORK_SHOW_ADDEVENT             = 500,
		FIREWORK_SHOW_REMOVEEVENT          = 501,
		FIREWORK_SHOW_REORDERSHOW          = 502,
		FIREWORK_SHOW_MODIFYEVENT          = 503,
		FIREWORK_SHOW_DELAYSELECTION       = 504,

		//Group Loot 511-520
		GROUP_LOOT_RULE                    = 511,
		GROUP_LOOT_CHANGED                 = 512,
		GROUP_LOOT_PICK_LOOTER             = 513,
		GROUP_LOOT_LOTTERY                 = 514,

		//Miscellaneous 1000+
		OBJECT_NAME                        = 1000,
		FINDSESSION                        = 1001,
		GARAGE_REPAIR                      = 1002,
		CAMP_STATUS                        = 1003,
		TUNE_CRYSTAL                       = 1004,
		INSTALL_MISSION_TERMINAL           = 1005,
		RECRUIT_SKILL_TRAINER              = 1006,
		HOLOGRIND_UNLOCK                   = 1007,
		MARKET_INFO                        = 1008,
		VENDOR_PHRASES                     = 1009,
		VENDOR_MOODS                       = 1010,
		VENDOR_CUSTOM_PHRASE               = 1011,
		VENDOR_ANIMATION                   = 1012,
		COLOR_GOGGLES                      = 1013,
		COLOR_ARMOR                        = 1014,	
		CUSTOMIZE_KIT                      = 1015, // listbox to select FRAME or TRIM
		MOUNT_GROWTH_ARREST                = 1016,
		HOLO_EMOTE_HELP                    = 1017,
		PROPOSE_UNITY                      = 1018,
		SELECT_UNITY_RING                  = 1019,
		SELECT_VETERAN_REWARD              = 1020,
		CONFIRM_VETERAN_REWARD             = 1021,
		CONFIRM_DIVORCE                    = 1022,
		CONFIRM_FLASH_SPEEDER_PURCHASE     = 1023,
		COA_MESSAGE_FRAGMENT               = 1024,
		COA_MESSAGE                        = 1025,
		DATA_STORAGE_UNIT_MESSAGE          = 1026,
		DROID_LOAD_STIMPACK                = 1027,
		SELECT_DROID_EFFECT                = 1028,
		SELECT_DROID_EFFECT_DELAY          = 1029,
		SELECT_MERCHANT_WAYPOINT           = 1030,
		DROID_PLAYBACK_MENU                = 1031,
		DROID_DELETE_TRACK                 = 1031,
		DROID_SET_INTEREST                 = 1032,
		NEWSNET_INFO                       = 1033,
		DROID_EDIT_ASSIGNED_STRUCTURES     = 1034,
		DROID_MAINTENANCE_RUN_LIST         = 1035,
		DROID_ADD_STRUCTURE_AMOUNT         = 1036,
		PET_FIX_DIALOG					   = 1037,
		JUKEBOX_SELECTION				   = 1038
	};
};

#endif /*SuiWindowType_H_*/
