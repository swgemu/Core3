stintaril_fleshripper = Creature:new {
	objectName = "@mob/creature_names:stintaril_fleshstripper",
	socialGroup = "stinaril",
	pvpFaction = "",
	faction = "",
	level = 16,
	chanceHit = 0.31,
	damageMin = 150,
	damageMax = 160,
	baseXp = 960,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
	hideType = "hide_bristley",
	hideAmount = 3,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/stintaril_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(stintaril_fleshripper, "stintaril_fleshripper")