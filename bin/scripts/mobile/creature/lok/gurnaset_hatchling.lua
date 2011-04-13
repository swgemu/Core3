gurnaset_hatchling = Creature:new {
	objectName = "@mob/creature_names:gurnaset_hatchling",
	socialGroup = "Gurnaset",
	pvpFaction = "",
	faction = "",
	level = 5,
	chanceHit = 0.250000,
	damageMin = 45,
	damageMax = 50,
	baseXp = 85,
	baseHAM = 150,
	baseHAMmax = 150,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 351,
	hideType = "hide_leathery",
	hideAmount = 278,
	boneType = "bone_mammal",
	boneAmount = 303,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/gurnaset_hatchling.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(gurnaset_hatchling, "gurnaset_hatchling")