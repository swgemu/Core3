# SWGEmu Core3

## What is SWGEmu?

Star Wars Galaxies was a massively multi-player online role playing game introduced by Sony Online Entertainment in the year 2003 and shut down in 2011.
It is this game the SWGEmu project focuses to recreate at a specific milestone referred to as Pre-CU, or Pre-Combat Upgrade. The Combat Upgrade was a set of game changes which radically changed the game-play, to the dislike of thousands of players. These changes led to the founding of this project, in an attempt to "recreate" the game as it was during the Pre-CU era.
At SWGEmu, Emulator refers to the software the SWGEmu team is building. This Emulator is meant to imitate Sony Online Entertainment's server-side software, which hosted the galaxies of Star Wars Galaxies during the Pre-CU era.

They will download with an extra _0.tre Back yours up and then change the name of these
Patch 03 https://drive.google.com/file/d/1MY5FmYkD9r4HfIELwARop8Puas4fEKXM/view?usp=sharing
Patch 11 https://drive.google.com/file/d/1flLuI5_sDtivVaEgq4oiZaorps6LqWV_/view?usp=sharing


## Changes in this repo
 * Will need to download 2 new tre files (patch 3 and 11)
  * Must pick Zabrak and start with Brawler
  * Stat Migration changed (higher min and max)
  * Buffs Nerfed to only 20% strength
 * Updated to current SWGEmu Code
 * Factory Crate Cap 1k
 * Factory Time Complexity Lowered
 * Create Character Timer Removed
 * Resource Deed 100k
 * All attachments are 25
 * Blue Frog Buffs
 * Starting Cash and Swoop
 * Resources Display Name in Inventory
 * CA/AA Now Display Name in Inventory
 * Structures now show item min/max capacity
 * Changed City timers and limits
 * Migrate Stats anywhere
 * Vehicle Spawn Time 5 Seconds

## How to Build

### Build
 
  * https://github.com/TrigsC/swgemutxt/blob/master/OpenPorts.JPG
  * Install dependencies (debian-9.12.0-amd64-netinst.iso, need to open ports)
        su -
        apt-get update && apt-get upgrade && apt-get install build-essential default-mysql-server default-libmysqlclient-dev default-jre libdb5.3-dev liblua5.3-dev libssl-dev cmake git gdb tmux
        exit

  * Clone Repo

        git clone https://github.com/TrigsC/Core3 && git clone https://github.com/TrigsC/engine3
        mkdir TRE
        nano ~/Core3/MMOCoreORB/bin/conf/config.lua
        change TrePath to /home/swgemu/TRE
        
  * Link Engine

        cd ~/Core3
        ln -s ../engine3/MMOEngine
        
  * Create Database

        su -
        export SWGEMU_DB="swgemu"
        export SWGEMU_DB_PASS="CHANGEPASSWORD"
        echo "CREATE DATABASE IF NOT EXISTS ${SWGEMU_DB};" | mysql -uroot -p${SWGEMU_DB_PASS}
        export SWGEMU_DB="swgemu"; export SWGEMU_DB_USER="swgemu"; export SWGEMU_DB_PASS="CHANGEPASSWORD"
        echo "CREATE DATABASE IF NOT EXISTS ${SWGEMU_DB};" | mysql -uroot -p${SWGEMU_DB_PASS}
        mysql -uroot -pCHANGEPASSWORD
        GRANT ALL ON ${SWGEMU_DB}.* TO '${SWGEMU_DB_USER}'@'localhost' IDENTIFIED BY '${SWGEMU_DB_PASS}'
        exit
        mysql -uroot -pCHANGEPASSWORD swgemu < /home/swgemu/Core3/MMOCoreORB/sql/swgemu.sql
        mysql -uroot -pCHANGEPASSWORD swgemu < /home/swgemu/Core3/MMOCoreORB/sql/datatables.sql
        mysql -uroot -pCHANGEPASSWORD
        use swgemu;
        UPDATE galaxy SET address="127.0.0.1"
        exit
        exit
        git submodule update --init
        
  * Optional Update resource spawn for max
  * Make

        cd ~/Core3/MMOCoreOrb
        make -j8
  * Run

        cd ~/Core3/MMOCoreOrb/bin
        ./core3
  * Add Admin

        create a new login
        su -
        mysql -pCHANGEPASSWORD swgemu -v -e "UPDATE accounts SET admin_level='15' WHERE username='YourUsername'"
        

## License

    Copyright (C) 2019 SWGEmu

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by the Free Software Foundation,
    either version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
    without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License along with this program.
    If not, see <http://www.gnu.org/licenses/>.

For more information, see https://review.swgemu.com.
