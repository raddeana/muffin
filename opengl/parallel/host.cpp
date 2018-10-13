#include "stdafx.h"
#include <string>
#include <CL/cl.h>
#include <time.h>
#define MAX_SOURCE_SIZE (0x100000)
 
int main () {
  cl_platform_id platform_id = NULL;
  cl_device_id device_id = NULL;
  cl_context context = NULL;
  cl_command_queue command_queue = NULL;
  cl_mem Amobj = NULL;
  cl_mem Bmobj = NULL;
  cl_mem Cmobj = NULL;
  cl_program program = NULL;
  cl_kernel kernel[4] = {NULL, NULL, NULL, NULL};
  cl_uint ret_num_devices;
  cl_uint ret_num_platforms;
  cl_int ret;
 
  int i, j;
  float *A, *B, *C;
 
  A = (float *) malloc(4 * 4 * sizeof(float));
  B = (float *) malloc(4 * 4 * sizeof(float));
  C = (float *) malloc(4 * 4 * sizeof(float));
 
  FILE *fp;
  const char fileName[] = "./taskParallel.cl";
  size_t source_size;
  char *source_str;
 
  // load kernel source file
  fp = fopen(fileName, "rb");

  if(!fp) {
    fprintf(stderr, "Failed to load kernel\n");
    exit(1);	
  }
 
  source_str = (char *)malloc(MAX_SOURCE_SIZE);
  source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
  fclose(fp);
 
  // initialize input data
  for(i = 0; i < 4; i ++) {
    for(j = 0; j < 4; j ++) {
      A[i * 4 + j] = i * 4 + j + 1;
      B[i * 4 + j] = j * 4 + i + 1;
    }	
  }
 
  // print A 
  printf("\nA initilization data: \n");
  for (i = 0; i < 4; i ++) {
    for (j = 0; j < 4; j ++) {
      printf("%.2f\t", A[i*4+j]);
    }

    printf("\n");
  }
 
  // print B 
  printf("\nB initilization data: \n");
  for (i = 0; i < 4; i ++) {
    for(j = 0; j < 4; j ++) {
      printf("%.2f\t", B[i * 4 + j]);
    }

    printf("\n");
  }
 
  clock_t start, finish;
  double duration;
  
  printf("TaskParallel kernels start to execute\n");
  start = clock();

  // get platform/device information
  ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
  ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
 
  // create opencl context
  context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
 
  // create command queue
  command_queue = clCreateCommandQueue(context, device_id, CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE, &ret);
 
  // create buffer object
  Amobj = clCreateBuffer(context, CL_MEM_READ_WRITE, 4 * 4 * sizeof(float), NULL, &ret);
  Bmobj = clCreateBuffer(context, CL_MEM_READ_WRITE, 4 * 4 * sizeof(float), NULL, &ret);
  Cmobj = clCreateBuffer(context, CL_MEM_READ_WRITE, 4 * 4 * sizeof(float), NULL, &ret);
 
  // copy input data to memory buffer
  ret = clEnqueueWriteBuffer(command_queue, Amobj, CL_TRUE, 0, 4 * 4 * sizeof(float), A, 0, NULL, NULL);
  ret = clEnqueueWriteBuffer(command_queue, Bmobj, CL_TRUE, 0, 4 * 4 * sizeof(float), B, 0, NULL, NULL);
 
  // create kernel from source
  program = clCreateProgramWithSource(context, 1, (const char **) & source_str, (const size_t *)&source_size, &ret);
  ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
 
  // create task parallel
  kernel[0] = clCreateKernel(program, "add_parallel", &ret);
  kernel[1] = clCreateKernel(program, "sub_parallel", &ret);
  kernel[2] = clCreateKernel(program, "mul_parallel", &ret);
  kernel[3] = clCreateKernel(program, "div_parallel", &ret);
 
  // set opencl kernel arguments
  for (i = 0; i < 4; i ++) {
    ret = clSetKernelArg(kernel[i], 0, sizeof(cl_mem), (void *) &Amobj);
    ret = clSetKernelArg(kernel[i], 1, sizeof(cl_mem), (void *) &Bmobj);
    ret = clSetKernelArg(kernel[i], 2, sizeof(cl_mem), (void *) &Cmobj);
  }
 
  // execute opencl kernels
  for(i = 0; i < 4; i ++) {
    ret = clEnqueueTask(command_queue, kernel[i], 0, NULL, NULL);
  }
 
  // copy result to host
  ret = clEnqueueReadBuffer(command_queue, Cmobj, CL_TRUE, 0, 4 * 4 * sizeof(float), C, 0, NULL, NULL);
 
  // end of execution
  finish = clock();
  duration = (double)(finish - start) / CLOCKS_PER_SEC;
  printf("\n%f seconds\n", duration);
 
  // display result
  printf("\nC result: \n");
  for (i = 0; i < 4; i ++) {
    for (j = 0; j < 4; j ++) {
      printf("%.2f\t", C[i * 4 + j]);
    }

    printf("\n");
  }

  printf("\n");
 
  // free
  ret = clFlush(command_queue);
  ret = clFinish(command_queue);
  ret = clReleaseKernel(kernel[0]);
  ret = clReleaseKernel(kernel[1]);
  ret = clReleaseKernel(kernel[2]);
  ret = clReleaseKernel(kernel[3]);
  ret = clReleaseProgram(program);
  ret = clReleaseMemObject(Amobj);
  ret = clReleaseMemObject(Bmobj);
  ret = clReleaseMemObject(Cmobj);
  ret = clReleaseCommandQueue(command_queue);
  ret = clReleaseContext(context);

  free(source_str);
  free(A);
  free(B);
  free(C);
 
  system("pause");
  return 0;
}
