#pragma once

#include "stdafx.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

class A {
	int data;
public:
	A() { data = 0; }
	__host__ __device__ void increment() { data++; }
	__host__ __device__ void print_data() const { printf("data = %d\n", data); }
};


__global__ void test(A a);

int tt();
