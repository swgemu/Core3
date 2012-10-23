poisonous_krevol_queen = Creature:new {
	objectName = "@mob/creature_names:poisonous_krevol_queen",
	socialGroup = "krevol",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.3,
	damageMin = 170,
	damageMax = 180,
	baseXp = 960,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {25,0,0,-1,20,0,20,-1,-1},
	meatType = "meat_insect",
	meatAmount = 12,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/poisonous_krevol_queen.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(poisonous_krevol_queen, "poisonous_krevol_queen")