#include <string.h>
#include "globals.h"

struct Piece piece_init(const char *name)
{
	return (struct Piece) {
		.name = name,
		.money = 1500,
		.color_count = {0},
		.railroad_count = 0,
		.utility_count = 0
	};
}

global_t globals_init(void) {
	static bool used = false;
	global_t dummy;
	dummy.turns = 0;
	dummy.remaining_hotels = 12;
	dummy.remaining_houses = 32;
	return dummy;
}

struct used_names used_names_init(void) {
	struct used_names name;
	memset(name.names, '\0', sizeof(char) * 8 * 32);
	name.used = 0;
	return name;
}

bool check_used_name(const char *name, struct used_names name_list) {
	for (int i = 0; i < name_list.used + 1; i++)
		if ( strcmp(name, name_list.names[i]) == 0 )
			return true;
	return false;
}

void add_used_name(const char *name, struct used_names *name_list) {
	if (8 > name_list->used) {
		if (check_used_name(name, *name_list)) {
			strncpy(name_list->names[name_list->used], name, 31);
			name_list->names[name_list->used][31] = '\0';
			name_list->used += 1;
		}
	}
}

