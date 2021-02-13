#include<iostream>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
using namespace std;
pthread_t* SouthThread;
pthread_t* NorthThread;
int M;    //Total Number of Cars
int N;    // Number of Car which we want to pass when the signal is Green
void DisplayProjectTitle(){
  cout<<"##################################"<<endl;
  cout<<"Intelligent Traffic Light System. "<<endl;
  cout<<"##################################"<<endl;
}
void SouthDir(int m,int n);
void NorthDir(int m,int n);
void NorthSignaldisplay(){
  cout<<"==================================================="<<endl;
  cout<<" North Signal is 'Green' .... South Signal is 'Red'"<<endl;
  cout<<"==================================================="<<endl;
}
void SouthSignaldisplay(){
  cout<<"==================================================="<<endl;
  cout<<" North Signal is 'Red' .... South Signal is 'Green'"<<endl;
  cout<<"==================================================="<<endl;
}
void* northcarmove(void* arg){
  cout<<"Car is Coming from North side to South side"<<endl;
  return NULL;
}
void* southcarmove(void* arg){
  cout<<"Car is Coming from South side to North side"<<endl;
  return NULL;
}

void NorthSideThread(int m,int n){
  NorthSignaldisplay();     // North Signal is Green and South  is RED
  NorthThread = new pthread_t[n];
  for(int i=0;i<n;i++){
    sleep(2);
    pthread_create(&NorthThread[i],NULL,northcarmove,NULL); //Displaying Car coming from NorthSide
  }
  for(int i=0;i<n;i++){
    pthread_join(NorthThread[i],NULL);
  }
}
void NorthDir(int m,int n){
    int z = 0; int half = m/2;
    int secondHalf=m-half;
    int c=0;
  for(int i = 0;i<=m/2;i++){
    if(z==n){
      c=c+z;
      z=0;
      NorthSideThread(m,n);
      SouthDir(m,n);
    }else if(i == half&&half==secondHalf){
        NorthSideThread(m,z);
        SouthDir(m,z);
    }if(i == half&&half!=secondHalf){
      if(c!=i){
        c=i-c;
        NorthSideThread(m,c);
      }
      SouthDir(m,z+1);
    }
    z++;
  }
}
void SouthSideThread(int m,int n){
  SouthSignaldisplay();     // South Signal is Green and North is RED
  SouthThread = new pthread_t[n];
  for(int i=0;i<n;i++){
    sleep(2);
    pthread_create(&SouthThread[i],NULL,southcarmove,NULL); //Displaying Car coming from SouthSide
  }
  for(int i=0;i<n;i++){
    pthread_join(SouthThread[i],NULL);
  }
}
void SouthDir(int m,int n){
   SouthSideThread(m,n);
}
int main(int args,char* argv[]){
  DisplayProjectTitle();    // Title of Project.
  M = atoi(argv[1]);        // getting total numbers of Car

  N = atoi(argv[2]);        // how many cars are cross at time when                             signal is green
  NorthDir(M,N);      //Passing M and N to NorthDirection Function
  return 0;
}