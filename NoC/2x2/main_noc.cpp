// main.cpp
#include "systemc.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "packet.h"
#include "source.h"
#include "sink.h"
#include "router.h"


int sc_main(int argc, char *argv[])
{
	sc_signal<packet> si_source[4];
	sc_signal<packet> si_input[16];
	sc_signal<packet> si_zero[16];
	sc_signal<packet> si_sink[4];
	sc_signal<packet> si_output[16];
	sc_signal<bool>  si_ack_src[4], si_ack_ou[16];
	sc_signal<bool>  si_ack_sink[4], si_ack_in[16];
	sc_signal<bool>  si_ack_zero[16];
	sc_signal<double >  time1, time2, time3, time4;
	sc_signal<sc_uint<4> > id0, id1, id2, id3;
	sc_signal<int> src_in;
	sc_signal<sc_uint<4> > chk;
	sc_clock s_clock("S_CLOCK", 125, SC_NS, 0.5, 0.0, SC_NS);
	sc_clock r_clock("R_CLOCK", 5, SC_NS, 0.5, 10.0, SC_NS);
	sc_clock d_clock("D_CLOCK", 5, SC_NS, 0.5, 10.0, SC_NS);
	
	int src, dst, ptn;
	
	
	source source0("source0");
	source0(si_source[0], id0, si_ack_src[0], s_clock, time1, src_in, chk);
    source source1("source1");
	source1(si_source[1], id1, si_ack_src[1], s_clock, time2, src_in, chk);
	source source2("source2");
	source2(si_source[2], id2, si_ack_src[2], s_clock, time3, src_in, chk);
	source source3("source3");
	source3(si_source[3], id3, si_ack_src[3], s_clock, time4, src_in, chk);


	//------------------------------
	
	router router0("router0");
	
	router0.in0(si_source[0]);
	router0.in1(si_output[2]);
	router0.in2(si_output[4]);
	router0.in3(si_zero[0]);
	router0.in4(si_zero[1]);

	router0.router_id(id0);

	router0.out0(si_sink[0]);
	router0.out2(si_output[0]);
	router0.out3(si_output[1]);
	router0.out1(si_zero[2]);
	router0.out4(si_zero[3]);

	router0.inack0(si_ack_sink[0]);
	router0.inack1(si_ack_in[2]);
	router0.inack2(si_ack_in[4]);
	router0.inack3(si_ack_zero[0]);
	router0.inack4(si_ack_zero[1]);

	router0.outack0(si_ack_src[0]);
	router0.outack2(si_ack_in[0]);
	router0.outack3(si_ack_in[1]);
	router0.outack1(si_ack_zero[2]);
	router0.outack4(si_ack_zero[3]);

	router0.rclk(r_clock);
	
	//------------------------------
	
	router router1("router1");
	
	router1.in0(si_source[1]);
	router1.in1(si_output[0]);
	router1.in2(si_output[6]);
	router1.in3(si_zero[4]);
	router1.in4(si_zero[5]);

	router1.router_id(id1);

	router1.out0(si_sink[1]);
	router1.out4(si_output[2]);
	router1.out3(si_output[3]);
	router1.out1(si_zero[6]);
	router1.out2(si_zero[7]);

	router1.inack0(si_ack_sink[1]);
	router1.inack1(si_ack_in[0]);
	router1.inack2(si_ack_in[6]);
	router1.inack3(si_ack_zero[4]);
	router1.inack4(si_ack_zero[5]);

	router1.outack0(si_ack_src[1]);
	router1.outack4(si_ack_in[2]);
	router1.outack3(si_ack_in[3]);
	router1.outack2(si_ack_zero[6]);
	router1.outack1(si_ack_zero[7]);

	router1.rclk(r_clock);
	
	//------------------------------

	router router2("router2");
	
	router2.in0(si_source[2]);
	router2.in1(si_output[1]);
	router2.in2(si_output[7]);
	router2.in3(si_zero[8]);
	router2.in4(si_zero[9]);

	router2.router_id(id2);

	router2.out0(si_sink[2]);
	router2.out1(si_output[4]);
	router2.out2(si_output[5]);
	router2.out3(si_zero[10]);
	router2.out4(si_zero[11]);
	
	router2.inack0(si_ack_sink[2]);
	router2.inack1(si_ack_in[1]);
	router2.inack2(si_ack_in[7]);
	router2.inack3(si_ack_zero[8]);
	router2.inack4(si_ack_zero[9]);
	
	router2.outack0(si_ack_src[2]);
	router2.outack1(si_ack_in[4]);
	router2.outack2(si_ack_in[5]);
	router2.outack3(si_ack_zero[10]);
	router2.outack4(si_ack_zero[11]);
	
	router2.rclk(r_clock);
	
	//------------------------------

	router router3("router3");
	router3.in0(si_source[3]);
	router3.in1(si_output[3]);
	router3.in2(si_output[5]);
	router3.in3(si_zero[12]);
	router3.in4(si_zero[13]);

	router3.router_id(id3);

	router3.out0(si_sink[3]);
	router3.out1(si_output[6]);
	router3.out4(si_output[7]);
	router3.out2(si_zero[14]);
	router3.out3(si_zero[15]);
	
	router3.inack0(si_ack_sink[3]);
	router3.inack1(si_ack_in[3]);
	router3.inack2(si_ack_in[5]);
	router3.inack3(si_ack_zero[12]);
	router3.inack4(si_ack_zero[13]);
	
	router3.outack0(si_ack_src[3]);
	router3.outack1(si_ack_in[6]);
	router3.outack4(si_ack_in[7]);
	router3.outack2(si_ack_zero[14]);
	router3.outack3(si_ack_zero[15]);

	router3.rclk(r_clock);

	//------------------------------

	sink sink0("sink0");
	sink0(si_sink[0], si_ack_sink[0], id0, d_clock, time1);
	sink sink1("sink1");
	sink1(si_sink[1], si_ack_sink[1], id1, d_clock, time2);
	sink sink2("sink2");
	sink2(si_sink[2], si_ack_sink[2], id2, d_clock, time3);
	sink sink3("sink3");
	sink3(si_sink[3], si_ack_sink[3], id3, d_clock, time4);

	
	sc_trace_file *tf = sc_create_vcd_trace_file("graph");

	sc_trace(tf, s_clock, "s_clock");
	sc_trace(tf, d_clock, "d_clock");
	sc_trace(tf, r_clock, "r_clock");
	sc_trace(tf, si_source[0], "si_source[0]");
	sc_trace(tf, si_source[1], "si_source[1]");
	sc_trace(tf, si_source[2], "si_source[2]");
	sc_trace(tf, si_source[3], "si_source[3]");
	sc_trace(tf, si_sink[0], "si_sink[0]");
	sc_trace(tf, si_sink[1], "si_sink[1]");
	sc_trace(tf, si_sink[2], "si_sink[2]");
	sc_trace(tf, si_sink[3], "si_sink[3]");
	
	id0.write(0);
	id1.write(1);
	id2.write(2);
	id3.write(3);
	
	cout << "Choose uniform(1) or neighbouring(2) pattern: ";
	cin >> ptn;
	
	if(ptn==1){
		cout << "Enter the source (0 - 3): ";
		cin >> src;
		cout << "Enter the destination (0 - 3): ";
		cin >> dst;

		if(src > 3 || dst > 3){
			cout << "invalid input" << endl;
			return 0;
		}
		
		src_in.write(dst);
		chk.write(src);

		cout << endl;
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << endl << " 4X4 mesh NOC simulator containing 4 5x5 Wormhole router " << endl;
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "This is the simulation of a 4x4 Wormhole router.  " << endl; 
		cout << "We assume the router has 5 input/output ports, with 4 buffers per input port " << endl;
		cout << "and each flit has 21 bits width " << endl;
		cout << "  Press \"Return\" key to start the simulation..." << endl << endl;

		getchar();
		sc_start(10*125+124,SC_NS);

		sc_close_vcd_trace_file(tf);

		cout << endl << endl << "-------------------------------------------------------------------------------" << endl;
		cout << "End of switch operation..." << endl;
		if(src==0){
			cout << "Total number of packets sent: " <<  source0.pkt_snt << endl;
		}
		if(dst==0){
			cout << "Total number of packets received: " <<  sink0.pkt_recv << endl;
		}
		if(src==1){
			cout << "Total number of packets sent: " <<  source1.pkt_snt << endl;
		}
		if(dst==1){
			cout << "Total number of packets received: " <<  sink1.pkt_recv << endl;
		}
		if(src==2){
			cout << "Total number of packets sent: " <<  source2.pkt_snt << endl;
		}
		if(dst==2){
			cout << "Total number of packets received: " <<  sink2.pkt_recv << endl;
		}
		if(src==3){
			cout << "Total number of packets sent: " <<  source3.pkt_snt << endl;
		}
		if(dst==3){
			cout << "Total number of packets received: " <<  sink3.pkt_recv << endl;
		}
	
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "  Press \"Return\" key to end the simulation..." << endl << endl;
		getchar();
	}else if(ptn==2){
		cout << endl;
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << endl << " 4X4 mesh NOC simulator containing 4 5x5 Wormhole router " << endl;
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "This is the simulation of a 4x4 Wormhole router.  " << endl; 
		cout << "We assume the router has 5 input/output ports, with 4 buffers per input port " << endl;
		cout << "and each flit has 21 bits width " << endl;
		cout << "  Press \"Return\" key to start the simulation..." << endl << endl;
    
		getchar();

		for (int src = 0; src < 4; ++src) {
			int dst = (src + 1) % 4; 

			src_in.write(dst);
			chk.write(src);

			sc_start(10*125+124,SC_NS);

			cout << endl << endl << "-------------------------------------------------------------------------------" << endl;
			cout << "End of switch operation..." << endl;
			if(src==0){
				cout << "Total number of packets sent: " <<  source0.pkt_snt << endl;
			}
			if(dst==0){
				cout << "Total number of packets received: " <<  sink0.pkt_recv << endl;
			}
			if(src==1){
				cout << "Total number of packets sent: " <<  source1.pkt_snt << endl;
			}
			if(dst==1){
				cout << "Total number of packets received: " <<  sink1.pkt_recv << endl;
			}
			if(src==2){
				cout << "Total number of packets sent: " <<  source2.pkt_snt << endl;
			}
			if(dst==2){
				cout << "Total number of packets received: " <<  sink2.pkt_recv << endl;
			}
			if(src==3){
				cout << "Total number of packets sent: " <<  source3.pkt_snt << endl;
			}
			if(dst==3){
				cout << "Total number of packets received: " <<  sink3.pkt_recv << endl;
			}
	
			cout << "-------------------------------------------------------------------------------" << endl;
			cout << "  Press \"Return\" key to go to next neighbour.." << endl << endl;
			getchar();
		}

		// After all iterations, close the trace file
		sc_close_vcd_trace_file(tf);

		cout << "Press \"Return\" key to end the simulation..." << endl << endl;
		getchar(); // Wait for user to press enter to end the simulation
	} else {
		cout << "invalid input" << endl;
	}

	return 0;
}
