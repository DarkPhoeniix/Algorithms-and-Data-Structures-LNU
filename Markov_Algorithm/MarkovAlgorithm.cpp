
#include <iostream>
#include <vector>
#include <utility>

#include "String.h"

using namespace std;

String MarkovAlgorithm(const String& str, const vector<pair<String, String>>& dictionary)
{
	String str_copy = str;

	for (int i = 0; i < dictionary.size(); ) {
		if (str_copy.find(dictionary[i].first) != -1) {
			str_copy.replace(str_copy.find(dictionary[i].first),
				dictionary[i].first.length(),
				dictionary[i].second);
			i = 0;
		} else {
			++i;
		}
	}

	return str_copy;
}
