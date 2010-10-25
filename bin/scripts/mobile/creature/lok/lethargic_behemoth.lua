lethargic_behemoth = Creature:new {
	objectName = "@mob/creature_names:flit_lethargic_behemoth",
	socialGroup = "Flit",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.350000,
	damageMin = 250,
	damageMax = 260,
	range = 0,
	baseXp = 2219,
	baseHAM = 7000,
	armor = 0,
	resists = {10,10,-1,-1,0,-1,0,0,-1},
	meatType = "meat_avian",
	meatAmount = 11,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 13,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(lethargic_behemoth, "lethargic_behemoth")
