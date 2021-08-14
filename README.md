# YES_NO_DETECTION-Project
The main of the project is to recognize the word and say whether it is "YES" or "NO" using Acoustic and Phonetics approach.

STEPS: 

-> We are making use of Short Term Energy i.e STE and Zero Cross Rate i.e. ZCR.

-> First step is to correct DC Shift, by recording the audio while turning off the microphone and then taking avarage of all data and finally subtracting it from the sample data values.

-> Next step is normalising the data values to + and - 5000 by calculating the normalisation factor.

->Now, we calculate the Energy and zcr for each frame and write those into a separate file

->Since there might be a possibility of background noise, therefore calculating the threshold energy and threshold zcr of first 5 frames (this choice can depend person to person)

-> For marking the start and end of word we check if the energy of i,i+1,i+2 frames is more than 3 times the threshold energy of noise then we say that the word has started. If the energy of i,i+1,i+2 frames is less than 3 times the threshold energy of noise then we say that the word has ended.

-> After getting the word we will check whether the zcr value is high for more than or equal to 30% of the size then it is "YES" else it is "NO".

----------------------------------------------------------------------------------------------------------------------

FILES:

1. There is one header file "util.h" that contais all the utility function used while recognition. The main file (YES_NO_DETECTOR) contains the code to run the program.
2. Data.txt is the Sample data file used. It is divided into 8 files containing one word each.
3. dc_shift.txt is the file that stores the DC shift values obtained by recording audio without turning on microphone.

----------------------------------------------------------------------------------------------------------------------

Instruction to execute:

1. Simply open the project folder in Microsoft Visual Studio 2010.
2. Save the sample data in text format in the same folder(Project folder) in side the main file folder.
3. Replace the name of the sample data file in the starting of the code with your file name. 
4. Press Ctrl + F5 key to build and run the project.
5. You will get the result in Comman prompt.

-----------------------------------------------------------------------------------------------------------------------
