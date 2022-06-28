#include "monopoly_spacedata.h"

unsigned int space_rent(struct Empty *space, struct Piece *player)
{
	switch (space->type)
	{
		uint8_t idx = 0;
		unsigned int val = 0;
		case PROPERTY:
			struct Property *prop = ((struct Property *)space);
			if (prop->monopoly) {
				idx += 1;
			}
			if (prop->hotel) {
				idx = 6;
			} else {
				idx += prop->houses;
			}
			val = prop->rent[idx];
			break;
		case RAILROAD:
			struct Railroad *rail = ((struct Railroad *)space);
			idx += rail->num_railroads;
			val = rail->rent[idx];
			break;
		case UTILITY:
			struct Utility *util = ((struct Utility *)space);
			if (util->monopoly) {
				idx += 1;
			}
			val = util->multiplier[idx];
			break;
		case TAX:
		case LUXURY_TAX:
			struct Taxable *tax = ((struct Taxable *)space);
			val = tax->tax.rate;
		case CHANCE:
		case COMMUNITY_CHEST:
		case GO:
		case JAIL:
		case GO_TO_JAIL:
		case FREE_PARKING:
			break;
	}
}
