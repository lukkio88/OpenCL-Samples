kernel void calculateSum(global float* v, global float* tmp)
{
	int currentSize = get_local_size(0) / 2;
	int i = get_global_id(0);
	tmp[i] = v[i];
	barrier(CLK_GLOBAL_MEM_FENCE);

	while (currentSize > 0)
	{
		tmp[i] = tmp[i] + tmp[i + currentSize];
		barrier(CLK_GLOBAL_MEM_FENCE);
		currentSize /= 2;
	}
}

kernel void maxArray(global float* v, global float* tmp)
{
	int currentSize = get_local_size(0) / 2;
	int i = get_global_id(0);
	tmp[i] = v[i];
	barrier(CLK_GLOBAL_MEM_FENCE);

	while (currentSize > 0)
	{
		tmp[i] = max(tmp[i],tmp[i + currentSize]);
		barrier(CLK_GLOBAL_MEM_FENCE);
		currentSize /= 2;
	}
}

kernel void minArray(global float* v, global float* tmp)
{
	int currentSize = get_local_size(0) / 2;
	int i = get_global_id(0);
	tmp[i] = v[i];
	barrier(CLK_GLOBAL_MEM_FENCE);

	while (currentSize > 0)
	{
		tmp[i] = min(tmp[i], tmp[i + currentSize]);
		barrier(CLK_GLOBAL_MEM_FENCE);
		currentSize /= 2;
	}
}