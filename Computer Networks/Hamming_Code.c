#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convertInt(char buff[],int d_size , int data[]){
	int j = 0 ;
	for(int i = d_size - 1 ; i >= 0 ; i -- ){
		switch( buff[i] ){
			case '0' : data[j] = 0 ; j ++ ; break ;
			case '1' : data[j] = 1 ; j ++ ; break ; 
			default : printf("Invalid Input\n");
						exit(0);
		}
	}
}

int generateParity(int data[],int d_size,int ham[]){

	int j = 1 ;
	ham[0] = -1 ;
	for( int i = 0 ; i < d_size ; ){
		switch(j){
			case 1 :
			case 2 :
			case 4 :
			case 8 : ham[j] = 0 ; j ++ ; break ;
			default : 
				ham[j] = data[i] ;
				i ++ ;
				j ++ ;
		}
	}
	return j ;
}

void seqencer(int ham[],  int h_size, int increment){

	for(int i = increment ; i < h_size ; i += 2*increment ){
		for(int j = 0 ; j < increment ; j ++){
			ham[increment] = ham[increment] ^ ham[i+j];
		}
	}

}

void displayArray(int data[],int d_size){
	printf("\n");
	for(int i = 0 ; i < d_size ; i ++){
		printf("%d", data[i] );
	}
	printf("\n");
}

void main(){
	char buff[100];
	int d_size , h_size ;
	int data[100] , ham[100];

	printf("Enter Data Size : ");
	scanf("%d",&d_size);

	printf("Enter Data : ");
	scanf( "%s" , buff);

	convertInt(buff,d_size,data);
	displayArray(data,d_size);

	h_size = generateParity(data,d_size,ham);
	seqencer(ham,h_size,1);
	seqencer(ham,h_size,2);
	seqencer(ham,h_size,4);
	displayArray(ham,h_size);

	scanf("%d",&d_size);

}