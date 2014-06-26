motley_kaadu = Creature:new {
	objectName = "@mob/creature_names:kaadu_motley",
	socialGroup = "kaadu",
	pvpFaction = "",
	faction = "",
	level = 8,
	chanceHit = 0.27,
	damageMin = 70,
	damageMax = 75,
	baseXp = 187,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 120,
	hideType = "hide_leathery",
	hideAmount = 75,
	boneType = "bone_avian",
	boneAmount = 65,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kaadu_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/kaadu_hue.iff",
	scale = 0.9,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(motley_kaadu, "motley_kaadu")
