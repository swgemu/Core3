vicious_huf_dun = Creature:new {
	objectName = "@mob/creature_names:vicious_huf_dun",
	socialGroup = "Huf Dun",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 220,
	baseXp = 1609,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,0},
	meatType = "meat_herbivore",
	meatAmount = 850,
	hideType = "hide_leathery",
	hideAmount = 900,
	boneType = "bone_mammal",
	boneAmount = 850,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 3,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 0,
	diet = CARNIVORE,

	templates = {"object/mobile/huf_dun.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(vicious_huf_dun, "vicious_huf_dun")