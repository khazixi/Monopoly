#ifndef BOARD_H
#define BOARD_H

#include "monopoly_piece.h"
#include "monopoly_spacedata.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
#define MAX_PLAYERS 8


// Refactor Struct types


// struct Board 	*board_init(enum property_t, union Spot_data);
struct Board 	*board_init(void *(allocator)(size_t));
void 		 board_append(struct Board *, property_t, struct Empty *, void *(allocator)(size_t));
void 		 board_destroy(struct Board *);


#ifdef __cplusplus
}
#endif // __cplusplus


#endif //BOARD_H
