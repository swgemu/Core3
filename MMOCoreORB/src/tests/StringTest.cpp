/*
 * StringTest.cpp
 *
 * Created on: 03/07/2026
 * Author: hakry
 *
 * Comprehensive unit tests for Engine3 String class
 */

#include "gtest/gtest.h"

#include "system/lang/String.h"
#include "system/lang/ArrayIndexOutOfBoundsException.h"
#include "system/lang/IllegalArgumentException.h"
#include "system/lang/StringBuffer.h"

// SSO_SIZE is sizeof(char*) * 2, typically 16 on 64-bit
static const int SSO_SIZE = int(sizeof(char*) * 2);

// Local constant to avoid ODR-use linker issues with NPOS
static const int NPOS = -1;

// Helper to create a string of exact length filled with 'a'
static String makeString(int len, char fill = 'a') {
	std::string s(len, fill);
	return String(s.c_str(), len);
}

// =============================================================================
// 1. Construction & Destruction
// =============================================================================

class StringConstructionTest : public ::testing::Test {};

TEST_F(StringConstructionTest, DefaultConstructor) {
	String s;
	EXPECT_EQ(s.length(), 0);
	EXPECT_TRUE(s.isEmpty());
	EXPECT_STREQ(s.toCharArray(), "");
}

TEST_F(StringConstructionTest, CStringConstructor) {
	String s("hello");
	EXPECT_EQ(s.length(), 5);
	EXPECT_STREQ(s.toCharArray(), "hello");
}

TEST_F(StringConstructionTest, CStringWithLengthConstructor) {
	String s("hello world", 5);
	EXPECT_EQ(s.length(), 5);
	EXPECT_STREQ(s.toCharArray(), "hello");
}

TEST_F(StringConstructionTest, CStringWithZeroLength) {
	String s("hello", 0);
	EXPECT_EQ(s.length(), 0);
	EXPECT_TRUE(s.isEmpty());
}

TEST_F(StringConstructionTest, CopyConstructor) {
	String original("test string");
	String copy(original);
	EXPECT_EQ(copy.length(), original.length());
	EXPECT_STREQ(copy.toCharArray(), original.toCharArray());
	// Verify independence - modifying copy doesn't affect original
	copy = "modified";
	EXPECT_STREQ(original.toCharArray(), "test string");
}

TEST_F(StringConstructionTest, MoveConstructor) {
	String original("this is a longer string for heap allocation test");
	const char* content = original.toCharArray();
	int len = original.length();
	String moved(std::move(original));
	EXPECT_EQ(moved.length(), len);
	EXPECT_STREQ(moved.toCharArray(), "this is a longer string for heap allocation test");
}

TEST_F(StringConstructionTest, StdStringConstructor) {
	std::string stdStr("from std::string");
	String s(stdStr);
	EXPECT_STREQ(s.toCharArray(), "from std::string");
	EXPECT_EQ(s.length(), (int)stdStr.length());
}

TEST_F(StringConstructionTest, NullPointerThrows) {
	EXPECT_THROW(String s(nullptr), IllegalArgumentException);
}

TEST_F(StringConstructionTest, SSOBoundaryExact) {
	// String at SSO_SIZE - 1 should use SSO
	String ssoStr = makeString(SSO_SIZE - 1);
	EXPECT_EQ(ssoStr.length(), SSO_SIZE - 1);

	// String at SSO_SIZE should use heap
	String heapStr = makeString(SSO_SIZE);
	EXPECT_EQ(heapStr.length(), SSO_SIZE);

	// String at SSO_SIZE + 1 should use heap
	String heapStr2 = makeString(SSO_SIZE + 1);
	EXPECT_EQ(heapStr2.length(), SSO_SIZE + 1);
}

// =============================================================================
// 2. Assignment Operators
// =============================================================================

class StringAssignmentTest : public ::testing::Test {};

TEST_F(StringAssignmentTest, AssignCString) {
	String s;
	s = "assigned";
	EXPECT_STREQ(s.toCharArray(), "assigned");
	EXPECT_EQ(s.length(), 8);
}

TEST_F(StringAssignmentTest, AssignCStringReplacesOld) {
	String s("original");
	s = "replaced";
	EXPECT_STREQ(s.toCharArray(), "replaced");
}

TEST_F(StringAssignmentTest, CopyAssignment) {
	String a("source");
	String b;
	b = a;
	EXPECT_STREQ(b.toCharArray(), "source");
	EXPECT_EQ(b.length(), a.length());
}

TEST_F(StringAssignmentTest, SelfAssignment) {
	String s("self");
	String& ref = s;
	s = ref;
	EXPECT_STREQ(s.toCharArray(), "self");
}

TEST_F(StringAssignmentTest, MoveAssignment) {
	String a("this is a long string to ensure heap allocation");
	String b;
	b = std::move(a);
	EXPECT_STREQ(b.toCharArray(), "this is a long string to ensure heap allocation");
}

TEST_F(StringAssignmentTest, MoveAssignmentSelf) {
	String s("self move");
	String& ref = s;
	s = std::move(ref);
	EXPECT_STREQ(s.toCharArray(), "self move");
}

TEST_F(StringAssignmentTest, AssignStdString) {
	std::string stdStr("from std");
	String s;
	s = stdStr;
	EXPECT_STREQ(s.toCharArray(), "from std");
}

TEST_F(StringAssignmentTest, SSOToHeapTransition) {
	String s("short"); // SSO
	s = "this is a much longer string that exceeds SSO buffer size"; // heap
	EXPECT_STREQ(s.toCharArray(), "this is a much longer string that exceeds SSO buffer size");
}

TEST_F(StringAssignmentTest, HeapToSSOTransition) {
	String s("this is a much longer string that exceeds SSO buffer size"); // heap
	s = "short"; // back to SSO
	EXPECT_STREQ(s.toCharArray(), "short");
}

// =============================================================================
// 3. Comparison
// =============================================================================

class StringComparisonTest : public ::testing::Test {};

TEST_F(StringComparisonTest, EqualStrings) {
	String a("hello");
	String b("hello");
	EXPECT_TRUE(a == b);
	EXPECT_TRUE(a == "hello");
	EXPECT_FALSE(a != b);
}

TEST_F(StringComparisonTest, UnequalStrings) {
	String a("hello");
	String b("world");
	EXPECT_TRUE(a != b);
	EXPECT_FALSE(a == b);
}

TEST_F(StringComparisonTest, EmptyStringComparison) {
	String empty1;
	String empty2("");
	EXPECT_TRUE(empty1 == empty2);
	EXPECT_TRUE(empty1 == "");
}

TEST_F(StringComparisonTest, CaseSensitivity) {
	String lower("hello");
	String upper("Hello");
	EXPECT_TRUE(lower != upper);
}

// Note: String::compareTo uses strcmp(str, begin()) — argument order is reversed
// so compareTo returns positive when the argument is lexicographically greater than this
TEST_F(StringComparisonTest, CompareToOrdering) {
	String s("beta");
	// strcmp("alpha", "beta") < 0, so compareTo("alpha") < 0
	EXPECT_LT(s.compareTo("alpha"), 0);
	EXPECT_EQ(s.compareTo("beta"), 0);
	// strcmp("gamma", "beta") > 0, so compareTo("gamma") > 0
	EXPECT_GT(s.compareTo("gamma"), 0);
}

TEST_F(StringComparisonTest, LessThanOperator) {
	String a("apple");
	String b("banana");
	// operator< uses compareTo(str) < 0
	// compareTo calls strcmp(str, begin()), so for a < b:
	// strcmp("banana", "apple") > 0, so compareTo > 0, so a < b is false in this implementation
	// Let's just test what the operator actually returns
	// Actually: a.operator<("banana") => a.compareTo("banana") < 0
	// a.compareTo("banana") = strcmp("banana", "apple") > 0
	// so a < "banana" is FALSE with this implementation
	// This means operator< is reversed from standard lexicographic ordering
	EXPECT_FALSE(a < b);
	EXPECT_TRUE(b < a);
}

TEST_F(StringComparisonTest, GreaterThanOperator) {
	String a("apple");
	String b("banana");
	// Similarly reversed
	EXPECT_TRUE(a > b);
	EXPECT_FALSE(b > a);
}

TEST_F(StringComparisonTest, FriendEqualityCStringLeft) {
	String s("test");
	EXPECT_TRUE("test" == s);
	EXPECT_FALSE("other" == s);
}

TEST_F(StringComparisonTest, FriendEqualityChar) {
	String s("x");
	EXPECT_TRUE('x' == s);
	EXPECT_TRUE(s == 'x');
	EXPECT_FALSE('y' == s);
}

TEST_F(StringComparisonTest, FriendInequalityCStringLeft) {
	String s("test");
	EXPECT_TRUE("other" != s);
	EXPECT_FALSE("test" != s);
}

TEST_F(StringComparisonTest, FriendInequalityChar) {
	String s("x");
	EXPECT_TRUE('y' != s);
	EXPECT_FALSE('x' != s);
	EXPECT_TRUE(s != 'y');
	EXPECT_FALSE(s != 'x');
}

TEST_F(StringComparisonTest, HeapStringEquality) {
	String a = makeString(SSO_SIZE + 10, 'z');
	String b = makeString(SSO_SIZE + 10, 'z');
	EXPECT_TRUE(a == b);
}

// =============================================================================
// 4. indexOf
// =============================================================================

class StringIndexOfTest : public ::testing::Test {};

TEST_F(StringIndexOfTest, IndexOfCharFound) {
	String s("hello world");
	EXPECT_EQ(s.indexOf('h'), 0);
	EXPECT_EQ(s.indexOf('o'), 4);
	EXPECT_EQ(s.indexOf('d'), 10);
}

TEST_F(StringIndexOfTest, IndexOfCharNotFound) {
	String s("hello");
	EXPECT_EQ(s.indexOf('z'), NPOS);
}

TEST_F(StringIndexOfTest, IndexOfCharFromIndex) {
	String s("hello world");
	EXPECT_EQ(s.indexOf('o', 0), 4);
	EXPECT_EQ(s.indexOf('o', 5), 7);
}

TEST_F(StringIndexOfTest, IndexOfCharFromIndexOutOfBounds) {
	String s("hello");
	EXPECT_EQ(s.indexOf('h', -1), NPOS);
	EXPECT_EQ(s.indexOf('h', 5), NPOS);
	EXPECT_EQ(s.indexOf('h', 100), NPOS);
}

TEST_F(StringIndexOfTest, IndexOfCString) {
	String s("hello world");
	EXPECT_EQ(s.indexOf("world"), 6);
	EXPECT_EQ(s.indexOf("hello"), 0);
	EXPECT_EQ(s.indexOf("xyz"), NPOS);
}

TEST_F(StringIndexOfTest, IndexOfCStringFromIndex) {
	String s("hello hello");
	EXPECT_EQ(s.indexOf("hello", 0), 0);
	EXPECT_EQ(s.indexOf("hello", 1), 6);
}

TEST_F(StringIndexOfTest, IndexOfString) {
	String s("the quick brown fox");
	String sub("quick");
	EXPECT_EQ(s.indexOf(sub), 4);
}

TEST_F(StringIndexOfTest, IndexOfStringFromIndex) {
	String s("abcabc");
	String sub("abc");
	EXPECT_EQ(s.indexOf(sub, 0), 0);
	EXPECT_EQ(s.indexOf(sub, 1), 3);
}

TEST_F(StringIndexOfTest, IndexOfEmptyStringInEmpty) {
	String s("");
	EXPECT_EQ(s.indexOf("test"), NPOS);
}

// =============================================================================
// 5. lastIndexOf
// =============================================================================

class StringLastIndexOfTest : public ::testing::Test {};

TEST_F(StringLastIndexOfTest, LastIndexOfChar) {
	String s("hello world");
	EXPECT_EQ(s.lastIndexOf('o'), 7);
	EXPECT_EQ(s.lastIndexOf('h'), 0);
}

TEST_F(StringLastIndexOfTest, LastIndexOfCharNotFound) {
	String s("hello");
	EXPECT_EQ(s.lastIndexOf('z'), NPOS);
}

TEST_F(StringLastIndexOfTest, LastIndexOfCharFromIndex) {
	String s("aXbXcX");
	// lastIndexOf(char, fromIndex) searches from fromIndex to end using strrchr
	EXPECT_EQ(s.lastIndexOf('X', 0), 5);
	EXPECT_EQ(s.lastIndexOf('X', 4), 5);
}

TEST_F(StringLastIndexOfTest, LastIndexOfCString) {
	String s("abcabcabc");
	EXPECT_EQ(s.lastIndexOf("abc"), 6);
}

TEST_F(StringLastIndexOfTest, LastIndexOfCStringNotFound) {
	String s("hello");
	EXPECT_EQ(s.lastIndexOf("xyz"), NPOS);
}

TEST_F(StringLastIndexOfTest, LastIndexOfString) {
	String s("test test test");
	String sub("test");
	EXPECT_EQ(s.lastIndexOf(sub), 10);
}

TEST_F(StringLastIndexOfTest, LastIndexOfSingleCharString) {
	String s("x");
	EXPECT_EQ(s.lastIndexOf('x'), 0);
	EXPECT_EQ(s.lastIndexOf("x"), 0);
}

// =============================================================================
// 6. Boolean Search (contains, beginsWith, endsWith)
// =============================================================================

class StringBooleanSearchTest : public ::testing::Test {};

TEST_F(StringBooleanSearchTest, ContainsCString) {
	String s("hello world");
	EXPECT_TRUE(s.contains("hello"));
	EXPECT_TRUE(s.contains("world"));
	EXPECT_TRUE(s.contains("lo wo"));
	EXPECT_FALSE(s.contains("xyz"));
}

TEST_F(StringBooleanSearchTest, ContainsString) {
	String s("hello world");
	String sub("world");
	EXPECT_TRUE(s.contains(sub));
	String absent("xyz");
	EXPECT_FALSE(s.contains(absent));
}

TEST_F(StringBooleanSearchTest, BeginsWithCString) {
	String s("hello world");
	EXPECT_TRUE(s.beginsWith("hello"));
	EXPECT_TRUE(s.beginsWith("h"));
	EXPECT_FALSE(s.beginsWith("world"));
	EXPECT_FALSE(s.beginsWith("xyz"));
}

TEST_F(StringBooleanSearchTest, BeginsWithString) {
	String s("hello world");
	String prefix("hello");
	EXPECT_TRUE(s.beginsWith(prefix));
	String notPrefix("world");
	EXPECT_FALSE(s.beginsWith(notPrefix));
}

TEST_F(StringBooleanSearchTest, EndsWithCString) {
	String s("hello world");
	EXPECT_TRUE(s.endsWith("world"));
	EXPECT_TRUE(s.endsWith("d"));
	EXPECT_FALSE(s.endsWith("hello"));
}

TEST_F(StringBooleanSearchTest, EndsWithString) {
	String s("hello world");
	String suffix("world");
	EXPECT_TRUE(s.endsWith(suffix));
	String notSuffix("hello");
	EXPECT_FALSE(s.endsWith(notSuffix));
}

TEST_F(StringBooleanSearchTest, BeginsWithFullString) {
	String s("exact");
	EXPECT_TRUE(s.beginsWith("exact"));
}

TEST_F(StringBooleanSearchTest, EndsWithFullString) {
	String s("exact");
	EXPECT_TRUE(s.endsWith("exact"));
}

TEST_F(StringBooleanSearchTest, EndsWithLargerString) {
	String s("exact");
	EXPECT_FALSE(s.endsWith("exact1"));
}

// =============================================================================
// 7. Concatenation
// =============================================================================

class StringConcatTest : public ::testing::Test {};

TEST_F(StringConcatTest, ConcatChar) {
	String s("hello");
	String result = s.concat('!');
	EXPECT_STREQ(result.toCharArray(), "hello!");
	EXPECT_STREQ(s.toCharArray(), "hello"); // original unchanged
}

TEST_F(StringConcatTest, ConcatInt) {
	String s("value: ");
	String result = s.concat(42);
	EXPECT_STREQ(result.toCharArray(), "value: 42");
}

TEST_F(StringConcatTest, ConcatCString) {
	String s("hello ");
	String result = s.concat("world");
	EXPECT_STREQ(result.toCharArray(), "hello world");
}

TEST_F(StringConcatTest, ConcatCStringWithLength) {
	String s("hello ");
	String result = s.concat("world!!!", 5);
	EXPECT_STREQ(result.toCharArray(), "hello world");
}

TEST_F(StringConcatTest, ConcatString) {
	String a("hello ");
	String b("world");
	String result = a.concat(b);
	EXPECT_STREQ(result.toCharArray(), "hello world");
}

TEST_F(StringConcatTest, ConcatEmpty) {
	String s("hello");
	String result = s.concat("");
	EXPECT_STREQ(result.toCharArray(), "hello");
}

TEST_F(StringConcatTest, ConcatToEmpty) {
	String s;
	String result = s.concat("hello");
	EXPECT_STREQ(result.toCharArray(), "hello");
}

TEST_F(StringConcatTest, OperatorPlusStringString) {
	String a("hello ");
	String b("world");
	String result = a + b;
	EXPECT_STREQ(result.toCharArray(), "hello world");
}

TEST_F(StringConcatTest, OperatorPlusCStringString) {
	String b("world");
	String result = "hello " + b;
	EXPECT_STREQ(result.toCharArray(), "hello world");
}

TEST_F(StringConcatTest, OperatorPlusStringCString) {
	String a("hello ");
	String result = a + "world";
	EXPECT_STREQ(result.toCharArray(), "hello world");
}

TEST_F(StringConcatTest, OperatorPlusStringChar) {
	String s("hello");
	String result = s + '!';
	EXPECT_STREQ(result.toCharArray(), "hello!");
}

TEST_F(StringConcatTest, OperatorPlusCharString) {
	String s("ello");
	String result = 'h' + s;
	EXPECT_STREQ(result.toCharArray(), "hello");
}

TEST_F(StringConcatTest, OperatorPlusStringInt) {
	String s("count: ");
	String result = s + 99;
	EXPECT_STREQ(result.toCharArray(), "count: 99");
}

TEST_F(StringConcatTest, PlusEqualsChar) {
	String s("abc");
	s += 'd';
	EXPECT_STREQ(s.toCharArray(), "abcd");
	EXPECT_EQ(s.length(), 4);
}

TEST_F(StringConcatTest, PlusEqualsCString) {
	String s("hello");
	s += " world";
	EXPECT_STREQ(s.toCharArray(), "hello world");
}

TEST_F(StringConcatTest, PlusEqualsString) {
	String s("hello");
	String suffix(" world");
	s += suffix;
	EXPECT_STREQ(s.toCharArray(), "hello world");
}

TEST_F(StringConcatTest, PlusEqualsSSOToHeap) {
	String s("ab"); // SSO
	// Grow past SSO boundary
	for (int i = 0; i < SSO_SIZE + 5; ++i) {
		s += 'x';
	}
	EXPECT_EQ(s.length(), 2 + SSO_SIZE + 5);
	EXPECT_STREQ(s.toCharArray() + 2, makeString(SSO_SIZE + 5, 'x').toCharArray());
}

TEST_F(StringConcatTest, ConcatSSOToHeapGrowth) {
	String s = makeString(SSO_SIZE - 2); // SSO
	String result = s.concat("xxxx"); // pushes past SSO
	EXPECT_EQ(result.length(), SSO_SIZE + 2);
}

// =============================================================================
// 8. Substring
// =============================================================================

class StringSubStringTest : public ::testing::Test {};

TEST_F(StringSubStringTest, SubStringToEnd) {
	String s("hello world");
	String sub = s.subString(6);
	EXPECT_STREQ(sub.toCharArray(), "world");
}

TEST_F(StringSubStringTest, SubStringRange) {
	String s("hello world");
	String sub = s.subString(0, 5);
	EXPECT_STREQ(sub.toCharArray(), "hello");
}

TEST_F(StringSubStringTest, SubStringMiddle) {
	String s("hello world");
	String sub = s.subString(3, 8);
	EXPECT_STREQ(sub.toCharArray(), "lo wo");
}

TEST_F(StringSubStringTest, SubStringEqualIndices) {
	String s("hello");
	String sub = s.subString(2, 2);
	EXPECT_TRUE(sub.isEmpty());
	EXPECT_STREQ(sub.toCharArray(), "");
}

TEST_F(StringSubStringTest, SubStringSingleChar) {
	String s("hello");
	String sub = s.subString(1, 2);
	EXPECT_STREQ(sub.toCharArray(), "e");
}

TEST_F(StringSubStringTest, SubStringBeginOutOfBounds) {
	String s("hello");
	EXPECT_THROW(s.subString(-1), ArrayIndexOutOfBoundsException);
	EXPECT_THROW(s.subString(5), ArrayIndexOutOfBoundsException);
}

TEST_F(StringSubStringTest, SubStringEndOutOfBounds) {
	String s("hello");
	EXPECT_THROW(s.subString(0, 6), ArrayIndexOutOfBoundsException);
	EXPECT_THROW(s.subString(0, -1), ArrayIndexOutOfBoundsException);
}

TEST_F(StringSubStringTest, SubStringBeginGreaterThanEnd) {
	String s("hello");
	EXPECT_THROW(s.subString(3, 1), ArrayIndexOutOfBoundsException);
}

// =============================================================================
// 9. Case Conversion
// =============================================================================

class StringCaseTest : public ::testing::Test {};

TEST_F(StringCaseTest, ToLowerCase) {
	String s("Hello WORLD");
	String lower = s.toLowerCase();
	EXPECT_STREQ(lower.toCharArray(), "hello world");
	EXPECT_STREQ(s.toCharArray(), "Hello WORLD"); // original unchanged
}

TEST_F(StringCaseTest, ToUpperCase) {
	String s("Hello world");
	String upper = s.toUpperCase();
	EXPECT_STREQ(upper.toCharArray(), "HELLO WORLD");
	EXPECT_STREQ(s.toCharArray(), "Hello world"); // original unchanged
}

TEST_F(StringCaseTest, ChangeToLowerCaseInPlace) {
	String s("Hello WORLD");
	s.changeToLowerCase();
	EXPECT_STREQ(s.toCharArray(), "hello world");
}

TEST_F(StringCaseTest, ChangeToUpperCaseInPlace) {
	String s("Hello world");
	s.changeToUpperCase();
	EXPECT_STREQ(s.toCharArray(), "HELLO WORLD");
}

TEST_F(StringCaseTest, AlreadyLowerCase) {
	String s("hello");
	String lower = s.toLowerCase();
	EXPECT_STREQ(lower.toCharArray(), "hello");
}

TEST_F(StringCaseTest, AlreadyUpperCase) {
	String s("HELLO");
	String upper = s.toUpperCase();
	EXPECT_STREQ(upper.toCharArray(), "HELLO");
}

TEST_F(StringCaseTest, NonAlphabeticUnchanged) {
	String s("123!@#");
	String lower = s.toLowerCase();
	String upper = s.toUpperCase();
	EXPECT_STREQ(lower.toCharArray(), "123!@#");
	EXPECT_STREQ(upper.toCharArray(), "123!@#");
}

TEST_F(StringCaseTest, MixedContentCase) {
	String s("Test123Value");
	EXPECT_STREQ(s.toLowerCase().toCharArray(), "test123value");
	EXPECT_STREQ(s.toUpperCase().toCharArray(), "TEST123VALUE");
}

// =============================================================================
// 10. Trim
// =============================================================================

class StringTrimTest : public ::testing::Test {};

TEST_F(StringTrimTest, TrimLeadingSpaces) {
	String s("   hello");
	EXPECT_STREQ(s.trim().toCharArray(), "hello");
}

TEST_F(StringTrimTest, TrimTrailingSpaces) {
	String s("hello   ");
	EXPECT_STREQ(s.trim().toCharArray(), "hello");
}

TEST_F(StringTrimTest, TrimBothSides) {
	String s("   hello   ");
	EXPECT_STREQ(s.trim().toCharArray(), "hello");
}

TEST_F(StringTrimTest, TrimTabs) {
	String s("\thello\t");
	EXPECT_STREQ(s.trim().toCharArray(), "hello");
}

TEST_F(StringTrimTest, TrimNewlines) {
	String s("\nhello\n");
	EXPECT_STREQ(s.trim().toCharArray(), "hello");
}

TEST_F(StringTrimTest, TrimCarriageReturn) {
	String s("\rhello\r");
	EXPECT_STREQ(s.trim().toCharArray(), "hello");
}

TEST_F(StringTrimTest, TrimFormFeed) {
	String s("\fhello\f");
	EXPECT_STREQ(s.trim().toCharArray(), "hello");
}

TEST_F(StringTrimTest, TrimMixedWhitespace) {
	String s(" \t\n\r\fhello \t\n\r\f");
	EXPECT_STREQ(s.trim().toCharArray(), "hello");
}

TEST_F(StringTrimTest, TrimAllWhitespace) {
	String s("   \t\n\r  ");
	String trimmed = s.trim();
	EXPECT_TRUE(trimmed.isEmpty());
}

TEST_F(StringTrimTest, TrimNoWhitespace) {
	String s("hello");
	EXPECT_STREQ(s.trim().toCharArray(), "hello");
}

TEST_F(StringTrimTest, TrimInternalWhitespacePreserved) {
	String s("  hello   world  ");
	EXPECT_STREQ(s.trim().toCharArray(), "hello   world");
}

TEST_F(StringTrimTest, TrimOriginalUnchanged) {
	String s("  hello  ");
	String trimmed = s.trim();
	EXPECT_STREQ(s.toCharArray(), "  hello  ");
	EXPECT_STREQ(trimmed.toCharArray(), "hello");
}

// =============================================================================
// 11. Escape String
// =============================================================================

class StringEscapeTest : public ::testing::Test {};

TEST_F(StringEscapeTest, EscapeNewline) {
	String s("line1\nline2");
	String escaped = s.escapeString();
	EXPECT_STREQ(escaped.toCharArray(), "line1\\nline2");
}

TEST_F(StringEscapeTest, EscapeCarriageReturn) {
	String s("line1\rline2");
	String escaped = s.escapeString();
	EXPECT_STREQ(escaped.toCharArray(), "line1\\rline2");
}

TEST_F(StringEscapeTest, EscapeBackslash) {
	String s("path\\to\\file");
	String escaped = s.escapeString();
	EXPECT_STREQ(escaped.toCharArray(), "path\\\\to\\\\file");
}

TEST_F(StringEscapeTest, EscapeDoubleQuote) {
	String s("say \"hello\"");
	String escaped = s.escapeString();
	EXPECT_STREQ(escaped.toCharArray(), "say \\\"hello\\\"");
}

TEST_F(StringEscapeTest, EscapeSingleQuote) {
	String s("it's");
	String escaped = s.escapeString();
	EXPECT_STREQ(escaped.toCharArray(), "it\\'s");
}

TEST_F(StringEscapeTest, EscapeNormalCharsUnchanged) {
	String s("hello world 123");
	String escaped = s.escapeString();
	EXPECT_STREQ(escaped.toCharArray(), "hello world 123");
}

TEST_F(StringEscapeTest, EscapeEmptyString) {
	String s;
	String escaped = s.escapeString();
	EXPECT_TRUE(escaped.isEmpty());
}

TEST_F(StringEscapeTest, EscapeMultipleSpecialChars) {
	String s("a\"b\\c\nd");
	String escaped = s.escapeString();
	EXPECT_STREQ(escaped.toCharArray(), "a\\\"b\\\\c\\nd");
}

// =============================================================================
// 12. valueOf (Type Conversions)
// =============================================================================

class StringValueOfTest : public ::testing::Test {};

TEST_F(StringValueOfTest, ValueOfIntPositive) {
	EXPECT_STREQ(String::valueOf(42).toCharArray(), "42");
}

TEST_F(StringValueOfTest, ValueOfIntNegative) {
	EXPECT_STREQ(String::valueOf(-42).toCharArray(), "-42");
}

TEST_F(StringValueOfTest, ValueOfIntZero) {
	EXPECT_STREQ(String::valueOf(0).toCharArray(), "0");
}

TEST_F(StringValueOfTest, ValueOfUint32) {
	EXPECT_STREQ(String::valueOf((uint32)4294967295U).toCharArray(), "4294967295");
}

TEST_F(StringValueOfTest, ValueOfInt64) {
	int64 val = 9223372036854775807LL;
	String result = String::valueOf(val);
	EXPECT_TRUE(result.contains("9223372036854775807"));
}

TEST_F(StringValueOfTest, ValueOfUint64) {
	uint64 val = 18446744073709551615ULL;
	String result = String::valueOf(val);
	EXPECT_TRUE(result.contains("18446744073709551615"));
}

TEST_F(StringValueOfTest, ValueOfFloat) {
	String result = String::valueOf(3.14f);
	EXPECT_TRUE(result.contains("3.14"));
}

TEST_F(StringValueOfTest, ValueOfFloatWithPrecision) {
	String result = String::valueOf(3.14159f, 2);
	EXPECT_STREQ(result.toCharArray(), "3.14");
}

TEST_F(StringValueOfTest, ValueOfDouble) {
	String result = String::valueOf(2.718281828);
	EXPECT_TRUE(result.contains("2.71828"));
}

TEST_F(StringValueOfTest, ValueOfBoolTrue) {
	EXPECT_STREQ(String::valueOf(true).toCharArray(), "true");
}

TEST_F(StringValueOfTest, ValueOfBoolFalse) {
	EXPECT_STREQ(String::valueOf(false).toCharArray(), "false");
}

TEST_F(StringValueOfTest, ValueOfCString) {
	EXPECT_STREQ(String::valueOf("test").toCharArray(), "test");
}

TEST_F(StringValueOfTest, ValueOfStringReference) {
	String original("test");
	const String& ref = String::valueOf(original);
	EXPECT_EQ(&ref, &original); // should return same reference
}

// =============================================================================
// 13. hexvalueOf & withCommas
// =============================================================================

class StringHexValueOfTest : public ::testing::Test {};

TEST_F(StringHexValueOfTest, HexInt) {
	EXPECT_STREQ(String::hexvalueOf(255).toCharArray(), "ff");
	EXPECT_STREQ(String::hexvalueOf(16).toCharArray(), "10");
	EXPECT_STREQ(String::hexvalueOf(0).toCharArray(), "0");
}

TEST_F(StringHexValueOfTest, HexUint32) {
	EXPECT_STREQ(String::hexvalueOf((uint32)0xDEADBEEF).toCharArray(), "deadbeef");
}

TEST_F(StringHexValueOfTest, HexInt64) {
	EXPECT_STREQ(String::hexvalueOf((int64)0xFF).toCharArray(), "ff");
}

TEST_F(StringHexValueOfTest, HexUint64) {
	EXPECT_STREQ(String::hexvalueOf((uint64)0xCAFEBABE).toCharArray(), "cafebabe");
}

class StringWithCommasTest : public ::testing::Test {};

TEST_F(StringWithCommasTest, WithCommasInt) {
	EXPECT_STREQ(String::withCommas(1000).toCharArray(), "1,000");
	EXPECT_STREQ(String::withCommas(1000000).toCharArray(), "1,000,000");
	EXPECT_STREQ(String::withCommas(999).toCharArray(), "999");
	EXPECT_STREQ(String::withCommas(0).toCharArray(), "0");
}

TEST_F(StringWithCommasTest, WithCommasNegative) {
	EXPECT_STREQ(String::withCommas(-1000).toCharArray(), "-1,000");
	EXPECT_STREQ(String::withCommas(-1000000).toCharArray(), "-1,000,000");
}

TEST_F(StringWithCommasTest, WithCommasUint64) {
	EXPECT_STREQ(String::withCommas((uint64)1234567890).toCharArray(), "1,234,567,890");
}

TEST_F(StringWithCommasTest, WithCommasInt64) {
	EXPECT_STREQ(String::withCommas((int64)1234567890).toCharArray(), "1,234,567,890");
	EXPECT_STREQ(String::withCommas((int64)-1234567890).toCharArray(), "-1,234,567,890");
}

// =============================================================================
// 14. Hash Code
// =============================================================================

class StringHashCodeTest : public ::testing::Test {};

TEST_F(StringHashCodeTest, InstanceHashEqualsStaticHash) {
	String s("test hash");
	EXPECT_EQ(s.hashCode(), String::hashCode("test hash"));
}

TEST_F(StringHashCodeTest, EqualStringsEqualHash) {
	String a("same");
	String b("same");
	EXPECT_EQ(a.hashCode(), b.hashCode());
}

TEST_F(StringHashCodeTest, StaticHashOfString) {
	String s("hello");
	EXPECT_EQ(String::hashCode(s), s.hashCode());
}

TEST_F(StringHashCodeTest, HashCodeConsistency) {
	String s("consistent");
	uint32 hash1 = s.hashCode();
	uint32 hash2 = s.hashCode();
	EXPECT_EQ(hash1, hash2);
}

TEST_F(StringHashCodeTest, CompileTimeHashMacro) {
	constexpr uint32 compiletime = STRING_HASHCODE("test");
	uint32 runtime = String::hashCode("test");
	EXPECT_EQ(compiletime, runtime);
}

TEST_F(StringHashCodeTest, HashCodeLiteralOperator) {
	constexpr uint32 literal = "test"_hashCode;
	uint32 runtime = String::hashCode("test");
	EXPECT_EQ(literal, runtime);
}

TEST_F(StringHashCodeTest, EmptyStringHash) {
	String s;
	uint32 hash = s.hashCode();
	EXPECT_EQ(hash, String::hashCode(""));
}

TEST_F(StringHashCodeTest, DifferentStringsDifferentHash) {
	// Not guaranteed in general, but for these specific strings it should hold
	String a("hello");
	String b("world");
	EXPECT_NE(a.hashCode(), b.hashCode());
}

// =============================================================================
// 15. Element Access & Bounds Checking
// =============================================================================

class StringAccessTest : public ::testing::Test {};

TEST_F(StringAccessTest, CharAtValid) {
	String s("hello");
	EXPECT_EQ(s.charAt(0), 'h');
	EXPECT_EQ(s.charAt(4), 'o');
}

TEST_F(StringAccessTest, CharAtOutOfBounds) {
	String s("hello");
	EXPECT_THROW(s.charAt(-1), ArrayIndexOutOfBoundsException);
	EXPECT_THROW(s.charAt(5), ArrayIndexOutOfBoundsException);
}

TEST_F(StringAccessTest, OperatorBracketRead) {
	String s("hello");
	EXPECT_EQ(s[0], 'h');
	EXPECT_EQ(s[4], 'o');
}

TEST_F(StringAccessTest, OperatorBracketOutOfBounds) {
	String s("hello");
	EXPECT_THROW(s[-1], ArrayIndexOutOfBoundsException);
	EXPECT_THROW(s[5], ArrayIndexOutOfBoundsException);
}

TEST_F(StringAccessTest, OperatorBracketMutable) {
	String s("hello");
	s[0] = 'H';
	EXPECT_STREQ(s.toCharArray(), "Hello");
}

TEST_F(StringAccessTest, ToCharArrayNullTerminated) {
	String s("test");
	const char* arr = s.toCharArray();
	EXPECT_EQ(arr[4], '\0');
}

TEST_F(StringAccessTest, BeginEndIterators) {
	String s("hello");
	EXPECT_EQ(s.end() - s.begin(), s.length());
}

TEST_F(StringAccessTest, IsEmpty) {
	String empty;
	String notEmpty("x");
	EXPECT_TRUE(empty.isEmpty());
	EXPECT_FALSE(notEmpty.isEmpty());
}

TEST_F(StringAccessTest, Length) {
	EXPECT_EQ(String().length(), 0);
	EXPECT_EQ(String("").length(), 0);
	EXPECT_EQ(String("a").length(), 1);
	EXPECT_EQ(String("hello").length(), 5);
}

TEST_F(StringAccessTest, LengthHeapString) {
	String s = makeString(SSO_SIZE + 10);
	EXPECT_EQ(s.length(), SSO_SIZE + 10);
}

// =============================================================================
// 16. Regex Operations
// =============================================================================

class StringRegexTest : public ::testing::Test {};

TEST_F(StringRegexTest, ReplaceFirstMatch) {
	String s("hello world");
	String result = s.replaceFirst("world", "there");
	EXPECT_STREQ(result.toCharArray(), "hello there");
}

TEST_F(StringRegexTest, ReplaceFirstNoMatch) {
	String s("hello world");
	String result = s.replaceFirst("xyz", "there");
	EXPECT_STREQ(result.toCharArray(), "hello world");
}

TEST_F(StringRegexTest, ReplaceFirstAtBeginning) {
	String s("hello world");
	String result = s.replaceFirst("hello", "goodbye");
	EXPECT_STREQ(result.toCharArray(), "goodbye world");
}

TEST_F(StringRegexTest, ReplaceFirstAtEnd) {
	String s("hello world");
	String result = s.replaceFirst("world", "earth");
	EXPECT_STREQ(result.toCharArray(), "hello earth");
}

TEST_F(StringRegexTest, ReplaceFirstEntireString) {
	String s("hello");
	String result = s.replaceFirst("hello", "goodbye");
	EXPECT_STREQ(result.toCharArray(), "goodbye");
}

TEST_F(StringRegexTest, ReplaceFirstRegexPattern) {
	String s("testing\nstuff");
	String result = s.replaceFirst("\n|\r", " ");
	EXPECT_STREQ(result.toCharArray(), "testing stuff");
}

TEST_F(StringRegexTest, ReplaceAllMultipleMatches) {
	String s("a#b#c#d");
	String result = s.replaceAll("#", "-");
	EXPECT_STREQ(result.toCharArray(), "a-b-c-d");
}

TEST_F(StringRegexTest, RegexIndexOfFound) {
	String s("hello 123 world");
	int pos = s.regexIndexOf("[0-9]+");
	EXPECT_EQ(pos, 6);
}

TEST_F(StringRegexTest, RegexIndexOfNotFound) {
	String s("hello world");
	int pos = s.regexIndexOf("[0-9]+");
	EXPECT_EQ(pos, NPOS);
}

// =============================================================================
// 17. Serialization (toString / parseFromString)
// =============================================================================

class StringSerializationTest : public ::testing::Test {};

TEST_F(StringSerializationTest, ToStringWrapsInQuotes) {
	String s("hello");
	String output;
	s.toString(output);
	EXPECT_TRUE(output.beginsWith("\""));
	EXPECT_TRUE(output.endsWith("\""));
}

TEST_F(StringSerializationTest, RoundTrip) {
	String original("hello world");
	String serialized;
	original.toString(serialized);

	String recovered;
	EXPECT_TRUE(recovered.parseFromString(serialized));
	EXPECT_STREQ(recovered.toCharArray(), original.toCharArray());
}

TEST_F(StringSerializationTest, RoundTripWithSpecialChars) {
	String original("path\\to\\file");
	String serialized;
	original.toString(serialized);

	String recovered;
	EXPECT_TRUE(recovered.parseFromString(serialized));
	EXPECT_STREQ(recovered.toCharArray(), original.toCharArray());
}

TEST_F(StringSerializationTest, ParseFromStringTooShort) {
	String s("x"); // length < 2
	String result;
	EXPECT_FALSE(result.parseFromString(s));
}

TEST_F(StringSerializationTest, ParseFromStringSingleChar) {
	String s("a");
	String result;
	EXPECT_FALSE(result.parseFromString(s));
}

// =============================================================================
// 18. std::string Interop
// =============================================================================

class StringInteropTest : public ::testing::Test {};

TEST_F(StringInteropTest, ImplicitStdStringConversion) {
	String s("hello");
	std::string stdStr = s;
	EXPECT_EQ(stdStr, "hello");
}

TEST_F(StringInteropTest, RoundTripStdString) {
	std::string original("test data");
	String engineStr(original);
	std::string backToStd = engineStr;
	EXPECT_EQ(original, backToStd);
}

TEST_F(StringInteropTest, EmptyStringInterop) {
	String s;
	std::string stdStr = s;
	EXPECT_TRUE(stdStr.empty());
}

// =============================================================================
// 19. String::format
// =============================================================================

class StringFormatTest : public ::testing::Test {};

TEST_F(StringFormatTest, FormatInt) {
	String result = String::format("value: %d", 42);
	EXPECT_STREQ(result.toCharArray(), "value: 42");
}

TEST_F(StringFormatTest, FormatString) {
	String result = String::format("hello %s", "world");
	EXPECT_STREQ(result.toCharArray(), "hello world");
}

TEST_F(StringFormatTest, FormatFloat) {
	String result = String::format("pi: %.2f", 3.14159);
	EXPECT_STREQ(result.toCharArray(), "pi: 3.14");
}

TEST_F(StringFormatTest, FormatMultipleArgs) {
	String result = String::format("%s has %d items worth %d credits", "Player", 5, 1000);
	EXPECT_STREQ(result.toCharArray(), "Player has 5 items worth 1000 credits");
}

TEST_F(StringFormatTest, FormatHex) {
	String result = String::format("0x%08X", 0xDEADBEEF);
	EXPECT_STREQ(result.toCharArray(), "0xDEADBEEF");
}

// =============================================================================
// 20. SSO Edge Cases
// =============================================================================

class StringSSOTest : public ::testing::Test {};

TEST_F(StringSSOTest, SSOMaxLength) {
	// SSO_SIZE - 1 is the max SSO string length (need null terminator)
	String s = makeString(SSO_SIZE - 1);
	EXPECT_EQ(s.length(), SSO_SIZE - 1);
	EXPECT_FALSE(s.isEmpty());
}

TEST_F(StringSSOTest, JustBeyondSSO) {
	String s = makeString(SSO_SIZE);
	EXPECT_EQ(s.length(), SSO_SIZE);
}

TEST_F(StringSSOTest, SSOCopyCorrectness) {
	String a = makeString(SSO_SIZE - 1, 'x');
	String b(a);
	EXPECT_STREQ(a.toCharArray(), b.toCharArray());
	EXPECT_EQ(a.length(), b.length());
}

TEST_F(StringSSOTest, HeapCopyCorrectness) {
	String a = makeString(SSO_SIZE + 10, 'y');
	String b(a);
	EXPECT_STREQ(a.toCharArray(), b.toCharArray());
	EXPECT_EQ(a.length(), b.length());
}

TEST_F(StringSSOTest, SSOMoveThenUseSource) {
	String a = makeString(SSO_SIZE - 1, 'z');
	String b(std::move(a));
	EXPECT_EQ(b.length(), SSO_SIZE - 1);
	// SSO move copies data, so source may still have its content
	// but we mainly verify the moved-to string is correct
}

TEST_F(StringSSOTest, HeapMoveThenUseSource) {
	String a = makeString(SSO_SIZE + 10, 'w');
	String b(std::move(a));
	EXPECT_EQ(b.length(), SSO_SIZE + 10);
	// After heap move, source should be emptied
	EXPECT_EQ(a.length(), 0);
}

TEST_F(StringSSOTest, ConcatSSOPlusSSO) {
	String a = makeString(SSO_SIZE - 2, 'a');
	String b = makeString(SSO_SIZE - 2, 'b');
	String result = a + b;
	EXPECT_EQ(result.length(), (SSO_SIZE - 2) * 2);
}

TEST_F(StringSSOTest, PlusEqualSSOBoundaryTransition) {
	String s = makeString(SSO_SIZE - 2, 'x');
	EXPECT_EQ(s.length(), SSO_SIZE - 2);
	s += "ab"; // should transition to heap (SSO_SIZE - 2 + 2 = SSO_SIZE, which is >= SSO_SIZE)
	EXPECT_EQ(s.length(), SSO_SIZE);
	// Verify content integrity across transition
	for (int i = 0; i < SSO_SIZE - 2; ++i) {
		EXPECT_EQ(s[i], 'x');
	}
	EXPECT_EQ(s[SSO_SIZE - 2], 'a');
	EXPECT_EQ(s[SSO_SIZE - 1], 'b');
}
