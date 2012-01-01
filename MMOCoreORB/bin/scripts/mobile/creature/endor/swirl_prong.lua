swirl_prong = Creature:new {
	objectName = "@mob/creature_names:swirl_prong",
	socialGroup = "Swirl Prong",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.32,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1426,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {5,20,5,35,35,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/swirl_prong.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(swirl_prong, "swirl_prong")