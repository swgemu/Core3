juvenile_canyon_krayt_dragon = Creature:new {
	objectName = "@mob/creature_names:juvenile_canyon_krayt",
	socialGroup = "Krayt",
	pvpFaction = "",
	faction = "",
	level = 122,
	chanceHit = 40,
	damageMin = 745,
	damageMax = 1200,
	baseXp = 11577,
	baseHAM = 54000,
	baseHAMmax = 64000,
	armor = 3,
	resists = {50,50,50,50,10,50,50,50,-1},
	meatType = "meat_carnivore",
	meatAmount = 750,
	hideType = "hide_bristley",
	hideAmount = 500,
	boneType = "bone_mammal",
	boneAmount = 410,
	milk = 0,
	tamingChance = 0,
	ferocity = 20,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/juvenile_canyon_krayt.iff"},
	lootGroups = {
	 {
	        groups = {
				{group = "krayt_tissue_common", chance = 3500000},
				{group = "krayt_dragon_common", chance = 6500000},
			},
			lootChance = 4000000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareaattack",""},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(juvenile_canyon_krayt_dragon, "juvenile_canyon_krayt_dragon")
