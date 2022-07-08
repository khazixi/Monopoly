#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdbool.h>
#include <inttypes.h>

struct Deck;

typedef struct Globals global_t;

struct Piece {
	const char * name;
	uint32_t money;
	uint8_t position;
	// Metadata on owned properties
	uint8_t railroad_count;
	uint8_t utility_count;
	uint8_t color_count[8];
};

struct used_names {
	char names[8][32];
	uint8_t used;
};

struct active_players {
	struct Piece active[8];
	uint8_t count;
};

struct Globals {
	uint8_t turns;
	uint8_t remaining_hotels;
	uint8_t remaining_houses;
	struct used_names player_used_names;
	struct active_players current_players;
};

global_t globals_init(void);
struct Piece piece_init(const char *);
void add_player(const char *, global_t *);
void remove_player(const char *, global_t *);
bool check_used_name(const char *, struct used_names);
void add_used_name(const char *, struct used_names *);

#endif // GLOBALS_H
