ALTER TABLE `loottable` DROP `item_string`, DROP `developernote`;
DELETE FROM `loottable` WHERE template_type = 805306373;
