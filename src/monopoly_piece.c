#include <stdarg.h>
#include "monopoly_piece.h"

struct Piece *piece_init(const char *str, void * (*allocator)(size_t)) {
	struct Piece *piece = allocator(sizeof(struct Piece));
	piece->money = 1500;
	piece->jail_turns = 0;
	piece->name = str;
	return piece;
}

void piece_destroy(struct Piece *piece, void (*allocator_free)(void *)) {
	allocator_free(piece);
	piece = NULL;
}
