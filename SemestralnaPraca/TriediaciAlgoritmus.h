#pragma once
#include <libds/amt/implicit_sequence.h>
#include "UzemnaJednotka.h"

class TriediaciAlgoritmus
{
public:
	static void triedData(ds::amt::ImplicitSequence<UzemnaJednotka*>& is, std::function<int(UzemnaJednotka*, UzemnaJednotka*)> komparator, size_t min, size_t max);
};

void TriediaciAlgoritmus::triedData(ds::amt::ImplicitSequence<UzemnaJednotka*>& is, std::function<int(UzemnaJednotka*, UzemnaJednotka*)> komparator, size_t min, size_t max) {
    // quick sort
    size_t pivotIndex = min + (max - min) / 2;
    UzemnaJednotka* pivot = is.access(pivotIndex)->data_;
    size_t left = min;
    size_t right = max;

    while (left <= right) {
        while (komparator(is.access(left)->data_, pivot) == -1) {
            left++;
        }

        while (komparator(pivot, is.access(right)->data_) == -1) {
            right--;
        }

        if (left <= right) {
            std::swap(is.access(left)->data_, is.access(right)->data_);
            left++;
            if (right == 0) {
                continue;
            }
            right--;
        }
    }
    if (min < right) {
        triedData(is, komparator, min, right);
    }
    if (left < max) {
        triedData(is, komparator, left, max);
    }
}