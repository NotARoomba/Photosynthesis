#include "./item.h"
Item* Item::asItem() {
    return static_cast<Item*>(this);
}