nyms_elite_patrol = Creature:new {
	objectName = "@mob/creature_names:nym_patrol_elite",
	socialGroup = "Nym",
	pvpFaction = "Nym",
	faction = "",
	level = 41,
	chanceHit = 0.44,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4097,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {40,55,30,30,60,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_nym_guard_elite_rod_m.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "nyms_common", chance = 2500000},
				{group = "rifles", chance = 2500000},
				{group = "carbines", chance = 2500000},
				{group = "tailor_components", chance = 2500000}
			},
			lootChance = 6500000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(nyms_elite_patrol, "nyms_elite_patrol")