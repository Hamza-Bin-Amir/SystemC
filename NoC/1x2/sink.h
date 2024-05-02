// sink.h
#include "packet.h"
SC_MODULE(sink) {
	sc_in<packet> packet_in;	// input port
	sc_out<bool> ack_out;		// output port
	sc_in<sc_uint<4> > sink_id;
	sc_in<bool> sclk;
	sc_in<double > time_in;
	int pkt_recv;
	double total_rcv_time;
	double total_send_time;
	double pkt_delay;
	
	void receive_data();

	// Constructor
	SC_CTOR(sink) {
		SC_METHOD(receive_data); // Method Process
		dont_initialize();
		sensitive << packet_in;
		sensitive << sclk.pos();
		pkt_recv = 0;
	}
};
