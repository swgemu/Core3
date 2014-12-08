local SithShadowIntroTheater = require("managers.jedi.village.sith_shadow_intro_theater")
local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local QuestManagerMocks = require("managers.quest.mocks.quest_manager_mocks")
local SpawnMobilesMocks = require("utils.mocks.spawn_mobiles_mocks")
local OldManEncounterMocks = require("managers.jedi.village.mocks.old_man_encounter_mocks")
local GoToDathomirMocks = require("managers.jedi.village.mocks.go_to_dathomir_mocks")

local THEATER_ID_STRING = "theaterId"

local READ_DISK_2_STRING = "@quest/force_sensitive/intro:read_disk2"
local READ_DISK_ERROR_STRING = "@quest/force_sensitive/intro:read_disk_error"

describe("SithShadowIntroTheater", function()
    local pCreatureObject = { "creatureObjectPointer" }
    local creatureObject
    local playerObjectId = 12345678
    local pFirstSithShadow = { "firstSithShadowObjectPointer" }
    local pSecondSithShadow = { "spawnedMobile2Pointer" }
    local firstSithShadowObject
    local secondSithShadowObject
    local spawnedSithShadowList = { pFirstSithShadow, pSecondSithShadow }
    local pInventory = { "inventoryPointer" }
    local firstSithShadowId = 12345
    local secondSithShadowId = 23456
    local pDatapad = { "datapadPointer" }
    local datapad
    local theaterObjectId = 45678901
    local pTheater = { "theaterObjectPointer" }

    setup(function()
        DirectorManagerMocks.mocks.setup()
        QuestManagerMocks.mocks.setup()
        SpawnMobilesMocks.mocks.setup()
        OldManEncounterMocks.mocks.setup()
        GoToDathomirMocks.mocks.setup()
    end)

    teardown(function()
        DirectorManagerMocks.mocks.teardown()
        QuestManagerMocks.mocks.teardown()
        SpawnMobilesMocks.mocks.teardown()
        OldManEncounterMocks.mocks.teardown()
        GoToDathomirMocks.mocks.teardown()
    end)

    before_each(function()
        DirectorManagerMocks.mocks.before_each()
        QuestManagerMocks.mocks.before_each()
        SpawnMobilesMocks.mocks.before_each()
        OldManEncounterMocks.mocks.before_each()
        GoToDathomirMocks.mocks.before_each()

        creatureObject = {}
        creatureObject.getObjectID = spy.new(function() return playerObjectId end)
        creatureObject.sendSystemMessage = spy.new(function() end)
        DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject

        firstSithShadowObject = {}
        firstSithShadowObject.setFollowObject = spy.new(function() end)
        firstSithShadowObject.getObjectID = spy.new(function() return firstSithShadowId end)
        firstSithShadowObject.getSlottedObject = spy.new(function() return pInventory end)
        DirectorManagerMocks.creatureObjects[pFirstSithShadow] = firstSithShadowObject
        DirectorManagerMocks.aiAgents[pFirstSithShadow] = firstSithShadowObject

        secondSithShadowObject = {}
        secondSithShadowObject.setFollowObject = spy.new(function() end)
        secondSithShadowObject.getObjectID = spy.new(function() return secondSithShadowId end)
        DirectorManagerMocks.creatureObjects[pSecondSithShadow] = secondSithShadowObject
        DirectorManagerMocks.aiAgents[pSecondSithShadow] = secondSithShadowObject

        datapad = {}
        datapad.destroyObjectFromWorld = spy.new(function() end)
        datapad.destroyObjectFromDatabase = spy.new(function() end)
        DirectorManagerMocks.sceneObjects[pDatapad] = datapad

        readData = spy.new(function(key)
            if key == playerObjectId .. SithShadowIntroTheater.taskName .. THEATER_ID_STRING then
                return theaterObjectId
            end
        end)

        getSceneObject = spy.new(function(id)
            if id == theaterObjectId then
                return pTheater
            end
        end)
    end)

    describe("onEnteredActiveArea", function()
        describe("When a player enters the active area", function()
            it("Should set all spawned sith shadows to attack the player.", function()
                SithShadowIntroTheater:onEnteredActiveArea(pCreatureObject, spawnedSithShadowList)

                assert.spy(firstSithShadowObject.setFollowObject).was.called_with(firstSithShadowObject, pCreatureObject)
                assert.spy(secondSithShadowObject.setFollowObject).was.called_with(secondSithShadowObject, pCreatureObject)
            end)

            it("Should activate the loot datapad 2 quest.", function()
                SithShadowIntroTheater:onEnteredActiveArea(pCreatureObject, spawnedSithShadowList)

                assert.spy(QuestManagerMocks.activateQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.LOOT_DATAPAD_2)
            end)
        end)
    end)

    describe("onSuccessfulSpawn", function()
        describe("When a sith shadow intro camp is spawned", function()
            it("Should activate the quest for the player that the camp belongs to.", function()
                SithShadowIntroTheater:onSuccessfulSpawn(pCreatureObject, spawnedSithShadowList)

                assert.spy(QuestManagerMocks.activateQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.FS_THEATER_CAMP)
            end)

            it("Should register an observer onLoot of the first spawned mobile.", function()
                SithShadowIntroTheater:onSuccessfulSpawn(pCreatureObject, spawnedSithShadowList)

                assert.spy(createObserver).was.called_with(LOOTCREATURE, SithShadowIntroTheater.taskName, "onLoot", pFirstSithShadow)
            end)

            it("Should register an observer for OBJECTDESTRUCTION on the player.", function()
                SithShadowIntroTheater:onSuccessfulSpawn(pCreatureObject, spawnedSithShadowList)

                assert.spy(createObserver).was.called_with(OBJECTDESTRUCTION, SithShadowIntroTheater.taskName, "onPlayerKilled", pCreatureObject)
            end)
        end)
    end)

    describe("onLoot", function()
        describe("When called with a pointer to a creature and a pointer to the looter", function()
            it("Should check if the player has the encounter quest active.", function()
                SithShadowIntroTheater:onLoot(pFirstSithShadow, pCreatureObject, 0)

                assert.spy(QuestManagerMocks.hasActiveQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.FS_THEATER_CAMP)
            end)

            describe("and the player has the quest active", function()
                before_each(function()
                    QuestManagerMocks.hasActiveQuest = spy.new(function() return true end)
                end)

                it("Should get the list of spawned sith shadows for the looter.", function()
                    SithShadowIntroTheater:onLoot(pFirstSithShadow, pCreatureObject, 0)

                    assert.spy(SpawnMobilesMocks.getSpawnedMobiles).was.called_with(pTheater, SithShadowIntroTheater.taskName)
                end)

                describe("and the player has a list of spawned sith shadows", function()
                    before_each(function()
                        SpawnMobilesMocks.getSpawnedMobiles = spy.new(function() return spawnedSithShadowList end)
                    end)

                    it("Should get the id of the first sith shadow in the list", function()
                        SithShadowIntroTheater:onLoot(pSecondSithShadow, pCreatureObject, 0)

                        assert.spy(firstSithShadowObject.getObjectID).was.called_with(firstSithShadowObject)
                    end)

                    it("Should get the id of the looted creature", function()
                        SithShadowIntroTheater:onLoot(pSecondSithShadow, pCreatureObject, 0)

                        assert.spy(secondSithShadowObject.getObjectID).was.called_with(secondSithShadowObject)
                    end)

                    describe("and both ids are identical", function()
                        it("Should create loot in the inventory of the sith shadow.", function()
                            SithShadowIntroTheater:onLoot(pFirstSithShadow, pCreatureObject, 0)

                            assert.spy(createLoot).was.called_with(pInventory, "sith_shadow_intro_theater_datapad", 0, true)
                        end)

                        it("Should return 1 to remove the observer.", function()
                            assert.same(1, SithShadowIntroTheater:onLoot(pFirstSithShadow, pCreatureObject, 0))
                        end)

                        it("Should complete the quests.", function()
                            SithShadowIntroTheater:onLoot(pFirstSithShadow, pCreatureObject, 0)

                            assert.spy(QuestManagerMocks.completeQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.FS_THEATER_CAMP)
                            assert.spy(QuestManagerMocks.completeQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.GOT_DATAPAD_2)
                        end)
                    end)

                    describe("and both ids are not identical", function()
                        it("Should not create loot in the inventory of the looted sith shadow.", function()
                            SithShadowIntroTheater:onLoot(pSecondSithShadow, pCreatureObject, 0)

                            assert.spy(createLoot).was.not_called()
                        end)

                        it("Should return 0 to keep the observer.", function()
                            assert.same(0, SithShadowIntroTheater:onLoot(pSecondSithShadow, pCreatureObject, 0))
                        end)
                    end)

                    it("Should complete the sith shadow ambush quests.", function()
                        SithShadowIntroTheater:onLoot(pFirstSithShadow, pCreatureObject, 0)

                        assert.spy(QuestManagerMocks.completeQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.FS_THEATER_CAMP)
                    end)
                end)

                describe("and the player has no spawned sith shadows", function()
                    before_each(function()
                        SpawnMobilesMocks.getSpawnedMobiles = spy.new(function() return nil end)
                    end)

                    it("Should not create loot in the inventory of the looted sith shadow.", function()
                        SithShadowIntroTheater:onLoot(pFirstSithShadow, pCreatureObject, 0)

                        assert.spy(createLoot).was.not_called()
                    end)

                    it("Should return 0 to keep the observer.", function()
                        assert.same(0, SithShadowIntroTheater:onLoot(pFirstSithShadow, pCreatureObject, 0))
                    end)
                end)
            end)

            describe("and the player does not have the quest active", function()
                it("Should not create loot in the inventory of the looted sith shadow.", function()
                    SithShadowIntroTheater:onLoot(pFirstSithShadow, pCreatureObject, 0)

                    assert.spy(createLoot).was.not_called()
                end)

                it("Should return 0 to keep the observer.", function()
                    assert.same(0, SithShadowIntroTheater:onLoot(pFirstSithShadow, pCreatureObject, 0))
                end)
            end)
        end)
    end)

    describe("onPlayerKilled", function()
        it("Should check if the killer is from the sith shadow spawn of the player.", function()
            SithShadowIntroTheater:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0)

            assert.spy(SpawnMobilesMocks.isFromSpawn).was.called_with(pCreatureObject, SithShadowIntroTheater.taskName, pFirstSithShadow)
        end)

        describe("and the killer is one of the sith shadows of the player", function()
            before_each(function()
                SpawnMobilesMocks.isFromSpawn = spy.new(function() return true end)
            end)

            it("Should remove the crystal from the player.", function()
                SithShadowIntroTheater:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0)

                assert.spy(OldManEncounterMocks.removeForceCrystalFromPlayer).was.called_with(OldManEncounterMocks, pCreatureObject)
            end)

            it("Should restart the old man encounter.", function()
                SithShadowIntroTheater:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0)

                assert.spy(OldManEncounterMocks.start).was.called_with(OldManEncounterMocks, pCreatureObject)
            end)

            it("Should reset the sith intro theater quests.", function()
                SithShadowIntroTheater:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0)

                assert.spy(QuestManagerMocks.resetQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.TWO_MILITARY)
                assert.spy(QuestManagerMocks.resetQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.LOOT_DATAPAD_1)
                assert.spy(QuestManagerMocks.resetQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.GOT_DATAPAD_1)
                assert.spy(QuestManagerMocks.resetQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.FS_THEATER_CAMP)
                assert.spy(QuestManagerMocks.resetQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.LOOT_DATAPAD_2)
                assert.spy(QuestManagerMocks.resetQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.GOT_DATAPAD_2)
            end)

            it("Should send spatial chat about returning the crystal.", function()
                SithShadowIntroTheater:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0)

                assert.spy(spatialChat).was.called_with(pFirstSithShadow, SITH_SHADOW_MILITARY_TAKE_CRYSTAL)
            end)

            it("Should return 1 to remove the observer.", function()
                assert.same(1, SithShadowIntroTheater:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0))
            end)
        end)

        describe("and the killer is not one of the sith shadows of the player", function()
            it("Should not remove the crystal from the player.", function()
                SithShadowIntroTheater:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0)

                assert.spy(OldManEncounterMocks.removeForceCrystalFromPlayer).was.not_called()
            end)

            it("Should not restart the old man encounter.", function()
                SithShadowIntroTheater:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0)

                assert.spy(OldManEncounterMocks.start).was.not_called()
            end)

            it("Should not reset the sith shadow intro theater quests.", function()
                SithShadowIntroTheater:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0)

                assert.spy(QuestManagerMocks.resetQuest).was.not_called()
            end)

            it("Should return 0 to keep the observer.", function()
                assert.same(0, SithShadowIntroTheater:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0))
            end)
        end)
    end)

    describe("useTheaterDatapad", function()
        describe("When called with a scene object and a player object", function()
            it("Should check if the player object has looted a datapad.", function()
                SithShadowIntroTheater:useTheaterDatapad(pDatapad, pCreatureObject)

                assert.spy(QuestManagerMocks.hasCompletedQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.GOT_DATAPAD_2)
            end)
        end)

        describe("and the player has looted a datapad", function()
            before_each(function()
                QuestManagerMocks.hasCompletedQuest = spy.new(function() return true end)
            end)

            it("Should send the disk string to the player.", function()
                SithShadowIntroTheater:useTheaterDatapad(pDatapad, pCreatureObject)

                assert.spy(creatureObject.sendSystemMessage).was.called_with(creatureObject, READ_DISK_2_STRING)
            end)

            it("Should destroy the datapad.", function()
                SithShadowIntroTheater:useTheaterDatapad(pDatapad, pCreatureObject)

                assert.spy(datapad.destroyObjectFromWorld).was.called_with(datapad)
                assert.spy(datapad.destroyObjectFromDatabase).was.called_with(datapad)
            end)

            it("Should start the DathomirGoTo quest.", function()
                SithShadowIntroTheater:useTheaterDatapad(pDatapad, pCreatureObject)

                assert.spy(GoToDathomirMocks.start).was.called_with(GoToDathomirMocks, pCreatureObject)
            end)

            it("Should complete the loot datapad 2 quest.", function()
                SithShadowIntroTheater:useTheaterDatapad(pDatapad, pCreatureObject)

                assert.spy(QuestManagerMocks.completeQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.LOOT_DATAPAD_2)
            end)
        end)

        describe("and the player has not looted a datapad", function()
            it("Should send an error string to the player.", function()
                SithShadowIntroTheater:useTheaterDatapad(pDatapad, pCreatureObject)

                assert.spy(creatureObject.sendSystemMessage).was.called_with(creatureObject, READ_DISK_ERROR_STRING)
            end)
        end)
    end)
end)
