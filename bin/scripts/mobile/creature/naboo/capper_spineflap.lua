capper_spineflap = Creature:new {
	objectName = "@mob/creature_names:capper_spineflap",
	socialGroup = "Cap. Spineflap",
	pvpFaction = "",
	faction = "",
	level = 6,
	chanceHit = 0.250000,
	damageMin = 50,
	damageMax = 55,
	baseXp = 147,
	baseHAM = 200,
	baseHAMmax = 200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 3,
	hideType = "",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 3,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/capper_spineflap.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(capper_spineflap, "capper_spineflap")