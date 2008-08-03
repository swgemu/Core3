/*
 * MySQL Query Browser Instructions
 * File>Open Script: If the contents of this script aren't automatically inserted,
 * then copy and paste the lines below into the Script 1 tab and hit the execute button.
 */

ALTER TABLE `shuttles` ADD COLUMN `tax` INTEGER UNSIGNED NOT NULL DEFAULT 0 AFTER `shut_dir_w`,
 ADD COLUMN `starport` TINYINT(1) UNSIGNED NOT NULL DEFAULT 1 AFTER `tax`;