#include "patterns/Decorator.h"
#include <iostream>

Decorator::~Decorator(void) { delete m_bestiole; }