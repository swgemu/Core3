Nightsister_rancor = Creature:new {
	objectName = "@mob/creature_names:nightsister_rancor",
	socialGroup = "Nightsister",
	pvpFaction = "",
	faction = "",
	level = 55,
	chanceHit = 0.5,
	damageMin = 395,
	damageMax = 500,
	baseXp = 5373,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 1,
	resists = {30,60,5,100,100,100,5,5,-1},
	meatType = "meat_carnivore",
	meatAmount = 950,
	hideType = "hide_leathery",
	hideAmount = 876,
	boneType = "bone_mammal",
	boneAmount = 776,
	milk = 0,
	tamingChance = 0,
	ferocity = 10,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/rancor.iff"},
	lootGroups = {
		{
			groups = {
				{group = "rancor_common", chance = 2800000},
				{group = "pistols", chance = 2800000},
				{group = "rifles", chance = 2800000},
				{group = "unarmed_melee", chance = 1600000}
			},
			lootChance = 4400000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareaknockdown","knockdownChance=30"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(Nightsister_rancor, "Nightsister_rancor")