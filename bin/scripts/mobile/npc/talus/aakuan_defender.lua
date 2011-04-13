aakuan_defender = Creature:new {
	objectName = "@mob/creature_names:aakuan_defender",
	socialGroup = "Aa'kuan",
	pvpFaction = "Aa'kuan",
	faction = "",
	level = 23,
	chanceHit = 0.330000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 2443,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {35,35,-1,0,0,-1,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"melee_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(aakuan_defender, "aakuan_defender")