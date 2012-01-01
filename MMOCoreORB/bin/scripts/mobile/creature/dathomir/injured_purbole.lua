injured_purbole = Creature:new {
	objectName = "@mob/creature_names:injured_purbole",
	socialGroup = "Purbole",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.29,
	damageMin = 140,
	damageMax = 150,
	baseXp = 430,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 15,
	hideType = "hide_bristley",
	hideAmount = 10,
	boneType = "bone_mammal",
	boneAmount = 10,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/purbole.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(injured_purbole, "injured_purbole")