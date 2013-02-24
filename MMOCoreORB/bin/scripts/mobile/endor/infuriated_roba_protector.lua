infuriated_roba_protector = Creature:new {
	objectName = "@mob/creature_names:roba_infuriated_protectorate",
	socialGroup = "roba",
	pvpFaction = "",
	faction = "",
	level = 57,
	chanceHit = 0.55,
	damageMin = 420,
	damageMax = 550,
	baseXp = 5555,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 0,
	resists = {35,35,15,20,15,20,15,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 120,
	hideType = "hide_leathery",
	hideAmount = 95,
	boneType = "bone_mammal",
	boneAmount = 70,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/roba_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(infuriated_roba_protector, "infuriated_roba_protector")
