// COE838 - Lab1 SystemC Intro
// ALU unit. 
//////////////////////////////////

#ifndef ALU_H
#define ALU_H

#include <systemc.h>

SC_MODULE(ALU) {
    // Ports and signals
    sc_in_clk clk;
    sc_in<bool> en;
    sc_in<sc_int<8> > shift_amt;
    sc_in<bool> l_r;
    sc_in<sc_int<8> > input_b;
    sc_in<sc_int<8> > input_a;
    sc_in<bool> op;
    sc_out<sc_int<8> > shifted_output;
    sc_out<sc_int<8> > result;

    // Processes
    void barrel_shift_process();
    void alu_process();

    // Constructor
    SC_CTOR(ALU) {
        SC_METHOD(barrel_shift_process);
        sensitive << clk.pos();

        SC_METHOD(alu_process);
        sensitive << clk.neg();
        dont_initialize();  // Ensure that the method is not triggered at time 0
    }
};

#endif // BARREL_SHIFTER_ALU_H
