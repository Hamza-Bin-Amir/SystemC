// source.cpp
#include "source.h"
void source:: func(){
	
	packet v_packet_out;
	v_packet_out.data=1000;
	v_packet_out.pkt_clk = '0';
	
	while(true){
		wait();
		if(!ach_in.read()){ 
			if(chk.read() == source_id.read()){
				v_packet_out.data = v_packet_out.data + source_id.read() + 1;
				v_packet_out.id = source_id.read();
				v_packet_out.dest = dst.read();
				if(v_packet_out.id == v_packet_out.dest) goto exclode;		 
				v_packet_out.pkt_clk = ~v_packet_out.pkt_clk ;
				v_packet_out.h_t = false;
				pkt_snt++;
				if((pkt_snt%5)==0)v_packet_out.h_t=true;
				packet_out.write(v_packet_out);
				cout << "New Pkt: " << v_packet_out.data << " is sent by source: " << source_id.read()  << "  to Destination:   "<< v_packet_out.dest <<endl;

				exclode:;
				
				total_send_time += sc_time_stamp().to_seconds();
				time_out.write(total_send_time);
			}
		}  
	}
}
