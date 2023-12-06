kernel void saxpy(global float* s, global float* x, global float* y, global float* z)
{
	int i = get_global_id(0);
	z[i] = (*s) * x[i] + y[i];
}