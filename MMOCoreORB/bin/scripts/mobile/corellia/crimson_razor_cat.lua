crimson_razor_cat = Creature:new {
	objectName = "@mob/creature_names:crimson_sand_panther",
	socialGroup = "panther",
	pvpFaction = "",
	faction = "",
	level = 29,
	chanceHit = 0.39,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3005,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {35,35,-1,-1,15,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/crimson_sand_panther.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(crimson_razor_cat, "crimson_razor_cat")