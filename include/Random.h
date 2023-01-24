#pragma once
#include <time.h>
#include <stdlib.h>

// シード値
inline void SrandFromTime() {
	srand((unsigned int)time(NULL));
}

// 範囲指定を指定してランダム
inline int Random(int min, int max) {
	return  min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

// 0~1の実数ランダム
inline float Random() {
	return (float)rand() / RAND_MAX;
}