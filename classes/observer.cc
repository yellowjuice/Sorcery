#include "observer.h"

Observer::Observer() : location{Location::NONE} { }
Observer::Observer(Location l) : location{l} { }
Observer::~Observer() = default;

Location Observer::getLocation() const { return location; }
void Observer::setLocation(Location l) {
    location = l;
}