#include "subnet_shortest_path.cuh"

__global__ void test(A a) {

	a.increment();
	a.print_data();
}

int tt() {

	A h_a;
	h_a.increment();
	h_a.print_data();
	test << <3, 5 >> >(h_a);
	cudaDeviceSynchronize();
	h_a.print_data();
	return 0;
}