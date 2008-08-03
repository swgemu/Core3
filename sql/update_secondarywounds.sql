/*
 * MySQL Query Browser Instructions
 * File>Open Script: If the contents of this script aren't automatically inserted,
 * then copy and paste the lines below into the Script 1 tab and hit the execute button.
 */

ALTER TABLE `characters` ADD COLUMN `StrengthWounds` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0 AFTER `HealthWounds`;
ALTER TABLE `characters` ADD COLUMN `ConstitutionWounds` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0 AFTER `StrengthWounds`;

ALTER TABLE `characters` ADD COLUMN `QuicknessWounds` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0 AFTER `ActionWounds`;
ALTER TABLE `characters` ADD COLUMN `StaminaWounds` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0 AFTER `QuicknessWounds`;

ALTER TABLE `characters` ADD COLUMN `FocusWounds` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0 AFTER `MindWounds`;
ALTER TABLE `characters` ADD COLUMN `WillpowerWounds` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0 AFTER `FocusWounds`;