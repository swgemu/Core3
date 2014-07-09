arven_wendik_missions =
  {
    {
      missionType = "deliver",
      primarySpawns =
      {
        { npcTemplate = "alowi_fintz", planetName = "naboo", npcName = "Alowi Fintz" }
      },
      secondarySpawns = {},
      itemSpawns =
      {
        { itemTemplate = "object/tangible/mission/quest_item/arven_wendik_q1_needed.iff", itemName = "Forged Permits" }
      },
      rewards =
      {
        { rewardType = "credits", amount = 25 },
      }
    },
    {
      missionType = "escort",
      primarySpawns =
      {
        { npcTemplate = "grel_rommo", planetName = "naboo", npcName = "Grel Rommo" }
      },
      secondarySpawns =
      {
        { npcTemplate = "stormtrooper", planetName = "naboo", npcName = "" },
        { npcTemplate = "stormtrooper", planetName = "naboo", npcName = "" },
        { npcTemplate = "stormtrooper", planetName = "naboo", npcName = "" },
      },
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 50 },
      }
    },
    {
      missionType = "escort",
      primarySpawns =
      {
        { npcTemplate = "needia_solum", planetName = "naboo", npcName = "Needia Solum" }
      },
      secondarySpawns =
      {
        { npcTemplate = "imperial_warrant_officer_i", planetName = "naboo", npcName = "" },
        { npcTemplate = "stormtrooper", planetName = "naboo", npcName = "" },
        { npcTemplate = "stormtrooper", planetName = "naboo", npcName = "" },
        { npcTemplate = "stormtrooper", planetName = "naboo", npcName = "" },
      },
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 100 },
      }
    }
  }

npcMapArvenWendik =
  {
    {
      spawnData = { planetName = "naboo", npcTemplate = "arven_wendik", x = 4713.5, z = 330, y = -1432.5, direction = -99, cellID = 0, position = STAND },
      worldPosition = { x = 4712, y = -1432 },
      npcNumber = 1,
      stfFile = "@static_npc/naboo/arven_wendik",
      missions = arven_wendik_missions
    }
  }

ArvenWendik = ThemeParkLogic:new {
  numberOfActs = 1,
  npcMap = npcMapArvenWendik,
  className = "ArvenWendik",
  screenPlayState = "arven_wendik_quest",
  distance = 600,
  faction = FACTIONREBEL
}

registerScreenPlay("ArvenWendik", true)

arven_wendik_mission_giver_conv_handler = mission_giver_conv_handler:new {
  themePark = ArvenWendik
}
arven_wendik_mission_target_conv_handler = mission_target_conv_handler:new {
  themePark = ArvenWendik
}