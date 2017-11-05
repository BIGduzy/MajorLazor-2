#include "hwlib.hpp"

using namespace due;

int main( void ){	
   // kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
   
	namespace target 	= hwlib::target;
	auto bitPin0       	= target::pin_out( target::pins::d22 );
	auto bitPin1       	= target::pin_out( target::pins::d23 );
	auto bitPin2       	= target::pin_out( target::pins::d24 );
	auto bitPin3       	= target::pin_out( target::pins::d25 );
	
	auto bitPin4       	= target::pin_out( target::pins::d26 );
	auto bitPin5       	= target::pin_out( target::pins::d27 );
	auto bitPin6       	= target::pin_out( target::pins::d28 );
	auto bitPin7       	= target::pin_out( target::pins::d29 );
	
	//auto testPin       	= target::pin_out( target::pins::d50 );
	
	auto ackPin       	= target::pin_out( target::pins::d50 );
	auto conPin       	= target::pin_in( target::pins::d51 );
	
	hwlib::wait_ms(500);
   
	uint8_t i = 170;
   
	bitPin0.set((i >> 7) & 1);
	bitPin1.set((i >> 6) & 1);
	bitPin2.set((i >> 5) & 1);
	bitPin3.set((i >> 4) & 1);
	
	bitPin4.set((i >> 3) & 1);
	bitPin5.set((i >> 2) & 1);
	bitPin6.set((i >> 1) & 1);
	bitPin7.set((i >> 0) & 1);
	
	hwlib::wait_ms(100);
	
	//testPin.set(1);
	ackPin.set(1);
	
	hwlib::wait_ms(500);
	
	ackPin.set(0);
   
	while (true) {}
   
}
