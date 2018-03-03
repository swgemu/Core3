jerrd_sonclim = Creature:new {
	objectName = "@theme_park/warren/warren_system_messages:name_jerrd",
	socialGroup = "",
	faction = "",
	level = 11,
	chanceHit = 1,
	damageMin = 121,
	damageMax = 270,
	baseXp = 2100,
	baseHAM = 8600,
	baseHAMmax = 9900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/warren_jerrd_sonclim.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4500000},
				{group = "loot_kit_parts", chance = 3000000},
				{group = "armor_attachments", chance = 500000},
				{group = "clothing_attachments", chance = 500000},
				{group = "wearables_common", chance = 1500000}
			}
		}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster,carbineermaster,riflemanmaster)
}

CreatureTemplates:addCreatureTemplate(jerrd_sonclim, "jerrd_sonclim")
