lost_aqualish_warchief = Creature:new {
	objectName = "@mob/creature_names:lost_aqualish_warchief",
	socialGroup = "Lost Aql. Reg.",
	pvpFaction = "Lost Aql. Reg.",
	faction = "",
	level = 27,
	chanceHit = 0.370000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2822,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {0,0,0,0,40,-1,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER + HERD,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(lost_aqualish_warchief, "lost_aqualish_warchief")