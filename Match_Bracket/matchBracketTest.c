#include "testUtils.h"
#include "matchBracket.h"
#include <stdlib.h>
//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

void test_1_matchs_all_brackets_of_input_string(){
	char* input = "[{(ram)dfas}]";
	ErrorMsg result;
	result = startMatch(input);
	ASSERT(0==result.isError);
};

void test_3_gives_error_if_there_is_nothing_on_stack_when_closing_bracket_occurs(){
	char* input = "}";
	ErrorMsg result;
	result = startMatch(input);
	ASSERT(1==result.isError==result.index);
	ASSERT('}'==result.bracket);
}

void test_3_gives_error_if_the_opening_bracket_doesnot_match(){
	char* input = "Digs(Raj)Naam]";
	ErrorMsg result;
	result = startMatch(input);
	ASSERT(result.isError==1);
	ASSERT(result.bracket==']');
	ASSERT(result.index==14);
}

void test_4_gives_error_if_anything_left_on_stack_on_the_end_of_string(){
	char* input = "([Digs(Raj)Naam]";
	ErrorMsg result;
	result = startMatch(input);
	ASSERT(result.isError==1);
	ASSERT(result.bracket=='\0');
	ASSERT(result.index==0);
}

void test_5_creates_the_last_result_in_structure_form(){
	Stack* stack = create(2, sizeof(char));
	ErrorMsg result = createResult(1, 0, '{', stack);
	ASSERT(1==result.isError);
	ASSERT(0==result.index);
	ASSERT('{'==result.bracket);
}

void test_8_gives_the_opening_bracket_of_given_closing_bracket(){
	ASSERT('{'==getOpeningBracket('}'));
	ASSERT('['==getOpeningBracket(']'));
	ASSERT('('==getOpeningBracket(')'));
}

void test_9_gives_null_if_the_given_character_is_not_a_closing_bracket(){
	ASSERT('\0'==getOpeningBracket('r'));
}
