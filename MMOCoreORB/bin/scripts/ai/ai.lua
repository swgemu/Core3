package.path = package.path .. ";scripts/ai/?.lua"
local ObjectManager = require("managers.object.object_manager")
--[[ Load Actions and Tasks ]]
includeAiFile("actions/actions.lua")
includeAiFile("tasks/tasks.lua")
includeAiFile("templates/templates.lua")
