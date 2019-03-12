#include <iostream>  
#include <algorithm>     
#include <iterator>
#include <deque>          
#include <list>  
#include <queue> 
#include <fstream>
#include <stdio.h>    
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <string.h>
#include <cmath>
#include <stack>
#include <locale>
#include <sstream>
#include <map>
using namespace std;

//vector<String> s;

int MAX_X = 8;
int MAX_Y = 7;
int maxDepth =5;
string legalMoves[100];
char BOARD[8][7];
map<string, vector<string> > legalMc;
map<string, vector<string> > legalMh;
//char BOARD[MAX_X][MAX_Y];
string toString(int );
string toString(char );
string inputF();
void generateLegal( );
void iPopulate();
void move( string, string);
void moveBack( string, string,char,char);
int toInt(string);
void MinMax();
int min( int ,int, int);
int max(int,int,int );
int evaluate();
int checkWin();
void print();
void printLegal();

int main(int argc, char *argv[]) {

	// char BOARD[MAX_X][7];
	string humanMove = "       ", s1,s2;
	int len, len1, len2,first;
	vector<string> temp;
	char *conv1,*conv2;
	map<string, vector<string> >::iterator it;
	vector<string>::iterator it2;

	for (int x = 0; x < MAX_X; x++)
	{
	 	for (int y = 0; y < MAX_Y; y++)
	      BOARD[x][y] = '-';
 	}
 	cout<< "Please enter 1 for you going first";
 	cin>>first;
	iPopulate ();
	if(first == 1){
		while(humanMove.compare("x")){
			generateLegal ();
			print ();
			// for (int y = 0; y < 20 ; y++)
		 //    	cout<< legalMoves[y]<<endl;
			printLegal();
			humanMove = inputF();
			if(humanMove.compare("x") != 0){
		        s1 = humanMove.substr(0, humanMove.length()/2);
		    	s2 = humanMove.substr(humanMove.length()/2);
		    	transform(s1.begin(), s1.end(),s1.begin(), ::toupper);
		    	transform(s2.begin(), s2.end(),s2.begin(), ::toupper);
		    	conv1 = new char[s1.length()];
		    	conv2 = new char[s2.length()];
		    	for (int index = 0; index < s1.length(); index++){
		    		conv1[index] = s1[index];
				}
				conv1[s1.length()] = '\0';
				for (int index = 0; index < s2.length(); index++){
		    		conv2[index] = s2[index];
				}
				conv2[s2.length()] = '\0';
				conv1[1]=conv1[1]-17;
				conv1[0]=(56-conv1[0])+48;
				conv2[1]=conv2[1]-17;
				conv2[0]=(56-conv2[0])+48;


				cout<< conv1[0]<<conv1[1]<< conv2[0]<<conv2[1] <<endl;

				s1 = conv1;
				s2 = conv2;

				cout<<"back to string "<<s1<<s2<<endl;

		    	it = legalMh.find(s1);
		    	if(it != legalMh.end()){
		    		temp = (*it).second;
		    		it2 = find(temp.begin(),temp.end(),s2);
		    		if(it2 != temp.end()){
		    			cout<< "move to "<<*it2<<endl;
		    			move ( s1, s2);
		    			MinMax( );
		    		}
		    		else{
		    			cout<< "Illegal move..."<<endl;
		    		}
		    		

		    	}
		    	else{
		    		cout<< "Move not found."<<endl;
		    	}
	    	}
	    }
	   }
	   else{
	    	MinMax( );
	    	while(humanMove.compare("x")){
				generateLegal ();
				print ();
				// for (int y = 0; y < 20 ; y++)
			 //    	cout<< legalMoves[y]<<endl;
				printLegal();
				humanMove = inputF();
				if(humanMove.compare("x") != 0){
			        s1 = humanMove.substr(0, humanMove.length()/2);
			    	s2 = humanMove.substr(humanMove.length()/2);
			    	transform(s1.begin(), s1.end(),s1.begin(), ::toupper);
			    	transform(s2.begin(), s2.end(),s2.begin(), ::toupper);
			    	conv1 = new char[s1.length()];
			    	conv2 = new char[s2.length()];
			    	for (int index = 0; index < s1.length(); index++){
			    		conv1[index] = s1[index];
					}
					conv1[s1.length()] = '\0';
					for (int index = 0; index < s2.length(); index++){
			    		conv2[index] = s2[index];
					}
					conv2[s2.length()] = '\0';
					conv1[1]=conv1[1]-17;
					conv1[0]=(56-conv1[0])+48;
					conv2[1]=conv2[1]-17;
					conv2[0]=(56-conv2[0])+48;


					cout<< conv1[0]<<conv1[1]<< conv2[0]<<conv2[1] <<endl;

					s1 = conv1;
					s2 = conv2;

					cout<<"back to string "<<s1<<s2<<endl;

			    	it = legalMh.find(s1);
			    	if(it != legalMh.end()){
			    		temp = (*it).second;
			    		it2 = find(temp.begin(),temp.end(),s2);
			    		if(it2 != temp.end()){
			    			cout<< "move to "<<*it2<<endl;
			    			move ( s1, s2);
			    			MinMax( );
			    		}
			    		else{
			    			cout<< "Illegal move..."<<endl;
			    		}
			    		

			    	}
			    	else{
			    		cout<< "Move not found."<<endl;
			    	}
		    	}
	    	}
		// len = strlen(humanMove);
		// len1 = len/2;
		// len2 = len - len1;
		// s1 = (string)malloc(len1+1);
		// memcpy(s1, humanMove, len1);
		// s1[len1] = '\0';
		// s2 = (string)malloc(len2+1);
		// memcpy(s2, humanMove+len1, len2);
		// s2[len2] = '\0';
		// cout<<*s1 << " BBB "<<*s2;
	}
}


string inputF(){
	string k;
	cout<<endl<<"Enter your move: ";
	cin>>k;
	return k;
}

void move( string s1, string s2){
	int c1 = toInt(s1),c2 = toInt(s2);
	char temp;
	temp = BOARD[c1/10][c1%10];
 	BOARD[c1/10][c1%10] = '-';
 	BOARD[c2/10][c2%10]=temp;
}

void moveBack( string s1, string s2, char k, char k2){
	int c1 = toInt(s1),c2 = toInt(s2);
	char temp;
 	BOARD[c1/10][c1%10] = k2;
 	BOARD[c2/10][c2%10]=k;
}

void print(){
	for (int x = 0; x < MAX_X; x++)
		{
			// cout<< MAX_X - x<< " ";
			cout<<8-x<< " ";
			for (int y = 0; y < MAX_Y; y++){
	    		cout << BOARD[x][y]<< " ";
	    		if(x == 0 && y == MAX_Y -1)
	    			cout<<" Computer";
	    		if(x == MAX_X-1 && y == MAX_Y -1)
	    			cout<<" Human";
			}
	    	cout<<endl;

		}
		cout<< "  ";
		for (int y = 0; y < MAX_Y; y++){
	    	cout << char(65 +y)<<" ";
	    	//cout<< y<< " ";
		}
		cout<<endl;
}

void printLegal(){
	cout<<"PC legal moves: "<<endl;
		for( map<string, vector<string> >::iterator iter = legalMc.begin(); iter != legalMc.end(); ++iter ) {
			vector<string> temp = (*iter).second;
   			string key = (*iter).first;
   			cout << key << " key";
   			for (unsigned i = 0; i < temp.size(); i++) {
      			cout << " " << temp[i];
   			}
   			cout << endl;
		}
		cout<<"Human legal moves: "<<endl;
		for( map<string, vector<string> >::iterator iter = legalMh.begin(); iter != legalMh.end(); ++iter ) {
			vector<string> temp = (*iter).second;
   			string key = (*iter).first;
   			cout << key << " key";
   			for (unsigned i = 0; i < temp.size(); i++) {
      			cout << " " << temp[i];
   			}
   			cout << endl;
		}
}

void iPopulate(){
 BOARD[0][0] = 'C';
 BOARD[1][1] = 'P';
 BOARD[2][0] = 'R';
 BOARD[2][1] = 'R';
 BOARD[2][2] = 'P';
 BOARD[2][3] = 'B';
 BOARD[2][4] = 'B';
 BOARD[3][0] = 'N';
 BOARD[3][1] = 'N';
 BOARD[3][3] = 'P';
 BOARD[3][4] = 'P';
 BOARD[3][5] = 'P';
 BOARD[3][6] = 'P';

 BOARD[7][0] = 'c';
 BOARD[6][1] = 'p';
 BOARD[5][0] = 'r';
 BOARD[5][1] = 'r';
 BOARD[5][2] = 'p';
 BOARD[5][3] = 'b';
 BOARD[5][4] = 'b';
 BOARD[4][0] = 'n';
 BOARD[4][1] = 'n';
 BOARD[4][3] = 'p';
 BOARD[4][4] = 'p';
 BOARD[4][5] = 'p';
 BOARD[4][6] = 'p';


}

void generateLegal(){
	int moves = 0,loc=0;
	vector<string> m;
	map<string, vector<string> > s;
	map<string, vector<string> > k;
	legalMh.swap( s );
	legalMc.swap( k );
	legalMh.clear();
	legalMc.clear();
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++){
			// cout << "X: " << x << ", " << "Y: " << y << endl;
			if(x<MAX_X && y<MAX_Y){
			if (BOARD[x][y] =='P'){
				if (BOARD[x+1][y] =='-'){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y);
					legalMc[toString(x) + toString(y)].push_back(toString(x+1) + toString(y));
					//cout<< legalMoves[moves]<<endl;
				}
				if (y+1<MAX_Y && x+1<MAX_X && BOARD[x+1][y+1] !='-' && BOARD[x+1][y+1] !='P' && BOARD[x+1][y+1] !='B' & BOARD[x+1][y+1] !='N' && 
				 BOARD[x+1][y+1] !='R' && BOARD[x+1][y+1] !='C' && BOARD[x+1][y+1] !='c'){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y+1);
					legalMc[toString(x) + toString(y)].push_back(toString(x+1) + toString(y+1));
					//cout<< legalMoves[moves]<<endl;
				}
				if (x+1<MAX_X && y>0 && BOARD[x+1][y-1] !='-' && BOARD[x+1][y-1] !='P' && BOARD[x+1][y-1] !='B' & BOARD[x+1][y-1] !='N' && 
				 BOARD[x+1][y-1] !='R' && BOARD[x+1][y-1] !='C'&& BOARD[x+1][y-1] !='c'){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y-1);
					legalMc[toString(x) + toString(y)].push_back(toString(x+1) + toString(y-1));
					//cout<< legalMoves[moves]<<endl;
				}
			}








			if (BOARD[x][y] =='p'){
				if (BOARD[x-1][y] =='-'){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x-1) + toString(y);
					//cout<< legalMoves[moves]<<endl;
					legalMh[toString(x) + toString(y)].push_back(toString(x-1) + toString(y));

					moves++;
				}
				if (x>0 && y<MAX_Y && BOARD[x-1][y+1] !='-' && BOARD[x-1][y+1] !='p' && BOARD[x-1][y+1] !='b' & BOARD[x-1][y+1] !='n' && 
				 BOARD[x-1][y+1] !='r' && BOARD[x-1][y+1] !='c'&& BOARD[x-1][y+1] !='C'){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x-1) + toString(y+1);
					legalMh[toString(x) + toString(y)].push_back(toString(x-1) + toString(y+1));

					//cout<< legalMoves[moves]<<endl;
				}
				if (x>0 && y>0 && BOARD[x-1][y-1] !='-' && BOARD[x-1][y-1] !='p' && BOARD[x-1][y-1] !='b' & BOARD[x-1][y-1] !='n' && 
				 BOARD[x-1][y-1] !='r' && BOARD[x-1][y-1] !='c'&& BOARD[x-1][y-1] !='C'){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x-1) + toString(y-1);
					legalMh[toString(x) + toString(y)].push_back(toString(x-1) + toString(y-1));

					//cout<< legalMoves[moves]<<endl;
				}
			}

			
			if (BOARD[x][y] =='N'){

				if(y-2>=0 && x+1<MAX_X && BOARD[x+1][y-2] =='-' ){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y);
					legalMc[toString(x) + toString(y)].push_back(toString(x-1) + toString(y-2));
					//cout<< legalMoves[moves]<<endl;
				}
				if(y+2<MAX_Y && x+1<MAX_X && BOARD[x+1][y+2] =='-' ){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y);
					legalMc[toString(x) + toString(y)].push_back(toString(x-1) + toString(y+2));
					//cout<< legalMoves[moves]<<endl;
				}
				if(x+2<MAX_X && y-1>=0 && BOARD[x+2][y-1] =='-' ){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y);
					legalMc[toString(x) + toString(y)].push_back(toString(x-2) + toString(y-1));
					//cout<< legalMoves[moves]<<endl;
				}
				if(x+2<MAX_X && y+1<MAX_Y && BOARD[x+2][y+1] =='-' ){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y);
					legalMc[toString(x) + toString(y)].push_back(toString(x-2) + toString(y+1));
					//cout<< legalMoves[moves]<<endl;
				}
				
				if(y+2<MAX_Y && x+1<MAX_X && BOARD[x+1][y+2] !='-' && BOARD[x+1][y+2] !='P' && BOARD[x+1][y+2] !='B' & BOARD[x+1][y+2] !='N' && 
				 BOARD[x+1][y+2] !='R'&& BOARD[x+1][y+2] !='c'&& BOARD[x+1][y+2] !='C' ){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y+1);
					legalMc[toString(x) + toString(y)].push_back(toString(x+1) + toString(y+2));
					//cout<< legalMoves[moves]<<endl;
				}
				if(y+1<MAX_Y && x+2<MAX_X & BOARD[x+2][y+1] !='-' && BOARD[x+2][y+1] !='P' && BOARD[x+2][y+1] !='B' & BOARD[x+2][y+1] !='N' && 
				 BOARD[x+2][y+1] !='R'&& BOARD[x+2][y+1] !='c'&& BOARD[x+2][y+1]!='C') {
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y+1);
					legalMc[toString(x) + toString(y)].push_back(toString(x+2) + toString(y+1));
					//cout<< legalMoves[moves]<<endl;
				}


				if(y-2>=0 && x+1<MAX_X && BOARD[x+1][y-2] !='-' && BOARD[x+1][y-2] !='P' && BOARD[x+1][y-2] !='B' & BOARD[x+1][y-2] !='N' && 
				 BOARD[x+1][y-2] !='R'&& BOARD[x+1][y-2] !='c'&& BOARD[x+1][y-2]!='C' ){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y+1);
					legalMc[toString(x) + toString(y)].push_back(toString(x+1) + toString(y-2));
					//cout<< legalMoves[moves]<<endl;
				}


				if(y-2>=0 && x-1>=0 && BOARD[x-1][y-2] !='-' && BOARD[x-1][y-2] !='P' && BOARD[x-1][y-2] !='B' & BOARD[x-1][y-2] !='N' && 
				 BOARD[x-1][y-2] !='R' && BOARD[x-1][y-2] !='c'&& BOARD[x-1][y-2]!='C' && y-2>=0 && x-1>=0){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y+1);
					legalMc[toString(x) + toString(y)].push_back(toString(x-1) + toString(y-2));
					//cout<< legalMoves[moves]<<endl;
				}
				if(y-1>=0 && (x-2)>=0 && BOARD[x-2][y-1] !='-' && BOARD[x-2][y-1] !='P' && BOARD[x-2][y-1] !='B' & BOARD[x-2][y-1] !='N' && 
				 BOARD[x-2][y-1] !='R' && BOARD[x-2][y-1] !='c'&& BOARD[x-2][y-1]!='C' && y-1>=0 && (x-2)>=0){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y+1);
					legalMc[toString(x) + toString(y)].push_back(toString(x-2) + toString(y-1));
					//cout<< legalMoves[moves]<<endl;
				}


				if(x-2>=0 && y+1<MAX_Y && BOARD[x-2][y+1] !='-' && BOARD[x-2][y+1] !='P' && BOARD[x-2][y+1] !='B' & BOARD[x-2][y+1] !='N' && 
				 BOARD[x-2][y+1] !='R'&& BOARD[x-2][y+1] !='c'&& BOARD[x-2][y+1]!='C' ){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y+1);
					legalMc[toString(x) + toString(y)].push_back(toString(x-2) + toString(y+1));
					//cout<< legalMoves[moves]<<endl;
				}



				if(x+2<MAX_X && y-1>=0 & BOARD[x+2][y-1] !='-' && BOARD[x+2][y-1] !='P' && BOARD[x+2][y-1] !='B' & BOARD[x+2][y-1] !='N' && 
				 BOARD[x+2][y-1] !='R' && BOARD[x+2][y-1] !='c'&& BOARD[x+2][y-1]!='C' ){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y+1);
					legalMc[toString(x) + toString(y)].push_back(toString(x+2) + toString(y-1));
					//cout<< legalMoves[moves]<<endl;
				}

				if(y+2<MAX_Y && x-1>=0 && BOARD[x-1][y+2] !='-' && BOARD[x-1][y+2] !='P' && BOARD[x-1][y+2] !='B' & BOARD[x-1][y+2] !='N' && 
				 BOARD[x-1][y+2] !='R' && BOARD[x-1][y+2] !='c'&& BOARD[x-1][y+2] !='C' ){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y+1);
					legalMc[toString(x) + toString(y)].push_back(toString(x-1) + toString(y+2));
					//cout<< legalMoves[moves]<<endl;
				}

	
			}









			if (BOARD[x][y] =='n'){

				if(y-2>=0 && x-1>=0 && BOARD[x-1][y-2] =='-' ){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y);
					legalMh[toString(x) + toString(y)].push_back(toString(x-1) + toString(y-2));
					//cout<< legalMoves[moves]<<endl;
				}
				if( y+2<MAX_Y && x-1>=0 && BOARD[x-1][y+2] =='-' ){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y);
					legalMh[toString(x) + toString(y)].push_back(toString(x-1) + toString(y+2));
					//cout<< legalMoves[moves]<<endl;
				}
				if(x-2>=0 && y-1>=0 && BOARD[x-2][y-1] =='-' ){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y);
					legalMh[toString(x) + toString(y)].push_back(toString(x-2) + toString(y-1));
					//cout<< legalMoves[moves]<<endl;
				}
				if(x-2>=0 && y+1<MAX_Y & BOARD[x-2][y+1] =='-' ){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y);
					legalMh[toString(x) + toString(y)].push_back(toString(x-2) + toString(y+1));
					//cout<< legalMoves[moves]<<endl;
				}
				
				if(y+2<MAX_Y && x+1<MAX_X && BOARD[x+1][y+2] !='-' && BOARD[x+1][y+2] !='p' && BOARD[x+1][y+2] !='b' & BOARD[x+1][y+2] !='n' && 
				 BOARD[x+1][y+2] !='r' && BOARD[x+1][y+2] !='c'&& BOARD[x+1][y+2] !='C' ){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y+1);
					legalMh[toString(x) + toString(y)].push_back(toString(x+1) + toString(y+2));
					//cout<< legalMoves[moves]<<endl;
				}
				if( y+1<MAX_Y && x+2<MAX_X && BOARD[x+2][y+1] !='-' && BOARD[x+2][y+1] !='p' && BOARD[x+2][y+1] !='b' & BOARD[x+2][y+1] !='n' && 
				 BOARD[x+2][y+1] !='r' && BOARD[x+2][y+1] !='c' && BOARD[x+2][y+1] !='c'){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y+1);
					legalMh[toString(x) + toString(y)].push_back(toString(x+2) + toString(y+1));
					//cout<< legalMoves[moves]<<endl;
				}


				if(y-1>=0 && x-2>=0 && BOARD[x-2][y-1] !='-' && BOARD[x-2][y-1] !='p' && BOARD[x-2][y-1] !='b' & BOARD[x-2][y-1] !='n' && 
				 BOARD[x-2][y-1] !='r' && BOARD[x-2][y-1] !='c'&& BOARD[x-2][y-1] !='C' ){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y+1);
					legalMh[toString(x) + toString(y)].push_back(toString(x-2) + toString(y-1));
					//cout<< legalMoves[moves]<<endl;
				}


				if(x-2>=0 && y+1<MAX_Y && BOARD[x-2][y+1] !='-' && BOARD[x-2][y+1] !='p' && BOARD[x-2][y+1] !='b' & BOARD[x-2][y+1] !='n' && 
				 BOARD[x-2][y+1] !='r' && BOARD[x-2][y-1] !='c' && BOARD[x-2][y-1] !='C' ){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y+1);
					legalMh[toString(x) + toString(y)].push_back(toString(x-2) + toString(y+1));
					//cout<< legalMoves[moves]<<endl;
				}
				if( y-2>=0 && x+1<MAX_X && BOARD[x+1][y-2] !='-' && BOARD[x+1][y-2] !='p' && BOARD[x+1][y-2] !='b' & BOARD[x+1][y-2] !='n' && 
				 BOARD[x+1][y-2] !='r' && BOARD[x+1][y-2] !='c' ){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y+1);
					legalMh[toString(x) + toString(y)].push_back(toString(x+1) + toString(y-2));
					//cout<< legalMoves[moves]<<endl;
				}


				if(x-1>=0 && y-2>=0 & BOARD[x-1][y-2] !='-' && BOARD[x-1][y-2] !='p' && BOARD[x-1][y-2] !='b' & BOARD[x-1][y-2] !='n' && 
				 BOARD[x-1][y-2] !='r' && BOARD[x-1][y-2] !='c' && BOARD[x-1][y-2] !='C'){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y+1);
					legalMh[toString(x) + toString(y)].push_back(toString(x-1) + toString(y-2));
					//cout<< legalMoves[moves]<<endl;
				}


				if(x+2<MAX_X && y-1>=0 && BOARD[x+2][y-1] !='-' && BOARD[x+2][y-1] !='p' && BOARD[x+2][y-1] !='b' & BOARD[x+2][y-1] !='n' && 
				 BOARD[x+2][y-1] !='r' && BOARD[x+2][y-1] !='c' && BOARD[x+2][y-1] !='C'){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y+1);
					legalMh[toString(x) + toString(y)].push_back(toString(x+2) + toString(y-1));
					//cout<< legalMoves[moves]<<endl;
				}

				if(y+2<MAX_Y && x-1>=0 && BOARD[x-1][y+2] !='-' && BOARD[x-1][y+2] !='p' && BOARD[x-1][y+2] !='b' & BOARD[x-1][y+2] !='n' && 
				 BOARD[x-1][y+2] !='r' && BOARD[x-1][y+2] !='c' && BOARD[x-1][y+2] !='C'){
					moves++;
					// legalMoves[moves] = toString(x) + toString(y) +toString(x+1) + toString(y+1);
					legalMh[toString(x) + toString(y)].push_back(toString(x-1) + toString(y+2));
					//cout<< legalMoves[moves]<<endl;
				}
			}








			if (BOARD[x][y] == 'R'){
				
				for(int i =x+1;i<MAX_X;i++){
					if (BOARD[i][y]!='-' && BOARD[i][y] !='P' && BOARD[i][y] !='B' & BOARD[i][y] !='N' && 
				 BOARD[i][y] !='R' && BOARD[i][y] !='C' && BOARD[i][y] !='c'){
						moves++;
						// legalMoves[moves] = toString(x) + toString(y) +toString(i) + toString(y);
						legalMc[toString(x) + toString(y)].push_back(toString(i) + toString(y));

						break;
					}else if (BOARD[i][y]!='-') break;
					else{
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(i) + toString(y);
						legalMc[toString(x) + toString(y)].push_back(toString(i) + toString(y));

					}
				}				
				for(int i =y+1;i<MAX_Y;i++){
					if (BOARD[x][i]!='-' && BOARD[x][i] !='P' && BOARD[x][i] !='B' & BOARD[x][i] !='N' && 
				 BOARD[x][i] !='R' && BOARD[x][i] !='C'&& BOARD[x][i] !='c'){
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(x) + toString(y);
						legalMc[toString(x) + toString(y)].push_back(toString(x) + toString(y));
						break;
					}
				}
				for(int i =y-1;i>=0;i--){
					if( BOARD[x][i]!='-' && BOARD[x][i] !='P' && BOARD[x][i] !='B' & BOARD[x][i] !='N' && 
				 BOARD[x][i] !='R' && BOARD[x][i] !='C'&& BOARD[x][i] !='c'){
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(x) + toString(y);
						legalMc[toString(x) + toString(y)].push_back(toString(x) + toString(y));
						break;
					}
				}
				for(int i =x-1;i>=0;i--){
					if (BOARD[i][y]!='-' && BOARD[i][y] !='P' && BOARD[i][y] !='B' & BOARD[i][y] !='N' && 
				 BOARD[i][y] !='R' && BOARD[i][y] !='C'&& BOARD[i][y] !='c'){
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(i) + toString(y);
						legalMc[toString(x) + toString(y)].push_back(toString(i) + toString(y));
						break;
					}
				}
			}






			if( BOARD[x][y] == 'r'){
				
				for(int i =x+1;i<MAX_X;i++){
					if (BOARD[i][y] !='-' && BOARD[i][y] !='p' && BOARD[i][y] !='b' & BOARD[i][y] !='n' && 
				 BOARD[i][y] !='r' && BOARD[i][y] !='c'&& BOARD[i][y] !='C'){
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(i) + toString(y);
						legalMh[toString(x) + toString(y)].push_back(toString(i) + toString(y));
						break;
					}
				}				
				for(int i =y+1;i<MAX_Y;i++){
					if (BOARD[x][i] !='-' && BOARD[x][i] !='p' && BOARD[x][i] !='b' & BOARD[x][i] !='n' && 
				 BOARD[x][i] !='r' && BOARD[x][i] !='c'&& BOARD[x][i] !='C'){
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(x) + toString(y);
						legalMh[toString(x) + toString(y)].push_back(toString(x) + toString(i));
						break;
					}
				}
				for(int i =y-1;i>=0;i--){
					if (BOARD[x][i] !='-' && BOARD[x][i] !='p' && BOARD[x][i] !='b' & BOARD[x][i] !='n' && 
				 BOARD[x][i] !='r' && BOARD[x][i] !='c'&& BOARD[x][i] !='C'){
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(x) + toString(y);
						legalMh[toString(x) + toString(y)].push_back(toString(x) + toString(i));
						break;
					}
				}
				for(int i =x-1;i>=0;i--){
					if (BOARD[i][y]!='-' && BOARD[i][y] !='p' && BOARD[i][y] !='b' & BOARD[i][y] !='n' && 
				 BOARD[i][y] !='r' && BOARD[i][y] !='c'&& BOARD[i][y] !='C'){
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(i) + toString(y);
						legalMh[toString(x) + toString(y)].push_back(toString(i) + toString(y));
						break;
					}else if (BOARD[i][y]!='-'){ break;}
					else{
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(i) + toString(y);
						legalMh[toString(x) + toString(y)].push_back(toString(i) + toString(y));
					}
				}
			}






			if (BOARD[x][y] == 'B'){
				loc = y;
				for(int i =x+1;i<MAX_X;i++){
					if(loc<MAX_Y-1){
						loc++;
					if (BOARD[i][loc]!='-' && BOARD[i][loc] !='P' && BOARD[i][loc] !='B' & BOARD[i][loc] !='N' && 
				 BOARD[i][loc] !='R' && BOARD[i][loc] !='C' && BOARD[i][loc] !='c'){
						moves++;
						// legalMoves[moves] = toString(x) + toString(y) +toString(i) + toString(y);
						legalMc[toString(x) + toString(y)].push_back(toString(i) + toString(loc));

						break;
					}else if (BOARD[i][loc]!='-') break;
					else{
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(i) + toString(y);
						legalMc[toString(x) + toString(y)].push_back(toString(i) + toString(loc));

					}
				}
				}			
				loc = x;	
				for(int i =y+1;i<MAX_Y;i++){
					if(loc>0){
						loc--;
					if (BOARD[loc][i] !='-' && BOARD[loc][i] !='P' && BOARD[loc][i] !='B' & BOARD[loc][i] !='N' && 
				 BOARD[loc][i] !='R' && BOARD[loc][i] !='C'&& BOARD[loc][i] !='c'){
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(x) + toString(y);
						legalMc[toString(x) + toString(y)].push_back(toString(loc) + toString(i));
						break;
					}
				}
				}
				loc = x;
				for(int i =y-1;i>=0;i--){
					if(loc<MAX_X-1){
						loc++;
					if (BOARD[loc][i]!='-' && BOARD[loc][i] !='P' && BOARD[loc][i] !='B' & BOARD[loc][i] !='N' && 
				 BOARD[loc][i] !='R' && BOARD[loc][i] !='C'&& BOARD[loc][i] !='c'){
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(x) + toString(y);
						legalMc[toString(x) + toString(y)].push_back(toString(loc) + toString(i));
						break;
					}else if (BOARD[loc][i]!='-'){break;}
					else{
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(x) + toString(i);
						legalMc[toString(x) + toString(y)].push_back(toString(loc) + toString(i));
					}
				}
				}
				loc=y;
				for(int i =x-1;i>=0;i--){
					if(loc>0){
						loc--;
					if (BOARD[i][loc] !='-' && BOARD[i][loc] !='P' && BOARD[i][loc] !='B' & BOARD[i][loc] !='N' && 
				 BOARD[i][loc] !='R' && BOARD[i][loc] !='C'&& BOARD[i][loc] !='c'){
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(i) + toString(y);
						legalMc[toString(x) + toString(y)].push_back(toString(i) + toString(loc));
						break;
					}
				}
				}
			}

			if (BOARD[x][y] == 'b'){
				loc = y;
				for(int i =x+1;i<MAX_X;i++){
					if(loc<MAX_Y-1){
						loc++;
					if (BOARD[i][loc] !='-' && BOARD[i][loc] !='p' && BOARD[i][loc] !='b' & BOARD[i][loc] !='n' && 
				 BOARD[i][loc] !='r' && BOARD[i][loc] !='c'&& BOARD[i][loc] !='C'){
						moves++;
						// legalMoves[moves] = toString(x) + toString(y) +toString(i) + toString(y);
						legalMh[toString(x) + toString(y)].push_back(toString(i) + toString(loc));

						break;
					}
					}
				}			
				loc = x;	
				for(int i =y+1;i<MAX_Y;i++){
					if(loc>0){
						loc--;
					if (BOARD[loc][i]!='-' && BOARD[loc][i] !='p' && BOARD[loc][i] !='b' & BOARD[loc][i] !='n' && 
				 BOARD[loc][i] !='r' && BOARD[loc][i] !='c'&& BOARD[loc][i] !='C'){
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(x) + toString(y);
						legalMh[toString(x) + toString(y)].push_back(toString(loc) + toString(i));
						break;
					}else if (BOARD[loc][i]!='-') break;
					else{
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(x) + toString(i);
						legalMh[toString(x) + toString(y)].push_back(toString(loc) + toString(i));
					}
				}
				}
				loc = x;
				for(int i =y-1;i>=0;i--){
					if(loc<MAX_X-1){
						loc++;
						if (BOARD[loc][i] !='-' && BOARD[loc][i] !='p' && BOARD[loc][i] !='b' & BOARD[loc][i] !='n' && 
						 BOARD[loc][i] !='r' && BOARD[loc][i] !='c'&& BOARD[loc][y] !='C'){
						//legalMoves[moves] = toString(x) + toString(y) +toString(x) + toString(y);
							legalMh[toString(x) + toString(y)].push_back(toString(loc) + toString(i));
							break;
						}
					}
				}
				loc=y;
				for(int i =x-1;i>=0;i--){
					if(loc>0){
						loc--;
					if (BOARD[i][loc]!='-' && BOARD[i][loc] !='p' && BOARD[i][loc] !='b' & BOARD[i][loc] !='n' && 
				 BOARD[i][loc] !='r' && BOARD[i][loc] !='c'&& BOARD[i][loc] !='C'){
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(i) + toString(y);
						legalMh[toString(x) + toString(y)].push_back(toString(i) + toString(loc));
						break;
					}else if (BOARD[i][loc]!='-'){ break;}
					else{
						moves++;
						//legalMoves[moves] = toString(x) + toString(y) +toString(i) + toString(y);
						legalMh[toString(x) + toString(y)].push_back(toString(i) + toString(loc));
					}
				}
				}
			}



			if (BOARD[x][y] == 'C'){
				int count = 0,i = x, z=y;
				if(y<3 && y<MAX_Y && x<MAX_X && BOARD[i+1][z+1] !='P' && BOARD[i+1][z+1] !='B' && BOARD[i+1][z+1] !='N' 
					&& BOARD[i+1][z+1] !='R'){
					legalMc[toString(x) + toString(y)].push_back(toString(i+1) + toString(z+1));
				}
				if(y>=3 && y<MAX_Y && x<MAX_X && BOARD[i][z+1] !='P' && BOARD[i][z+1] !='B' && BOARD[i][z+1] !='N'
					&& BOARD[i][z+1] !='R'){
					legalMc[toString(x) + toString(y)].push_back(toString(i) + toString(z+1));
				}

			
			}

			if (BOARD[x][y] == 'c'){
				int count = 0,i = x, z=y;
				if(y<3 && y<MAX_Y && BOARD[i-1][z+1] !='p' && BOARD[i-1][z+1] !='b' && BOARD[i-1][z+1] !='n' 
					&& BOARD[i-1][z+1] !='r'){
					legalMh[toString(x) + toString(y)].push_back(toString(i-1) + toString(z+1));
				}
				if(y>=3 && y<MAX_Y && x<MAX_X && BOARD[i][z+1] !='p' && BOARD[i][z+1] !='b' && BOARD[i][z+1] !='n' 
					&& BOARD[i][z+1] !='r'){
					legalMh[toString(x) + toString(y)].push_back(toString(i) + toString(z+1));
				}

			
			}


	      }
		}
	}
	//printLegal();
}



void MinMax(){
	map<string, vector<string> > tempMap;
	generateLegal();
	tempMap.swap(legalMc);
	char board2[MAX_X][7];
	char k,k2;
	char *conv1,*conv2;
	string display, display1;
	// copy( BOARD[0][0],  BOARD[0][0]+MAX_X*MAX_Y, BOARD2[0][0]);
	for(int x = 0; x<MAX_X;x++){
		for(int y = 0;y<MAX_Y;y++){
		 board2[x][y]=BOARD[x][y];
		}
	}
	string best1, best2;
	int bestScore = -9999,score,depth = 0;
	for( map<string, vector<string> >::iterator iter = tempMap.begin(); iter != tempMap.end(); ++iter ) {
			vector<string> temp = (*iter).second;
   			string key = (*iter).first;
   			// cout << key << " key";
   			for (unsigned i = 0; i < temp.size(); i++) {
   				k=BOARD[toInt(temp[i])/10][toInt(temp[i])%10];
   				k2 = BOARD[toInt(key)/10][toInt(key)%10];
      			move (key,temp[i]);
      			score = max ( depth+1, -9999,9999);
      			if (score > bestScore) { best1=key; best2=temp[i]; bestScore=score; }
      			moveBack (key,temp[i],k,k2);
      			//cout<<"key "<<key<<" temp "<<temp[i]<<endl;
   			}
   			// cout << endl;
		}
		conv1 = new char[best1.length()];
		conv2 = new char[best2.length()];
		for (int index = 0; index < best1.length(); index++){
		    conv1[index] = best1[index];
		}
		conv1[best1.length()] = '\0';
		for (int index = 0; index < best2.length(); index++){
		    conv2[index] = best2[index];
		}
		conv2[best2.length()] = '\0';
		conv2[1]=conv2[1]+17;
		conv1[0]=(conv1[0])+1;
		conv1[1]=conv1[1]+17;
		conv2[0]=(conv2[0])+1;
		display = conv1;
		display1 = conv2;
		cout << "flipped move is " << display << " " << display1 << endl;
		conv1[0]='0'+('8'-((conv1[0])-1));
		conv2[0]='0'+('8'-((conv2[0])-1));
		display = conv1;
		display1 = conv2;
		cout << "my move is " << display << " " << display1 << endl;
		move (best1,best2);
}

int min(int depth,int alpha,int beta){
	map<string, vector<string> > tempMap;
	generateLegal( );
	tempMap.swap(legalMh);
	int best = beta, b = beta,score;
	char k,k2;
	if(checkWin() != -1) return checkWin ();
	if(depth == maxDepth) return evaluate ();
	for( map<string, vector<string> >::iterator iter = tempMap.begin(); iter != tempMap.end(); ++iter ) {
			vector<string> temp = (*iter).second;
   			string key = (*iter).first;
   			//cout<<"min"<<score<<endl;
   			for (unsigned i = 0; i < temp.size(); i++) {
   				k =BOARD[toInt(temp[i])/10][toInt(temp[i])%10];
   				k2 = BOARD[toInt(key)/10][toInt(key)%10];
      			move (key,temp[i]);
      			//print ();
      			//printLegal();
      			//cout<<endl<<"depth  "<<depth<<endl;
      			score = max (depth+1,alpha, b);
      			if (score <best) best = score ;
      			if (score <= alpha) {
      				moveBack (key,temp[i],k,k2);
      				return best;
      			}
      			if (score <  b) b=score;
      			moveBack (key,temp[i],k,k2);
   			}
   			 cout << endl;
		}
		cout<<"min"<<best<<endl;
		return best;
}
int max(int depth,int alpha,int beta){
	map<string, vector<string> > tempMap;
	generateLegal( );
	tempMap.swap(legalMc);
	int best = alpha, a= alpha,score;
	char k,k2;
	if(checkWin() != -1) return checkWin ();
	if(depth == maxDepth) return evaluate ();
	for( map<string, vector<string> >::iterator iter = tempMap.begin(); iter != tempMap.end(); ++iter ) {
			vector<string> temp;
			temp = (*iter).second;
   			string key = (*iter).first;
   			//cout<<"max "<<score<<endl;
   			for (unsigned i = 0; i < temp.size(); i++) {
   				k = BOARD[toInt(temp[i])/10][toInt(temp[i])%10];
   				k2 = BOARD[toInt(key)/10][toInt(key)%10];
      			move (key,temp[i]);
      			//print ();
      			//printLegal();
      			cout<<"depth  "<<depth<<endl;
      			score = min (depth+1,a, beta);
      			if (score >best) best = score ;
      			if (score >= beta){
      				moveBack (key,temp[i],k,k2);
      				return best;
      			}
      			if (score > a) a=score;
      			moveBack (key,temp[i],k,k2);
   			}
   			// cout << endl;
		}
		cout<<"max"<<best<<endl;
		return best;
}

int evaluate(){
	int score=0,cScore=0,hScore=0,Cx,Cy,cx,cy;
	//cout<<"evaluate"<<endl;
	for(int x =0; x<MAX_X;x++){
		for(int y = 0; y<MAX_Y;y++){
			if (BOARD[x][y]=='P') cScore++;
			if (BOARD[x][y]=='p') hScore++;
			if (BOARD[x][y]=='N') cScore=cScore+3;
			if (BOARD[x][y]=='n') hScore=hScore+3;
			if (BOARD[x][y]=='B') cScore=cScore+3;
			if (BOARD[x][y]=='b') hScore=hScore+3;
			if (BOARD[x][y]=='R') cScore=cScore+5;
			if (BOARD[x][y]=='r') hScore=hScore+5;
			if (BOARD[x][y]=='C') {
				Cx =x;
				Cy =y;
				cScore = cScore+((y+1)*20);
			}
			if (BOARD[x][y]=='c') {
				cx =x;
				cy =y;
				hScore = hScore+((y+1)*20);
			}
		}
	}
	score = cScore - hScore;
	//cout<<"Score "<<score<<endl;
	return score;
}

int checkWin(){
	//cout<<"checkwin"<<endl;
	if (BOARD[3][6]=='C') return 9999;
	if (BOARD[4][6]=='c') return -9999;
	return -1;
}

string toString(int x){
	string String = static_cast<ostringstream*>( &(ostringstream() << x) )->str();
	return String;
}

string toString(char x){
	string String = static_cast<ostringstream*>( &(ostringstream() << x) )->str();
	return String;
}

int toInt(string s){
	int x = 0;
	stringstream con(s); 
    con >> x; 
    con.str(string());
    return x;
}