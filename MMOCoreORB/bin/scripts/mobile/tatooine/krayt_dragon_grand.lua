krayt_dragon_grand = Creature:new {
	objectName = "@mob/creature_names:krayt_dragon_grand",
	socialGroup = "krayt",
	faction = "",
	level = 306,
	chanceHit = 30,
	damageMin = 2170,
	damageMax = 4150,
	baseXp = 28049,
	baseHAM = 390000,
	baseHAMmax = 481000,
	armor = 3,
	resists = {90,90,90,100,65,90,90,90,-1},
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

	templates = {"object/mobile/krayt_dragon.iff"},
	scale = 1.1;
	lootGroups = {
		{
	        groups = {
				{group = "krayt_tissue_rare", chance = 3300000},
				{group = "krayt_dragon_common", chance = 3300000},
				{group = "pearls_flawless", chance = 3400000}				
			},
			lootChance = 6500000
		},
		{
	        groups = {
				{group = "composite_armor", chance = 2000000},
				{group = "ubese_armor", chance = 2000000},
				{group = "melee_two_handed", chance = 2000000},
				{group = "rifles", chance = 2000000},
				{group = "wearables_all", chance = 2000000},				
			},
			lootChance = 3500000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareacombo","stateAccuracyBonus=50"},
		{"blindattack","stateAccuracyBonus=50"},
		{"intimidationattack","stateAccuracyBonus=50"},
		{"creatureareaknockdown","stateAccuracyBonus=50"},
		{"stunattack","stateAccuracyBonus=50"}
	}
}

CreatureTemplates:addCreatureTemplate(krayt_dragon_grand, "krayt_dragon_grand")
