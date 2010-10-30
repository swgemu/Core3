slum_rat = Creature:new {
	objectName = "@mob/creature_names:womprat_city",
	socialGroup = "Lesser Desert W'rat",
	pvpFaction = "",
	faction = "",
	level = 6,
	chanceHit = 0.250000,
	damageMin = 50,
	damageMax = 55,
	baseXp = 113,
	baseHAM = 200,
	baseHAMmax = 200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 7,
	hideType = "hide_leathery",
	hideAmount = 7,
	boneType = "bone_mammal",
	boneAmount = 3,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/lesser_desert_womp_rat.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(slum_rat, "slum_rat")