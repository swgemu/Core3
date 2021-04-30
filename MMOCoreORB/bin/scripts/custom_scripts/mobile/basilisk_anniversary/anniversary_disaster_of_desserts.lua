anniversary_disaster_of_desserts = Creature:new {
	customName = "Alton Flay (a Disaster of Desserts)",
	socialGroup = "",
	faction = "",
	level = 4,
	chanceHit = 0.24,
	damageMin = 40,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 113,
	baseHAMmax = 138,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = HERD,
	optionsBitmask = CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_chef_trainer_devaronian_male_01.iff"},
	lootGroups = {
			groups = {
				{group = "anniversary_quest_loot_group", chance = 10000000},
			}
		},
	weapons = {},
	conversationTemplate = "AnniversaryAltonFlayConvoTemplate",
	attacks = {brawlermaster}
}

CreatureTemplates:addCreatureTemplate(anniversary_disaster_of_desserts, "anniversary_disaster_of_desserts")