// util.h : include file for project specific files
//that are used frequently, but are changed infrequently
#include "stdafx.h"
#include "stdio.h"
#include "ctype.h"
#include<stdlib.h>
#include<math.h>

void parameter(FILE *file_input,FILE *file_output){

	//This function is calculating the Energy and zcr for Sample Data
	char frame[100];
	double energy=0,zcr=0,prev_x=0,count=0;
	double x=0;
	while(!feof(file_input)){
		fgets(frame,100,file_input);
		if(!isalpha(frame[0])){				//using isalpha function to skip alphabets i.e. header information.
			x=atof(frame);	 
			if(count==100){
				fprintf(file_output,"%lf %f\n",(energy/100.0),zcr);
				energy=0;
				zcr=0;
				count=0;
				}
			energy+=x*x;					//Energy is sum of squares of data values divided by number of sample data.
			zcr+=prev_x*x<0;				// ZCR is the number of time x changes from +ve to -ve and vice versa.
			count++;
			prev_x=x;	 
			}
	
		}
}

char* predict(double *energy,double *zcr, long start,long end){
		
	//This function will check whether is YES or NO and return string
	double fricatives = 0;
	for(int i=start; i<=end-1; ++i){
		if(zcr[i] > 15 && zcr[i+1] > 15)
			fricatives ++;
	}

	//Logic: if fricative's count is more than 30% of word then it is YES else NO

	double count_frames = end - start + 1;
	if(fricatives >= count_frames * 0.3)
		return "YES";
	else
		return "NO";


}

double DC_shift(FILE *file_input){

	//Calculating DC shift 
	char ch;
	char arr[10];
	ch=fgetc(file_input);
	int index=0;
	double dcshift=0;
	double sample_count=0;
	while(!feof(file_input)){

		while(ch!='\n'){
			arr[index++]=ch;			
			ch=fgetc(file_input);	
		}

		arr[index]='\0';
		sample_count++;
		dcshift+=atoi(arr);
		index=0;
		ch=fgetc(file_input);	
	}
	
	dcshift/=sample_count*1.0;        //Calculation DC shift is done as:  summation of dc shift values divided by number of samples.
	
	printf("DC Shift : %lf \n",dcshift);
	return dcshift;

}

double normalisation_factor(FILE *file_input){
		
	//Calculating Normalization factor taking limit as + and - 5000
	char ch;
	int num=0;
	char arr[10];
	double max=0;
	ch=fgetc(file_input);
	int index=0;
	double factor=0;
	rewind(file_input);
	while(!feof(file_input)){
		while(isalpha(ch)){             //ignoring the header information in sample data, 
			while(ch!='\n'){			//This can be skipped by saving data without header information also.
			ch=fgetc(file_input);
			}
			ch=fgetc(file_input);
		}
		while(ch!='\n' ){
			arr[index++]=ch;
			ch=fgetc(file_input);	
		}
		arr[index]='\0';				//reading characters and storing in array then converting it to integer
		num=abs(atoi(arr));
		if(max<num)
			max=num;
		index=0;
		ch=fgetc(file_input);
		
	}
	factor=(max-5000.0)/(max*1.0);					//Calculation of normalisation factor using maximum absolute amplitude
	printf("Maximum Amplitude : %lf \n",max);
	printf("Normalisation Factor : %lf \n",factor);
	printf("---------------------------------------\n");
	return factor;
	
}

void normalisation(FILE *file_input,FILE *file_output){

	FILE * input;
	fopen_s(&input,"dc_shift.txt","r");
	double dcshift=DC_shift(input);
	fclose(input);
	double factor=normalisation_factor(file_input);

	//Normalising the  given data by subtracting DC shift and multipying normalisation factor
	
		
	char ch;
	double num=0;
	char arr[1024];
	ch=fgetc(file_input);
	int index=0;
	rewind(file_input);
	ch=fgetc(file_input);	
	while(!feof(file_input)){
		while(isalpha(ch)){							//ignoring the header information in sample data, 
			while(ch!='\n'){						//This can be skipped by saving data without header information also.
			ch=fgetc(file_input);
			}
			ch=fgetc(file_input);
		}
		while(ch!='\n' ){
			arr[index++]=ch;
			ch=fgetc(file_input);	
		}
		arr[index++]='\0';
		num=atof(arr);
		index=0;
		num=(num-dcshift)*factor;       //Correcting dc shift by subtracting it with each sample data and normalising it to +/-5000.
		if(abs(num)>1){ 		
		fprintf(file_output,"%lf\n",num);  
		}
		ch=fgetc(file_input);
		
	}
	
}



	
	