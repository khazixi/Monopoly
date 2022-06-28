#include <inttypes.h>

#include "monopoly_board.h"


struct Board {
	uint8_t size;
	struct Spot *head;
	struct Spot *tail;	// located a size - 1
};

struct Spot {
	struct Spot *next;
	struct Spot *prev;
	u_int8_t position;
	property_t type;
	struct PieceArray pieces;
	struct Empty data;
};

struct Board *board_init(void *(allocator)(size_t)) {
	struct Board *board_header = allocator(sizeof(struct Board));
	board_header->size = 0;
	board_header->head = NULL;
	board_header->tail = NULL;
	return board_header;
}

void board_append(struct Board *header, property_t type, struct Empty data, void *(allocator)(size_t))
{
	static uint8_t appended = 0;
	struct Spot *space = allocator(sizeof(struct Spot));
	space->type = type;
};
