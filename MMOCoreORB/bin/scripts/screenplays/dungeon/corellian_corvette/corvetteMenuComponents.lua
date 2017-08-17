local ObjectManager = require("managers.object.object_manager")

CorvetteRoomPanelMenuComponent = { }

function CorvetteRoomPanelMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
end

function CorvetteRoomPanelMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or selectedID ~= 20) then
		return
	end

	if (SceneObject(pPlayer):getParentID() ~= SceneObject(pSceneObject):getParentID() or not CreatureObject(pPlayer):isInRangeWithObject(pSceneObject, 4)) then
		return
	end

	local panelID = SceneObject(pSceneObject):getObjectID()

	if (readData(panelID .. ":roomUnlocked") == 1) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:already_open") -- 	This door was already opened by someone else...
		return
	end

	local corvetteID = readData(SceneObject(pPlayer):getObjectID() .. "corvetteID")
	local pCorvette = getSceneObject(corvetteID)

	if (pCorvette == nil) then
		return
	end

	local roomName = readStringSharedMemory(panelID .. ":panelRoom")

	if (roomName == "meetingroom38") then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:unlock_meeting") -- You have reset the locking mechanism on the meeting room door.
		CorellianCorvette:unlockRoom(pCorvette, "meetingroom38")
		writeData(SceneObject(pPlayer):getObjectID() .. ":unlocked:meetingroom38", 1)
	elseif (roomName == "elevator57") then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:unlock_elevator") -- You have reset the locking mechanism on the elevator door.
		CorellianCorvette:unlockRoom(pCorvette, "elevator57")
		writeData(SceneObject(pPlayer):getObjectID() .. ":unlocked:elevator57", 1)
	end
	writeData(panelID .. ":roomUnlocked", 1)
end

CorvetteDestroyTerminalMenuComponent = { }

function CorvetteDestroyTerminalMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
end

function CorvetteDestroyTerminalMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or selectedID ~= 20) then
		return
	end

	if (SceneObject(pPlayer):getParentID() ~= SceneObject(pSceneObject):getParentID() or not CreatureObject(pPlayer):isInRangeWithObject(pSceneObject, 4)) then
		return
	end


	local corvetteID = readData(SceneObject(pPlayer):getObjectID() .. "corvetteID")
	local questType = readStringData("corvetteQuestType:" .. corvetteID)

	if (questType ~= "destroy") then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:does_nothing")
		return
	end

	local terminalType = readStringSharedMemory(SceneObject(pSceneObject):getObjectID() .. ":terminalType")

	if (terminalType == "engine") then
		CorvetteSui:sendEngineSui(pPlayer, pSceneObject)
	elseif (terminalType == "fuel") then
		CorvetteSui:sendFuelSui(pPlayer, pSceneObject)
	elseif (terminalType == "hyperdrive") then
		CorvetteSui:sendHyperdriveSui(pPlayer, pSceneObject)
	end
end

CorvetteKeypadMenuComponent = { }

function CorvetteKeypadMenuComponent:fillObjectMenuResponse(pKeypad, pMenuResponse, pPlayer)
end

function CorvetteKeypadMenuComponent:handleObjectMenuSelect(pKeypad, pPlayer, selectedID)
	if (pKeypad == nil or pPlayer == nil or selectedID ~= 20) then
		return
	end

	if (SceneObject(pKeypad):getParentID() ~= SceneObject(pPlayer):getParentID() or not CreatureObject(pPlayer):isInRangeWithObject(pKeypad, 4)) then
		return
	end


	local corvetteID = readData(SceneObject(pPlayer):getObjectID() .. "corvetteID")
	local pCorvette = getSceneObject(corvetteID)

	if (pCorvette == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local keypadRoom = readStringSharedMemory(SceneObject(pKeypad):getObjectID() .. ":keypadRoom")

	if (keypadRoom == "elevator57") then
		if (CorellianCorvette:readDataFromGroup(pCorvette, ":unlocked:elevator57") == 1) then
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:open") -- This door is now unlocked.
			CorellianCorvette:unlockRoom(pCorvette, "elevator57")
			CorellianCorvette:writeDataToGroup(pCorvette, ":unlocked:elevator57", 1)
		else
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:elevator_locked") -- This elevator is disabled. The Override switch is in the meeting room on this floor.
		end
	elseif (keypadRoom == "meetingroom38") then
		if (CorellianCorvette:readDataFromGroup(pCorvette, ":unlocked:meetingroom38") == 1) then
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:open") -- This door is now unlocked.
			CorellianCorvette:unlockRoom(pCorvette, "meetingroom38")
			CorellianCorvette:writeDataToGroup(pCorvette, ":unlocked:meetingroom38", 1)
		else
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:meeting_room_locked") -- This keypad is disabled. Use the SECURITY CONSOLE in the Engine Room to have it restored.
		end
	elseif (keypadRoom ~= "") then
		CorvetteSui:sendKeypadSui(pKeypad, pPlayer)
	end

end

CorvetteComputerMenuComponent = { }

function CorvetteComputerMenuComponent:fillObjectMenuResponse(pComputer, pMenuResponse, pPlayer)
end

function CorvetteComputerMenuComponent:handleObjectMenuSelect(pComputer, pPlayer, selectedID)
	if (pComputer == nil or pPlayer == nil or selectedID ~= 20) then
		return
	end

	if (SceneObject(pPlayer):getParentID() ~= SceneObject(pComputer):getParentID() or not CreatureObject(pPlayer):isInRangeWithObject(pComputer, 4)) then
		return
	end


	local corvetteID = readData(SceneObject(pPlayer):getObjectID() .. "corvetteID")
	local pCorvette = getSceneObject(corvetteID)

	if (pCorvette == nil) then
		return
	end

	local computerID = SceneObject(pComputer):getObjectID()
	local playerID = SceneObject(pPlayer):getObjectID()

	if (readData(computerID .. ":spawnedEnemies") ~= 1) then
		CorellianCorvette:spawnComputerEnemies(pCorvette, pComputer)
		writeData(computerID .. ":spawnedEnemies", 1)
	end

	local computerLabel = readStringSharedMemory(computerID .. ":computerLabel")

	if (computerLabel == "") then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:loading") -- 	Loading...
	elseif (computerLabel == "one") then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:computer_one") -- The screen is filled with number crunching. Probably the hyper drive analysis.
	elseif (computerLabel == "two") then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:armory_code") -- Printing Out Code for Armory:

		local accessCode = readData(computerID .. ":accessCode")

		if (accessCode == 0) then
			accessCode = getRandomNumber(10000, 99999)
			CorellianCorvette:writeDataToGroup(pCorvette, ":code:armorybackroom55", accessCode)
			writeData(computerID .. ":accessCode", accessCode)
		end

		CreatureObject(pPlayer):sendSystemMessage(accessCode)
	elseif (computerLabel == "three") then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:computer_three") -- Gold Screen Of Doom: Software has caused a general protection fault @ 64x11300314 Unknown Error 55113-s.
	elseif (computerLabel == "four") then
		if (readData(computerID .. ":terminalRebooted") == 1) then
			local accessCode = readData(computerID .. ":accessCode")

			if (accessCode == 0) then
				accessCode = getRandomNumber(10000, 99999)
				CorellianCorvette:writeDataToGroup(pCorvette, ":code:bridge66", accessCode)
				writeData(computerID .. ":accessCode", accessCode)
			end

			CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:bridge_code") -- Bridge Code Updated:
			CreatureObject(pPlayer):sendSystemMessage(accessCode)
		else
			local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")
			if (pInventory ~= nil) then
				local pBootDisk = getContainerObjectByTemplate(pInventory, "object/tangible/loot/dungeon/corellian_corvette/bootdisk.iff", true)

				if (pBootDisk ~= nil) then
					SceneObject(pBootDisk):destroyObjectFromWorld()
					SceneObject(pBootDisk):destroyObjectFromDatabase()
					writeData(computerID .. ":terminalRebooted", 1)
					CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:insert_disk") -- You insert the disk into the drive and the machine reboots.
				else
					local slicingSkill = CorellianCorvette:checkSlicingSkill(pPlayer)
					local sliceChance = getRandomNumber(1, 8)

					if (sliceChance > slicingSkill or readData(computerID .. ":sliceAttempted") == 1) then
						CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:reboot") -- This computer needs to be rebooted. Please insert Operations Disk #4 into the terminal.

						if (slicingSkill > 0) then
							writeData(computerID .. ":sliceAttempted", 1)
						end
					else
						writeData(computerID .. ":terminalRebooted", 1)
						CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:sliced") -- The computer was down, but your slicing skill allows you to reboot it without the disk.
					end
				end
			end
		end
	elseif (computerLabel == "five") then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:journal") -- Journal Entry #334: We've found a strange glitch with the engines and the new fuel type we're using. Apparently if you set the hyperdrive settings lower than the fuel intake, then drop the engines to their lowest power level, it's only a matter of time before the fuel pressure causes a catastrophic failure.
	elseif (computerLabel == "six") then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:officer_starboard") -- Printing Out Security Code for Officer Quarters, Starboard Side:

		local accessCode = readData(computerID .. ":accessCode")

		if (accessCode == 0) then
			accessCode = getRandomNumber(10000, 99999)
			CorellianCorvette:writeDataToGroup(pCorvette, ":code:officerquarters64", accessCode)
			writeData(computerID .. ":accessCode", accessCode)
		end

		CreatureObject(pPlayer):sendSystemMessage(accessCode)
	elseif (computerLabel == "seven") then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:officer_port") -- Printing Out Security Code for Officer Quarters, Port Side:

		local accessCode = readData(computerID .. ":accessCode")

		if (accessCode == 0) then
			accessCode = getRandomNumber(10000, 99999)
			CorellianCorvette:writeDataToGroup(pCorvette, ":code:officerquarters65", accessCode)
			writeData(computerID .. ":accessCode", accessCode)
		end

		CreatureObject(pPlayer):sendSystemMessage(accessCode)
	elseif (computerLabel == "eight") then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:prison_code") -- 	Printing Out Security Code for Prisoner quarters:

		local accessCode = readData(computerID .. ":accessCode")

		if (accessCode == 0) then
			accessCode = getRandomNumber(10000, 99999)
			CorellianCorvette:writeDataToGroup(pCorvette, ":code:officerquarters63", accessCode)
			writeData(computerID .. ":accessCode", accessCode)
		end

		CreatureObject(pPlayer):sendSystemMessage(accessCode)
	elseif (computerLabel == "nine") then -- Rebel only computer
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:droid_explanation_rebel") -- I knew this would be worth it. We've found nothing but evidence of the Alliance's treachery since we boarded and took this ship. The engine room's even filled with illegal battle droids. An electrical surge down there has made them all aggressive so I'm keeping non-essential personnel away from the area. These Rebels have got to be stopped!
	elseif (computerLabel == "ten") then -- Imperial only computer
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:droid_explanation_imperial") -- 	I tried to convince the Lieutenant that the battle droids were a bad idea, but he got such a good deal on them from the merc's that it was hard to turn down. Now they're all over the place though. I think the engine room is full of them. Some kind of malfunction or short circuit. As soon as we get near a base I'll call for a commando squad to come in and deactivate them...
	end
end
