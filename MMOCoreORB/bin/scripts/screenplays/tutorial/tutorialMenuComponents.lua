local ObjectManager = require("managers.object.object_manager")

tutorialInsuranceTerminal = {  }

function tutorialInsuranceTerminal:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
end

function tutorialInsuranceTerminal:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (readData(SceneObject(pPlayer):getObjectID() .. ":tutorial:insuranceTerminalUsed") == 1) then
		return 0
	end

	if (selectedID == 20) then
		writeData(SceneObject(pPlayer):getObjectID() .. ":tutorial:insuranceTerminalUsed", 1)
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:declare_insured")
	end
	return 0
end

tutorialCloningTerminal = {  }

function tutorialCloningTerminal:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local response = LuaObjectMenuResponse(pMenuResponse)
	response:addRadialMenuItem(20, 3, "@ui_radial:item_use_terminal_cloning")
end

function tutorialCloningTerminal:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (readData(SceneObject(pPlayer):getObjectID() .. ":tutorial:cloningTerminalUsed") == 1) then
		return 0
	end

	if (selectedID == 20) then
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:declare_cloned")
		writeData(SceneObject(pPlayer):getObjectID() .. ":tutorial:cloningTerminalUsed", 1)
		createEvent(1000, "TutorialScreenPlay", "handleRoomFive", pPlayer, "")
	end

	return 0
end

tutorialMissionTerminal = {  }

function tutorialMissionTerminal:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
end

function tutorialMissionTerminal:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (selectedID == 20) then
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:mission_terminal")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_00_mission_terminal.snd")

		local giverID = readData(SceneObject(pPlayer):getObjectID() .. ":tutorial:roomTenMissionGiver")
		local pMissionGiver = getSceneObject(giverID)

		if (pMissionGiver ~= nil) then
			if (readData(SceneObject(pPlayer):getObjectID() .. ":tutorial:hasGottenMission") == 1) then
				spatialChat(pMissionGiver, "@newbie_tutorial/newbie_convo:mission_repeat")
			else
				spatialChat(pMissionGiver, "@newbie_tutorial/newbie_convo:mission_hail")
			end
		end
	end

	return 0
end