gungan_reject_quest_bardo = Creature:new {
	objectName = "@mob/creature_names:mordran_gungan_reject",
	socialGroup = "borvo",
	faction = "borvo",
	level = 35,
	chanceHit = 0.41,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3460,
	baseHAM = 8800,
	baseHAMmax = 10800,
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
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/gungan_s03_male.iff"},
	lootGroups = {
		{
			groups = {
					{group = "task_loot_bank_codes_quest_bardo", chance = 10000000}
				},
			lootChance = 10000000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "bardo_klinj_mission_target_convotemplate",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(gungan_reject_quest_bardo, "gungan_reject_quest_bardo")
