ALTER TABLE `swgemu`.`characters` ADD COLUMN `factionStatus` TINYINT(1) UNSIGNED NOT NULL DEFAULT 0 AFTER `public`,
 ADD COLUMN `factionRank` TINYINT(1) UNSIGNED NOT NULL DEFAULT 0 AFTER `factionStatus`;

DROP TABLE `swgemu`.`character_faction`;

CREATE TABLE `swgemu`.`character_faction_points` (
  `character_id` INT UNSIGNED NOT NULL,
  `faction_name` VARCHAR(25)  NOT NULL,
  `faction_points` INT  NOT NULL,
  `hash` VARCHAR(32)  NOT NULL,
  PRIMARY KEY(`hash`)
)
ENGINE = MYISAM;

