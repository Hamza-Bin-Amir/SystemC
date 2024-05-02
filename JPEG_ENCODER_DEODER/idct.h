#include "systemc.h"
#include <math.h>

#ifndef IDCT_H
#define IDCT_H

struct idct : sc_module{ 
	
	sc_in<double> in64[8][8];
	sc_out<char> out64_idct[8][8];
	sc_in<double> fcosine[8][8];
	sc_in<bool> clk;

	void calculate_idct( void );

	SC_CTOR( idct ) { 
		SC_METHOD( calculate_idct );
		dont_initialize();
		sensitive << clk.pos();
	}
};

#endif