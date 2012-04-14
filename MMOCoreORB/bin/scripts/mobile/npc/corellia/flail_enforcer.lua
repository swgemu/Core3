flail_enforcer = Creature:new {
	objectName = "",
	customName = "a Flail enforcer",
	socialGroup = "Flail",
	pvpFaction = "Flail",
	faction = "",
	level = 19,
	chanceHit = 0.33,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1426,
	baseHAM = 4500,
	baseHAMmax = 5500,
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
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootGroups = {
			{
			groups = {
				{group = "junk", chance = 5500000},
				{group = "rifles", chance = 4000000},
				{group = "crystals", chance = 500000}
			},
			lootChance = 4500000
		}
	},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(flail_enforcer, "flail_enforcer")