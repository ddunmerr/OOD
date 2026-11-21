#include "CApplicationSingletone.h"
#include <iostream>

int main()
{
	CApplicationSingletone::Instance().Run(INPUT_FILE);

	return 0;
}
