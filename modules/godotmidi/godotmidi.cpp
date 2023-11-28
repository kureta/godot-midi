/* godotmidi.cpp */

#include "godotmidi.h"

void GodotMIDI::add(int p_value) {
	count += p_value;
}

void GodotMIDI::reset() {
	count = 0;
}

int GodotMIDI::get_total() const {
	return count;
}

void GodotMIDI::_bind_methods() {
	ClassDB::bind_method(D_METHOD("add", "value"), &GodotMIDI::add);
	ClassDB::bind_method(D_METHOD("reset"), &GodotMIDI::reset);
	ClassDB::bind_method(D_METHOD("get_total"), &GodotMIDI::get_total);
}

GodotMIDI::GodotMIDI() {
	count = 0;
}
