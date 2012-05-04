blood_razor_strong_pirate = Creature:new {
	objectName = "@mob/creature_names:blood_razor_pirate_strong",
	socialGroup = "bloodrazor",
	pvpFaction = "bloodrazor",
	faction = "bloodrazor",
	level = 26,
	chanceHit = 0.36,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2730,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {20,40,15,-1,-1,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_blood_razor_pirate_strong_hum_f.iff",
		"object/mobile/dressed_blood_razor_pirate_strong_hum_m.iff",
		"object/mobile/dressed_blood_razor_pirate_strong_nikto_m.iff",
		"object/mobile/dressed_blood_razor_pirate_strong_rod_m.iff",
		"object/mobile/dressed_blood_razor_pirate_strong_tran_m.iff",
		"object/mobile/dressed_blood_razor_pirate_strong_wee_m.iff",
		"object/mobile/dressed_blood_razor_pirate_strong_zab_m.iff"
		},
	lootGroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(blood_razor_strong_pirate, "blood_razor_strong_pirate")