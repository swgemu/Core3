mountain_squill = Creature:new {
	objectName = "@mob/creature_names:mountain_squill",
	socialGroup = "squill",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.41,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3279,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {30,30,30,-1,30,30,30,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 3,
	hideType = "hide_leathery",
	hideAmount = 3,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 10,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/mountain_squill.iff"},
	controlDeviceTemplate = "object/intangible/pet/squill_hue.iff",
	scale = 1.15,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mountain_squill, "mountain_squill")
