// MIT License
//
// Copyright(c) 2019 Pharap
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <cstdlib>
#include <iostream>

#include "DrunkWalk.h"

int main()
{
	constexpr std::size_t data_height = 24;
	constexpr std::size_t data_width = 64;
	constexpr std::size_t walker_count = 64;
	constexpr std::size_t walker_step_count = 2;

	while(true)
	{
		drunk_walk<data_width, data_height, walker_count, walker_step_count>(std::cout);

		// Get the user's input
		auto nextCharacter = std::cin.get();

		using cin_type = decltype(std::cin);

		// Break if end of file
		if(nextCharacter == cin_type::traits_type::eof())
			break;

		// Break if character is 'x'
		cin_type::char_type c = static_cast<cin_type::char_type>(nextCharacter);
		if(c == 'x')
			break;
	}

	return EXIT_SUCCESS;
}