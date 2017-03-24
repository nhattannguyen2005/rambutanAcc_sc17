//kernel
__device__ void stencil(void* sArgs, void* aArgs){
  sysArgsType sysArgs= (sysArgsType)sArgs;
  int threadId_x = sysArgs.threadId_x; 
  int blockId_x = sysArgs.blockId_x;
  ... //retrieve app arguments and compute
} 
//task definition
struct stencilTask{
  double *Uold, *Unew, *north, *south, *east, *west;
  void depend_data(TaskName me) {
    memType loc = GPU_DRAM;
    register_input (&Uold, dataMapping(me), loc);
    if(hasNorth) //likewise for south, east, and west
      register_input (&north, dataMapping(me), loc);
    register_output (&Unew, dataMapping(me), loc);
  } 
  void execute(){
    appArgs args(Uold, Unew, north, south, east, west);
    offload_function(&stencil, &args);
  } 
};
