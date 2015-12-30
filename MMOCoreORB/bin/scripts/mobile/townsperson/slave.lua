slave = Creature:new {
	objectName = "@mob/creature_names:slave",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "townsperson",
	faction = "townsperson",
	level = 4,
	chanceHit = 0.240000,
	damageMin = 40,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 113,
	baseHAMmax = 138,
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

	templates = {"object/mobile/twilek_female.iff",
				 "object/mobile/twilek_male.iff",
				 "object/mobile/human_male.iff",
				 "object/mobile/human_female.iff",
				 "object/mobile/wookiee_male.iff",
				 "object/mobile/wookiee_female.iff",
				 "object/mobile/rodian_male.iff",
				 "object/mobile/rodian_female.iff",
				 "object/mobile/trandoshan_male.iff",
				 "object/mobile/trandoshan_female.iff",
				 "object/mobile/bothan_male.iff",
				 "object/mobile/bothan_female.iff",},
	lootGroups = {
      	{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "wearables_common", chance = 3000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
			}
		}
	},
	weapons = {},
	reactionStf = "@npc_reaction/townperson",
	attacks = brawlernovice
}

CreatureTemplates:addCreatureTemplate(slave, "slave")
