lowland_salt_mynock = Creature:new {
	objectName = "@mob/creature_names:lowland_salt_mynock",
	socialGroup = "Mynock",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.350000,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2730,
	baseHAM = 7550,
	baseHAMmax = 7550,
	armor = 0,
	resists = {20,35,0,50,50,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 55,
	hideType = "hide_leathery",
	hideAmount = 73,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/salt_mynock.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(lowland_salt_mynock, "lowland_salt_mynock")