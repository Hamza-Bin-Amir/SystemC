// source.h
#include "packet.h"
SC_MODULE(source) {

	sc_out<packet> packet_out; 
	sc_in<sc_uint<4> > source_id; 
	sc_in<bool > ach_in;
	sc_in_clk CLK;
	sc_out<double > time_out;
	sc_in<int> dst;
	sc_in<sc_uint<4> > chk;
	int pkt_snt;
	double total_send_time;

	void func();
  
	SC_CTOR(source)
    {
		SC_CTHREAD(func, CLK.pos());
		pkt_snt=0;
    }  
};
