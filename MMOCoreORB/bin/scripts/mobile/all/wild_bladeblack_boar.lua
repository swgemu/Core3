wild_bladeblack_boar = Creature:new {
	objectName = "@mob/creature_names:quest_hero_of_tatooine_ferocious_beast",
	socialGroup = "Zuuca Boar",
	pvpFaction = "",
	faction = "",
	level = 39,
	chanceHit = 0.44,
	damageMin = 355,
	damageMax = 420,
	baseXp = 3915,
	baseHAM = 9100,
	baseHAMmax = 11100,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,0},
	meatType = "meat_herbivore",
	meatAmount = 120,
	hideType = "hide_leathery",
	hideAmount = 80,
	boneType = "bone_mammal",
	boneAmount = 50,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 0,
	diet = CARNIVORE,

	templates = {"object/mobile/zucca_boar.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(wild_bladeblack_boar, "wild_bladeblack_boar")