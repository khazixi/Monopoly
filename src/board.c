#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "globals.h"
#include "board.h"


// OPTIMIZE: lower the number of lines the program uses

/* NOTE: struct node exists here to ensure that it cannot be initialized in main
 * node structure used to form a linked list.
 * @param *next - points to n + 1 position, if n = 39 -> 0
 * @param *prev - points to n - 1 position, if n = 0 -> 39
 */

// WARNING: using global variable
// NOTE: static is to ensures the variable stays in this file scope

struct node {
	struct node *next;
	struct node *prev;
	location_t data;
};

// TODO: impliment a name function that queries from stdin
static struct Empty __empty_init(const char *name, property_t type, unsigned int pos)
{
	return (struct Empty) {
		.name = name,
		.type = type,
		.position = pos
	};
}

static struct Empty __drawable_init(property_t type, uint8_t pos)
{
	const char *name;
	if (type == COMMUNITY_CHEST)
		name = "Community Chest";
	else if (type == CHANCE)
		name = "Chance";
	return (struct Empty) {
		.name = name,
		.type = type,
		.position = pos
	};
}

static struct Utility __utility_init(const char *name, uint8_t pos)
{
	return (struct Utility){
		.name = name,
		.type = UTILITY,
		.position = pos,
		.price = 150,
		.rent = {4, 10},
		.owner = NULL
	};
}

static struct Railroad __railroad_init(const char *name, uint8_t pos)
{
	return (struct Railroad) {
		.name = name,
		.type = RAILROAD,
		.position = pos,
		.rent = {25, 50, 100, 200},
		.price = 200,
		.owner = NULL
	};
}

static struct Tax __tax_init(const char *name, unsigned int pos, uint8_t rent)
{
	return (struct Tax){
		.name = name,
		.type = TAX,
		.position = pos,
		.rent = rent,
	};
}

static struct Development __development_init(const char *name, uint8_t pos, uint16_t price, uint16_t rent[static 7], colort_t color)
{
	struct Development data = {
		.name = name,
		.type = PROPERTY,
		.position = pos,
		.color = color,
		.houses = 0,
		.hotel = 0,
		.owner = NULL
	};
	memcpy(data.rent, rent, sizeof(uint16_t) * 7);
	return data;
}

// TODO: if structs are storable, store the data for all structs
// HACK: Uses a series of if statements in otder to handle variables
// NOTE: Inline array structure is (int[]) {1, 2, ...}
static location_t __spotdata_construct(unsigned int position)
{
	location_t a;
	switch (position) {
		// INFO: Community Chest and Chance
		case 2:
		case 17:
		case 33: a.fill = __drawable_init(COMMUNITY_CHEST, position);
			break;
		case 7:
		case 22:
		case 36: a.fill = __drawable_init(CHANCE, position);
			break;
		// INFO: Tax
		case 4: a.tax = __tax_init("Income Tax", position, 200);
			break;
		case 38: a.tax = __tax_init("Luxury Tax", position, 75);
			break;
		// INFO: Unique Properties
		case 0: a.fill = __empty_init("Go", GO, position);
			break;
		case 10: a.fill = __empty_init("Jail", JAIL, position);
			break;
		case 20: a.fill = __empty_init("Free Parking", FREE_PARKING, position);
			break;
		case 30: a.fill = __empty_init("Go To Jail", GO_TO_JAIL, position);
			break;
		// INFO: Railroads
		case 5: a.rail = __railroad_init("Reading Railroad", position);
			break;
		case 15: a.rail = __railroad_init("Pennsylvania Railroad", position);
			break;
		case 25: a.rail = __railroad_init("B&O Railroad", position);
			break;
		case 35: a.rail = __railroad_init("Short Line", position);
			break;
		// INFO: Utilities
		case 12: a.util = __utility_init("Electric Company", position);
			break;
		case 28: a.util = __utility_init("Water Works", position);
			break;
		// INFO: Developable Properties
		// INFO: Purple
		case 1: a.dev = __development_init("Mediterranean Avenue", position, 60,
					(uint16_t[]){2, 4, 10, 30, 90, 160, 250}, PURPLE);
			break;
		case 3: a.dev = __development_init("Mediterranean Avenue", position, 60,
					(uint16_t[]){4, 8, 20, 60, 180, 320, 450}, PURPLE);
			break;
		// INFO: Light Blue
		case 6: a.dev = __development_init("Oriental Avenue", position, 100,
					(uint16_t[]){6, 12, 30, 90, 270, 400, 550}, L_BLUE);
			break;
		case 8: a.dev = __development_init("Vermont Avenue", position, 100,
					(uint16_t[]){6, 12, 30, 90, 270, 400, 550}, L_BLUE);
			break;
		case 9: a.dev = __development_init("Connecticut Avenue", position, 120,
					(uint16_t[]){8, 16, 40, 100, 300, 450, 600}, L_BLUE);
			break;
		// INFO: Pink
		case 11: a.dev = __development_init("St. Charles Place", position, 140, 
					(uint16_t[]){10, 20, 50, 150, 450, 625, 750}, PINK);
			break;
		case 13: a.dev = __development_init("States Avenue", position, 140, 
					(uint16_t[]){10, 20, 50, 150, 450, 625, 750}, PINK);
			break;
		case 14: a.dev = __development_init("Virginia Avenue", position, 160, 
					(uint16_t[]){12, 24, 60, 180, 500, 705, 900}, PINK);
			break;
		// INFO: Orange
		case 16: a.dev = __development_init("St. James Placce", position, 180, 
					(uint16_t[]){14, 28, 70, 200, 550, 750, 950}, ORANGE);
			break;
		case 18: a.dev = __development_init("Tennessee Avenue", position, 180, 
					(uint16_t[]){14, 28, 70, 200, 550, 750, 950}, ORANGE);
			break;
		case 19: a.dev = __development_init("New York Avenue", position, 200, 
					(uint16_t[]){16, 32, 80, 220, 600, 800, 1000}, ORANGE);
			break;
		// INFO: Red
		case 21: a.dev = __development_init("Kentucky Avenue", position, 220, 
					(uint16_t[]){18, 36, 90, 250, 700, 875, 1050}, RED);
			break;
		case 23: a.dev = __development_init("Indiana Avenue", position, 220, 
					(uint16_t[]){18, 36, 90, 250, 700, 875, 1050}, RED);
			break;
		case 24: a.dev = __development_init("Illinois Avenue", position, 240, 
					(uint16_t[]){20, 40, 100, 300, 750, 925, 1100}, RED);
			break;
		// INFO: Yellow
		case 26: a.dev = __development_init("Atlantic Avenue", position, 260, 
					(uint16_t[]){22, 44, 110, 330, 800, 975, 1150}, YELLOW);
			break;
		case 27: a.dev = __development_init("Ventor Avenue", position, 260, 
					(uint16_t[]){22, 44, 110, 330, 800, 975, 1150}, YELLOW);
			break;
		case 29: a.dev = __development_init("Marvin Gardens", position, 280, 
					(uint16_t[]){24, 48, 120, 360, 850, 1025, 1200}, YELLOW);
			break;
		// INFO: Green
		case 31: a.dev = __development_init("Pacific Avenue", position, 320, 
					(uint16_t[]){26, 52, 130, 390, 900, 1100, 1275}, GREEN);
			break;
		case 32: a.dev = __development_init("North Carolina Avenue", position, 320, 
					(uint16_t[]){26, 52, 130, 390, 900, 1100, 1275}, GREEN);
			break;
		case 34: a.dev = __development_init("Pennsylvania Avenue", position, 320, 
					(uint16_t[]){28, 56, 150, 450, 1000, 1200, 1400}, GREEN);
			break;
		// INFO: Dark Blue
		case 37: a.dev = __development_init("Park Place", position, 350, 
					(uint16_t[]){35, 70, 170, 500, 1100, 1300, 1500}, D_BLUE);
			break;
		case 39: a.dev = __development_init("Boardwalk", position, 400, 
					(uint16_t[]){50, 100, 200, 600, 1400, 1700, 2000}, D_BLUE);
			break;
	}
	return a;
}

void board_init(struct Board_Header *header)
{
	struct node *a = malloc(sizeof(struct node));	
	a->data = __spotdata_construct(0);
	a->next = NULL;
	a->prev = NULL;
	header->head = a;
	header->tail = a;
}

void board_append(struct Board_Header *header, unsigned int pos)
{
	struct node *b = malloc(sizeof(struct node));	
	b->data = __spotdata_construct(pos);
	b->prev = header->tail;	// Sets the current node to the previous tail node
	b->next = NULL;
	header->tail->next = b;
	header->tail = b;
}

void board_free(struct Board_Header *header)
{
	header->tail->next = NULL;
	struct node *nxt = NULL;
	struct node *cur = header->head;
	while (1) {
		nxt = cur->next;
		free(cur);
		if (nxt == NULL) break;
		cur = nxt;
	}
}

void buy(struct Piece *piece, struct node *spot)
{
	property_t type = spot->data.fill.type;
	switch (type) {
		case COMMUNITY_CHEST:
		case FREE_PARKING:
		case GO_TO_JAIL:
		case CHANCE:
		case GO:
		case JAIL:
		case TAX:
		case ERROR:
			return;
		case PROPERTY:
			if (spot->data.dev.owner == NULL) {
				if (piece->money > spot->data.dev.price) {
					piece->money -= spot->data.dev.price;
					spot->data.dev.owner = piece;
					piece->color_count[spot->data.dev.color] += 1;
				}
			}
			return;
		case UTILITY:
			if (spot->data.util.owner == NULL) {
				if (piece->money > spot->data.util.price) {
					piece->money -= spot->data.util.price;
					spot->data.util.owner = piece;
					piece->utility_count += 1;
				}
			}
			return;
		case RAILROAD:
			if (spot->data.rail.owner == NULL) {
				if (piece->money > spot->data.rail.price) {
					piece->money -= spot->data.rail.price;
					spot->data.rail.owner = piece;
					piece->railroad_count += 1;
				}
			}
			return;
	}
}

// TODO: Change the int return type to bool, uint8_t, or int8_t
int monopoly(struct Piece piece, colort_t color)
{
	switch (color) {
		case D_BLUE:
		case PURPLE:
			if (piece.color_count[color] == 2)
				return 1;
			return 0;
		case L_BLUE:
		case ORANGE:
		case YELLOW:
		case PINK:
		case RED:
		case GREEN:
			if (piece.color_count[color] == 3)
				return 1;
			return 0;
	}
}

void sell(struct Piece piece)
{
	// TODO: Work on this laterLater
}

// NOTE: Impliment these todo's after buy/sell features
// TODO: Impliment a dead feature
// TODO: Impliment a panic sell feature
bool charge(struct Piece *piece, struct node *spot)
{
	int roll;
	switch (spot->data.fill.type) {
		case COMMUNITY_CHEST:
		case FREE_PARKING:
		case GO_TO_JAIL:
		case CHANCE:
		case GO:
		case JAIL:
		case ERROR:
			return false;
		case TAX:
			if (piece->money > spot->data.tax.rent)
				piece->money -= spot->data.tax.rent;
			else 
				piece->money = 0;
			return true;
		case PROPERTY:
			if (monopoly(*piece, spot->data.dev.color)) {
				if (spot->data.dev.hotel) {
					if (piece->money > spot->data.dev.rent[6])
						piece->money -= spot->data.dev.rent[6];
					else
						piece->money = 0;
				} else {
					if (piece->money > spot->data.dev.rent[1 + spot->data.dev.houses])
						piece->money -= spot->data.dev.rent[1 + spot->data.dev.houses];
					else
						piece->money = 0;
				}
			} else {
				if (piece->money > spot->data.dev.rent[0])
					piece->money -= spot->data.dev.rent[0];
				else
				 	piece->money = 0;
			}
			return true;
		case UTILITY:
			roll = rand() % 11 + 2;	// INFO: produces a random number in range 2, 12
			if (piece->money > spot->data.util.rent[piece->utility_count])
				piece->money -= spot->data.util.rent[piece->utility_count];
			else
				piece->money = 0;
			return true;
		case RAILROAD:
			if (piece->money > spot->data.rail.rent[piece->railroad_count - 1])
				piece->money -= spot->data.rail.rent[piece->railroad_count - 1];
			else
				piece->money = 0;
			return true;
	}
}

// NOTE: This function handles user input
void piece_activate(struct Piece *piece, struct Board_Header *header, unsigned int pos)
{
	struct node *a;
	char *action;

	// Finds the node
	if ( (0 <= pos) && (pos < 20) ) {
		a = header->head;
		while(a->data.fill.position != pos)
			a++;
	} else if ( (20 <= pos) && (pos < 40) ) {
		a = header->tail;
		while(a->data.fill.position != pos)
			a--;
	}
	
	// Queries the action
	scanf("Action %[^\n]s\n", action);
	fflush(stdin);

	// Checks if the player can be charged, if not the player has the option to purchase the spot if purchaseable
	if ( charge(piece, a) )
		return;

	if ( strcmp("Buy", action) == 0 || strcmp("buy", action) == 0 )
		buy(piece, a);
	else if ( strcmp("Wait", action) == 0 || strcmp("wait", action) == 0 )
		return;
}

// TODO: add pre-move actions function
// TODO: expand on this functions logic
void piece_move(struct Piece *piece, struct Board_Header *header)
{
	int move_amount = rand() % 11 + 2;	// INFO: produces a random number in range 2, 12
	piece->position += move_amount;
	if (39 < piece->position)
		piece->position -= 40;
	piece_activate(piece, header, piece->position);
}
