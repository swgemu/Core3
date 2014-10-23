plasma_thief_leader = Creature:new {
	objectName = "@mob/creature_names:plasma_thief_leader",
	socialGroup = "plasma_thief",
	pvpFaction = "plasma_thief",
	faction = "plasma_thief",
	level = 9,
	chanceHit = 0.27,
	damageMin = 80,
	damageMax = 90,
	baseXp = 292,
	baseHAM = 675,
	baseHAMmax = 825,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_plasma_thief_leader.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 5000000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "plasma_thief_common", chance = 1000000}
			},
			lootChance = 3200000
		}
	},
	weapons = {"ranged_weapons"},
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(plasma_thief_leader, "plasma_thief_leader")
