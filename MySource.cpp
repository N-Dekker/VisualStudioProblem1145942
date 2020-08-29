/*******************************************************************************
* Copyright 2020 Niels Dekker, LKEB, Leiden University Medical Center
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

// Aims to reproduce Visual Studio problem 1145942:
// "VS2019 Internal compiler error using __restrict keyword in Release build"
// https://developercommunity.visualstudio.com/content/problem/1145942/vs2019-internal-compiler-error-using-restrict-keyw.html

template <typename T> void CallMyFunctor(T func) {
    func();
}

void MyFunction(int n, int *__restrict ptr) {
    int zero_val = 0;
    if (n) {
        for (int i = 0; i < n; ++i)
            ptr[i] = zero_val;
    } else {
        CallMyFunctor([&]() { ptr[0] = zero_val; });
    }
}
