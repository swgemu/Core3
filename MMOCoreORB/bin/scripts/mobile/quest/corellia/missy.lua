missy = Creature:new {
	objectName = "@mob/creature_names:sand_panther_cub",
	socialGroup = "panther",
	faction = "",
	level = 1,
	chanceHit = 0.28,
	damageMin = 5,
	damageMax = 20,
	baseXp = 356,
	baseHAM = 810,
	baseHAMmax = 990,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 25,
	hideType = "hide_bristley",
	hideAmount = 14,
	boneType = "bone_mammal",
	boneAmount = 12,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 264,
	diet = CARNIVORE,

	templates = {"object/mobile/corellian_sand_panther_cub.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "diktatTargetConvo",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(missy, "missy")
