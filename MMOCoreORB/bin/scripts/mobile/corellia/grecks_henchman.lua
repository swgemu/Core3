grecks_henchman = Creature:new {
  objectName = "@mob/creature_names:greck_henchman",
  randomNameType = NAME_GENERIC,
  randomNameTag = true,
  socialGroup = "olag_greck",
  faction = "olag_greck",
  level = 6,
  chanceHit = 0.25,
  damageMin = 50,
  damageMax = 55,
  baseXp = 147,
  baseHAM = 180,
  baseHAMmax = 220,
  armor = 0,
  resists = {5,5,5,-1,-1,-1,-1,-1,-1},
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
  optionsBitmask = AIENABLED,
  diet = HERBIVORE,

  templates = {"thug"},
  lootGroups = {
    {
      groups = {
        {group = "junk", chance = 7000000},
        {group = "loot_kit_parts", chance = 2000000},
        {group = "tailor_components", chance = 1000000}
      }
    }
  },
  weapons = {"pirate_weapons_light"},
  conversationTemplate = "",
  reactionStf = "@npc_reaction/slang",
  attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(grecks_henchman, "grecks_henchman")
