int getIndex(int i, int j, int orderMatrix)
{
	return i*orderMatrix + j;
}

kernel void gaussElimination(global float* A, global int* iteration, global int* orderMatrix)
{
	//From my pseudocode of gaussian elimination
	int k = *iteration;
	int i = get_global_id(0);
	int j = get_global_id(1);

	float pivotElement = - A[getIndex(i + k + 1, k, *orderMatrix)]/A[getIndex(k,k, *orderMatrix)];
	int currentIndex = getIndex(i + k + 1, j + k, *orderMatrix);
	A[currentIndex] += pivotElement*A[getIndex(k, j + k,*orderMatrix)];
	++k;
	barrier(CLK_GLOBAL_MEM_FENCE);
	*iteration = k;
}