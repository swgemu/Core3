giant_gubber = Creature:new {
	objectName = "@mob/creature_names:giant_gubbur",
	socialGroup = "gubber",
	pvpFaction = "",
	faction = "",
	level = 9,
	chanceHit = 0.27,
	damageMin = 70,
	damageMax = 75,
	baseXp = 235,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {0,0,0,0,0,10,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 10,
	hideType = "hide_leathery",
	hideAmount = 15,
	boneType = "bone_mammal",
	boneAmount = 15,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_gubbur.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(giant_gubber, "giant_gubber")