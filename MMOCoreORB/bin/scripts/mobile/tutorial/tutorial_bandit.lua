tutorial_bandit = Creature:new {
	objectName = "@mob/creature_names:bandit",
	socialGroup = "",
	faction = "",
	level = 1,
	chanceHit = 0.390000,
	damageMin = 5,
	damageMax = 10,
	baseXp = 100,
	baseHAM = 1000,
	baseHAMmax = 1000,
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
	pvpBitmask = ATTACKABLE + ENEMY,
	optionsBitmask = 128,
	creatureBitmask = NONE,
	diet = NONE,

	templates = {"object/mobile/dressed_cobral_bandit_bith_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "tutorial_pirate", chance = 10000000}
			},
			lootChance = 10000000
		}
	},
	weapons = {"tutorial_bandit"},--dont change this
	attacks = {{"defaultattack", ""}},
	conversationTemplate = "",
}

CreatureTemplates:addCreatureTemplate(tutorial_bandit, "tutorial_bandit")
