#include <systemc.h>
#include "multi.h"

int sc_main(int argc, char* argv[]) {
    sc_trace_file *tf; 
    sc_signal<sc_uint<8> > ain;
    sc_signal<sc_uint<8> > bin;
    sc_signal<sc_uint<16> > product;

    sc_clock clk("clk", 10, SC_NS, 0.5); 

	//module instance
    multi my_multi("multi"); 
    my_multi.bin(bin);
	my_multi.clk(clk);
    my_multi.ain(ain);
    my_multi.product(product);

    tf = sc_create_vcd_trace_file("trace_file");
    tf->set_time_unit(1, SC_NS);
	sc_trace(tf, clk, "clk");
    sc_trace(tf, product, "Product");
    sc_trace(tf, bin, "B");
    sc_trace(tf, ain, "A");

	// Simulation
    cout << "Starting Simulation" << endl;
    cout << "-------------------" << endl;
    cout << "                   " << endl;

    ain.write(5);
    bin.write(10);
    sc_start(10, SC_NS);
	
	cout << "@" << sc_time_stamp() << " input_a: " << ain.read() << ", input_b: " << bin.read() << endl;
    cout << "@" << sc_time_stamp() << " Product: " << product.read() << endl;

    ain.write(10);
    bin.write(0);
    sc_start(10, SC_NS);
	
	cout << "@" << sc_time_stamp() << " input_a: " << ain.read() << ", input_b: " << bin.read() << endl;
    cout << "@" << sc_time_stamp() << " Product: " << product.read() << endl;

    ain.write(255);
    bin.write(255);
    sc_start(10, SC_NS);
	
	cout << "@" << sc_time_stamp() << " input_a: " << ain.read() << ", input_b: " << bin.read() << endl;
    cout << "@" << sc_time_stamp() << " Product: " << product.read() << endl;

    ain.write(5);
    bin.write(255);
    sc_start(10, SC_NS);
	
	cout << "@" << sc_time_stamp() << " input_a: " << ain.read() << ", input_b: " << bin.read() << endl;
    cout << "@" << sc_time_stamp() << " Product: " << product.read() << endl;

    ain.write(0);
    bin.write(0);
    sc_start(10, SC_NS);
	
	cout << "@" << sc_time_stamp() << " input_a: " << ain.read() << ", input_b: " << bin.read() << endl;
    cout << "@" << sc_time_stamp() << " Product: " << product.read() << endl;

    ain.write(255);
    bin.write(0);
    sc_start(10, SC_NS);
	
	cout << "@" << sc_time_stamp() << " input_a: " << ain.read() << ", input_b: " << bin.read() << endl;
    cout << "@" << sc_time_stamp() << " Product: " << product.read() << endl;

    cout << "                   " << endl;
    cout << "-------------------" << endl;
    cout << "Simulation Ended" << endl;

    sc_close_vcd_trace_file(tf);

    return 0;
}
