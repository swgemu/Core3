desert_vesp = Creature:new {
	objectName = "@mob/creature_names:desert_vesp",
	socialGroup = "Vesp",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3005,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {20,20,20,100,75,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 15,
	hideType = "hide_leathery",
	hideAmount = 6,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/vesp.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"strongpoison",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(desert_vesp, "desert_vesp")