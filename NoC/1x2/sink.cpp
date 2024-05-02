// sink.cpp
#include "sink.h"
void sink::receive_data(){

	packet v_packet;
	if ( sclk.event() ) ack_out.write(false);
	if (packet_in.event() ) 
	{ 
		pkt_recv++ ;
		total_send_time = time_in.read();
		total_rcv_time += sc_time_stamp().to_seconds();
		pkt_delay = (total_rcv_time - total_send_time)/pkt_recv;
		ack_out.write(true);
		v_packet= packet_in.read();
		cout << "			New Pkt:  " << (int)v_packet.data<< " is received from source: " << (int)v_packet.id  << " by sink:  " << (int)sink_id.read() << endl;
		//cout << "total rcv time:" << total_rcv_time*1e9 << endl;
		//cout << "total send time:" << total_send_time*1e9 << endl;
		cout << "				Avg Pkt Delay:	" << pkt_delay*1e9 << "ns" << endl;

	}
}
