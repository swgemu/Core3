bandit_tutorial_1 = Creature:new {
	objectName = "@mob/creature_names:bandit",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",--dont change this
	level = 10,
	chanceHit = 0.390000,
	damageMin = 5,
	damageMax = 10,
	baseXp = 100,
	baseHAM = 300,
	baseHAMmax = 400,
	armor = 0,
	resists = {-1,-1,-1,-1,-1,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	diet = NONE,
	lootchance = 10000000,

	templates = {"object/mobile/dressed_cobral_bandit_bith_male_01.iff"},
	lootgroups = {
		{group = "bandit_1", chance = 10000000}
	},
	weapons = {"tutorial_bandit_weapons"},--dont change this
	attacks = {"defaultattack", ""},
	conversationTemplate = "",
	optionsBitmask = 0
}

CreatureTemplates:addCreatureTemplate(bandit_tutorial_1, "bandit_tutorial_1")