#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#define MinBD 1900
#define MaxMark 100
#define InputData "data.txt"
#define Output "Students.txt"
#define CSV "Students.csv"

string range(unsigned int M){
	string temp="";
	if(M<41) temp="F";
	else if(M>=41 && M<51) temp="Fx";		
	else if(M>=51 && M<61) temp="E";	
	else if(M>=61 && M<71) temp="D";	
	else if(M>=71 && M<81) temp="C";
	else if(M>=81 && M<91) temp="B";	 
	else temp="A";
	return temp;
}

void Open(const char *FileName,char a){
	ifstream input(FileName);
	if(a=='C') input.close();
}
void Template(const char *FileName){
    ofstream output(FileName,fstream::out|fstream::app);
    output<<"#,Saxeli,Gvari,Father_name,BDay,Result,Attendance\n";
    output.close();
}

struct person{
	string fname;
	string sname;
	string ffname;
	string attend;
	unsigned int birth_year;
	unsigned int mark;
	person(){
		fname="John";
		sname="Doe";
		ffname="John father";
		birth_year=1900;
		mark=0;
	}
	person(string FName,string SName,string FFName,unsigned int BD,unsigned int M,string Attend){
		fname=FName;
		sname=SName;
		ffname=FFName;
		SetBD(BD);
		SetMark(M);	
	}
	void SetBD(unsigned int BD){
		if(BD>2021) birth_year=2021; 
		else if(BD<MinBD) birth_year=MinBD;
		else birth_year=BD;
	}
	void SetMark(unsigned int M){	
		if(M>MaxMark) mark=MaxMark;
		else mark=M;
	}
};

istream& operator >>(istream& inp,person &P){
	Open("data.txt",' ');
	inp>>P.fname;
	inp>>P.sname;
	inp>>P.ffname;
	unsigned int BD;inp>>BD;P.SetBD(BD);
	unsigned int M;inp>>M;P.SetMark(M);
	Open("data.txt",'C');
	return inp;	
}

ostream& operator <<(ostream& out,person &P){
	person temp=P;
	out<<temp.fname<<','<<temp.sname<<','<<temp.ffname<<','<<temp.birth_year<<','<<temp.mark;
	return out;
}

bool File(const char *FileName){
	ifstream infile(FileName);
	return infile.good();
} 
bool operator >(person P1,person P2){
	if(P1.mark>P2.mark) return true;
	else return false;
}
bool operator <(person P1,person P2){
	if(P1.mark<P2.mark) return true;
	else return false;
}

struct MyPersonVector{
	unsigned int N;
	person *V;
	MyPersonVector(){
		N=1;
		V=new person[N];
	}
	MyPersonVector(unsigned int n){
		N=n;
		V=new person[N];
	}
	double MAvg(){
		double Avg=0;
		for(int i=0;i<N;i++){
			Avg+=V[i].mark;
		}
		Avg=Avg/N;
		return Avg;
	}
	string SetAttend(unsigned int M){
		if(V[M].mark>=MAvg()){
		 	return "Higher";	
		}else {
			return "Lower";
		}
	}	
};

void DisplayData(const char *FileName,MyPersonVector BSU,int j){
	fstream fs(FileName,fstream::out |fstream::app);
	for(int i=0;i<BSU.N;i++){
		fs<<j+1<<","<<BSU.V[i]<<","<<range(BSU.V[i].mark)<<","<<BSU.SetAttend(i)<<","<<endl;			
		j++;
	}
	fs.close();
}

void GetData(const char *FileName,person *P){
	ifstream input(FileName);
	unsigned int i=0;
	while(input.good()){
		input>>P[i];
		i++;
	}
	input.close();
}

bool CheckFile(const char *FileName){
	ifstream inp(FileName);
	return inp.good();
}

unsigned int Count(const char *FileName){
	unsigned int lines=0;
	string s="";
	ifstream Counts;
	Counts.open(FileName);
	while(!Counts.eof()){
		getline(Counts, s);
		lines ++;	
	}
	Counts.close();
	return lines;
}

void CheckDisplay(const char *FileName,MyPersonVector BSU){
	if(!CheckFile(Output)) Template(Output);
	if(!CheckFile(FileName)) DisplayData(FileName,BSU,1);
	else DisplayData(FileName,BSU,Count(FileName)-2);
}

void ConvertCSV(const char *FileName,MyPersonVector BSU){
    string line;
    string word;
    ifstream in(Output);
    ofstream out(CSV);
    while(getline(in,line)){
      stringstream k(line);
      while (k>>word){
         out<<word;
      }
      out<<endl;
   }
   in.close();
   out.close();
}

int main(int argc, char** argv){
	MyPersonVector BSU=MyPersonVector(Count(InputData));
	GetData(InputData,BSU.V);
	CheckDisplay(Output,BSU);
	ConvertCSV(CSV,BSU);
	return 0;
}
