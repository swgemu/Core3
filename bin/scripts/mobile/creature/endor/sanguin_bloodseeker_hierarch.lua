sanguin_bloodseeker_hierarch = Creature:new {
	objectName = "@mob/creature_names:bloodseeker_mite_sanguine_hierarch",
	socialGroup = "Bloodseeker",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.350000,
	damageMin = 230,
	damageMax = 240,
	range = 0,
	baseXp = 2443,
	baseHAM = 5550,
	armor = 0,
	resists = {15,15,0,20,0,20,20,0,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "hide_scaley",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(sanguin_bloodseeker_hierarch, "sanguin_bloodseeker_hierarch")
