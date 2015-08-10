krayt_dragon_ancient = Creature:new {
	objectName = "@mob/creature_names:krayt_dragon_ancient",
	socialGroup = "krayt",
	faction = "",
	level = 336,
	chanceHit = 30.0,
	damageMin = 2270,
	damageMax = 4250,
	baseXp = 28549,
	baseHAM = 410000,
	baseHAMmax = 501000,
	armor = 3,
	resists = {195,195,195,195,165,195,195,195,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_bristley",
	hideAmount = 950,
	boneType = "bone_mammal",
	boneAmount = 905,
	milk = 0,
	tamingChance = 0,
	ferocity = 30,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,
	scale = 1.5,

	templates = {"object/mobile/krayt_dragon.iff"},
	lootGroups = {
		{
	        groups = {
				{group = "krayt_tissue_rare", chance = 2000000},
				{group = "krayt_dragon_common", chance = 2000000},
				{group = "pearls_flawless", chance = 1500000},
				{group = "armor_all", chance = 1500000},
				{group = "weapons_all", chance = 1500000},
				{group = "wearables_all", chance = 1500000},
			},
			lootChance = 7720000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareacombo","stateAccuracyBonus=100"},
		{"creatureareaknockdown","stateAccuracyBonus=100"}
	}
}

CreatureTemplates:addCreatureTemplate(krayt_dragon_ancient, "krayt_dragon_ancient")
