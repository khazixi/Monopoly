#ifndef SPACE_DATA_H
#define SPACE_DATA_H

#include <inttypes.h>
#include <stdbool.h>

#include "monopoly_piece.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef enum {
	// Rent Types
	PROPERTY,
	RAILROAD,
	UTILITY,

	// Drawable Types
	CHANCE,
	COMMUNITY_CHEST,

	// Tax Types
	TAX,
	LUXURY_TAX,

	// Empty types
	GO,
	JAIL,
	GO_TO_JAIL,
	FREE_PARKING,
} property_t;

typedef enum {
	PURPLE,
	LIGHT_BLUE,
	PINK,
	ORANGE,
	RED,
	YELLOW,
	GREEN,
	DARK_BLUE,

} color_t;

struct Empty {
	char name[32];
	uint32_t position;
	property_t type;
};

struct Taxable {
	struct Empty;
	union {
		struct {
			uint16_t percent;
			uint16_t rate;
		} income_tax;
		uint8_t rate;
	} tax;
};

struct Property {
	struct Empty;
	bool monopoly;
	bool hotel;
	color_t color;
	uint8_t price;		// Mortgage is half of price
	uint8_t house_cost;
	uint16_t houses;
	uint16_t rent[7];
};

struct Railroad {
	struct Empty;
	uint8_t price;
	uint8_t num_railroads;
	uint16_t rent[4];
};

struct Drawable {
	struct Empty;
	bool chance;	// If true = chance, false = community chest
};

struct Utility {
	struct Empty;
	bool monopoly;
	uint8_t price;
	uint8_t multiplier[2];
};

// TODO: Figure out how to call to the board so monopoly and other values are checked
// NULL out the methods implimentation based on type data
unsigned int space_rent(struct Empty  *, struct Piece *);
unsigned int space_buy(struct Empty *, struct Piece *);
unsigned int space_sell(struct Empty *, struct Piece *);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SPACE_DATA_H
