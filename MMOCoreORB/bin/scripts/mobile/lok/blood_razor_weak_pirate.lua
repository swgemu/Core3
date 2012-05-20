blood_razor_weak_pirate = Creature:new {
	objectName = "@mob/creature_names:blood_razor_pirate_weak",
	socialGroup = "bloodrazor",
	pvpFaction = "bloodrazor",
	faction = "bloodrazor",
	level = 21,
	chanceHit = 0.33,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2006,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {10,25,10,10,-1,-1,10,-1,-1},
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
		"object/mobile/dressed_blood_razor_pirate_weak_hum_f.iff",
		"object/mobile/dressed_blood_razor_pirate_weak_hum_m.iff",
		"object/mobile/dressed_blood_razor_pirate_weak_nikto_m.iff",
		"object/mobile/dressed_blood_razor_pirate_weak_rod_m.iff",
		"object/mobile/dressed_blood_razor_pirate_weak_wee_m.iff",
		"object/mobile/dressed_blood_razor_pirate_weak_zab_m.iff"
		},
	lootGroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(blood_razor_weak_pirate, "blood_razor_weak_pirate")