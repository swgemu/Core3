furious_ronto = Creature:new {
	objectName = "@mob/creature_names:ronto_furious",
	socialGroup = "ronto",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.37,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2730,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {115,125,-1,150,140,-1,15,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 465,
	hideType = "hide_leathery",
	hideAmount = 320,
	boneType = "bone_mammal",
	boneAmount = 200,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 1,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/ronto_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/ronto_hue.iff",
	scale = 1.25,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(furious_ronto, "furious_ronto")
