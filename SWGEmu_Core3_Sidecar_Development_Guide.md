# SWGEmu Core3 Developer Guide for Sidecar Applications

## Table of Contents

1. [Introduction](#introduction)
2. [System Architecture Overview](#system-architecture-overview)
   - [Core Components](#core-components)
   - [Zone Managers](#zone-managers)
   - [Object Model](#object-model)
3. [REST API Integration](#rest-api-integration)
   - [Enabling the REST API](#enabling-the-rest-api)
   - [API Endpoints](#api-endpoints)
   - [Authentication](#authentication)
   - [Example API Requests](#example-api-requests)
4. [Creating Sidecar Applications](#creating-sidecar-applications)
   - [Web Dashboards](#web-dashboards)
   - [Custom Clients](#custom-clients)
   - [Server Monitoring](#server-monitoring)
   - [Data Analysis](#data-analysis)
5. [Best Practices for Sidecar Applications](#best-practices-for-sidecar-applications)
   - [Security Considerations](#security-considerations)
   - [Performance Considerations](#performance-considerations)
   - [Error Handling](#error-handling)
6. [Example Use Cases](#example-use-cases)
   - [Player Information Dashboard](#player-information-dashboard)
   - [Administrative Bot](#administrative-bot)
   - [Resource Tracker](#resource-tracker)
7. [Advanced Topics](#advanced-topics)
   - [Custom Server Configuration](#custom-server-configuration)
   - [Database Integration](#database-integration)
   - [Event-Driven Architecture](#event-driven-architecture)
8. [Troubleshooting](#troubleshooting)
9. [Resources](#resources)
10. [Conclusion](#conclusion)

## Introduction

[SWGEmu](https://www.swgemu.com/) (Star Wars Galaxies Emulator) [Core3](https://github.com/swgemu/Core3) is an open-source project that aims to recreate the Pre-Combat Upgrade (Pre-CU) era of Star Wars Galaxies, a massively multiplayer online role-playing game (MMORPG) that was shut down in 2011. The Core3 engine provides the server-side implementation of the game, allowing players to experience the game as it existed during the Pre-CU era.

This guide is designed for developers who want to create sidecar applications that interact with a SWGEmu Core3 server. Sidecar applications can extend the functionality of the server, provide administrative tools, or offer alternative ways for players to interact with the game.

For more information about the SWGEmu project, visit the [official website](https://www.swgemu.com/) or the [GitHub repository](https://github.com/swgemu/Core3). The [SWGEmu Wiki](https://www.swgemu.com/wiki/index.php) also provides valuable information about the project and its development.

## System Architecture Overview

SWGEmu Core3 is built with a modular architecture that separates different aspects of the game into distinct components. Understanding this architecture is essential for developing effective sidecar applications.

### Core Components

The main components of the SWGEmu Core3 system are:

1. **[ServerCore](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/ServerCore.cpp)**: The main server process that initializes and manages all other components.

2. **[LoginServer](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/login/LoginServer.cpp)**: Handles player authentication and account management. It verifies user credentials and manages the connection between the client and the zone server.

3. **[ZoneServer](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/ZoneServer.idl)**: The main game server that manages the game world. It handles:
   - Zones (game worlds like Tatooine, Naboo, etc.)
   - Game objects (players, NPCs, items, buildings, etc.)
   - Game mechanics (combat, crafting, etc.)

4. **[PingServer](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/ping/PingServer.cpp)**: Handles ping requests to monitor server connectivity and ensure clients maintain a stable connection.

5. **[StatusServer](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/status/StatusServer.cpp)**: Provides server status information, including player count, uptime, and other metrics.

6. **[RESTServer](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/web/RESTServer.cpp)**: Provides a REST API for external applications to interact with the game server. This is the primary interface for sidecar applications.

### Zone Managers

The ZoneServer contains numerous managers that handle different aspects of the game:

- **[PlayerManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/managers/player/PlayerManager.idl)**: Handles player-related functionality such as character creation, experience, skills, and more.
- **[ObjectManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/managers/object/ObjectManager.h)**: Creates, loads, and persists game objects in the database.
- **[ChatManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/chat/ChatManager.idl)**: Manages in-game chat, mail, and other communication systems.
- **[GuildManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/managers/guild/GuildManager.idl)**: Manages player guilds, including membership, ranks, and guild halls.
- **[CityManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/managers/city/CityManager.idl)**: Manages player cities, including city structures, citizenship, and city elections.
- **[CraftingManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/managers/crafting/CraftingManager.idl)**: Handles item crafting, including schematics, resources, and factories.
- **[LootManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/managers/loot/LootManager.idl)**: Controls loot drops from creatures and other sources.
- **[ResourceManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/managers/resource/ResourceManager.idl)**: Manages resource spawns, harvesting, and resource pools.
- **[MissionManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/managers/mission/MissionManager.idl)**: Handles mission generation, assignment, and completion.
- **[SkillManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/managers/skill/SkillManager.idl)**: Manages player skills, including skill acquisition and progression.
- **[FactionManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/managers/faction/FactionManager.idl)**: Handles faction-related functionality, including Imperial vs. Rebel standings.

These managers provide the core functionality of the game and can be accessed through the REST API for sidecar applications.

### Object Model

The game uses a comprehensive object model with SceneObject as the base class:

- **[SceneObject](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/objects/scene/SceneObject.idl)**: Base class for all game objects. It provides common functionality such as position, orientation, and containment.
  - **[TangibleObject](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/objects/tangible/TangibleObject.idl)**: Physical objects in the game world that can be interacted with.
    - **[CreatureObject](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/objects/creature/CreatureObject.idl)**: Living entities such as players and NPCs.
      - **[PlayerObject](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/objects/player/PlayerObject.idl)**: Player-controlled characters.
      - **[AiAgent](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/objects/creature/ai/AiAgent.idl)**: Non-player characters with AI behavior.
    - **[BuildingObject](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/objects/building/BuildingObject.idl)**: Structures that players can enter.
    - **[WeaponObject](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/objects/tangible/weapon/WeaponObject.idl)**: Weapons that can be equipped and used.
    - **[ArmorObject](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/objects/tangible/wearables/ArmorObject.idl)**: Armor that can be equipped for protection.
    - **[ResourceContainer](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/objects/resource/ResourceContainer.idl)**: Containers for resources.
    - **[FactoryCrate](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/objects/factorycrate/FactoryCrate.idl)**: Containers for crafted items.
  - **[IntangibleObject](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/objects/intangible/IntangibleObject.idl)**: Non-physical objects such as waypoints and data items.
    - **[MissionObject](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/objects/mission/MissionObject.idl)**: Mission data objects.
    - **[WaypointObject](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/objects/waypoint/WaypointObject.idl)**: Navigation waypoints.
    - **[DatapadObject](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/objects/tangible/terminal/Terminal.idl)**: Player datapads containing waypoints and missions.

Understanding this object hierarchy is important for working with the REST API, as many endpoints operate on specific object types.

## REST API Integration

The REST API is the primary way for sidecar applications to interact with the game server. It provides a set of endpoints for accessing and manipulating game data.

### Enabling the REST API

The REST API is disabled by default and needs to be configured in the `config-local.lua` file:

```lua
Core3.RESTServerPort = 44443
Core3.RESTServer = {
    LogLevel = 4, -- -1 NONE, 0 FATAL, 1 ERROR, 2 WARNING, 3 LOG, 4 INFO, 5 DEBUG
    APIToken = "your_secure_token_here",
    SSLKeyFile = "conf/ssl.key",
    SSLCertFile = "conf/ssl.crt",
}
```

You'll need to generate SSL certificates for secure communication:

```bash
cd bin/conf
openssl genrsa -out ssl.key 2048
openssl req -new -key secrets/ssl.key -out ssl.csr -subj "/C=US/ST=NY/L=Somewhere/O=MyOrg/CN=Core3API"
openssl x509 -req -days 3650 -in ssl.csr -signkey secrets/ssl.key -out ssl.crt
rm -f ssl.csr
```

And generate a secure API token:

```bash
openssl rand -base64 18
```

After configuring the REST API, you'll need to restart the server or reload the configuration for the changes to take effect.

### API Endpoints

The REST API provides several endpoints for different aspects of the game:

#### Version Information

- `GET /v1/version/`: Returns API and Core3 version information.

#### Object Management ([APIProxyObjectManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/web/APIProxyObjectManager.cpp))

- `GET /v1/object/{oid}/`: Retrieves information about a specific object by its object ID.
- `GET /v1/object/?oids=id1,id2,id3`: Retrieves information about multiple objects.
- `DELETE /v1/object/{oid}/`: Deletes an object from the game.
- `PUT /v1/object/{oid}/{class}/{property}/`: Updates a property of an object.

#### Player Management ([APIProxyPlayerManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/web/APIProxyPlayerManager.cpp))

- `GET /v1/lookup/character/?name=characterName`: Looks up character information by name.
- `GET /v1/lookup/character/?search=partial`: Searches for characters with names starting with the provided string.
- `POST /v1/admin/account/{accountID}/`: Performs administrative actions on an account.
- `POST /v1/admin/account/{accountID}/galaxy/{galaxyID}/character/{characterID}/`: Performs administrative actions on a character.

#### Guild Management ([APIProxyGuildManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/web/APIProxyGuildManager.cpp))

- `GET /v1/lookup/guild/?name=guildName`: Looks up guild information by name.

#### Chat Management ([APIProxyChatManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/web/APIProxyChatManager.cpp))

- `POST /v1/chat/mail/`: Sends in-game mail to players.
- `POST /v1/chat/message/`: Sends in-game messages to players.
- `POST /v1/chat/galaxy/`: Sends galaxy-wide announcements.

#### Configuration Management ([APIProxyConfigManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/web/APIProxyConfigManager.cpp))

- `GET /v1/admin/config/{key}/`: Gets server configuration values.
- `POST /v1/admin/config/{key}/`: Updates server configuration values.

#### Statistics ([APIProxyStatisticsManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/web/APIProxyStatisticsManager.cpp))

- `GET /v1/admin/stats/`: Gets server statistics, including player count and resource usage.

#### Console Commands

- `POST /v1/admin/console/{command}/?args=arguments`: Executes server console commands.

### Authentication

All API requests require authentication using the Bearer token specified in the configuration:

```
Authorization: Bearer your_secure_token_here
```

This token should be included in the HTTP headers of all API requests.

### Example API Requests

Here are some examples of common API requests:

#### Get Server Version

This example shows how to get the server version information:

```bash
curl -s -k -H "Authorization: Bearer your_secure_token_here" "https://127.0.0.1:44443/v1/version"
```

Response:
```json
{
  "api_version": 1,
  "core3_version": "SWGEmu Core3 Engine v1.0.0"
}
```

#### Look Up a Character

This example shows how to look up a character by name using the [PlayerManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/web/APIProxyPlayerManager.cpp#L33):

```bash
curl -s -k -H "Authorization: Bearer your_secure_token_here" "https://127.0.0.1:44443/v1/lookup/character/?name=Luke"
```

Response:
```json
{
  "metadata": {
    "exportTime": "2025-04-22 22:30:45",
    "objectCount": 1,
    "maxDepth": 3,
    "recursive": false
  },
  "names": {
    "Luke": 123456789
  }
}
```

#### Send a Galaxy-Wide Message

This example shows how to send a galaxy-wide message using the [ChatManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/web/APIProxyChatManager.cpp):

```bash
curl -s -k -H "Authorization: Bearer your_secure_token_here" -X POST -d '{"message": "Server maintenance in 15 minutes!"}' "https://127.0.0.1:44443/v1/chat/galaxy/"
```

Response:
```json
{
  "status": "success",
  "message": "Galaxy message sent"
}
```

#### Execute a Console Command

This example shows how to execute a server console command:

```bash
curl -s -k -H "Authorization: Bearer your_secure_token_here" -X POST "https://127.0.0.1:44443/v1/admin/console/broadcast/?args=Server%20restarting%20in%205%20minutes"
```

Response:
```json
{
  "console_command": "broadcast Server restarting in 5 minutes"
}
```

## Creating Sidecar Applications

Sidecar applications can be built to extend the functionality of the SWGEmu Core3 server. Here are some common types of sidecar applications:

### Web Dashboards

Web dashboards can provide administrative interfaces for server management:

- **Player Management Dashboard**: Search for players, view their information, and perform administrative actions like banning or kicking.
- **Server Statistics Dashboard**: Monitor server health, player count, and resource usage.
- **Guild Management Dashboard**: View and manage guilds, including membership and guild halls.
- **Resource Management Dashboard**: Track resource spawns, quality, and availability.

### Custom Clients

Custom clients can provide alternative ways to interact with the game:

- **Mobile Companion Apps**: Allow players to check their character status, manage inventory, or communicate with other players from their mobile devices.
- **Web-Based Interfaces**: Provide web interfaces for certain game functions, such as crafting or trading.
- **Administrative Tools**: Create specialized tools for server administrators to manage the game world.

### Server Monitoring

Monitoring applications can track server health and performance:

- **Player Count Tracker**: Track player count over time to identify peak hours and trends.
- **Resource Usage Monitor**: Monitor server resource usage to identify performance issues.
- **Error Logger**: Log and alert on server errors for quick troubleshooting.

### Data Analysis

Data analysis tools can provide insights into game data:

- **Player Activity Analysis**: Analyze player activity patterns to inform game design decisions.
- **Economy Monitor**: Track the in-game economy, including item prices and resource values.
- **Combat Balance Analysis**: Analyze combat data to identify balance issues.

## Best Practices for Sidecar Applications

### Security Considerations

1. **API Token Security**: Keep your API token secure and rotate it regularly. Never expose it in client-side code.

2. **SSL/TLS**: Always use HTTPS for API communication to encrypt data in transit.

3. **Access Control**: Implement proper access control in your sidecar applications to ensure that only authorized users can perform sensitive operations.

4. **Firewall Rules**: Restrict access to the REST API port to trusted IPs to prevent unauthorized access.

5. **Input Validation**: Validate all user input to prevent injection attacks and other security vulnerabilities.

6. **Audit Logging**: Log all administrative actions for accountability and troubleshooting.

### Performance Considerations

1. **Rate Limiting**: Implement rate limiting in your applications to avoid overloading the server with too many requests.

2. **Caching**: Cache API responses when appropriate to reduce server load and improve response times.

3. **Batch Operations**: Use batch operations when possible to reduce the number of API calls.

4. **Asynchronous Processing**: Use asynchronous processing for long-running operations to avoid blocking the user interface.

5. **Pagination**: Implement pagination for large data sets to reduce response size and improve performance.

### Error Handling

1. **Graceful Degradation**: Design your applications to gracefully handle API failures and continue functioning with reduced capabilities.

2. **Retry Logic**: Implement retry logic with exponential backoff for transient errors to improve reliability.

3. **Comprehensive Logging**: Log all API errors with sufficient context for troubleshooting.

4. **User Feedback**: Provide clear and helpful error messages to users when operations fail.

5. **Monitoring and Alerting**: Set up monitoring and alerting for API errors to detect and address issues quickly.

## Example Use Cases

### Player Information Dashboard

A web dashboard that displays information about online players:

```javascript
// Example code to fetch online players
async function getOnlinePlayers() {
  try {
    const response = await fetch('https://your-server:44443/v1/admin/stats/', {
      headers: {
        'Authorization': 'Bearer your_secure_token_here'
      }
    });
    
    if (!response.ok) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }
    
    const data = await response.json();
    return data.onlinePlayers;
  } catch (error) {
    console.error('Error fetching online players:', error);
    return [];
  }
}

// Display online players in a table
async function displayOnlinePlayers() {
  const players = await getOnlinePlayers();
  const tableBody = document.getElementById('players-table-body');
  
  tableBody.innerHTML = '';
  
  players.forEach(player => {
    const row = document.createElement('tr');
    
    const nameCell = document.createElement('td');
    nameCell.textContent = player.name;
    row.appendChild(nameCell);
    
    const levelCell = document.createElement('td');
    levelCell.textContent = player.level;
    row.appendChild(levelCell);
    
    const locationCell = document.createElement('td');
    locationCell.textContent = `${player.zone} (${player.x.toFixed(0)}, ${player.y.toFixed(0)})`;
    row.appendChild(locationCell);
    
    const actionsCell = document.createElement('td');
    const kickButton = document.createElement('button');
    kickButton.textContent = 'Kick';
    kickButton.onclick = () => kickPlayer(player.id);
    actionsCell.appendChild(kickButton);
    row.appendChild(actionsCell);
    
    tableBody.appendChild(row);
  });
}

// Refresh the player list every 30 seconds
setInterval(displayOnlinePlayers, 30000);
displayOnlinePlayers();
```

### Administrative Bot

A Discord bot that allows administrators to execute server commands:

```javascript
const { Client, Intents } = require('discord.js');
const fetch = require('node-fetch');

const client = new Client({ intents: [Intents.FLAGS.GUILDS, Intents.FLAGS.GUILD_MESSAGES] });
const API_TOKEN = 'your_secure_token_here';
const API_BASE_URL = 'https://your-server:44443';
const ADMIN_ROLE_ID = 'your_admin_role_id';

client.on('ready', () => {
  console.log(`Logged in as ${client.user.tag}!`);
});

client.on('messageCreate', async message => {
  // Ignore messages from bots and non-commands
  if (message.author.bot || !message.content.startsWith('!swg')) return;
  
  // Check if user has admin role
  const member = message.guild.members.cache.get(message.author.id);
  if (!member.roles.cache.has(ADMIN_ROLE_ID)) {
    return message.reply('You do not have permission to use this command.');
  }
  
  const args = message.content.slice('!swg'.length).trim().split(/ +/);
  const command = args.shift().toLowerCase();
  
  if (command === 'kick') {
    if (args.length < 2) {
      return message.reply('Usage: !swg kick <player_name> <reason>');
    }
    
    const playerName = args[0];
    const reason = args.slice(1).join(' ');
    
    try {
      // First, look up the player to get their ID
      const lookupResponse = await fetch(`${API_BASE_URL}/v1/lookup/character/?name=${playerName}`, {
        headers: {
          'Authorization': `Bearer ${API_TOKEN}`
        }
      });
      
      const lookupData = await lookupResponse.json();
      
      if (!lookupData.names || !lookupData.names[playerName]) {
        return message.reply(`Player ${playerName} not found.`);
      }
      
      const playerId = lookupData.names[playerName];
      
      // Then, kick the player
      const kickResponse = await fetch(`${API_BASE_URL}/v1/admin/account/0/galaxy/0/character/${playerId}/`, {
        method: 'POST',
        headers: {
          'Authorization': `Bearer ${API_TOKEN}`,
          'Content-Type': 'application/json'
        },
        body: JSON.stringify({
          command: 'kick',
          admin: message.author.id,
          reason: reason
        })
      });
      
      const kickData = await kickResponse.json();
      
      message.reply(`Player ${playerName} has been kicked. Reason: ${reason}`);
    } catch (error) {
      console.error('Error kicking player:', error);
      message.reply('An error occurred while trying to kick the player.');
    }
  } else if (command === 'broadcast') {
    if (args.length < 1) {
      return message.reply('Usage: !swg broadcast <message>');
    }
    
    const broadcastMessage = args.join(' ');
    
    try {
      const response = await fetch(`${API_BASE_URL}/v1/admin/console/broadcast/?args=${encodeURIComponent(broadcastMessage)}`, {
        method: 'POST',
        headers: {
          'Authorization': `Bearer ${API_TOKEN}`
        }
      });
      
      const data = await response.json();
      
      message.reply(`Broadcast sent: ${broadcastMessage}`);
    } catch (error) {
      console.error('Error sending broadcast:', error);
      message.reply('An error occurred while trying to send the broadcast.');
    }
  }
});

client.login('your_discord_bot_token');
```

### Resource Tracker

A web application that tracks resource spawns and quality:

```javascript
// Example code to fetch resource information
async function getResources() {
  try {
    const response = await fetch('https://your-server:44443/v1/object/?oids=resourceManager', {
      headers: {
        'Authorization': 'Bearer your_secure_token_here'
      }
    });
    
    if (!response.ok) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }
    
    const data = await response.json();
    return data.objects.resourceManager.resources;
  } catch (error) {
    console.error('Error fetching resources:', error);
    return [];
  }
}

// Display resources in a table
async function displayResources() {
  const resources = await getResources();
  const tableBody = document.getElementById('resources-table-body');
  
  tableBody.innerHTML = '';
  
  Object.entries(resources).forEach(([resourceId, resource]) => {
    const row = document.createElement('tr');
    
    const nameCell = document.createElement('td');
    nameCell.textContent = resource.name;
    row.appendChild(nameCell);
    
    const typeCell = document.createElement('td');
    typeCell.textContent = resource.type;
    row.appendChild(typeCell);
    
    const planetCell = document.createElement('td');
    planetCell.textContent = resource.planet;
    row.appendChild(planetCell);
    
    // Create cells for each resource attribute
    const attributes = ['cr', 'cd', 'dr', 'fl', 'hr', 'ma', 'pe', 'oq', 'sr', 'ut', 'er'];
    attributes.forEach(attr => {
      const attrCell = document.createElement('td');
      attrCell.textContent = resource.attributes[attr] || '-';
      row.appendChild(attrCell);
    });
    
    tableBody.appendChild(row);
  });
}

// Refresh the resource list every 5 minutes
setInterval(displayResources, 300000);
displayResources();
```

## Advanced Topics

### Custom Server Configuration

SWGEmu Core3 servers can be customized through [configuration files](https://github.com/swgemu/Core3/tree/master/MMOCoreORB/bin/conf). Sidecar applications can help manage these configurations:

- **Configuration Editor**: Create a web interface for editing server configuration files like [config.lua](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/bin/conf/config.lua) and [config-local.lua](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/bin/conf/config-local.lua.example).
- **Configuration Backup**: Automatically back up configuration files before making changes.
- **Configuration Validation**: Validate configuration changes to prevent errors.

The [APIProxyConfigManager](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/web/APIProxyConfigManager.cpp) provides a way to interact with server configuration through the REST API.

### Database Integration

SWGEmu Core3 uses a [MySQL database](https://github.com/swgemu/Core3/tree/master/MMOCoreORB/sql) to store game data. Sidecar applications can interact with this database directly for advanced functionality:

- **Database Backup**: Automatically back up the database at regular intervals.
- **Database Migration**: Help migrate data between servers or versions.
- **Advanced Queries**: Perform complex queries that aren't possible through the REST API.

The [ServerDatabase](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/db/ServerDatabase.h) class provides the interface to the database.

### Event-Driven Architecture

For real-time updates, consider implementing an event-driven architecture:

- **Webhooks**: Configure the server to send webhooks for important events.
- **WebSockets**: Implement a WebSocket server for real-time communication.
- **Message Queues**: Use message queues for asynchronous processing of events.

The SWGEmu Core3 server uses an [Observer pattern](https://github.com/swgemu/Core3/blob/master/MMOCoreORB/src/server/zone/objects/scene/ObserverEventType.h) internally that could be extended to support external event notifications.

## Troubleshooting

Common issues and their solutions:

### API Connection Issues

- **SSL Certificate Problems**: Ensure that your SSL certificates are valid and properly configured.
- **Firewall Blocking**: Check that your firewall allows connections to the REST API port.
- **API Token Issues**: Verify that you're using the correct API token and that it's properly formatted.

### Performance Issues

- **Slow API Responses**: Check server load and consider optimizing your queries or implementing caching.
- **High CPU Usage**: Monitor server CPU usage and consider scaling up your server or optimizing your code.
- **Memory Leaks**: Watch for memory leaks in long-running applications and implement proper cleanup.

### Data Consistency Issues

- **Stale Data**: Implement proper cache invalidation to ensure you're not working with stale data.
- **Race Conditions**: Use proper locking or optimistic concurrency control to prevent race conditions.
- **Database Corruption**: Regularly back up your database and implement integrity checks.

## Resources

- [SWGEmu Official Website](https://www.swgemu.com/)
- [SWGEmu GitHub Repository](https://github.com/swgemu/Core3)
- [SWGEmu Wiki](https://www.swgemu.com/wiki/index.php)
- [SWGEmu Forums](https://www.swgemu.com/forums/)
- [SWGEmu API Documentation](https://github.com/swgemu/Core3/tree/master/MMOCoreORB/src/server/web)
- [SWGEmu Server Configuration Guide](https://www.swgemu.com/wiki/index.php?title=Server_Setup_Guide)
- [SWGEmu Database Schema](https://github.com/swgemu/Core3/tree/master/MMOCoreORB/sql)
- [SWGEmu Zone Server Documentation](https://github.com/swgemu/Core3/tree/master/MMOCoreORB/src/server/zone)
- [SWGEmu Object Model Documentation](https://github.com/swgemu/Core3/tree/master/MMOCoreORB/src/server/zone/objects)
- [SWGEmu Manager Classes](https://github.com/swgemu/Core3/tree/master/MMOCoreORB/src/server/zone/managers)

## Conclusion

[SWGEmu Core3](https://github.com/swgemu/Core3) provides a robust platform for Star Wars Galaxies emulation with extensive capabilities for sidecar application development through its [REST API](https://github.com/swgemu/Core3/tree/master/MMOCoreORB/src/server/web). By understanding the system architecture and following best practices, developers can create powerful tools and applications that enhance the gaming experience and server management.

This guide has covered the basics of SWGEmu Core3 sidecar application development, including system architecture, REST API integration, best practices, and example use cases. With this knowledge, you should be able to start building your own sidecar applications to extend and enhance your SWGEmu Core3 server.

Remember to always prioritize security, performance, and user experience in your applications, and to contribute back to the [SWGEmu community](https://www.swgemu.com/forums/) when possible.

For additional help and resources, visit the [SWGEmu Wiki](https://www.swgemu.com/wiki/index.php) or join the discussion on the [SWGEmu Forums](https://www.swgemu.com/forums/).
