#ifndef FACTIONS_H_
#define FACTIONS_H_

class Factions {
public:
	enum FactionCRC: uint32 {
		FACTIONNEUTRAL = 0,
		FACTIONIMPERIAL = 0xDB4ACC54,
		FACTIONREBEL = 0x16148850
	};

	static String factionToString(uint32 value) {
		switch(value) {
			case FACTIONIMPERIAL: return "imperial";
			case FACTIONREBEL: return "rebel";
			default: return "";
		}
	}
};

#endif //FACTIONS_H_
