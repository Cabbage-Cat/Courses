#include <pthread.h>
#include <stdio.h>
const int maxn = 100;
int buf_one[100]; int cnt_one = 0;
int buf_two[100]; int cnt_two = 0;
pthread_mutex_t lock;
void* read_int_to_bufone(void* args){
  pthread_mutex_lock(&lock);
  FILE* fp = (FILE*)args;
  fscanf(fp,"%d",&buf_one[cnt_one++]);
  pthread_mutex_unlock(&lock);
}

void* read_int_to_buftwo(void* args){
  pthread_mutex_lock(&lock);
  FILE* fp = (FILE*)args;
  fscanf(fp,"%d",&buf_two[cnt_two++]);
  pthread_mutex_unlock(&lock);
}

void* calc_from_buf(void* args){
  pthread_mutex_lock(&lock);
  if (cnt_one && cnt_two){
    printf("%d plus %d = %d\n",buf_one[cnt_one-1],buf_two[cnt_two-1],buf_one[cnt_one-1]+buf_two[cnt_two-1]);
    printf("%d mul %d = %d\n\n",buf_one[cnt_one-1],buf_two[cnt_two-1],buf_one[cnt_one-1]*buf_two[cnt_two-1]);

  }
  pthread_mutex_unlock(&lock);
}

int main(){
  FILE* file_one = fopen("1.dat","r");
  FILE* file_two = fopen("2.dat","r");
  pthread_t pids[3];
  pthread_mutex_init(&lock,NULL);
  while (!feof(file_one) || !feof(file_two)){
    if (!feof(file_one))
      pthread_create(pids,NULL,read_int_to_bufone,file_one);
    if (!feof(file_two))
      pthread_create(pids+1,NULL,read_int_to_buftwo,file_two);
    
    // waiting for two read thread done.
    pthread_join(pids[0],NULL);
    pthread_join(pids[1],NULL);

    // output read sol
    pthread_create(pids+2,NULL,calc_from_buf,NULL);
    pthread_join(pids[2],NULL);
  }
  return 0;
}