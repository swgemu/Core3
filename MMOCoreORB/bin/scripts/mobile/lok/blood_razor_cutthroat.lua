blood_razor_cutthroat = Creature:new {
	objectName = "@mob/creature_names:blood_razor_cutthroat",
	socialGroup = "bloodrazor",
	pvpFaction = "bloodrazor",
	faction = "bloodrazor",
	level = 34,
	chanceHit = 0.4,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3460,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {0,45,0,0,-1,0,0,-1,-1},
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

	aiTemplate = "default",

	templates = {
		"object/mobile/dressed_blood_razor_pirate_cutthroat_hum_f.iff",
		"object/mobile/dressed_blood_razor_pirate_cutthroat_hum_m.iff",
		"object/mobile/dressed_blood_razor_pirate_cutthroat_nikto_m.iff",
		"object/mobile/dressed_blood_razor_pirate_cutthroat_tran_m.iff",
		"object/mobile/dressed_blood_razor_pirate_cutthroat_wee_m.iff"
		},
	lootGroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(blood_razor_cutthroat, "blood_razor_cutthroat")