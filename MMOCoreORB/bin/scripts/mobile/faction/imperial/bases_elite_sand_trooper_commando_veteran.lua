bases_elite_sand_trooper_commando_veteran = Creature:new {
	objectName = "@mob/creature_names:an_elite_sand_trooper_commando_veteran",
	randomNameType = NAME_STORMTROOPER_TAG,
	socialGroup = "imperial",
	faction = "imperial",
	level = 160,
	chanceHit = 0.53,
	damageMin = 670,
	damageMax = 1020,
	baseXp = 6302,
	baseHAM = 145000,
	baseHAMmax = 175000,
	armor = 3,
	resists = {0,0,40,100,-1,-1,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_stormtrooper_sand_trooper_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 6550000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
				{group = "melee_weapons", chance = 550000},
				{group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 25000},
				{group = "armor_attachments", chance = 25000},
				{group = "stormtrooper_common", chance = 100000},
				{group = "wearables_rare", chance = 1000000}
			}
		}
	},
	weapons = {"sandtrooper_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster)
}

CreatureTemplates:addCreatureTemplate(bases_elite_sand_trooper_commando_veteran, "bases_elite_sand_trooper_commando_veteran")
