canyon_krayt_dragon = Creature:new {
	objectName = "@mob/creature_names:canyon_krayt_dragon",
	socialGroup = "Krayt",
	pvpFaction = "",
	faction = "",
	level = 275,
	chanceHit = 27.25,
	damageMin = 1520,
	damageMax = 2750,
	baseXp = 26356,
	baseHAM = 321000,
	baseHAMmax = 392000,
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

	templates = {"object/mobile/canyon_krayt_dragon.iff"},
	lootGroups = {
	 {
	        groups = {
				{group = "krayt_dragon_common2", chance = 4000000},
				{group = "krayt_tissue_common", chance = 2000000}				
			},
			lootChance = 6500000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareaattack",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(canyon_krayt_dragon, "canyon_krayt_dragon")