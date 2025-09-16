#include "animation/Abstract.h"

void AbstractAnimation::step() {
    delay(this->config->animationSpeed);
}
