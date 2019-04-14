#pragma once

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

#include <iostream>
#include <random>
#include <array>

void print_line(std::ostream & ostream, std::size_t length)
{
	for(std::size_t index = 0; index < length; ++index)
		ostream << '-';
}

template< std::size_t height, std::size_t width >
void print_2d_array(std::ostream & ostream, const bool(&array)[height][width])
{
	ostream << '+';
	print_line(ostream, width);
	ostream << '+';
	ostream << '\n';

	for(std::size_t y = 0; y < height; ++y)
	{
		ostream << '|';
		for(std::size_t x = 0; x < width; ++x)
			ostream << (array[y][x] ? '#' : ' ');
		ostream << '|';
		ostream << '\n';
	}

	ostream << '+';
	print_line(ostream, width);
	ostream << '+';
}

template< std::size_t width, std::size_t height, std::size_t walker_count, std::size_t walker_step_count >
void drunk_walk(std::ostream & output)
{
	// Initialise a random device
	std::random_device random_device;

	// Generate a base seed value
	const auto base_seed = random_device();

	// Call actual drunk walk
	drunk_walk<width, height, walker_count, walker_step_count, std::random_device::result_type>(output, base_seed);
}

template< std::size_t width, std::size_t height, std::size_t walker_count, std::size_t walker_step_count, typename IntType >
void drunk_walk(std::ostream & output, IntType base_seed)
{
	// Useful constants
	constexpr std::size_t y_min = 0;
	constexpr std::size_t y_max = (height - 1);

	constexpr std::size_t x_min = 0;
	constexpr std::size_t x_max = (width - 1);

	// Declare field
	bool data[height][width] {};

	// Declare distributions
	std::uniform_int_distribution<std::mt19937::result_type> y_distribution { 0, (height - 1) };
	std::uniform_int_distribution<std::mt19937::result_type> x_distribution { 0, (width - 1) };
	std::uniform_int_distribution<std::mt19937::result_type> direction_distribution { 0, 3 };

	// Iterate for each walker
	for(std::size_t walker_index = 0; walker_index < walker_count; ++walker_index)
	{
		const auto seed = static_cast<std::mt19937::result_type>(base_seed + walker_index);

		// Seed the random generator
		std::mt19937 random_generator { seed };

		// Generate start y and start x
		std::size_t y = static_cast<std::size_t>(y_distribution(random_generator));
		std::size_t x = static_cast<std::size_t>(x_distribution(random_generator));

		// Set the initial square
		data[y][x] = true;

		// Walk like a drunkard for walker_step_count steps
		for(std::size_t walker_step = 0; walker_step < walker_step_count; ++walker_step)
		{
			const auto direction = direction_distribution(random_generator);

			switch(direction)
			{
			case 0:
				if(y > y_min)
					--y;
				else
					y = y_max;
				break;
			case 1:
				if(y < y_max)
					++y;
				else
					y = y_min;
				break;
			case 2:
				if(x > x_min)
					--x;
				else
					x = x_max;
				break;
			case 3:
				if(x < x_max)
					++x;
				else
					x = x_min;
				break;
			}

			data[y][x] = true;
		}
	}

	print_2d_array(std::cout, data);
}
