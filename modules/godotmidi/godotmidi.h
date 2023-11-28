/* godotmidi.h */

#ifndef GODOTMIDI_H
#define GODOTMIDI_H

#include "core/object/ref_counted.h"
#include <rtmidi/RtMidi.h>

class GodotMIDI : public RefCounted {
	GDCLASS(GodotMIDI, RefCounted);

	int count;

private:
	bool chooseMidiPort( RtMidiOut *rtmidi );
	RtMidi::Api chooseMidiApi();
	RtMidiOut *midiout = 0;

protected:
	static void _bind_methods();

public:
	void add(int p_value);
	void reset();
	int get_total() const;

	GodotMIDI();
};

#endif // GODOTMIDI_H
