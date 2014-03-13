// Copyright (c) Microsoft
// All rights reserved
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
// THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
// See the Apache Version 2.0 License for specific language governing permissions and limitations under the License.
/// <tags>P0</tags>
/// <summary>Test whether defaulted default constructors have restrict(cpu) specifiers.</summary>
#include <amptest.h>
#include <amptest_main.h>
#include "../common_defaulted_default_ctor_cpu.01.h"
using namespace concurrency;
using namespace concurrency::Test;

bool test() restrict(cpu)
{
	A1 a1;
	A2 a2;
	A3 a3;
	A4 a4;
	A5 a5;
	return true; // Compile-time tests
}

runall_result test_main()
{
	accelerator_view av = require_device().get_default_view();

	runall_result result;
	result &= test();
	return result;
}
