#ifndef PIECE_H
#define PIECE_H

#include <stddef.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus 

struct Piece {
	int64_t money;
	uint8_t jail_turns;
	const char* name;
};

struct PieceArray {
	uint8_t capacity;
	struct Piece *data[8];
};

struct Piece 	*piece_init(const char *, void * (*allocator)(size_t));
void 		 piece_destroy(struct Piece *, void (*allocator_free)(void *));


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // PIECE_H
