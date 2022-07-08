#ifndef BOARD_H
#define BOARD_H

#define MAX_PLAYERS 8
#include <inttypes.h>

/* TODO:
 * Refactor to use more specific integer types
 *
 *
 */
struct node;
struct used_names;

// TODO: consider adding luxury tax type
typedef enum {
	COMMUNITY_CHEST,
	RAILROAD,
	PROPERTY,
	UTILITY,
	CHANCE,
	TAX,

	// Noncharging Spaces
	GO,
	JAIL,
	GO_TO_JAIL,
	FREE_PARKING,

	// For error handling
	ERROR,
} property_t;

typedef enum {
	PURPLE,
	L_BLUE,
	PINK,
	ORANGE,
	RED,
	YELLOW,
	GREEN,
	D_BLUE,
} colort_t;

struct Empty {
	const char * name;
	property_t type;
	uint8_t position;
};

struct Railroad {
	const char * name;
	property_t type;
	uint8_t position;
	uint8_t price;
	uint8_t rent[4];
	struct Piece *owner;
};

struct Development {
	const char * name;
	property_t type;
	uint8_t position;
	uint16_t price;
	uint16_t rent[7];
	struct Piece *owner;
	uint8_t houses;
	uint8_t hotel;
	colort_t color;
};

struct Utility {
	const char * name;
	property_t type;
	uint8_t position;
	uint8_t price;
	uint8_t rent[2];
	struct Piece *owner;
};

struct Tax {
	const char * name;
	property_t type;
	uint8_t position;
	uint8_t rent;
};

typedef union {
	struct Empty fill;
	struct Development dev;
	struct Railroad rail;
	struct Utility util;
	struct Tax tax;
} location_t;

struct Piece {
	const char * name;
	uint32_t money;
	uint8_t position;
	// Metadata on owned properties
	uint8_t railroad_count;
	uint8_t utility_count;
	uint8_t color_count[8];
};

struct Board_Header {
	struct node *head;
	struct node *tail;
};

#endif // BOARD_H
