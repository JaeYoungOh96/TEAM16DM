#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <cstdio>


using namespace std;

int main(int argc, char *argv[]) {
		char line[30];
		char *save = (char*)malloc(30 * sizeof(char));
		memset(save, -1, 30 * sizeof(char));
		int saveint;

		int* p = (int*)malloc(729*sizeof(int));
		memset(p, -1, 729*sizeof(int));

		int* input = (int*)malloc(81*sizeof(int));
		memset(input, -1, 81*sizeof(int));
		
		int* output = (int*)malloc(81*sizeof(int));
		memset(output, -1, 81*sizeof(int));

		ifstream inData;
		ofstream outData;


        int saveast[4];
        int nofast=0;
		int n0 = 0;

		inData.open("input.txt");	


		if(!inData.is_open()){
			printf("input.txt is not open!!!!!\n");

		}

		for (int i = 0; !inData.eof(); i++) {
			inData.getline(line, 20);
			save = strtok(line, " ");
			if (strcmp(save, "*") == 0)
				input[i * 9 + 0] = 42;
			else input[i * 9 + 0] = atoi(save);
			for (int j = 1; j < 9; j++) {
				save = strtok(NULL, " ");
				if (strcmp(save, "*") == 0)
					input[i * 9 + j] = 42;
				else input[i * 9 + j] = atoi(save);
			}
		}

        inData.close();

        for(int i = 0; i < 81; i ++) {
            if(input[i] == 42) {
                saveast[nofast++] = i;
                for(int j = 0; j < 9; j ++) {
                    p[i*9 + j] = 3;
                }
            }
			

            else if(input[i] != 0) {
                p[i*9 + input[i]-1] = 1;
            }
            if(input[i] == 0) {
               for(int j = 0; j < 9; j ++) {
                    p[i*9 + j] = 0;
                }
            }
        }


	for(int k = 0; k < 9*9*9; k ++) {
	
	if(p[k] == 1) {
		n0++; 
	}
	if(p[k] == -1) {
		n0++; 
	}

}

	



	outData.open("formula.txt");
	if (nofast > 2) {
		outData << "p cnf " << 729 << " " << 81+ 81+ 81+ n0 + 18*(nofast - 1) << endl;//448 8181//6075//18*(nast-1)
	}
	else
		outData << "p cnf " << 729 << " "<< 81+ 81+ 81+ 448 + n0 <<endl;//448 8181//6075//18*(nast-1)


	for(int i = 0; i < 9; i ++) {
		for(int n = 1; n <=9; n ++) {
			for(int j = 0; j < 9; j ++) {
				outData << i*81 + n + j*9 << " " ;
			}
		outData << 0 << endl;
				
		}
	}//row 81

	for(int j = 0; j < 9; j ++ ){
		for(int n = 1; n <= 9; n ++) {
			for(int i =0; i < 9; i ++) {
				outData << i*81 + n + j*9 << " " ;
			}
		outData << 0 << endl;
			
		}	
	}//columm 81 
	

	for(int i = 0; i < 9; i ++) {
		for(int j = 0; j < 9; j ++) {
			for(int n = 1; n <=8; n++) {
				for(int m = n+1; m <=9; m++) {
						outData << -(i*81 + j*9 + n) << " " ; 
						outData << -(i*81 + j*9 + m) << " " << 0 << endl; 
					
				
				
						outData << -(i*81 + j*9 + m) << " "; 
						outData << -(i*81 + j*9 + n) << " " << 0 <<endl; 
					
					
				}
			}
		}
	}//448

	

	for(int r = 0; r <3; r ++ ) {
		for(int s = 0; s <3; s++) {
			for(int n = 1; n <= 9; n ++) {
				for(int i = 0; i < 3; i ++) {
					for(int j = 0; j < 3; j ++) {
						outData << (i + 3*r)*81 + (j+3*s)*9 + n << " "; 
					}
				}
			outData << 0 << endl;	
			
			}	
		}
	}//81


for(int k = 0; k < 9*9*9; k ++) {
	
	if(p[k] == 1) {
		outData << k+1 << " " << 0 << endl; 
		
	}
	if(p[k] == -1) {
		outData << -(k+1) << " " << 0 <<endl; 
	}
}//n0



	if(nofast > 1) {
		for(int k = 0; k< nofast-1; k ++) {
			
			for(int n = 1; n <= 9; n ++) {
				outData << -(saveast[k]*9 + n) << " "; 
				outData << saveast[k+1]*9 + n << " " << 0 <<endl;
				outData << saveast[k]*9 + n << " "; 
				outData << -(saveast[k+1]*9 + n) << " " << 0 << endl;
			}
		}		
	}//18*(nofast-1)


	outData.close();


	system("C:\\Users\\jaeyo\\Desktop\\DM\\z3-4.3.2-x64-win\\bin\\z3 -dimacs formula.txt > z3output.txt");//please modify this line!!!
		
			
	inData.open("z3output.txt");

	outData.open("output.txt");


	if (!inData.is_open()) {
		printf("z3output is not open!!!\n");

		inData.close();
		outData.close();


		free(p);
		free(input);
		free(output);

		return 0;
	}


		int a = 0;

		int nout = 0;

		inData >> line;
		if (strncmp(line, "unsat", 5) == 0) {
			printf("It is a unset");
			outData << "It is a unset." << endl;

			inData.close();
			outData.close();
			free(p);
			free(input);
			free(output);
			return 0;
		}

		while (!inData.eof()) {
			inData >> line;
			saveint = atoi(line);
			if (saveint > 0) {
				nout = saveint % 81 % 9;
				if (nout == 0) {
					output[a++] = 9;
				}
				else
					output[a++] = nout;
			}
		}


		

		inData.close();



		for (int i = 0; i < 81; i++) {
			outData << output[i] << " ";
			if (i % 9 == 8)
				outData << endl;
		}


		outData.close();


		free(p);
		free(input);
		free(output);
		
		return 0;
}

		

