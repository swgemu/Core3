/*
  Alters account and characters with two new fields for pcp integration.
  - These fields will not impact anything in game, and no code changes are needed at this time, nor is a database wipe.
*/

ALTER TABLE `account` ADD COLUMN `adminLevel` tinyint(1) unsigned NOT NULL default '4' AFTER `active`;
ALTER TABLE `characters` ADD COLUMN `public` tinyint(1) unsigned NOT NULL default '0' AFTER `adminLevel`;