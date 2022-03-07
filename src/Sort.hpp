#pragma once

#include <vector>
#include <iostream>

class Sort
{
	private:
		bool m_IsSorted;
	public:
		Sort();
		~Sort();

		std::vector<float> GenerateHeights(int windowHeight, int amount);

		void BubbleSort(std::vector<float>& heights);
		void SelectionSort(std::vector<float>& heights);
		void InsertionSort(std::vector<float>& heights);

		inline bool IsSorted() const { return m_IsSorted; }
};

