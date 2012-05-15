blood_razor_elite_pirate = Creature:new {
	objectName = "@mob/creature_names:blood_razor_pirate_elite",
	socialGroup = "bloodrazor",
	pvpFaction = "bloodrazor",
	faction = "bloodrazor",
	level = 33,
	chanceHit = 0.39,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3370,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {20,60,20,20,-1,20,20,-1,-1},
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
		"object/mobile/dressed_blood_razor_pirate_elite_hum_f.iff",
		"object/mobile/dressed_blood_razor_pirate_elite_hum_m.iff",
		"object/mobile/dressed_blood_razor_pirate_elite_nikto_m.iff"
		},
	lootGroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(blood_razor_elite_pirate, "blood_razor_elite_pirate")