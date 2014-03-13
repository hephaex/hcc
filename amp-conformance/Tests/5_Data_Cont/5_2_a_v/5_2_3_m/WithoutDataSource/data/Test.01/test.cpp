// Copyright (c) Microsoft
// All rights reserved
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
// THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
// See the Apache Version 2.0 License for specific language governing permissions and limitations under the License.

/// <summary>Test 'data' member function on array_views without a data source</summary>
#include <amptest.h>
#include <amptest_main.h>

using namespace Concurrency;
using namespace Concurrency::Test;

/*
* Testing 'data' on array_view object created without data source.
* before p_f_e and after p_f_e
*/
runall_result test1(const accelerator_view &av)
{
	runall_result result;
	const int M = 256;
		
	array_view<int,1> arrViewSrc(M);
	int* dataPtr1 = arrViewSrc.data();
	
	result &= REPORT_RESULT( dataPtr1 != NULL );
	
	parallel_for_each(av,arrViewSrc.get_extent(),[=](index<1> idx) restrict(amp){
		arrViewSrc(idx) = idx[0];
	});
	
	int* dataPtr2 = arrViewSrc.data();
	result &= REPORT_RESULT( dataPtr2 != NULL);
	result &= REPORT_RESULT( dataPtr1 == dataPtr2);
	
	bool passed = true;
	for (size_t i = 0; i < M; ++i) {
		if (dataPtr2[i] != i) {
			Log(LogType::Error) << "Expected = " << i << ", Actual = " << dataPtr2[i] << std::endl;
			passed = false;
		}
	}
	result &= REPORT_RESULT(passed);
	return result;
}

runall_result test_main()
{
    accelerator_view av = require_device().get_default_view();
    runall_result res;
	
    res &= REPORT_RESULT(test1(av));
	
    return res;
}

