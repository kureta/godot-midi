/* register_types.cpp */

#include "register_types.h"

#include "core/object/class_db.h"
#include "godotmidi.h"

void initialize_godotmidi_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
			return;
	}
	ClassDB::register_class<GodotMIDI>();
}

void uninitialize_godotmidi_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
			return;
	}
   // Nothing to do here in this example.
}
