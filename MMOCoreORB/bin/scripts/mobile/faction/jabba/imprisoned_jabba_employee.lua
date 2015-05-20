imprisoned_jabba_employee = Creature:new {
	objectName = "@mob/creature_names:imprisoned_jabba_employee",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "jabba",
	faction = "jabba",
	level = 12,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 430,
	baseHAM = 1200,
	baseHAMmax = 1400,
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
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_tatooine_jabba_thief.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 6400000},
				{group = "color_crystals", chance = 600000},
				{group = "crystals_good", chance = 400000},
				{group = "melee_polearm", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "clothing_attachments", chance = 200000},
				{group = "armor_attachments", chance = 200000},
				{group = "wearables_common", chance = 1000000}
			}
		}
	},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(imprisoned_jabba_employee, "imprisoned_jabba_employee")
