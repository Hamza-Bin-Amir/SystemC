#include "multi.h"

void multi::multi_method() {
    sc_uint<8> sum, carout, a, b, a_b, sin, lsb_val, cin;
    sc_uint<8> cpa_sum, cpa_cout, cpa_temp_cout, cpa_cin, msb_val;
    sc_uint<16> out;
    int i, j, k, x, y = 0;
    int temp_sum[8][8];
    int temp_cout[8][8];
	int temp_out[16];

	a = ain.read();
    b = bin.read();
    a_b = a & b;

    //CSA row 1-7 computations
    for (i = 0; i < 8; i++) { //row
        for (j = 0; j < 8; j++) { //col
            if (i == 0) {
                sin = 0;
                cin = 0;
                a_b = a[j] & b[i];
                sum = (a_b ^ sin) ^ cin;
                carout = (a_b & sin) | (sin & cin) | (a_b & cin);
				temp_sum[i][j] = sum;
                temp_cout[i][j] = carout;
				lsb_val[i] = (j == 0) ? sum[j] : lsb_val[i];
            } else if ((j == 7) && (i != 0)) {
				sin = 0;
                cin = temp_cout[i - 1][j];
                a_b = a[j] & b[i];
                sum = (a_b ^ sin) ^ cin;
                carout = (a_b & sin) | (sin & cin) | (a_b & cin);
                temp_sum[i][j] = sum;
                temp_cout[i][j] = carout;
            } else {
				sin = temp_sum[i - 1][j + 1];
				cin = temp_cout[i - 1][j];
                a_b = a[j] & b[i];
                sum = (a_b ^ sin) ^ cin;
                carout = (a_b & sin) | (sin & cin) | (a_b & cin);
                temp_sum[i][j] = sum;
                temp_cout[i][j] = carout;
				lsb_val[i] = (j == 0) ? sum[j] : lsb_val[i];
            }
        }
    }


    //CPA last row computations
    for (x = 0; x < 8; x++) {
        if (x == 0) {
            cpa_cin = 0;
            a = temp_sum[7][x + 1];
            b = temp_cout[7][x];
        } else if (x == 7) {
            cpa_cin = 0;
            b = cpa_temp_cout[x - 1];
            a = temp_cout[7][x];
        } else {
            cpa_cin = cpa_temp_cout[x - 1];
            b = temp_cout[7][x];
            a = temp_sum[7][x + 1];
        }

        cpa_sum = (a ^ b) ^ cpa_cin;
        cpa_cout = (a & b) | (cpa_cin & b) | (a & cpa_cin);

        msb_val[x] = cpa_sum;
        cpa_temp_cout[x] = cpa_cout;
    }

	

    for (y = 0; y < 16; y++) {
        out[y] = (y < 8) ? lsb_val[y] : msb_val[y - 8];
		temp_out[y] = out[y];
    }

	for (k = 15; k >= 0; k--) {
		cout << temp_out[k];
    }


	cout << endl;

    product.write(out);
}
