#include "hwlib.hpp"
#include "irReceiver.hpp"

int main() {
	WDT->WDT_MR = WDT_MR_WDDIS;
	hwlib::wait_ms( 500 );
    
    IrReceiver receiver(1, 14);
    
    receiver.test();

    
    
	return 0;
}