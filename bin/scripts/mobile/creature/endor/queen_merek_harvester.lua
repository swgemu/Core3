queen_merek_harvester = Creature:new {
	objectName = "@mob/creature_names:queen_merek_harvester",
	socialGroup = "Merek",
	pvpFaction = "",
	faction = "",
	level = 50,
	chanceHit = 0.500000,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4825,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {60,-1,0,100,50,0,50,0,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 50,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/queen_merek_harvester.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"creatureareableeding",""}
	}
}

CreatureTemplates:addCreatureTemplate(queen_merek_harvester, "queen_merek_harvester")