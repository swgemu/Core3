krayt_dragon_adolescent = Creature:new {
	objectName = "@mob/creature_names:krayt_dragon_adolescent",
	socialGroup = "Krayt",
	pvpFaction = "",
	faction = "",
	level = 200,
	chanceHit = 27.25,
	damageMin = 1220,
	damageMax = 2150,
	baseXp = 26356,
	baseHAM = 268000,
	baseHAMmax = 312000,
	armor = 3,
	resists = {60,60,60,60,50,60,60,60,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_bristley",
	hideAmount = 750,
	boneType = "bone_mammal",
	boneAmount = 675,
	milk = 0,
	tamingChance = 0,
	ferocity = 20,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/krayt_dragon_hue.iff"},
	scale = 0.7;
	lootGroups = {
		{
	        groups = {
				{group = "krayt_dragon_common", chance = 6000000},
				{group = "krayt_tissue_uncommon", chance = 4000000}				
			},
			lootChance = 5000000
		},
		{
	        groups = {
				{group = "composite_armor", chance = 2000000},
				{group = "ubese_armor", chance = 2000000},
				{group = "melee_two_handed", chance = 2000000},
				{group = "rifles", chance = 2000000},
				{group = "wearables_all", chance = 2000000},				
			},
			lootChance = 2500000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareattack",""},
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(krayt_dragon_adolescent, "krayt_dragon_adolescent")
