#include "ALU.h"

void ALU::barrel_shift_process() {
    // Temporary variable to store the result
    sc_int<8> temp_result;
	temp_result = input_b.read();
	int shift_amount = shift_amt.read();

    // Perform barrel shift based on l_r control signal and shift amount
	if (shift_amount >= 8) {
        // If shift_amt is larger or equal to the bit width, pass through without shifting
        temp_result = input_b.read();
    } else if (en.read() == 1) {
        if (l_r.read()) {
            temp_result = input_b.read() >> shift_amt.read();
        } else {
            temp_result = input_b.read() << shift_amt.read();
        }
    } else {
        // Pass through without shifting
        temp_result = input_b.read();
    }


    // Update the shifted_output signal
    shifted_output.write(temp_result);

}

void ALU::alu_process() {
    sc_int<8> operand_a = input_a.read();
    sc_int<8> operand_b = shifted_output.read();


    // Perform addition or subtraction based on op control signal
    if (op.read() == 1) {
        result.write(operand_a + operand_b);
    } else if(op.read() == 0){
        result.write(operand_a - operand_b);
    } else {
		result.write(operand_a + operand_b);	
	}
}