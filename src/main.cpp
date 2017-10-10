#include "hwlib.hpp"

int main() {
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	return 0;
}