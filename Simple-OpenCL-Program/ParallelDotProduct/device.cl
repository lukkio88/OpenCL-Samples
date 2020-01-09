__kernel void dotProduct(
	__global double * inputA,
	__global double * inputB,
	__local double * partialSum,
	__global double * result) {

	size_t idx = get_global_id(0);
	size_t group_size = get_local_size(0);

    //Performing all the products
	partialSum[idx] = inputA[idx]*inputB[idx];
	barrier(CLK_LOCAL_MEM_FENCE);

	//Now we perform the sum reduction
    for (uint stride = group_size/2; stride>0; stride /=2)
    {
        // Waiting for each 2x2 addition into given workgroup
        barrier(CLK_LOCAL_MEM_FENCE);

        // Add elements 2 by 2 between local_id and local_id + stride
        if (idx < stride)
        partialSum[idx] += partialSum[idx + stride];
    }

    // Write result into partialSums[nWorkGroups]
    if (idx == 0)
        result[get_group_id(0)] = partialSum[0];
}