// COE838 - Lab1 SystemC Intro
// ALU unit. 
//////////////////////////////////
//Testbench driver for ALU

#include <systemc.h>
#include "ALU.h"


int sc_main(int argc, char* argv[]) {
    // Signals
	sc_trace_file *tf;
    sc_signal<bool> en_signal;
    sc_signal<sc_int<8> > shift_amt_signal;
    sc_signal<bool> l_r_signal;
    sc_signal<sc_int<8> > input_b_signal;
    sc_signal<sc_int<8> > input_a_signal;
    sc_signal<bool> op_signal;
    sc_signal<sc_int<8> > shifted_output_signal;
    sc_signal<sc_int<8> > result_signal;
	
	sc_clock clk("clk",10,SC_NS,0.5);

    // Module instance
    ALU my_alu("my_alu");
	my_alu.clk(clk);  // Assuming clk is a sc_clock signal
	my_alu.en(en_signal);
	my_alu.shift_amt(shift_amt_signal);
	my_alu.l_r(l_r_signal);
	my_alu.input_b(input_b_signal);
	my_alu.input_a(input_a_signal);
	my_alu.op(op_signal);
	my_alu.shifted_output(shifted_output_signal);
	my_alu.result(result_signal);

	tf = sc_create_vcd_trace_file("trace_file");
    tf->set_time_unit(1, SC_NS);
	sc_trace(tf, clk, "clk");
	sc_trace(tf, en_signal, "en_signal");
	sc_trace(tf, shift_amt_signal, "shift_amt_signal");
	sc_trace(tf, l_r_signal, "l_r_signal");
	sc_trace(tf, input_b_signal, "input_b_signal");
	sc_trace(tf, input_a_signal, "input_a_signal");
	sc_trace(tf, op_signal, "op_signal");
	sc_trace(tf, shifted_output_signal, "shifted_output_signal");
	sc_trace(tf, result_signal, "result_signal");

	// Simulation
    cout << "Starting Simulation" << endl;
    cout << "-------------------" << endl;
    cout << "                   " << endl;

    //basic scenarios
	// Scenario 1
	en_signal.write(false);//disabled
	shift_amt_signal.write(2);
    l_r_signal.write(0); //left
    input_b_signal.write(23);
    input_a_signal.write(-22);
    op_signal.write(1); //add
    sc_start(10, SC_NS);

    cout << "@" << sc_time_stamp() << " Inputs for Scenario 1 - input_a: " << input_a_signal.read() << ", input_b: " << input_b_signal.read() << ", op: " << op_signal.read() << endl;
    cout << "@" << sc_time_stamp() << " ALU Output: " << result_signal.read() << endl;

    // Scenario 2
	en_signal.write(false);//disabled
	shift_amt_signal.write(2);
    l_r_signal.write(0); //left
    input_b_signal.write(34);
    input_a_signal.write(100);
    op_signal.write(0); //subtract
    sc_start(10, SC_NS);

    cout << "@" << sc_time_stamp() << " Inputs for Scenario 2 - input_a: " << input_a_signal.read() << ", input_b: " << input_b_signal.read() << ", op: " << op_signal.read() << endl;
    cout << "@" << sc_time_stamp() << " ALU Output: " << result_signal.read() << endl;
    
    // Scenario 3
	en_signal.write(true);//enabled
	shift_amt_signal.write(2);
    l_r_signal.write(1); //right
    input_b_signal.write(34);
    input_a_signal.write(95);
    op_signal.write(1); //add
    sc_start(10, SC_NS);

    cout << "@" << sc_time_stamp() << " Inputs for Scenario 3 - input_a: " << input_a_signal.read() << ", input_b: " << input_b_signal.read() << ", op: " << op_signal.read() << endl;
    cout << "@" << sc_time_stamp() << " ALU Output: " << result_signal.read() << endl;

    // Scenario 4
	en_signal.write(true);//enabled
	shift_amt_signal.write(3);
    l_r_signal.write(0); //left
    input_b_signal.write(67);
    input_a_signal.write(88);
    op_signal.write(1); //add
    sc_start(10, SC_NS);

    cout << "@" << sc_time_stamp() << " Inputs for Scenario 4 - input_a: " << input_a_signal.read() << ", input_b: " << input_b_signal.read() << ", op: " << op_signal.read() << endl;
    cout << "@" << sc_time_stamp() << " ALU Output: " << result_signal.read() << endl;

    // Scenario 5
	en_signal.write(true);//enabled
	shift_amt_signal.write(5);
    l_r_signal.write(1); //right
    input_b_signal.write(34);
    input_a_signal.write(32);
    op_signal.write(0); //subtract
    sc_start(10, SC_NS);

    cout << "@" << sc_time_stamp() << " Inputs for Scenario 5 - input_a: " << input_a_signal.read() << ", input_b: " << input_b_signal.read() << ", op: " << op_signal.read() << endl;
    cout << "@" << sc_time_stamp() << " ALU Output: " << result_signal.read() << endl;

    // Scenario 6
	en_signal.write(true);//enabled
	shift_amt_signal.write(3);
    l_r_signal.write(0); //left
    input_b_signal.write(67);
    input_a_signal.write(55);
    op_signal.write(0); //subtract
    sc_start(10, SC_NS);

    cout << "@" << sc_time_stamp() << " Inputs for Scenario 6 - input_a: " << input_a_signal.read() << ", input_b: " << input_b_signal.read() << ", op: " << op_signal.read() << endl;
    cout << "@" << sc_time_stamp() << " ALU Output: " << result_signal.read() << endl;

    //edge case scenarios
    // Scenario 1 - shift larger than 8 bits
    en_signal.write(true);
	shift_amt_signal.write(9);
    l_r_signal.write(1); //right
    input_b_signal.write(5);
    input_a_signal.write(10);
    op_signal.write(0); //subtract
    sc_start(10, SC_NS);

    cout << "@" << sc_time_stamp() << " Inputs for Scenario e1 - input_a: " << input_a_signal.read() << ", input_b: " << input_b_signal.read() << ", op: " << op_signal.read() << endl;
    cout << "@" << sc_time_stamp() << " ALU Output: " << result_signal.read() << endl;

    // Scenario 2 - greater than 8 bit input
    en_signal.write(false); //shift disabled
	shift_amt_signal.write(2);
    l_r_signal.write(1); //right
    input_b_signal.write(5);
    input_a_signal.write(382);
    op_signal.write(1); //add
    sc_start(10, SC_NS);

    cout << "@" << sc_time_stamp() << " Inputs for Scenario e2-1 - input_a: " << input_a_signal.read() << ", input_b: " << input_b_signal.read() << ", op: " << op_signal.read() << endl;
    cout << "@" << sc_time_stamp() << " ALU Output: " << result_signal.read() << endl;

    // Scenario 2 - greater than 8 bit input
    en_signal.write(false); //shift disabled
	shift_amt_signal.write(2);
    l_r_signal.write(1); //right
    input_b_signal.write(5);
    input_a_signal.write(381);
    op_signal.write(1); //add
    sc_start(10, SC_NS);

    cout << "@" << sc_time_stamp() << " Inputs for Scenario e2-2 - input_a: " << input_a_signal.read() << ", input_b: " << input_b_signal.read() << ", op: " << op_signal.read() << endl;
    cout << "@" << sc_time_stamp() << " ALU Output: " << result_signal.read() << endl;

    // Scenario 2 - greater than 8 bit input
    en_signal.write(false); //shift disabled
	shift_amt_signal.write(2);
    l_r_signal.write(1); //right
    input_b_signal.write(5);
    input_a_signal.write(255);
    op_signal.write(1); //add
    sc_start(10, SC_NS);

    cout << "@" << sc_time_stamp() << " Inputs for Scenario e2-3 - input_a: " << input_a_signal.read() << ", input_b: " << input_b_signal.read() << ", op: " << op_signal.read() << endl;
    cout << "@" << sc_time_stamp() << " ALU Output: " << result_signal.read() << endl;

    // Scenario 2 - greater than 8 bit input
    en_signal.write(false); //shift disabled
	shift_amt_signal.write(2);
    l_r_signal.write(1); //right
    input_b_signal.write(5);
    input_a_signal.write(127);
    op_signal.write(1); //add
    sc_start(10, SC_NS);

    cout << "@" << sc_time_stamp() << " Inputs for Scenario e2-4 - input_a: " << input_a_signal.read() << ", input_b: " << input_b_signal.read() << ", op: " << op_signal.read() << endl;
    cout << "@" << sc_time_stamp() << " ALU Output: " << result_signal.read() << endl;
    
    // Scenario 2 - greater than 8 bit input
    en_signal.write(false); //shift disabled
	shift_amt_signal.write(2);
    l_r_signal.write(1); //right
    input_b_signal.write(5);
    input_a_signal.write(130);
    op_signal.write(1); //add
    sc_start(10, SC_NS);

    cout << "@" << sc_time_stamp() << " Inputs for Scenario e2-5 - input_a: " << input_a_signal.read() << ", input_b: " << input_b_signal.read() << ", op: " << op_signal.read() << endl;
    cout << "@" << sc_time_stamp() << " ALU Output: " << result_signal.read() << endl;

    // Scenario 3 - unkown set values
    en_signal.write(true); //shift enabled
	shift_amt_signal.write(2);
    l_r_signal.write(4); //unknown
    input_b_signal.write(24);
    input_a_signal.write(10);
    op_signal.write(3); //unknown
    sc_start(12, SC_NS);

    cout << "@" << sc_time_stamp() << " Inputs for Scenario e3 - input_a: " << input_a_signal.read() << ", input_b: " << input_b_signal.read() << ", op: " << op_signal.read() << endl;
    cout << "@" << sc_time_stamp() << " ALU Output: " << result_signal.read() << endl;

    cout << "                   " << endl;
    cout << "-------------------" << endl;
    cout << "Simulation Ended" << endl;

	sc_close_vcd_trace_file(tf);

    return 0;
}
