/*
 * VendorType.h
 *
 *  Created on: Mar 18, 2011
 *      Author: polonel
 */

#ifndef VENDORTYPE_H_
#define VENDORTYPE_H_

#include "engine/engine.h"

class VendorType {
public:

	/*
	 * VendorType List - HIRING
	 * This list is ordered by the skill mod hiring.
	 */

	// ARTISAN BUSINESS III - Hiring skill +10
	static const int TERMINAL = 9;
	static const int TERMINAL_BULKY = 10;

	// ARTISAN BUSINESS IV - Hiring skill +20
	static const int DROID = 19;
	static const int DROID_BARTENDER = 20;

	// NOVICE MERCHANT - Hiring skill + 30
	static const int NPC = 28;
	static const int TERMINAL_STANDARD = 29;
	static const int NPC_RANDOM = 30;

	// HIRING I - Hiring skill +50
	static const int TERMINAL_SMALL = 40;
	static const int DROID_POWER = 41;
	static const int NPC_BOTHAN = 42;
	static const int NPC_HUMAN = 43;
	static const int NPC_MONCAL = 44;
	static const int NPC_RODIAN = 45;
	static const int NPC_TRANDOSHAN = 46;
	static const int NPC_TWILEK = 47;
	static const int NPC_WOOKIEE = 48;
	static const int NPC_ZABRAK = 49;

	// HIRING II - Hiring skill +60
	static const int DROID_WED = 50;
	static const int NPC_AQUALISH = 51;
	static const int NPC_BITH = 52;
	static const int NPC_DEVARONIAN = 53; // only male
	static const int NPC_GRAN = 54; // only male
	static const int NPC_ISHI = 55; // only male
	static const int NPC_ITHORIAN = 56;
	static const int NPC_NIKTO = 57; // only male
	static const int NPC_QUARREN = 58; // only male
	static const int NPC_SULLUSTAN = 59;
	static const int NPC_WEEQUAY = 60; // only male

	// HIRING III - Hiring skill +75
	static const int TERMINAL_FANCY = 75;

	//HIRING IV - Hiring skill +90
	static const int TERMINAL_SLIM = 89;
	static const int DROID_SURGICAL = 90;

	// MASTER MERCHANT hiring skil +100
	static const int DROID_PROTOCOL = 100;

	static const int GENDER_MALE = 200;
	static const int GENDER_FEMALE = 201;


	static bool isTerminalType(int type) {
		return (type == 10 || type == 29 || type == 40 || type == 75 || type == 89);
	}

	static bool isDroidType(int type) {
		return (type == 20 || type == 41 || type == 50 || type == 90 || type == 100);
	}

	static bool isNpcType(int type) {
		return (type == 30 || (type >= 42 && type <= 49) || (type >= 51 && type <= 60));
	}

	static bool isMaleOnly(int type) {
		return ((type >= 53 && type <= 55) || type == 57 || type == 58 || type == 60);
	}

	static String getVendorStfName(int vendorType) {
		String name = "";

		switch (vendorType) {

		case TERMINAL:
			name = "@player_structure:terminal";
			break;

		case TERMINAL_BULKY:
			name = "@player_structure:terminal_bulky";
			break;

		case DROID:
			name = "@player_structure:droid";
			break;

		case DROID_BARTENDER:
			name = "@player_structure:droid_bartender";
			break;

		case TERMINAL_STANDARD:
			name = "@player_structure:terminal_standard";
			break;

		case NPC:
			name = "@player_structure:npc";
			break;

		case NPC_RANDOM:
			name = "@player_structure:race_random";
			break;

		case TERMINAL_SMALL:
			name = "@player_structure:terminal_small";
			break;

		case DROID_POWER:
			name = "@player_structure:droid_power";
			break;

		case NPC_BOTHAN:
			name = "@player_structure:race_bothan";
			break;

		case NPC_HUMAN:
			name = "@player_structure:race_human";
			break;

		case NPC_MONCAL:
			name = "@player_structure:race_moncal";
			break;

		case NPC_RODIAN:
			name = "@player_structure:race_rodian";
			break;

		case NPC_TRANDOSHAN:
			name = "@player_structure:race_trandoshan";
			break;

		case NPC_TWILEK:
			name = "@player_structure:race_twilek";
			break;

		case NPC_WOOKIEE:
			name = "@player_structure:race_wookiee";
			break;

		case NPC_ZABRAK:
			name = "@player_structure:race_zabrak";
			break;

		case DROID_WED:
			name = "@player_structure:droid_wed";
			break;

		case NPC_AQUALISH:
			name = "@player_structure:race_aqualish";
			break;

		case NPC_BITH:
			name = "@player_structure:race_bith";
			break;

		case NPC_DEVARONIAN:
			name = "@player_structure:race_devaronian";
			break;

		case NPC_GRAN:
			name = "@player_structure:race_gran";
			break;

		case NPC_ISHI:
			name = "@player_structure:race_ishi_tib";
			break;

		case NPC_ITHORIAN:
			name = "@player_structure:race_ithorian";
			break;

		case NPC_NIKTO:
			name = "@player_structure:race_nikto";
			break;

		case NPC_QUARREN:
			name = "@player_structure:race_quarren";
			break;

		case NPC_SULLUSTAN:
			name = "@player_structure:race_sullustan";
			break;

		case NPC_WEEQUAY:
			name = "@player_structure:race_weequay";
			break;

		case TERMINAL_FANCY:
			name = "@player_structure:terminal_fancy";
			break;

		case TERMINAL_SLIM:
			name = "@player_structure:terminal_slim";
			break;

		case DROID_SURGICAL:
			name = "@player_structure:droid_surgical";
			break;

		case DROID_PROTOCOL:
			name = "@player_structure:droid_protocol";
			break;
		}

		return name;
	}

	static String getVendorTypeName(int vendorType) {
		String name = "";

		switch (vendorType) {

		case TERMINAL_BULKY:
			name = "vendor_terminal_bulky";
			break;

		case DROID_BARTENDER:
			name = "vendor_droid_bartender";
			break;

		case TERMINAL_STANDARD:
			name = "vendor_terminal_standard";
			break;

		case TERMINAL_SMALL:
			name = "vendor_terminal_small";
			break;

		case DROID_POWER:
			name = "vendor_droid_power";
			break;

		case NPC_BOTHAN:
			name = "bothan";
			break;

		case NPC_HUMAN:
			name = "human";
			break;

		case NPC_MONCAL:
			name = "moncal";
			break;

		case NPC_RODIAN:
			name = "rodian";
			break;

		case NPC_TRANDOSHAN:
			name = "trandoshan";
			break;

		case NPC_TWILEK:
			name = "twilek";
			break;

		case NPC_WOOKIEE:
			name = "wookiee";
			break;

		case NPC_ZABRAK:
			name = "zabrak";
			break;

		case DROID_WED:
			name = "vendor_droid_wed";
			break;

		case NPC_AQUALISH:
			name = "aqualish";
			break;

		case NPC_BITH:
			name = "bith";
			break;

		case NPC_DEVARONIAN:
			name = "devaronian";
			break;

		case NPC_GRAN:
			name = "gran";
			break;

		case NPC_ISHI:
			name = "ishi_tib";
			break;

		case NPC_ITHORIAN:
			name = "ithorian";
			break;

		case NPC_NIKTO:
			name = "nikto";
			break;

		case NPC_QUARREN:
			name = "quarren";
			break;

		case NPC_SULLUSTAN:
			name = "sullustan";
			break;

		case NPC_WEEQUAY:
			name = "weequay";
			break;

		case TERMINAL_FANCY:
			name = "vendor_terminal_fancy";
			break;

		case TERMINAL_SLIM:
			name = "vendor_terminal_slim";
			break;

		case DROID_SURGICAL:
			name = "vendor_droid_surgical";
			break;

		case DROID_PROTOCOL:
			name = "vendor_droid_protocol";
			break;
		}

		return name;

	}

};

#endif /* VENDORTYPE_H_ */
