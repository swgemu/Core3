skaak_tipper_prowler = Creature:new {
	objectName = "@mob/creature_names:skaak_tipper_prowler",
	socialGroup = "Sk.Tip. Gang",
	pvpFaction = "Thug",
	faction = "",
	level = 5,
	chanceHit = 0.250000,
	damageMin = 45,
	damageMax = 50,
	baseXp = 85,
	baseHAM = 135,
	baseHAMmax = 165,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {},
	lootGroups = {
		{
			groups = {
				{group = "loot_kit_items", chance = 10000000}
			},
			lootChance = 3500000
		}
	},
	weapons = {"pirate_weapons_light"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(skaak_tipper_prowler, "skaak_tipper_prowler")