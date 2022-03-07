#include "Sort.hpp"

Sort::Sort()
    : m_IsSorted(false)
{
}

Sort::~Sort()
{

}

std::vector<float> Sort::GenerateHeights(int windowHeight, int amount)
{
    std::vector<float> heights;

    for (int i = 0; i < amount; i++)
    {
        float random = ((float)rand()) / (float)RAND_MAX;
        float range = (windowHeight / 100.0f) - 0.2f;

        float num = (random * range) + 0.2f;
        float pow_10 = pow(10.0f, (float)1);
        num = round(num * pow_10) / pow_10;

        heights.push_back(num);
    }

    return heights;
}

void Sort::BubbleSort(std::vector<float>& heights)
{
    bool swapped = false;
    for (int i = 0; i < heights.size()-1; i++) {
        for (int j = heights.size() - 1; j > i; j--) {
            if (heights[j - 1] > heights[j]) {
                std::swap(heights[j - 1], heights[j]);
                swapped = true;
                break;
            }
        }
    }
    m_IsSorted = !swapped;
}

void Sort::SelectionSort(std::vector<float>& heights)
{
    int t = -1;
    bool swapped = false;
    for (int i = 0; i < heights.size() - 1; i++) {
        t = i;
        for (int j = heights.size() - 1; j > i; j--) {
            if (heights[t] > heights[j]) {
                t = j;
            }
        }
        if (i != t) {
            std::swap(heights[i], heights[t]);
            swapped = true;
            break;
        }
    }
    m_IsSorted = !swapped;
}

void Sort::InsertionSort(std::vector<float>& heights)
{
    bool swapped = false;
    for (int i = 1; i < heights.size(); i++) {
        for (int j = i; j > 0 && heights[j - 1] > heights[j]; j--) {
            std::swap(heights[j - 1], heights[j]);
            swapped = true;
            break;
        }
    }
    m_IsSorted = !swapped;
}
