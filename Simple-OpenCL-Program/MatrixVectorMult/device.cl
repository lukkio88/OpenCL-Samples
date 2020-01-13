__kernel void matrixVectorMultiplication(
	__global double * inputM,
	__global double * inputX,
	__local double * partialSum, //same size as the matrix
	__global double * result) {

    size_t global_idx = get_global_id(0);
	size_t local_idx = get_local_id(0);
	size_t group_idx = get_group_id(0);
	size_t group_size = get_local_size(0);

    //Performing all the products
	partialSum[global_idx] = inputM[global_idx]*inputX[local_idx];
	barrier(CLK_LOCAL_MEM_FENCE);

	//Now we perform the sum reduction
    for (uint stride = group_size/2; stride>0; stride /=2)
    {
        // Waiting for each 2x2 addition into given workgroup
        barrier(CLK_LOCAL_MEM_FENCE);

        // Add elements 2 by 2 between local_id and local_id + stride
        if (local_idx < stride)
            partialSum[global_idx] += partialSum[global_idx + stride];
    }

    // Write result into partialSums[nWorkGroups]
    result[group_idx] = partialSum[group_idx*group_size];
}