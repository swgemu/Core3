deadly_vesp = Creature:new {
	objectName = "@mob/creature_names:deadly_vesp",
	socialGroup = "Vesp",
	pvpFaction = "",
	faction = "",
	level = 93,
	chanceHit = 0.900000,
	damageMin = 670,
	damageMax = 1050,
	baseXp = 8871,
	baseHAM = 14500,
	baseHAMmax = 14500,
	armor = 0,
	resists = {40,40,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 15,
	hideType = "hide_leathery",
	hideAmount = 6,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/vesp.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"strongpoison",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(deadly_vesp, "deadly_vesp")