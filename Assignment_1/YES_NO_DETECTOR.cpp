// YES_NO_DETECTOR.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "stdio.h"
#include "ctype.h"
#include<stdlib.h>
#include "stdafx.h"
#include "stdio.h"
#include "ctype.h"
#include<stdlib.h>
#include "util.h"       //including header file of the used functions

int samples[1000000];

double threshold_E = 0, threshold_z = 0;

FILE *file_input, *file_output, *normalised;

int _tmain(int argc, _TCHAR* argv[])
{
	fopen_s(&file_input,"sample7.txt","r");
	fopen_s(&normalised,"Normalised_data.txt","a+");
	fopen_s(&file_output,"Energy_zcr.txt","a+");
	
	//Normalising the data by calling this function by correcting dc shift 
	// multiplying by normalisation factor
	normalisation(file_input,normalised);
	rewind(normalised);

	//Calling this function to get Energy and zcr 
	parameter(normalised,file_output);

	char frame[100],*st;

	//Reading parameter file and storing energy and zcr in array
	rewind(file_output);
	double energy[10000], zcr[10000];
	long word_start, word_end, frameCount = 0;
	bool flag = false;
	while(!feof(file_output)){
			fgets(frame, 100, file_output);
			energy[frameCount] = strtod(frame, &st);
			zcr[frameCount] = atof(st + 1);
			frameCount++;
		}
	
	//Calculating threshold energy and threshold zcr for first 5 frames
	for(int i=0;i<5;i++){
			threshold_E+=energy[i];
			threshold_z=zcr[i];
	}
	threshold_E/=5;
	threshold_z/=5;

	printf("Threshold Energy Value : %lf \nThreshold ZCR Value : %lf \n",threshold_E,threshold_z);

	//Finding Start and End Marker
	for(int i=0; i<frameCount-3; ++i){
			if(!flag && energy[i+1] > threshold_E * 3 && energy[i+2] > threshold_E *3 && energy[i+3] > threshold_E * 3){
					word_start = i;
					flag = true;
			}
			else if(flag && energy[i+1] <= threshold_E * 3 && energy[i+2] <= threshold_E * 3 && energy[i+3] <= threshold_E * 3){
				word_end = i;
				flag = false;
				break;
			}
		}

	//if end is not found then making the last frame - 3 as the end marker for the word
	if(flag) word_end = frameCount - 3;
	
	printf("Start of Frame : %d End of Frame : %d \n",word_start,word_end);
	printf("---------------------------------------\n\n");
	printf("RESULT : The word said is  %s \n\n",predict(energy,zcr,word_start,word_end));

	//Closing the currently opened file
	fclose(file_input);
	fclose(file_output);
	fclose(normalised);

	//removing the files that were created during the program 
	remove("Normalised_data.txt");
	remove("Energy_zcr.txt");

	return 0;
}

