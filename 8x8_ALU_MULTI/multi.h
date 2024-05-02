#ifndef multi_H
#define multi_H

#include <systemc.h>

SC_MODULE(multi) {
	sc_in_clk clk;
    sc_in<sc_uint<8> > bin;
    sc_in<sc_uint<8> > ain;
    sc_out<sc_uint<16> > product;

    void multi_method();

    SC_CTOR(multi) {
        SC_METHOD(multi_method);
        dont_initialize();
        sensitive << clk.pos(); // edge sensitive (positive)
    }
};

#endif
