#pragma once
#include <time.h>
#include <stdlib.h>

// �V�[�h�l
inline void SrandFromTime() {
	srand((unsigned int)time(NULL));
}

// �͈͎w����w�肵�ă����_��
inline int Random(int min, int max) {
	return  min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

// 0~1�̎��������_��
inline float Random() {
	return (float)rand() / RAND_MAX;
}