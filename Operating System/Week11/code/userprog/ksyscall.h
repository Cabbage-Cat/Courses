/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#include "kernel.h"




void SysHalt()
{
  kernel->interrupt->Halt();
}

int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

int SysWrite(char *buffer,int size,OpenFileId id){
  OpenFile *opfile = (OpenFile*)id;
  return opfile->Write(buffer,size);
}

int Read(char *buffer, int size, OpenFileId id){
  OpenFile *opfile = (OpenFile*)id;
  return opfile->Read(buffer,size);
}





#endif /* ! __USERPROG_KSYSCALL_H__ */
