#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cuda_runtime.h>

using namespace std;
//************************************************** Global variables ***********************************************//
int rows_matrix,rows_mask,columns_matrix = 0,columns_mask = 0;
float matrix_used[100000],mask_used[100];
int index_mat = 0;
int index_mask = 0;
//*************************************************** Function declarations ******************************************//
int get_input_matrix(string file_name);
int get_each_element(string array[],int array_length, string type);
void display();
//************************************************** Main Function *************************************************//
int main(int argc,char *argv[]) {
	string file_name = argv[1];
	get_input_matrix(file_name);
  	return 0;
}
//************************************************** Fucntion to get the input matrix in string format**************//
int get_input_matrix(string file_name){
	/*
		THIS FUNCTION READS FROM THE GIVEN TEXT FILES AND STORES EACH ROW OF A MATRIX AS AN ENTRY OF AN ARRAY OF TYPE STRING. THUS , THE NUMBER OF ENTRIES OF THE ARRAY GIVES THE NUMBER OF ROWS OF THE MATRIX

	*/
	string matrix[10000],mask[10];
	ifstream inputfile;
	int i =0,j=0;
	inputfile.open(file_name);

	if(!inputfile.is_open()) {
		exit(EXIT_FAILURE);
	}

	while(inputfile.good()) {
		getline(inputfile, matrix[i]);
		if(matrix[i].length() == 0) {
			goto label;		
		}
		cout << matrix[i] << endl;

		i++;
	}
	label:
	cout << endl;
	while(inputfile.good()) {
		getline(inputfile,mask[j]);
		cout << mask[j] << endl;
		j++;

	}
	rows_matrix = i;
	rows_mask = j;
	cout << endl;
	cout << "The number of rows are:  "<< rows_matrix << endl;
	cout << "The number of rows are:  "<< rows_mask << endl;

	get_each_element(matrix,rows_matrix,"matrix");
	get_each_element(mask,rows_mask,"mask");
	display();
	return 0;
}
//************************** Function to read the rows of the input matrices and extract each element ************//
int get_each_element(string array[],int array_length,string type){
	/*
		THIS FUNCTION TAKES THE OBTAINED STRING TYPE MATRIX AS THE INPUTS AND SEPARTAES EACH ELEMENT AND STORES IT IN AN ARRAY OF DOUBLE DOUBLE DEPENDING ON WHETHER IT IS THE MATRIX INPUT OR THE KERNAL MASK
	*/
		for(int ind = 0;ind < array_length; ind++){
		string temp = " ";
		for (int ind_1 = 0;ind_1 < array[ind].length(); ind_1++){
			
			if(array[ind][ind_1] != ' ') {
				temp += array[ind][ind_1];
				if(ind_1 == array[ind].length() - 1){
					if(type == "matrix"){
						matrix_used[index_mat] = atof(temp.c_str());
						index_mat++;
				    }
				    else {
				    	mask_used[index_mask] = atof(temp.c_str());
					    index_mask++;
				    }
					temp = " ";
					goto label_3;
				}
			}
			else if(array[ind][ind_1] == ' '){
				if(type == "matrix"){
					matrix_used[index_mat] = atof(temp.c_str());
					index_mat++;
				}
				else{
					mask_used[index_mask] = atof(temp.c_str());
					index_mask++;
				}
				temp = " ";
				goto label_2;
			}
			if(ind_1 == array[ind].length() - 1){
				if(type == "matrix"){
					matrix_used[index_mat] = atof(temp.c_str());
					index_mat++;
				}
				else{
					mask_used[index_mask] = atof(temp.c_str());
					index_mask++;
				}
				temp = " ";
				goto label_3;
			}
			label_2:;
		}
		label_3:;
		if(ind == 0) {
			if(type == "matrix"){
				columns_matrix = index_mat;
			}
			else{
				columns_mask = index_mask;
			}
		}
	}
  return 0;
}
//********************************************************* Function to display the result ********************************************//
void display(){
	/*
		THIS FUNCTION DISPLAYS THE RESULTS TO THE CONSOLE
	*/
	cout<<"Matrix is given below"<< endl;
	for(int k = 0;k<index_mat;k++){
		cout<< matrix_used[k] <<endl;
	}
	cout << endl;
	cout<<"Kernal matrix is shown below:"<< endl;
	for(int l =0;l<index_mask;l++){
		cout << mask_used[l] << endl;
	}
	cout <<"The number of rows of matrix =  "<<rows_matrix<<endl;
	cout<<"The number of columns of matrix =  "<<columns_matrix<<endl;
	cout <<"The number of rows of mask =  "<<rows_mask<<endl;
	cout<<"The number of columns of mask =  "<<columns_mask<<endl;
}