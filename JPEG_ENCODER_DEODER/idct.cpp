#include "idct.h"

//inverse discrete cosine transform
void idct::calculate_idct(void){
	unsigned char 	u, v, x, y;
	double 	temp; 
	double cu, cv;

    for (x = 0; x < 8; x++) {
        for (y = 0; y < 8; y++) {
            temp = 0.0;
            
            for (u = 0; u < 8; u++) {
                cu = (u == 0) ? 1.0 / sqrt(2.0) : 1.0;
                
                for (v = 0; v < 8; v++) {
                    cv = (v == 0) ? 1.0 / sqrt(2.0) : 1.0;

                    temp += 0.25 * cu * cv * in64[u][v] * fcosine[x][u].read() * fcosine[y][v].read();
                }
            }
            
            out64_idct[x][y].write(temp);
        }
    }
}