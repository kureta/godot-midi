/* godotmidi.cpp */

#include "godotmidi.h"

void GodotMIDI::add(int p_value) {
	std::vector<unsigned char> message;
	// Note On: 144, 64, 90
	message[0] = 144;
	message[1] = 64;
	message[2] = 90;
	this->midiout->sendMessage( &message );
}

void GodotMIDI::reset() {
	std::vector<unsigned char> message;
	// Note Off: 128, 64, 40
	message[0] = 128;
	message[1] = 64;
	message[2] = 40;
	this->midiout->sendMessage( &message );
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
	// RtMidiOut constructor
	try {
		this->midiout = new RtMidiOut(chooseMidiApi());
	}
	catch ( RtMidiError &error ) {
		error.printMessage();
	}

	// Call function to select port.
	try {
		if ( this->chooseMidiPort( this->midiout ) == false ) delete this->midiout;
	}
	catch ( RtMidiError &error ) {
		error.printMessage();
		delete this->midiout;
	}
}

bool GodotMIDI::chooseMidiPort( RtMidiOut *rtmidi )
{
	std::cout << "\nWould you like to open a virtual output port? [y/N] ";

	std::string keyHit;
	std::getline( std::cin, keyHit );
	if ( keyHit == "y" ) {
		rtmidi->openVirtualPort();
		return true;
	}

	std::string portName;
	unsigned int i = 0, nPorts = rtmidi->getPortCount();
	if ( nPorts == 0 ) {
		std::cout << "No output ports available!" << std::endl;
		return false;
	}

	if ( nPorts == 1 ) {
		std::cout << "\nOpening " << rtmidi->getPortName() << std::endl;
	}
	else {
		for ( i=0; i<nPorts; i++ ) {
			portName = rtmidi->getPortName(i);
			std::cout << "  Output port #" << i << ": " << portName << '\n';
		}

		do {
			std::cout << "\nChoose a port number: ";
			std::cin >> i;
		} while ( i >= nPorts );
	}

	std::cout << "\n";
	rtmidi->openPort( i );

	return true;
}

RtMidi::Api GodotMIDI::chooseMidiApi()
{
	std::vector< RtMidi::Api > apis;
	RtMidi::getCompiledApi(apis);

	if (apis.size() <= 1)
		return RtMidi::Api::UNSPECIFIED;

	std::cout << "\nAPIs\n  API #0: unspecified / default\n";
	for (size_t n = 0; n < apis.size(); n++)
		std::cout << "  API #" << apis[n] << ": " << RtMidi::getApiDisplayName(apis[n]) << "\n";

	std::cout << "\nChoose an API number: ";
	unsigned int i;
	std::cin >> i;

	std::string dummy;
	std::getline(std::cin, dummy);  // used to clear out stdin

	return static_cast<RtMidi::Api>(i);
}
