///////////////////////////////////////////////////////////////////////////////
// 
// MacroRepeat
// 
// This header provides macros for repeating code.
// 
///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2004 Robert Geiman.
//
// Permission to copy, modify, and use this code for personal and commercial
// software is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without any expressed or implied warranty.
//
// Any comments or questions can be sent to: rgeiman@buckeye-express.com
//
///////////////////////////////////////////////////////////////////////////////

#ifndef MACRO_REPEAT_H
#define MACRO_REPEAT_H


#define MACRO_EMPTY_SEPERATOR 
#define MACRO_COMMA_SEPERATOR ,
#define MACRO_SEMICOLAN_SEPERATOR ;
#define MACRO_BEGIN_PAREN_SEPERATOR (
#define MACRO_END_PAREN_SEPERATOR )

#define MACRO_EMPTY_MACRO(num)
#define MACRO_TEMPLATE_PARAMETER(num) typename A##num
#define MACRO_TEMPLATE_ARGUMENT(num) A##num
#define MACRO_FUNCTION_PARAMETER(num) A##num a##num
#define MACRO_FUNCTION_ARGUMENT(num) a##num


#define MACRO_REPEAT_0(begin_seperator, seperator, macro, end_seperator) 
#define MACRO_REPEAT_1(begin_seperator, seperator, macro, end_seperator) begin_seperator macro(0) end_seperator
#define MACRO_REPEAT_2(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_1(begin_seperator, seperator, macro, end_seperator) seperator macro(1) end_seperator
#define MACRO_REPEAT_3(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_2(begin_seperator, seperator, macro, end_seperator) seperator macro(2) end_seperator
#define MACRO_REPEAT_4(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_3(begin_seperator, seperator, macro, end_seperator) seperator macro(3) end_seperator
#define MACRO_REPEAT_5(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_4(begin_seperator, seperator, macro, end_seperator) seperator macro(4) end_seperator
#define MACRO_REPEAT_6(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_5(begin_seperator, seperator, macro, end_seperator) seperator macro(5) end_seperator
#define MACRO_REPEAT_7(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_6(begin_seperator, seperator, macro, end_seperator) seperator macro(6) end_seperator
#define MACRO_REPEAT_8(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_7(begin_seperator, seperator, macro, end_seperator) seperator macro(7) end_seperator
#define MACRO_REPEAT_9(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_8(begin_seperator, seperator, macro, end_seperator) seperator macro(8) end_seperator
#define MACRO_REPEAT_10(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_9(begin_seperator, seperator, macro, end_seperator) seperator macro(9) end_seperator
#define MACRO_REPEAT_11(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_10(begin_seperator, seperator, macro, end_seperator) seperator macro(10) end_seperator
#define MACRO_REPEAT_12(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_11(begin_seperator, seperator, macro, end_seperator) seperator macro(11) end_seperator
#define MACRO_REPEAT_13(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_12(begin_seperator, seperator, macro, end_seperator) seperator macro(12) end_seperator
#define MACRO_REPEAT_14(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_13(begin_seperator, seperator, macro, end_seperator) seperator macro(13) end_seperator
#define MACRO_REPEAT_15(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_14(begin_seperator, seperator, macro, end_seperator) seperator macro(14) end_seperator
#define MACRO_REPEAT_16(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_15(begin_seperator, seperator, macro, end_seperator) seperator macro(15) end_seperator
#define MACRO_REPEAT_17(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_16(begin_seperator, seperator, macro, end_seperator) seperator macro(16) end_seperator
#define MACRO_REPEAT_18(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_17(begin_seperator, seperator, macro, end_seperator) seperator macro(17) end_seperator
#define MACRO_REPEAT_19(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_18(begin_seperator, seperator, macro, end_seperator) seperator macro(18) end_seperator
#define MACRO_REPEAT_20(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_19(begin_seperator, seperator, macro, end_seperator) seperator macro(19) end_seperator
#define MACRO_REPEAT_21(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_20(begin_seperator, seperator, macro, end_seperator) seperator macro(20) end_seperator
#define MACRO_REPEAT_22(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_21(begin_seperator, seperator, macro, end_seperator) seperator macro(21) end_seperator
#define MACRO_REPEAT_23(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_22(begin_seperator, seperator, macro, end_seperator) seperator macro(22) end_seperator
#define MACRO_REPEAT_24(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_23(begin_seperator, seperator, macro, end_seperator) seperator macro(23) end_seperator
#define MACRO_REPEAT_25(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_24(begin_seperator, seperator, macro, end_seperator) seperator macro(24) end_seperator
#define MACRO_REPEAT_26(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_25(begin_seperator, seperator, macro, end_seperator) seperator macro(25) end_seperator
#define MACRO_REPEAT_27(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_26(begin_seperator, seperator, macro, end_seperator) seperator macro(26) end_seperator
#define MACRO_REPEAT_28(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_27(begin_seperator, seperator, macro, end_seperator) seperator macro(27) end_seperator
#define MACRO_REPEAT_29(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_28(begin_seperator, seperator, macro, end_seperator) seperator macro(28) end_seperator
#define MACRO_REPEAT_30(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_29(begin_seperator, seperator, macro, end_seperator) seperator macro(29) end_seperator
#define MACRO_REPEAT_31(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_30(begin_seperator, seperator, macro, end_seperator) seperator macro(30) end_seperator
#define MACRO_REPEAT_32(begin_seperator, seperator, macro, end_seperator) MACRO_REPEAT_31(begin_seperator, seperator, macro, end_seperator) seperator macro(31) end_seperator


#define MACRO_LIST(num, macro) MACRO_REPEAT_##num(MACRO_EMPTY_SEPERATOR, MACRO_COMMA_SEPERATOR, macro, MACRO_EMPTY_SEPERATOR)
#define MACRO_LIST_APPEND(num, macro) MACRO_REPEAT_##num(MACRO_COMMA_SEPERATOR, MACRO_COMMA_SEPERATOR, macro, MACRO_EMPTY_SEPERATOR)
#define MACRO_LIST_PREPEND(num, macro) MACRO_REPEAT_##num(MACRO_EMPTY_SEPERATOR, MACRO_COMMA_SEPERATOR, macro, MACRO_COMMA_SEPERATOR)
#define MACRO_BEGIN_PAREN(num, macro) MACRO_REPEAT_##num(MACRO_BEGIN_PAREN_SEPERATOR, MACRO_EMPTY_SEPERATOR, macro, MACRO_EMPTY_SEPERATOR)
#define MACRO_END_PAREN(num, macro) MACRO_REPEAT_##num(MACRO_END_PAREN_SEPERATOR, MACRO_EMPTY_SEPERATOR, macro, MACRO_EMPTY_SEPERATOR)
#define MACRO_REPEAT(num, macro) MACRO_REPEAT_##num(MACRO_EMPTY_SEPERATOR, MACRO_EMPTY_SEPERATOR, macro, MACRO_EMPTY_SEPERATOR)


#endif