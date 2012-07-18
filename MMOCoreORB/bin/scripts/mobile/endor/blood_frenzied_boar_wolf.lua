blood_frenzied_boar_wolf = Creature:new {
	objectName = "@mob/creature_names:blood_frenzied_boar_wolf",
	socialGroup = "boar",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.44,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4461,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {30,30,30,75,75,-1,30,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/boar_wolf_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"creatureareableeding",""}
	}
}

CreatureTemplates:addCreatureTemplate(blood_frenzied_boar_wolf, "blood_frenzied_boar_wolf")