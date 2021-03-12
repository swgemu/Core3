criminal_target_noble = Creature:new {
  objectName = "@mob/creature_names:noble",
  randomNameType = NAME_GENERIC,
  randomNameTag = true,
  socialGroup = "townsperson",
  faction = "townsperson",
  level = 6,
  chanceHit = 0.250000,
  damageMin = 50,
  damageMax = 55,
  baseXp = 113,
  baseHAM = 180,
  baseHAMmax = 220,
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
  optionsBitmask = AIENABLED,
  diet = HERBIVORE,


  templates = {"noble"},
  lootGroups = {
    {
      groups = {
        {group = "task_loot_medallion_dark_jedi", chance = 10000000}
      },
      lootChance = 10000000
    }
  },
  weapons = {"pirate_weapons_light"},
  conversationTemplate = "",
  attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(criminal_target_noble, "criminal_target_noble")
