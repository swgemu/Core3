/^[	 ]*#[	 ]*undef[	 ][	 ]*[_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ][_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789]*[	 ]*$/b def
/^[	 ]*#[	 ]*define[	 ][	 ]*[_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ][_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789]*[(	 ]/b def
b
:def
s/$/ /
s,^\([	 #]*\)[^	 ]*\([	 ]*PACKAGE_NAME\)[	 (].*,\1define\2 "core3" ,
s,^\([	 #]*\)[^	 ]*\([	 ]*PACKAGE_TARNAME\)[	 (].*,\1define\2 "core3" ,
s,^\([	 #]*\)[^	 ]*\([	 ]*PACKAGE_VERSION\)[	 (].*,\1define\2 "1.0" ,
s,^\([	 #]*\)[^	 ]*\([	 ]*PACKAGE_STRING\)[	 (].*,\1define\2 "core3 1.0" ,
s,^\([	 #]*\)[^	 ]*\([	 ]*PACKAGE_BUGREPORT\)[	 (].*,\1define\2 "" ,
s,^\([	 #]*\)[^	 ]*\([	 ]*PACKAGE\)[	 (].*,\1define\2 "core3" ,
s,^\([	 #]*\)[^	 ]*\([	 ]*VERSION\)[	 (].*,\1define\2 "1.0" ,
s/ $//
s,^[	 #]*u.*,/* & */,
