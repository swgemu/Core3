local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local SpawnMobiles = require("utils.spawn_mobiles")

local SPAWN_MOBILES_STRING = "_spawn_mobiles"
local IN_USE_STRING = "_in_use"
local NUMBER_OF_SPAWNS_STRING = "_number_of_spawns"
local PREFIX_IN_USE = 0x14053
local PREFIX_FREE = 0

describe("Spawn Mobile", function()
	local prefix = "myPrefix"
	local pCreatureObject = { "creatureObjectPointer" }
	local x = 33
	local y = 22
	local zoneName = "testzone"
	local mobileTemplate = "template_name"
	local spawnList
	local spawnPoints
	local playerID = 12345678
	local sceneObjectPlayer
	local playerParentID = 0
	local pSpawnedObject1 = { "spawnedObjectPointer1" }
	local pSpawnedObject2 = { "spawnedObjectPointer2" }
	local pSpawnedObject3 = { "spawnedObjectPointer3" }
	local pSpawnedObject4 = { "spawnedObjectPointer4" }
	local pSpawnedObject5 = { "spawnedObjectPointer5" }
	local spawnedObject1
	local spawnedObject2
	local spawnedObject3
	local spawnedObject4
	local spawnedObject5
	local spawnObject1Id = 1234
	local spawnObject2Id = 2345
	local spawnObject3Id = 3456
	local spawnObject4Id = 4567
	local spawnObject5Id = 5678
	local spawnedMobilesList
	local mobileObjectIDs = {
		spawnObject1Id,
		spawnObject2Id,
		spawnObject3Id,
		spawnObject4Id,
		spawnObject5Id
	}

	setup(function()
		DirectorManagerMocks.mocks.setup()
	end)

	teardown(function()
		DirectorManagerMocks.mocks.teardown()
	end)

	before_each(function()
		DirectorManagerMocks.mocks.before_each()

		spawnList = {
			{ template = mobileTemplate, minimumDistance = 32, maximumDistance = 64, referencePoint = 0 },
			{ template = mobileTemplate, minimumDistance = 16, maximumDistance = 64, referencePoint = 0 },
			{ template = mobileTemplate, minimumDistance = 32, maximumDistance = 48, referencePoint = 1 },
			{ template = mobileTemplate, minimumDistance = 32, maximumDistance = 64, referencePoint = 0 },
			{ template = mobileTemplate, minimumDistance = 32, maximumDistance = 64, referencePoint = 4 }
		}
		spawnPoints = {
			{ 1, 2, 3 },
			{ 4, 5, 6 },
			{ 7, 8, 9 },
			{ 10, 11, 12 },
			{ 13, 14, 15 }
		}
		spawnedMobilesList = {
			pSpawnedObject1,
			pSpawnedObject2,
			pSpawnedObject3,
			pSpawnedObject4,
			pSpawnedObject5
		}
		mobileObjectIDs = {
			spawnObject1Id,
			spawnObject2Id,
			spawnObject3Id,
			spawnObject4Id,
			spawnObject5Id
		}

		sceneObjectPlayer = {}
		sceneObjectPlayer.getObjectID = spy.new(function() return playerID end)
		sceneObjectPlayer.getWorldPositionX = spy.new(function() return x end)
		sceneObjectPlayer.getWorldPositionY = spy.new(function() return y end)
		sceneObjectPlayer.getZoneName = spy.new(function() return zoneName end)
		sceneObjectPlayer.getParentID = spy.new(function() return playerParentID end)
		DirectorManagerMocks.sceneObjects[pCreatureObject] = sceneObjectPlayer

		spawnedObject1 = {}
		spawnedObject1.destroyObjectFromWorld = spy.new(function() end)
		spawnedObject1.getObjectID = spy.new(function() return spawnObject1Id end)
		DirectorManagerMocks.sceneObjects[pSpawnedObject1] = spawnedObject1

		spawnedObject2 = {}
		spawnedObject2.destroyObjectFromWorld = spy.new(function() end)
		spawnedObject2.getObjectID = spy.new(function() return spawnObject2Id end)
		DirectorManagerMocks.sceneObjects[pSpawnedObject2] = spawnedObject2

		spawnedObject3 = {}
		spawnedObject3.destroyObjectFromWorld = spy.new(function() end)
		spawnedObject3.getObjectID = spy.new(function() return spawnObject3Id end)
		DirectorManagerMocks.sceneObjects[pSpawnedObject3] = spawnedObject3

		spawnedObject4 = {}
		spawnedObject4.destroyObjectFromWorld = spy.new(function() end)
		spawnedObject4.getObjectID = spy.new(function() return spawnObject4Id end)
		DirectorManagerMocks.sceneObjects[pSpawnedObject4] = spawnedObject4

		spawnedObject5 = {}
		spawnedObject5.destroyObjectFromWorld = spy.new(function() end)
		spawnedObject5.getObjectID = spy.new(function() return spawnObject5Id end)
		DirectorManagerMocks.sceneObjects[pSpawnedObject5] = spawnedObject5
	end)

	describe("Interface functions", function()
		describe("spawnMobiles", function()
			local realIsPrefixFree
			local realSpawnMobilesWithPrefix

			setup(function()
				realIsPrefixFree = SpawnMobiles.isPrefixFree
				realSpawnMobilesWithPrefix = SpawnMobiles.spawnMobilesWithPrefix
			end)

			teardown(function()
				SpawnMobiles.isPrefixFree = realIsPrefixFree
				SpawnMobiles.spawnMobilesWithPrefix = realSpawnMobilesWithPrefix
			end)

			before_each(function()
				SpawnMobiles.isPrefixFree = spy.new(function() end)
				SpawnMobiles.spawnMobilesWithPrefix = spy.new(function() end)
			end)

			describe("When called with appropriate arguments", function()
				it("Should check if the prefix is free to use.", function()
					SpawnMobiles.spawnMobiles(pCreatureObject, prefix, spawnList)

					assert.spy(SpawnMobiles.isPrefixFree).was.called_with(pCreatureObject, prefix)
				end)

				describe("and the prefix is free to use", function()
					before_each(function()
						SpawnMobiles.isPrefixFree = spy.new(function() return true end)
						SpawnMobiles.spawnMobilesWithPrefix = spy.new(function() return spawnedMobilesList end)
					end)

					it("Should call spawnMobilesWithPrefix function.", function()
						SpawnMobiles.spawnMobiles(pCreatureObject, prefix, spawnList)

						assert.spy(SpawnMobiles.spawnMobilesWithPrefix).was.called_with(pCreatureObject, prefix, spawnList, false)
					end)

					it("Should return a list of the spawned mobiles.", function()
						assert.same(spawnedMobilesList, SpawnMobiles.spawnMobiles(pCreatureObject, prefix, spawnList))
					end)
				end)

				describe("and the prefix is in use", function()
					before_each(function()
						SpawnMobiles.isPrefixFree = spy.new(function() return false end)
					end)

					it("Should not call spawnMobilesWithPrefix function.", function()
						SpawnMobiles.spawnMobiles(pCreatureObject, prefix, spawnList)

						assert.spy(SpawnMobiles.spawnMobilesWithPrefix).was.not_called()
					end)

					it("Should return nil.", function()
						assert.is_nil(SpawnMobiles.spawnMobiles(pCreatureObject, prefix, spawnList))
					end)
				end)
			end)
		end)

		describe("despawnMobiles", function()
			describe("When called with a prefix", function()
				local realGetSpawnedMobiles
				local realDespawnMobilesInList

				setup(function()
					realGetSpawnedMobiles = SpawnMobiles.getSpawnedMobiles
					realDespawnMobilesInList = SpawnMobiles.despawnMobilesInList
				end)

				teardown(function()
					SpawnMobiles.getSpawnedMobiles = realGetSpawnedMobiles
					SpawnMobiles.despawnMobilesInList = realDespawnMobilesInList
				end)

				before_each(function()
					SpawnMobiles.getSpawnedMobiles = spy.new(function() return spawnedMobilesList end)
					SpawnMobiles.despawnMobilesInList = spy.new(function() end)
				end)

				it("Should get a list with pointers to the spawned mobiles from the prefix.", function()
					SpawnMobiles.despawnMobiles(pCreatureObject, prefix)

					assert.spy(SpawnMobiles.getSpawnedMobiles).was.called_with(pCreatureObject, prefix)
				end)

				it("Should call the despawnMobilesInList function.", function()
					SpawnMobiles.despawnMobiles(pCreatureObject, prefix)

					assert.spy(SpawnMobiles.despawnMobilesInList).was.called_with(spawnedMobilesList)
				end)

				it("Should set the in use variable for the prefix to not in use.", function()
					SpawnMobiles.despawnMobiles(pCreatureObject, prefix)

					assert.spy(writeData).was.called_with(playerID .. prefix .. SPAWN_MOBILES_STRING .. IN_USE_STRING, PREFIX_FREE)
				end)
			end)
		end)

		describe("getSpawnedMobiles", function()
			describe("When called with a player and a prefix", function()
				local realIsPrefixFree
				local realGetSpawnedMobilePointersList

				setup(function()
					realIsPrefixFree = SpawnMobiles.isPrefixFree
					realGetSpawnedMobilePointersList = SpawnMobiles.getSpawnedMobilePointersList
				end)

				teardown(function()
					SpawnMobiles.isPrefixFree = realIsPrefixFree
					SpawnMobiles.getSpawnedMobilePointersList = realGetSpawnedMobilePointersList
				end)

				before_each(function()
					SpawnMobiles.isPrefixFree = spy.new(function() return true end)
					SpawnMobiles.getSpawnedMobilePointersList = spy.new(function() return spawnedMobilesList end)
				end)

				it("Should check if the prefix is in use.", function()
					SpawnMobiles.getSpawnedMobiles(pCreatureObject, prefix)

					assert.spy(SpawnMobiles.isPrefixFree).was.called_with(pCreatureObject, prefix)
				end)

				describe("and the prefix is not in use", function()
					it("Should return nil.", function()
						assert.is_nil(SpawnMobiles.getSpawnedMobiles(pCreatureObject, prefix))
					end)
				end)

				describe("and the prefix is in use", function()
					before_each(function()
						SpawnMobiles.isPrefixFree = spy.new(function() return false end)
					end)

					it("Should call the getSpawnedMobilesPointersList function.", function()
					SpawnMobiles.getSpawnedMobiles(pCreatureObject, prefix)

					assert.spy(SpawnMobiles.getSpawnedMobilePointersList).was.called_with(pCreatureObject, prefix)
					end)

					it("Should return a list with pointers to the spawned mobiles.", function()
						assert.same(spawnedMobilesList, SpawnMobiles.getSpawnedMobiles(pCreatureObject, prefix))
					end)
				end)
			end)
		end)

		describe("isFromSpawn", function()
			describe("When called with a pointer to a creature and a prefix", function()
				local realGetSpawnedMobiles

				setup(function()
					realGetSpawnedMobiles = SpawnMobiles.getSpawnedMobiles
				end)

				teardown(function()
					SpawnMobiles.getSpawnedMobiles = realGetSpawnedMobiles
				end)

				before_each(function()
					SpawnMobiles.getSpawnedMobiles = spy.new(function() return spawnedMobilesList end)
				end)

				it("Should get the list of spawned mobiles for the prefix.", function()
					SpawnMobiles.isFromSpawn(pCreatureObject, prefix, pSpawnedObject1)

					assert.spy(SpawnMobiles.getSpawnedMobiles).was.called_with(pCreatureObject, prefix)
				end)

				it("Should get the object id of the creature.", function()
					SpawnMobiles.isFromSpawn(pCreatureObject, prefix, pSpawnedObject1)

					assert.spy(spawnedObject1.getObjectID).was.called_with(spawnedObject1)
				end)

				describe("and the creature was spawned with the prefix", function()
					it("Should return true.", function()
						assert.is_true(SpawnMobiles.isFromSpawn(pCreatureObject, prefix, pSpawnedObject1))
					end)
				end)

				describe("and the creature was not spawned with the prefix", function()
					it("Should return false.", function()
						assert.is_false(SpawnMobiles.isFromSpawn(pCreatureObject, prefix, pCreatureObject))
					end)

					it("Should get the object id of every mobile in the spawn.", function()
						SpawnMobiles.isFromSpawn(pCreatureObject, prefix, pCreatureObject)

						assert.spy(spawnedObject1.getObjectID).was.called_with(spawnedObject1)
						assert.spy(spawnedObject2.getObjectID).was.called_with(spawnedObject2)
						assert.spy(spawnedObject3.getObjectID).was.called_with(spawnedObject3)
						assert.spy(spawnedObject4.getObjectID).was.called_with(spawnedObject4)
						assert.spy(spawnedObject5.getObjectID).was.called_with(spawnedObject5)
					end)
				end)
			end)
		end)
	end)

	describe("Private functions", function()
		describe("isPrefixFree", function()
			describe("When called with a prefix", function()
				it("Should read the <prefix>_spawn_mobiles_in_use data.", function()
					SpawnMobiles.isPrefixFree(pCreatureObject, prefix)

					assert.spy(readData).was.called_with(playerID .. prefix .. SPAWN_MOBILES_STRING .. IN_USE_STRING)
				end)

				describe("and the readData for the prefix returns the in use value", function()
					before_each(function()
						readData = spy.new(function() return PREFIX_IN_USE end)
					end)

					it("Should return false.", function()
						assert.is_false(SpawnMobiles.isPrefixFree(pCreatureObject, prefix))
					end)
				end)

				describe("and the readData for the prefix returns zero", function()
					it("Should return true.", function()
						assert.is_true(SpawnMobiles.isPrefixFree(pCreatureObject, prefix))
					end)
				end)
			end)
		end)

		describe("spawnMobilesWithPrefix", function()
			describe("When called with a player", function()
				local realGenerateSpawnPoints
				local realGenerateEncounterObjects

				setup(function()
					realGenerateSpawnPoints = SpawnMobiles.generateSpawnPoints
					realGenerateEncounterObjects = SpawnMobiles.generateMobileObjects
				end)

				teardown(function()
					SpawnMobiles.generateSpawnPoints = realGenerateSpawnPoints
					SpawnMobiles.generateMobileObjects = realGenerateEncounterObjects
				end)

				before_each(function()
					SpawnMobiles.generateSpawnPoints = spy.new(function() return nil end)
					SpawnMobiles.generateMobileObjects = spy.new(function() return spawnedMobilesList end)
				end)

				it("Should get spawn points for all objects in the encounter.", function()
					SpawnMobiles.spawnMobilesWithPrefix(pCreatureObject, prefix, spawnList, false)

					assert.spy(SpawnMobiles.generateSpawnPoints).was.called_with(pCreatureObject, spawnList, false)
				end)

				describe("and a list of spawn points are returned from the generateSpawnPoints function", function()
					before_each(function()
						SpawnMobiles.generateSpawnPoints = spy.new(function() return spawnPoints end)
					end)

					it("Should spawn the encounter objects.", function()
						SpawnMobiles.spawnMobilesWithPrefix(pCreatureObject, prefix, spawnList, false)

						assert.spy(SpawnMobiles.generateMobileObjects).was.called_with(pCreatureObject, prefix, spawnList, spawnPoints)
					end)

					it("Should return the list of spawned mobiles from the generateMobileObjects function.", function()
						assert.same(spawnedMobilesList, SpawnMobiles.spawnMobilesWithPrefix(pCreatureObject, prefix, spawnList, false))
					end)
				end)

				describe("and nil is returned from the generateSpawnPoints function", function()
					it("Should not spawn the encounter objects.", function()
						SpawnMobiles.spawnMobilesWithPrefix(pCreatureObject, prefix, spawnList, false)

						assert.spy(SpawnMobiles.generateMobileObjects).was.not_called()
					end)

					it("Should return nil.", function()
						assert.is_nil(SpawnMobiles.spawnMobilesWithPrefix(pCreatureObject, prefix, spawnList, false))
					end)
				end)
			end)
		end)

		describe("generateSpawnPoints", function()
			describe("When called with a player object", function()
				local realSpawnObjectList
				local realGetSpawnPointParameters

				setup(function()
					realSpawnObjectList = SpawnMobiles.spawnObjectList
					realGetSpawnPointParameters = SpawnMobiles.getSpawnPointParameters
				end)

				teardown(function()
					SpawnMobiles.spawnObjectList = realSpawnObjectList
					SpawnMobiles.getSpawnPointParameters = realGetSpawnPointParameters
				end)

				before_each(function()
					SpawnMobiles.getSpawnPointParameters = spy.new(function(pCO, mobileList, spawnPointList, no)
						assert.same(pCreatureObject, pCO)
						assert.is_not_nil(spawnPointList)
						return nil
					end)
				end)

				it("Should get the spawn point parameters.", function()
					SpawnMobiles.generateSpawnPoints(pCreatureObject, spawnList, false)

					assert.spy(SpawnMobiles.getSpawnPointParameters).was.called()
				end)

				describe("and nil is returned from the getSpawnPointParameters function", function()
					it("Should return nil.", function()
						assert.same(nil, SpawnMobiles.generateSpawnPoints(pCreatureObject, spawnList, false))
					end)
				end)

				describe("and spawn point parameters are returned from the getSpawnPointParameters function", function()
					local expectedNo
					local spawnPointParameterList = {
						{ x = 1, y = 2, min = 3, max = 4 },
						{ x = 5, y = 6, min = 7, max = 8 },
						{ x = 9, y = 10, min = 11, max = 12 },
						{ x = 13, y = 14, min = 15, max = 16 },
						{ x = 17, y = 18, min = 19, max = 20 }
					}
					local spawnPointList = {
						{ 1, 2, 3 },
						{ 4, 5, 6 },
						{ 7, 8, 9 },
						{ 10, 11, 12 },
						{ 13, 14, 15 }
					}

					before_each(function()
						expectedNo = 1
						SpawnMobiles.getSpawnPointParameters = spy.new(function(pCO, mobileList, spawnPointList, no)
							assert.same(pCreatureObject, pCO)
							assert.same(spawnList, mobileList)
							assert.is_not_nil(spawnPointList)
							assert.same(expectedNo, no)
							expectedNo = expectedNo + 1
							return spawnPointParameterList[no]
						end)
						getSpawnPoint = spy.new(function(pCO, x, y, min, max, force)
							assert.same(pCreatureObject, pCO)
							assert.same(spawnPointParameterList[expectedNo - 1]["x"], x)
							assert.same(spawnPointParameterList[expectedNo - 1]["y"], y)
							assert.same(spawnPointParameterList[expectedNo - 1]["min"], min)
							assert.same(spawnPointParameterList[expectedNo - 1]["max"], max)
							assert.same(false, force)
							return spawnPointList[expectedNo - 1]
						end)
					end)

					it("Should call getSpawnPointParameters one time per object to spawn.", function()
						SpawnMobiles.generateSpawnPoints(pCreatureObject, spawnList, false)

						assert.spy(SpawnMobiles.getSpawnPointParameters).was.called(5)
					end)

					it("Should call getSpawnPoint one time per object to spawn.", function()
						SpawnMobiles.generateSpawnPoints(pCreatureObject, spawnList, false)

						assert.spy(getSpawnPoint).was.called(5)
					end)

					describe("and getSpawnPoint returns nil", function()
						before_each(function()
							getSpawnPoint = spy.new(function() return nil end)
						end)

						it("Should return nil.", function()
							assert.same(nil, SpawnMobiles.generateSpawnPoints(pCreatureObject, spawnList, false))
						end)
					end)

					describe("and a spawn point is returned from getSpawnPoint", function()
						it("Should return a list of spawn points.", function()
							assert.same(spawnPointList, SpawnMobiles.generateSpawnPoints(pCreatureObject, spawnList, false))
						end)
					end)
				end)
			end)
		end)

		describe("getSpawnPointParameters", function()
			describe("when called with spawnObjectNumber equal to 1", function()
				it("Should return the min and max parameters from the spawn object list for the current spawnObjectNumber.", function()
					local parameters = SpawnMobiles.getSpawnPointParameters(pCreatureObject, spawnList, nil, 1)

					assert.same(spawnList[1]["minimumDistance"], parameters["min"])
					assert.same(spawnList[1]["maximumDistance"], parameters["max"])
				end)

				it("Should return, x and y coordinates from the player.", function()
					local parameters = SpawnMobiles.getSpawnPointParameters(pCreatureObject, spawnList, nil, 1)

					assert.same(x, parameters["x"])
					assert.same(y, parameters["y"])
				end)

				describe("and the spawn object list indicates that the spawn point should not be around the player", function()
					before_each(function()
						spawnList[1]["spawnedAroundPlayer"] = false
					end)

					after_each(function()
						spawnList[1]["spawnedAroundPlayer"] = true
					end)

					it("Should still return, x and y coordinates from the player.", function()
						local parameters = SpawnMobiles.getSpawnPointParameters(pCreatureObject, spawnList, nil, 1)

						assert.same(x, parameters["x"])
						assert.same(y, parameters["y"])
					end)
				end)
			end)

			describe("When called with spawnObjectNumber equal to or higher than 2", function()
				it("Should return the min and max parameters from the spawn object list for the current spawnObjectNumber.", function()
					local parameters = SpawnMobiles.getSpawnPointParameters(pCreatureObject, spawnList, spawnPoints, 2)

					assert.same(spawnList[2]["minimumDistance"], parameters["min"])
					assert.same(spawnList[2]["maximumDistance"], parameters["max"])
				end)

				describe("and the list item in the spawn object list indicates to use the player as center", function()
					it("Should return, x and y coordinates from the player.", function()
						local parameters = SpawnMobiles.getSpawnPointParameters(pCreatureObject, spawnList, spawnPoints, 2)

						assert.same(x, parameters["x"])
						assert.same(y, parameters["y"])
					end)
				end)

				describe("and the list item in the spawn object list indicates to not use the player as center", function()
					it("Should return, x and y coordinates from the first spawn point.", function()
						local parameters = SpawnMobiles.getSpawnPointParameters(pCreatureObject, spawnList, spawnPoints, 3)

						assert.same(spawnPoints[1][1], parameters["x"])
						assert.same(spawnPoints[1][3], parameters["y"])
					end)
				end)
			end)

			describe("When called with a spawn object number that is less than 1", function()
				it("Should return nil", function()
					assert.is_nil(SpawnMobiles.getSpawnPointParameters(pCreatureObject, spawnList, nil, 0))
				end)
			end)

			describe("When called with a spawn object number that is more than the defined number of spawn objects", function()
				it("Should return nil", function()
					assert.is_nil(SpawnMobiles.getSpawnPointParameters(pCreatureObject, spawnList, nil, 6))
				end)
			end)

			describe("When called with a spawn list containing a mobile spawn with a reference point that is negative", function()
				before_each(function()
					spawnList[1]["referencePoint"] = -1
				end)

				after_each(function()
					spawnList[1]["referencePoint"] = 0
				end)

				it("Should return nil", function()
					assert.is_nil(SpawnMobiles.getSpawnPointParameters(pCreatureObject, spawnList, nil, 1))
				end)
			end)

			describe("When called with a spawn list containing a mobile spawn with a reference point that is not zero and the spawnPoint list is nil", function()
				before_each(function()
					spawnList[1]["referencePoint"] = 1
				end)

				after_each(function()
					spawnList[1]["referencePoint"] = 0
				end)

				it("Should return nil", function()
					assert.is_nil(SpawnMobiles.getSpawnPointParameters(pCreatureObject, spawnList, nil, 1))
				end)
			end)

			describe("When called with a spawn list containing a mobile spawn with a reference point that is higher than the number of spawn points in the list", function()
				before_each(function()
					spawnList[1]["referencePoint"] = 6
				end)

				after_each(function()
					spawnList[1]["referencePoint"] = 0
				end)

				it("Should return nil", function()
					assert.is_nil(SpawnMobiles.getSpawnPointParameters(pCreatureObject, spawnList, spawnPoints, 1))
				end)
			end)
		end)

		describe("generateMobileObjects", function()
			local realSpawnMobileObjects
			local realSaveSpawnedMobileObjects
			local spawnedMobilesList = { { "spawnedObject1" }, { "spawnedObject2" }, { "spawnedObject3" } }

			setup(function()
				realSpawnMobileObjects = SpawnMobiles.spawnMobileObjects
				realSaveSpawnedMobileObjects = SpawnMobiles.saveSpawnedMobileObjects
			end)

			teardown(function()
				SpawnMobiles.spawnMobileObjects = realSpawnMobileObjects
				SpawnMobiles.saveSpawnedMobileObjects = realSaveSpawnedMobileObjects
			end)

			before_each(function()
				SpawnMobiles.spawnMobileObjects = spy.new(function() return spawnedMobilesList end)
				SpawnMobiles.saveSpawnedMobileObjects = spy.new(function() end)
			end)

			it("Should spawn the encounter objects.", function()
				SpawnMobiles.generateMobileObjects(pCreatureObject, prefix, spawnList, spawnPoints)

				assert.spy(SpawnMobiles.spawnMobileObjects).was.called_with(pCreatureObject, spawnList, spawnPoints)
			end)

			describe("and all objects could be spawned", function()
				it("Should save the spawned the encounter objects on the player.", function()
					SpawnMobiles.generateMobileObjects(pCreatureObject, prefix, spawnList, spawnPoints)

					assert.spy(SpawnMobiles.saveSpawnedMobileObjects).was.called_with(pCreatureObject, prefix, spawnedMobilesList)
				end)

				it("Should return a list with pointers to the spawned mobiles.", function()
					assert.same(spawnedMobilesList, SpawnMobiles.generateMobileObjects(pCreatureObject, prefix, spawnList, spawnPoints))
				end)
			end)

			describe("and non of the objects could be spawned", function()
				before_each(function()
					SpawnMobiles.spawnMobileObjects = spy.new(function() return nil end)
				end)

				it("Should not save the spawned the encounter objects on the player.", function()
					SpawnMobiles.generateMobileObjects(pCreatureObject, prefix, spawnList, spawnPoints)

					assert.spy(SpawnMobiles.saveSpawnedMobileObjects).was.not_called()
				end)

				it("Should return nil.", function()
					assert.is_nil(SpawnMobiles.generateMobileObjects(pCreatureObject, prefix, spawnList, spawnPoints))
				end)
			end)
		end)

		describe("spawnMobileObjects", function()
			describe("When called with a player and a list of spawn points.", function()
				local callNumber

				before_each(function()
					callNumber = 1

					spawnMobile = spy.new(function(zoneName, templateName, respawnTime, x, z, y, heading, parentID)
						assert.same(zoneName, zoneName)
						assert.same(mobileTemplate, templateName)
						assert.same(0, respawnTime)
						assert.same(spawnPoints[callNumber][1], x)
						assert.same(spawnPoints[callNumber][2], z)
						assert.same(spawnPoints[callNumber][3], y)
						assert.same(0, heading)
						assert.same(playerParentID, parentID)
						callNumber = callNumber + 1

						return spawnedMobilesList[callNumber - 1]
					end)
				end)

				it("Should spawn an object per spawn point.", function()
					SpawnMobiles.spawnMobileObjects(pCreatureObject, spawnList, spawnPoints)

					assert.spy(spawnMobile).was.called(5)
				end)

				describe("and all objects could be spawned", function()
					it("Should return a list with pointers to all spawned objects.", function()
						assert.same(spawnedMobilesList, SpawnMobiles.spawnMobileObjects(pCreatureObject, spawnList, spawnPoints))
					end)
				end)

				describe("and one of the objects could not be spawned", function()
					before_each(function()
						spawnedMobilesList = {
							pSpawnedObject1,
							pSpawnedObject2,
							nil,
							nil,
							nil
						}
					end)

					it("Should return nil.", function()
						assert.is_nil(SpawnMobiles.spawnMobileObjects(pCreatureObject, spawnList, spawnPoints))
					end)

					it("Should destroy all already succesfully spawned objects.", function()
						SpawnMobiles.spawnMobileObjects(pCreatureObject, spawnList, spawnPoints)

						assert.spy(spawnedObject1.destroyObjectFromWorld).was.called_with(spawnedObject1)
						assert.spy(spawnedObject2.destroyObjectFromWorld).was.called_with(spawnedObject2)
					end)
				end)

				describe("and one of the objects, not the last one, could not be spawned", function()
					before_each(function()
						spawnedMobilesList = {
							pSpawnedObject1,
							nil,
							pSpawnedObject3,
							pSpawnedObject4,
							pSpawnedObject5
						}
					end)

					it("Should not spawn the last object.", function()
						SpawnMobiles.spawnMobileObjects(pCreatureObject, spawnList, spawnPoints)

						assert.spy(spawnMobile).was.called(2)
					end)
				end)
			end)
		end)

		describe("saveSpawnedEncounterObjects", function()
			describe("When called with a player and a list of spawned encounter objects.", function()
				local callNumber
				local spawnedMobilesList = {
					pSpawnedObject1,
					pSpawnedObject2,
					pSpawnedObject3,
					pSpawnedObject4,
					pSpawnedObject5
				}

				before_each(function()
					callNumber = 0
					writeData = spy.new(function(key, value)
						if callNumber == 0 then
							assert.same(playerID .. prefix .. SPAWN_MOBILES_STRING .. IN_USE_STRING, key)
							assert.same(PREFIX_IN_USE, value)
						elseif callNumber == 1 then
							assert.same(playerID .. prefix .. SPAWN_MOBILES_STRING .. NUMBER_OF_SPAWNS_STRING, key)
							assert.same(table.getn(spawnedMobilesList), value)
						else
							assert.same(playerID .. prefix .. SPAWN_MOBILES_STRING .. (callNumber - 1), key)
							assert.same(mobileObjectIDs[callNumber - 1], value)
						end
						callNumber = callNumber + 1
					end)
				end)

				it("Should save each object id on the player witht the encounter name as prefix and a running number", function()
					SpawnMobiles.saveSpawnedMobileObjects(pCreatureObject, prefix, spawnedMobilesList)

					assert.spy(writeData).was.called(7)
				end)
			end)
		end)

		describe("getSpawnedMobilePointersList", function()
			describe("When called with a player and a prefix", function()
				local callNumberReadData
				local callNumberGetSceneObject

				before_each(function()
					callNumberReadData = 0
					readData = spy.new(function(key)
						callNumberReadData = callNumberReadData + 1
						if callNumberReadData == 1 then
							assert.same(playerID .. prefix .. SPAWN_MOBILES_STRING .. NUMBER_OF_SPAWNS_STRING, key)
							return table.getn(mobileObjectIDs)
						else
							assert.same(playerID .. prefix .. SPAWN_MOBILES_STRING .. (callNumberReadData - 1), key)
							return mobileObjectIDs[callNumberReadData - 1]
						end
					end)

					callNumberGetSceneObject = 1
					getSceneObject = spy.new(function(id)
						assert.same(mobileObjectIDs[callNumberGetSceneObject], id)
						callNumberGetSceneObject = callNumberGetSceneObject + 1
						return spawnedMobilesList[callNumberGetSceneObject - 1]
					end)
				end)

				it("Should read the number of saved spawns on that prefix and all spawn ids.", function()
					SpawnMobiles.getSpawnedMobilePointersList(pCreatureObject, prefix)

					assert.spy(readData).was.called(6)
				end)

				it("Should get the pointer to the mobile for every saved id.", function()
					SpawnMobiles.getSpawnedMobilePointersList(pCreatureObject, prefix)

					assert.spy(getSceneObject).was.called(5)
				end)

				it("Should return a list with pointers to the spawned mobiles.", function()
					assert.same(spawnedMobilesList, SpawnMobiles.getSpawnedMobilePointersList(pCreatureObject, prefix))
				end)

				describe("and a mobile pointer can not be found by the getSceneObject", function()
					local expectedList

					before_each(function()
						spawnedMobilesList[2] = nil
						spawnedMobilesList[4] = nil

						expectedList = {}
						expectedList[1] = spawnedMobilesList[1]
						expectedList[2] = spawnedMobilesList[3]
						expectedList[3] = spawnedMobilesList[5]

						callNumberGetSceneObject = 1
						getSceneObject = spy.new(function(id)
							assert.same(mobileObjectIDs[callNumberGetSceneObject], id)
							callNumberGetSceneObject = callNumberGetSceneObject + 1
							return spawnedMobilesList[callNumberGetSceneObject - 1]
						end)
					end)

					it("Should not add that pointer to the list.", function()
						assert.same(expectedList, SpawnMobiles.getSpawnedMobilePointersList(pCreatureObject, prefix))
					end)
				end)
			end)
		end)

		describe("despawnMobilesInList", function()
			describe("When called with a list of spawned mobiles", function()
				it("Should call destroyObjectFromWorld on each of them.", function()
					SpawnMobiles.despawnMobilesInList(spawnedMobilesList)

					assert.spy(spawnedObject1.destroyObjectFromWorld).was.called_with(spawnedObject1)
					assert.spy(spawnedObject2.destroyObjectFromWorld).was.called_with(spawnedObject2)
					assert.spy(spawnedObject3.destroyObjectFromWorld).was.called_with(spawnedObject3)
					assert.spy(spawnedObject4.destroyObjectFromWorld).was.called_with(spawnedObject4)
					assert.spy(spawnedObject5.destroyObjectFromWorld).was.called_with(spawnedObject5)
				end)
			end)
		end)
	end)
end)
