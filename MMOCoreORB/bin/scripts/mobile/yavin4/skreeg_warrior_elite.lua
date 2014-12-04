skreeg_warrior_elite = Creature:new {
	objectName = "@mob/creature_names:skreeg_warrior_elite",
	socialGroup = "skreeg",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3005,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {-1,175,20,-1,200,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 5,
	hideType = "hide_bristley",
	hideAmount = 9,
	boneType = "bone_mammal",
	boneAmount = 7,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/skreeg_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/skreeg_hue.iff",
	scale = 1.25,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(skreeg_warrior_elite, "skreeg_warrior_elite")
