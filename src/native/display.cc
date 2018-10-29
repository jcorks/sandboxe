#include <sandboxe/native/display.h>

static Sandboxe::DisplayObject * reference = nullptr;
Sandboxe::DisplayObject * Sandboxe::DisplayObject::GetMainDisplay() {
    return reference;
}

void Sandboxe::DisplayObject::SetMainDisplay(Sandboxe::DisplayObject * ref) {
    reference = ref;
}
