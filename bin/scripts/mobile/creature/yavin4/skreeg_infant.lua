skreeg_infant = Creature:new {
	objectName = "@mob/creature_names:skreeg_infant",
	socialGroup = "Skreeg",
	pvpFaction = "",
	faction = "",
	level = 4,
	chanceHit = 0.240000,
	damageMin = 40,
	damageMax = 45,
	baseXp = 85,
	baseHAM = 125,
	baseHAMmax = 125,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 15,
	hideType = "hide_bristley",
	hideAmount = 9,
	boneType = "bone_mammal",
	boneAmount = 7,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/skreeg_infant.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(skreeg_infant, "skreeg_infant")