/* You may have to enter each of these commands manually for it to work */

ALTER TABLE `characters` ADD COLUMN `PvpRating` SMALLINT(5) UNSIGNED NOT NULL DEFAULT 1200 AFTER `BattleFatigue`;