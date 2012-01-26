capper_spineflap = Creature:new {
	objectName = "@mob/creature_names:capper_spineflap",
	socialGroup = "Cap. Spineflap",
	pvpFaction = "",
	faction = "",
	level = 6,
	chanceHit = 0.25,
	damageMin = 50,
	damageMax = 55,
	baseXp = 147,
	baseHAM = 180,
	baseHAMmax = 220,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 3,
	hideType = "hide_scaley",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 3,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/capper_spineflap.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(capper_spineflap, "capper_spineflap")