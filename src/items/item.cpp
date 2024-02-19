#include "./item.h"
#include <vector>
Item* Item::asItem() {
    return static_cast<Item*>(this);
}