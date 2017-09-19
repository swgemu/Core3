local ObjectManager = require("managers.object.object_manager")

huff_darklighter_missions =
	{
		{
			missionType = "escort",
			planetName = "tatooine",
			preReq = { type = "state", screenPlayState = "krayt_skull_epic_quest", state = 2 },
			primarySpawns =
			{
				{ npcTemplate = "huff_niece", npcName = "Huff's Niece" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 500 },
			}
		},
		{
			missionType = "assassinate",
			planetName = "tatooine",
			primarySpawns =
			{
				{ npcTemplate = "thug", npcName = "Slaver" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "loot",  lootGroup = "task_reward_huff_quest_krayt_dragon_skull" }
			}
		},
	}

huff_guard_missions =
	{
		{
			missionType = "deliver",
			planetName = "tatooine",
			preReq = { type = "item", itemTemplate = "object/tangible/loot/quest/rifle_quest_tusken.iff", destroy = false },
			primarySpawns =
			{
				{ npcTemplate = "huff_delivery_guy", npcName = "Delivery Guy" }
			},
			secondarySpawns = {},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/ledger_s01.iff", itemName = "A Ledger" }
			},
			rewards = {}
		},
	}

borvo_the_hutt_missions =
	{
		{
			missionType = "assassinate",
			planetName = "naboo",
			preReq = { type = "state", screenPlayState = "krayt_skull_epic_quest", state = 1 },
			primarySpawns =
			{
				{ npcTemplate = "srio", npcName = "Sri-O" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 100 },
			}
		},
		{
			missionType = "confiscate",
			planetName = "naboo",
			primarySpawns =
			{
				{ npcTemplate = "montrus", npcName = "Montrus" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/keepsakes.iff", itemName = "Precious Keep-sakes" }
			},
			rewards =
			{
				{ rewardType = "loot",  lootGroup = "task_reward_huff_quest_tusken_king_rifle" }
			}
		},
	}

thale_dusturnner_missions =
	{
		{
			missionType = "assassinate",
			planetName = "corellia",
			preReq = { type = "item", itemTemplate = "object/tangible/loot/quest/huff_quest_corsec_badge.iff", destroy = false },
			primarySpawns =
			{
				{ npcTemplate = "aldalad", npcName = "Aldalad" }
			},
			secondarySpawns =	{},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 25 },
			}
		},
		{
			missionType = "confiscate",
			planetName = "corellia",
			primarySpawns =
			{
				{ npcTemplate = "maerzen", npcName = "Maerzen" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/briefcase_s01.iff", itemName = "A Locked Briefcase" }
			},
			rewards =
			{
				{ rewardType = "loot",  lootGroup = "task_reward_huff_quest_borvos_money" }
			}
		}
	}

borvo_guard_missions =
	{
		{
			missionType = "escort",
			planetName = "naboo",
			primarySpawns =
			{
				{ npcTemplate = "dagorel", npcName = "Dagorel" }
			},
			secondarySpawns = {},
			itemSpawns = {},
			rewards =
			{
				{ rewardType = "credits", amount = 25 },
			}
		},
		{
			missionType = "confiscate",
			planetName = "naboo",
			primarySpawns =
			{
				{ npcTemplate = "frangee", npcName = "Frangee" }
			},
			secondarySpawns =	{},
			itemSpawns =
			{
				{ itemTemplate = "object/tangible/loot/misc/ledger_s01.iff", itemName = "A Ledger" }
			},
			rewards =
			{
				{ rewardType = "loot",  lootGroup = "task_reward_huff_quest_corsec_badge" }
			}
		}
	}

npcMapKraytDragonSkull =
	{
		{
			spawnData = { planetName = "tatooine", npcTemplate = "huff_darklighter", x = 0.1, z = 1.0, y = 2.4, direction = 177, cellID = 1845354, position = STAND },
			worldPosition = { x = -698, y = -6750 },
			npcNumber = 16,
			stfFile = "@epic_quest/krayt_skull/huff_darklighter",
			missions = huff_darklighter_missions
		},
		{
			spawnData = { planetName = "tatooine", npcTemplate = "huffs_guard", x = -694.1, z = 8.0, y = -6733.8, direction = -12, cellID = 0, position = STAND },
			worldPosition = { x = -694, y = -6734 },
			npcNumber = 8,
			stfFile = "@epic_quest/krayt_skull/huff_guard",
			missions = huff_guard_missions
		},
		{
			spawnData = { planetName = "naboo", npcTemplate = "borvo_the_hutt", x = -30.8, z = -0.5, y = 7.5, direction = 33, cellID = 121, position = STAND },
			worldPosition = { x = 4875, y = -4590 },
			npcNumber = 4,
			stfFile = "@epic_quest/krayt_skull/borvo_the_hutt",
			missions = borvo_the_hutt_missions
		},
		{
			spawnData = { planetName = "corellia", npcTemplate = "thale_dustrunner", x = -0.05, z = 3.08, y = -10.94, direction = 187.3, cellID = 1855463, position = STAND },
			worldPosition = { x = -209, y = -4581 },
			npcNumber = 2,
			stfFile = "@epic_quest/krayt_skull/corsec_captain",
			missions = thale_dusturnner_missions
		},
		{
			spawnData = { planetName = "naboo", npcTemplate = "borvos_guard", x = -18.4, z = -0.9, y = 18.3, direction = 173, cellID = 120, position = STAND },
			worldPosition = { x = 4888, y = -4600 },
			npcNumber = 1,
			stfFile = "@epic_quest/krayt_skull/borvo_guard",
			missions = borvo_guard_missions
		},
	}

KraytDragonSkull = ThemeParkLogic:new {
	npcMap = npcMapKraytDragonSkull,
	className = "KraytDragonSkull",
	screenPlayState = "krayt_dragon_skull",
	requiredPlanets = { "naboo", "corellia", "tatooine" },
	distance = 800
}

registerScreenPlay("KraytDragonSkull", true)

KraytSkullContainerComponent = {}

function KraytSkullContainerComponent:transferObject(pContainer, pObj, slot)
	local pPlayer = KraytDragonSkull:getObjOwner(pObj)

	if (pPlayer == nil or pContainer == nil) then
		return 0
	end

	if (SceneObject(pContainer):getObjectName() == "borvo_the_hutt") then
		if (SceneObject(pObj):getTemplateObjectPath() == "object/tangible/loot/quest/huff_quest_borvos_money.iff") then
			spatialChat(pContainer, "Good")
			CreatureObject(pPlayer):setScreenPlayState(1, "krayt_skull_epic_quest")
			
      if (not SceneObject(pObj):isPlayerCreature()) then
			 SceneObject(pObj):destroyObjectFromWorld()
			 SceneObject(pObj):destroyObjectFromDatabase()
			end
			return 1
		else
			spatialChat(pContainer, "@static_npc/naboo/borvo:notit_1")
			return 0
		end
	elseif (SceneObject(pContainer):getCustomObjectName() == "Huff Darklighter") then
		if (KraytDragonSkull:getActiveNpcNumber(pPlayer) ~= 16) then
			spatialChat(pContainer, "@epic_quest/krayt_skull/huff_darklighter:notyet")
		elseif (SceneObject(pObj):getTemplateObjectPath() == "object/tangible/loot/quest/rifle_quest_tusken.iff") then
			spatialChat(pContainer, "@epic_quest/krayt_skull/huff_darklighter:good")
			CreatureObject(pPlayer):setScreenPlayState(2, "krayt_skull_epic_quest")
			
			if (not SceneObject(pObj):isPlayerCreature()) then
			 SceneObject(pObj):destroyObjectFromWorld()
			 SceneObject(pObj):destroyObjectFromDatabase()
		  end
			return 1
		else
			spatialChat(pContainer, "@epic_quest/krayt_skull/huff_darklighter:notit")
			return 0
		end
	end

	return 0
end

function KraytSkullContainerComponent:canAddObject(pContainer, pObj, slot)
	local pPlayer = KraytDragonSkull:getObjOwner(pObj)

	if (pPlayer == nil or pContainer == nil) then
		return -1
	end

	if (SceneObject(pContainer):getObjectName() == "borvo_the_hutt" and CreatureObject(pPlayer):hasScreenPlayState(1, "krayt_skull_epic_quest")) or
		(SceneObject(pContainer):getCustomObjectName() == "Huff Darklighter" and CreatureObject(pPlayer):hasScreenPlayState(2, "krayt_skull_epic_quest")) then
		return -1
	else
		return true
	end
end

function KraytSkullContainerComponent:removeObject(pContainer, pObj, slot)
	return -1
end

function KraytDragonSkull:getObjOwner(pObj)
	if (pObj == nil) then
		return nil
	end

	local pPlayerInv = SceneObject(pObj):getParent()

	if (pPlayerInv == nil) then
		return nil
	end

	local parent = SceneObject(pPlayerInv):getParent()

	if (parent == nil) then
		return nil
	end

	if (SceneObject(parent):isCreatureObject()) then
		return parent
	end

	return nil
end

-- Custom spawnNpcs to handle setting npcs as containers for quest item turnin
function KraytDragonSkull:spawnNpcs()
	local planetName = self.planetName
	for i = 1, # self.npcMap do
		local npcSpawnData = self.npcMap[i].spawnData

		if (npcSpawnData.planetName ~= nil and npcSpawnData.planetName ~= "") then
			planetName = npcSpawnData.planetName
		end

		local pNpc = spawnMobile(npcSpawnData.planetName, npcSpawnData.npcTemplate, 1, npcSpawnData.x, npcSpawnData.z, npcSpawnData.y, npcSpawnData.direction, npcSpawnData.cellID)
		if pNpc ~= nil and npcSpawnData.position == SIT then
			CreatureObject(pNpc):setState(STATESITTINGONCHAIR)
		end

		if pNpc ~= nil and npcSpawnData.npcTemplate == "borvo_the_hutt" or npcSpawnData.npcTemplate == "huff_darklighter" then
			SceneObject(pNpc):setContainerComponent("KraytSkullContainerComponent")
		end
	end
	
	return true
end

krayt_dragon_skull_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = KraytDragonSkull
}
krayt_dragon_skull_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = KraytDragonSkull
}
