deadly_vesp = Creature:new {
	objectName = "@mob/creature_names:deadly_vesp",
	socialGroup = "Vesp",
	pvpFaction = "",
	faction = "",
	level = 93,
	chanceHit = 0.9,
	damageMin = 670,
	damageMax = 1050,
	baseXp = 8871,
	baseHAM = 13000,
	baseHAMmax = 16000,
	armor = 0,
	resists = {40,40,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 15,
	hideType = "hide_leathery",
	hideAmount = 6,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
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

CreatureTemplates:addCreatureTemplate(deadly_vesp, "deadly_vesp")