#include "bin/BigNumber/include/bignumber.h"
#include <assert.h>
#include <iostream>

int main(int argc, char const *argv[])
{
	assert((BigNumber("-100") - BigNumber("-5")) == -95);
	std::cout << "over!!!" << std::endl;
	return 0;
}
