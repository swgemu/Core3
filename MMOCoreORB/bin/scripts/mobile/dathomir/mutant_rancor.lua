mutant_rancor = Creature:new {
	objectName = "@mob/creature_names:mutant_rancor",
	socialGroup = "rancor",
	pvpFaction = "",
	faction = "",
	level = 75,
	chanceHit = 0.7,
	damageMin = 495,
	damageMax = 700,
	baseXp = 7207,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 1,
	resists = {145,160,25,200,200,200,25,25,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 901,
	boneType = "bone_mammal",
	boneAmount = 851,
	milk = 0,
	tamingChance = 0,
	ferocity = 12,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/mutant_rancor.iff"},
	scale = 1.15,
	lootGroups = {
		{
			groups = {
				{group = "rancor_common", chance = 4000000},
				{group = "pistols", chance = 750000},
				{group = "heavy_weapons", chance = 500000},
				{group = "rifles", chance = 750000},
				{group = "carbines", chance = 500000},
				{group = "grenades_looted", chance = 500000},
				{group = "armor_all", chance = 1000000},
				{group = "melee_unarmed", chance = 1000000},
				{group = "wearables_common", chance = 500000},
				{group = "wearables_uncommon", chance = 500000}
			},
			lootChance = 2700000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareableeding",""},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mutant_rancor, "mutant_rancor")
