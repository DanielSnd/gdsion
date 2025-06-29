/***************************************************/
/* Part of GDSiON software synthesizer             */
/* Copyright (c) 2024 Yuri Sizov and contributors  */
/* Provided under MIT                              */
/***************************************************/

#include "godot_util.h"

#include "modules/regex/regex.h"


PackedStringArray split_string_by_regex(const String &p_string, const String &p_regex) {
	// This is boilerplate to split a string by a regex in Godot.
	PackedStringArray arr;

	Ref<RegEx> re_split = RegEx::create_from_string(p_regex);
	Array matches = re_split->search_all(p_string);

	int last_index = 0;
	for (int i = 0; i < matches.size(); i++) {
		Ref<RegExMatch> separator = matches.get(i);
		String match = p_string.substr(last_index, separator->get_start(0) - last_index);

		arr.append(match);
		last_index = separator->get_end(0);
	}

	String last_match = p_string.substr(last_index);
	arr.append(last_match);

	return arr;
}
