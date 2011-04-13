novatrooper_squad_leader = Creature:new {
	objectName = "Novatrooper Squad Leader",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 122,
	chanceHit = 4.000000,
	damageMin = 745,
	damageMax = 1200,
	baseXp = 11577,
	baseHAM = 44000,
	baseHAMmax = 54000,
	armor = 0,
	resists = {55,45,80,30,0,0,30,45,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"stormtrooper_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(novatrooper_squad_leader, "novatrooper_squad_leader")