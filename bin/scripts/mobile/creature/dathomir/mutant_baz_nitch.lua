mutant_baz_nitch = Creature:new {
	objectName = "@mob/creature_names:mutant_baz_nitch",
	socialGroup = "Baz Nitch",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3097,
	baseHAM = 9300,
	baseHAMmax = 9300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_wild",
	meatAmount = 5,
	hideType = "hide_leathery",
	hideAmount = 3,
	boneType = "bone_mammal",
	boneAmount = 3,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/mutant_baz_nitch.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(mutant_baz_nitch, "mutant_baz_nitch")