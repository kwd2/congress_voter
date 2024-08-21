



#include <iomanip>
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctype.h>
#include <stdlib.h>

#include <list>
#include <vector>
#include <map>
#include<bits/stdc++.h>

using namespace std;



class Node{
public:
  string              symbol;                  

 
  long long int            dollars;                              
  list<long long int>      dollars_list;                              

  int                 number_donations;
  
  list<Node>          branches;
  map<string,Node*>   branches_map;


  void   input        (list<string>::iterator sym, long int amount);
  void   input        (list<string>::iterator sym, long int amount, long long int number_donations);

  void   output       ( int  depth,  int tabs );
  void   output1      ( int  depth,  int tabs, list<string> head_nodes );


  void   roll_dollars     (int depth);
  void   roll_dollars_sort(int depth);
  int    check_depth(int depth);
  
  Node(){dollars=0;number_donations=0;};
  Node(string name, long long int value ){symbol=name;dollars= value;number_donations=0;/*cout<<name<<" "<<value<<endl;*/}

}; 



//----------------------------------------
//
int
Node::check_depth( int depth){

  if (depth==0) return 1;

  list<Node>::iterator b=branches.begin();

  for (;b!=branches.end();b++){

    int retval = b->check_depth(depth-1);

    if (retval==1) return 1;
  }

  return 0;
}




//----------------------------------------
//
void
Node::roll_dollars( int depth){


  dollars_list.push_front(dollars);

  dollars=0;

  if (depth > 0 ){

    list<Node>::iterator b=branches.begin();

    for (;b!=branches.end();b++){

      //cout<<"r- "<<b->symbol<<endl;

      
      b->roll_dollars(depth-1);
    }
  }

}

//----------------------------------------
//
void
Node::roll_dollars_sort( int depth){


  dollars_list.push_front(dollars);

  dollars=0;

  if (depth > 0 ){

    
    multimap<long long int,Node*>                    br_sort;


    list<Node>::iterator s = branches.begin();

    for (;s!=branches.end();s++){

      long long int d1=0;

      //d1 = atol(s->symbol.c_str());
      d1 = dollars;

      if (d1>-1)
      br_sort.insert(pair<long long int,Node*>(d1, &(*s)));
    }

    
    multimap<long long int,Node*>::iterator  b = br_sort.begin();

    long long int total = 0;
    
    for ( ; b!= br_sort.end(); b++){

      if (b->second->dollars >0) {

	total += b->second->dollars;

	b->second->dollars = total;

      }
    }

    
      list<Node>::iterator b1=branches.begin();

      for (;b1!=branches.end();b1++){

	//cout<<"r- "<<b1->symbol<<endl;

      
	b1->roll_dollars_sort(depth-1);
      }

  }
}



//----------------------------------------
//
void
Node::input( list<string>::iterator symbol, long int amount, long long int number ){

  //cout<< *symbol<<endl;

    dollars += amount;

    number_donations += number;
    
  if (*symbol=="-stop") return;

  
  map< string, Node*>::iterator sn = branches_map.find(*symbol);

   if (sn == branches_map.end()){
    
    Node temp(*symbol, 0 );

    branches.push_back(temp);

    branches_map.insert( pair<string,Node*>(*symbol,&(branches.back() )));
    
    sn = branches_map.find(*symbol);
  }


   //sn->second->dollars += amount;

   sn->second->input( ++symbol, amount, number );
    
}

//----------------------------------------
//
void
Node::input( list<string>::iterator symbol, long int amount){

  //cout<< *symbol<<endl;

  dollars += amount;
 

    number_donations++;
    
  if (*symbol=="-stop") return;

  
  map< string, Node*>::iterator sn = branches_map.find(*symbol);

   if (sn == branches_map.end()){
    
    Node temp(*symbol, 0 );

    branches.push_back(temp);

    branches_map.insert( pair<string,Node*>(*symbol,&(branches.back() )));
    
    sn = branches_map.find(*symbol);
  }


   //sn->second->dollars += amount;

  sn->second->input( ++symbol, amount );
    
}

//----------------------------------------
//
void
Node::output1( int depth, int tabs, list<string> head_nodes ){


  cout<<symbol;
  //cout<<"\t"<<symbol<<"\t";

  if (depth == 1 ) {
  
    int size = symbol.size();  if (size>60) size=60;

    for (int i=0;i!=60-size;i++) cout<<" ";
    cout<<"\t";

    //cout<<number_donations<<"\t";
  
    for  (int i=0;i!=12;i++) if (dollars<pow(10,i)) cout<<" ";

    cout << dollars ;
    //if (depth==1) cout << dollars ;

    if (number_donations==0) number_donations=-1;
    
    //cout<<"\t"<<dollars/number_donations<<"\t"<<number_donations;   //<<"\t"<<branches.size();
  
    list<long long int>::iterator d = dollars_list.begin();

    for ( ; d!=dollars_list.end(); d++){

      //cout<<"\t"<<*d;
      if (depth==1) cout<<"\t"<<*d;
    }

  }  // depth==1
  
  cout << endl;
  
  if (depth-1>0){

      head_nodes.push_back(symbol);
    
    multimap<long long int,Node*>                    br_sort;
    multimap<long long int,Node*>::reverse_iterator  br;

    list<Node>::iterator s = branches.begin();

    int s1=0;
    for (;s!=branches.end();s++,s1++){

      long long int d1=0;
      long long int y1=0;


      if (s->dollars_list.size()>0){

	d1 = s->dollars;

	list<long long int>::iterator dl = s->dollars_list.begin();
	//for (; dl != s->dollars_list.end();dl++) if (*dl>0) y1++;
	for (; dl != s->dollars_list.end();dl++) d1+= *dl;

	//d1=   s->dollars_list.size()*100000  + (s->dollars_list.back())  +y1;

	//cout<<"here"<<endl;
      br_sort.insert(pair<long long int,Node*>(d1, &(*s)));
	
      }else{

	if (symbol=="date") {

	  int s1 =0;
	  int s2 =0;
	  s2=s->symbol.find("/", s1); string month =s->symbol.substr(s1,s2-s1); s1+=s2-s1+1;
	  s2=s->symbol.find("/", s1); string day =s->symbol.substr(s1,s2-s1); s1+=s2-s1+1;
	  s2=s->symbol.find("/", s1); string year =s->symbol.substr(s1,s2-s1); s1+=s2-s1+1;
	  
	  //cout<<month<<"  "<<day<<"  "<<year<<endl;
	  
	  d1 = atoi(year.c_str())*12 + atoi(month.c_str());
	}
	else{
	  d1 = s->dollars;
	}


      //d1 = s->dollars/ s->number_donations;

      //d1 = atol(s->symbol.c_str());

      
      //y1=1;
      //d1 += pow(1000,10);	
      //list<long int>::iterator dl = s->dollars_list.begin();
      //for (; dl != s->dollars_list.end();dl++,y1++) if (d1==0) d1 = -*dl;
      //br_sort.insert(pair<long int,Node*>(s1, &(*s)));
      //br_sort.insert(pair<long int,Node*>(d1+y1, &(*s)));

      if (d1>-1)
      br_sort.insert(pair<long long int,Node*>(d1, &(*s)));
      }

    }
    
    //for (;s!=branches.end();s++) br_sort.insert(pair<long int,Node*>(s->dollars, &(*s)));


    multimap<long long int,Node*>::iterator  b = br_sort.begin();

    long long int total = 0;
    
    for ( ; b!= br_sort.end(); b++){

      if (b->second->dollars >0) b->second->dollars = total + b->second->dollars;

    }

    
    for (br=br_sort.rbegin();br!=br_sort.rend();++br){

      cout<<tabs<<"\t";
      list<string>::iterator h = head_nodes.begin();
      
      for (;h!=head_nodes.end();h++) cout<<*h<<"\t";
      
      //for (int i=0; i!= tabs; i++) cout<<"\t";
      
      br->second->output1(depth-1, tabs+1, head_nodes);
      
    }
    
  }
  
}




//----------------------------------------
//
void
Node::output( int depth, int tabs ){

  cout<<symbol;

  int size = symbol.size();  if (size>60) size=60;

  for (int i=0;i!=60-size;i++) cout<<" ";
  

  for  (int i=0;i!=12;i++) if (dollars<pow(10,i)) cout<<" ";
  cout << dollars ;

  list<long long int>::iterator d = dollars_list.begin();

  for ( ; d!=dollars_list.end(); d++){

    cout<<"\t"<<*d;
  }

  cout << endl;
  
  if (depth-1>0){

    multimap<long int,Node*>                    br_sort;
    multimap<long int,Node*>::reverse_iterator  br;

    list<Node>::iterator s = branches.begin();

    for (;s!=branches.end();s++) br_sort.insert(pair<long int,Node*>(s->dollars, &(*s)));
    
    for (br=br_sort.rbegin();br!=br_sort.rend();++br){

      cout<<symbol;
      
      for (int i=0; i!= tabs+1; i++) cout<<"\t";
  
      br->second->output(depth-1, tabs+1);

    }

  }

}


//----------------------------------------
//
int main1()
{

  string year,month,day;

  string cmte_type;

  string         line;
  string         field;

  int            s1=0;
  int            s2=0;

  
  extern   map<string,list<int> > suid_map;
  
  
  
  // ----- parse header file

  map<string,Node*>  columns;
  vector<string>     columns1;

  int      count=0;
  int year_count=0;
  
  ifstream datafile1;  datafile1.open("voter_header.txt");  if(!datafile1.is_open()){cout<<"Error 1"<<endl;return 0;}


  getline(datafile1, line);  //  1st line

  //cout<<line<<endl;      

  s1 = 1;
  s2 = 0;
  
  while (s2 != string::npos ){

    s2=line.find("\",", s1);field=line.substr(s1,s2-s1); s1+=s2-s1+3;

    if (field.size()>1 && field.back()=='"') field.pop_back();
    
    cout<<"--- "<<count++<<"\t"<<field<<endl;
    
    Node* node = new Node(field,0);

    columns.insert(pair<string,Node*>(field, node));

    columns1.push_back(field);
  }

  // ----- parse header file



  


  cout<<"num columns= "<<columns1.size()<<endl;    

  Node column_graph("column",0);
  
  int num_lines=0;

  int dollars1 = 0;
  
  long int total_dollars=0;

  // ------------------------------------ parse main data file


  
  while (getline(cin, line)){


    //cout<<line<<endl;

    if (line =="-roll" ){

      column_graph.roll_dollars(6);
      cout<<"rolling"<<endl;
      continue;
    }

    
    num_lines++;    

    //if (num_lines>4500000) break;
    
    dollars1 = -100000000;    
    
    vector<string> fields;
    
    s1=1;
    s2=0;    

    int num_commas = 0;

 
 
    while (s2 != string::npos ){
 
	num_commas++;
      
	s2=line.find("\",", s1);field=line.substr(s1,s2-s1); s1+=s2-s1+3;    



	for (int i =0; i!= field.size();i++){
	  field[i] = toupper(field[i]);
	}
	
	if (field != " " ) fields.push_back(field);	

	//cout<<field<<endl;


    }  // while

    //cout<<"num fields"<<fields.size()<<endl;
   
    if (num_commas != 32 ) {       //error check
	  
      cout<<num_commas<<endl;
      cout<<line<<endl;
      vector<string>::iterator i;
      for ( i=fields.begin();i!=fields.end();i++){
	cout<<*i<<endl;
      }    
    }

    

   // ---------------------   change date
    if (fields[6].size()>7){
      
      string year  = "";
      string month= fields[6].substr(0,2);

      if (month.find("/") != string::npos) month = fields[6].substr(0,1);

      if (fields[6].size()==8)  year = fields[6].substr(4,4);
      if (fields[6].size()==9)  year = fields[6].substr(5,4);
      if (fields[6].size()==10) year = fields[6].substr(6,4);

      //cout<<month<<"  "<<year<<endl;
  
      fields[6] = month + "/" + year; 
    }

    if (fields[8].size()>7){
      
      string year  = "";
      string month= fields[8].substr(0,2);

      if (month.find("/") != string::npos) month = fields[8].substr(0,1);

      if (fields[8].size()==8)  year = fields[8].substr(4,4);
      if (fields[8].size()==9)  year = fields[8].substr(5,4);
      if (fields[8].size()==10) year = fields[8].substr(6,4);

      //cout<<month<<"  "<<year<<endl;
  
      fields[8] = month + "/" + year; 
    }
    // ---------------------   change date

    //cout<<fields[31]<<endl;

    if (fields[31].size()>1) {
      //cout<<"here"<<endl;
      //cout<<fields[31].substr(0, fields[31].size())<<"*"<<endl;;
      fields[31] = fields[31].substr(0, fields[31].size()-2);
    }
    
    //cout<<fields[31]<<endl;

      
        //cout<<fields[6]<<"-  "<<fields[0]<<"  "<<fields[5]<<"  "<<fields[15]<<"  "<<fields[7]<<"  "<<dollars1<<"  "<<fields[13]<<endl;
      
   //cout<<fields[0]<<","<<fields[2]<<","<<fields[3]<<","<<fields[4]<<","<<fields[18]<<","<<fields[7]<<","<<fields[10]


    /*
    map<string,list<int> >::iterator s1 = suid_map.find(fields[0]);

    if (s1==suid_map.end()) continue;

    if (s1->second.size()==0) {
      //cout<<here<<endl;
      for (int i = 0; i!=6;i++) s1->second.push_back(0);
    }
    */

    /*
    // ----------------------------------  make judicical district spreadsheet


    cout<< fields[3]+" "+fields[4]+" "+fields[2]+" "+fields[5]<<"|"<<

      //fields[0] <<"|"<<
	fields[7] <<"|"<<
	fields[10] <<"|"<<
	fields[11] <<"|"<<
	fields[12] <<"|"<<

	fields[13]+" "+fields[14]+" "+fields[15]+" "+fields[16]<<"|"<<

       fields[18] <<"|"<<
       fields[20] <<"|"<<
      fields[31] ;


    if (s1->second.size()!=6) cout<<"error"<<endl;


    list<int>::iterator l = s1->second.begin();

    for (;l!=s1->second.end();l++) cout<< "|"<<*l;

    cout<<endl;
    if (int i=1) continue;
    // ----------------------------------  make judicical district spreadsheet
    */

    

    // -----------------------------------  make data graph   
 
    list<string>             symbols;
    list<string>::iterator   s;

    vector <string>       ::iterator   f  = fields.begin();
    map    <string,Node*> ::iterator   c  = columns.begin();
    vector <string>       ::iterator   c1 = columns1.begin();

    //cout<<endl;

    int ccnt=0;
    for (;c1!=columns1.end();c1++,f++,ccnt++){


      //cou<<*f<<"\t"<<*c1<<endl;
      
      symbols.clear();

      symbols.push_back( *c1  );
      symbols.push_back( *f  );

      //if (ccnt==18)  symbols.push_back(); 
      //if (ccnt==0)  symbols.push_back(fields[7]);  

 
      
      symbols.push_back("-stop");
      s = symbols.begin();


      if ((ccnt!=0 && ccnt<11) || ccnt==18 || ccnt==27)
	column_graph.input( s, 1 );
      
    }

    /*
    // --------------- make il_suid file

    cout<<fields[0]<<","<<fields[2]<<","<<fields[3]<<","<<fields[4]<<","<<fields[18]<<","<<fields[7]<<","<<fields[10]

	<<","<<fields[11]<<","<<fields[12]

	<<",";

    if (fields[13]!="") cout<<fields[13]<<" ";

    cout<<fields[14];

    if (fields[15]!="") cout<<" "<<fields[15];
    if (fields[16]!="") cout<<" "<<fields[16];

    cout<<","<<fields[31] <<","<<fields[6] <<","<<fields[8] ;

    cout<<endl;

    // --------------- make il_suid file
    */




    
    
    /*
      symbols.clear();
      symbols.push_back("SUID"); 
      symbols.push_back(fields[0] );
      symbols.push_back("LastName"); 
      symbols.push_back(fields[2] );
      symbols.push_back("-stop"); 
      s = symbols.begin();
      column_graph.input( s, 1 );

     symbols.clear();
      symbols.push_back("SUID"); 
      symbols.push_back(fields[0] );
      symbols.push_back("FirstName"); 
      symbols.push_back(fields[3] );
      symbols.push_back("-stop"); 
      s = symbols.begin();
      column_graph.input( s, 1 );


     symbols.clear();
      symbols.push_back("SUID"); 
      symbols.push_back(fields[0] );
      symbols.push_back("MiddleName"); 
      symbols.push_back(fields[4] );
      symbols.push_back("-stop"); 
      s = symbols.begin();
      column_graph.input( s, 1 );

     symbols.clear();
      symbols.push_back("SUID"); 
      symbols.push_back(fields[0] );
      symbols.push_back("VoteCity"); 
      symbols.push_back(fields[18] );
      symbols.push_back("-stop"); 
      s = symbols.begin();
            column_graph.input( s, 1 );
    */




      
    
    // -----------------------------------  make data graph   

	
  }
  // ------------------------------------ parse main data file


  
 
  


  // -----------------------------------  print out data graph   
  
  list<string> s_e; 

  int ii=0;

  list<Node>::iterator b =column_graph.branches.begin();
  for (               ;b!=column_graph.branches.end();b++){

    cout<<"--- "<<b->symbol;
    if (b->symbol.size()<12) cout<<"\t";

    cout<<"\t #unique=\t"<<b->branches.size()<<endl; 
    
  }

  

    
  b =column_graph.branches.begin();
  for (               ;b!=column_graph.branches.end();b++){

    
    cout<<endl<<"--- ";    
      b->output1(2,0, s_e);

      cout<<endl<<"--- ";    
      b->output1(3,0, s_e);

  }

// -----------------------------------  print out data graph          



    return 0;
}






//----------------------------------------
//
int main2(Node* graph0)
{


  string         line;
  string         field;

  int            s1=0;
  int            s2=0;

  int            first =0;
  int            count=0;

  //Node graph0("fields",0);

  
  

  //----------------------------------------- read the data

    
  while (getline(cin, line)){                //   $ cat datafile.txt | ./a.out > scr.txt

    if (first==1 || line =="-first") {

      first=0;
    
      for (int i = 0;i!=24;i++){     // skip first 24 output lines in fec*.txt files
	getline(cin,line);
      
      }      
    }

    //cout<<line<<endl;

    if (line =="-roll" ){

      cout<<"rolling- "<<graph0->symbol<<endl<<endl;

      
      graph0->roll_dollars(6);
      //graph0-> roll_dollars_sort(6);


      first=1;


      list<Node>::iterator b =graph0->branches.begin();
      for (               ;b!=graph0->branches.end();b++){

	cout<<"--- "<<b->symbol;
	if (b->symbol.size()<12) cout<<"\t";

	cout<<"\t #unique=\t"<<b->branches.size()<<endl;     
      }

      
      continue;
    }
    
    count++;

    //if (count>1000) break;

    if ( isdigit( line.c_str()[0] )) {

      //cout<<line<<endl;

      int count1 = atoi(line.substr(0,1).c_str());

      //count1 = 2+ (count1)*2;
      count1 = 2+ (count1);

      int    s1      =0;
      int    s2      =0;
      string field;
      string field1;
      list<string>             symbols;
      list<string>::iterator   s;

      
      s2=line.find("\t", s1); s1+=s2-s1+1;     // skip first field
     
      for (int i=0; i!= count1; i++){

	s2=line.find("\t", s1);field=line.substr(s1,s2-s1); s1+=s2-s1+1;  	

	//remove padding white space

	int last_not_space = 0;
	
	int ii =0;
	
	for ( ;ii< field.length(); ++ii ){

	  if (field[ii] != ' ') last_not_space = ii;
	  
	}

	field1 = field.substr(0, last_not_space+1);
	
    
	//cout<<"*"<<field1<<"*"<<endl;
	
	symbols.push_back(field1);
      }

      /*
      {
	// city of Aurora study -  cities.txt -> aurora.txt

	//2	CT_type	CITY OF AURORA	AURORA WARD 8	YYWLQ52Y

	symbols.pop_front();
	string s1 = *symbols.begin();
	symbols.pop_front();
	symbols.push_front(field1);
	symbols.push_front(s1);
	symbols.pop_back();
      }
      */
      
      symbols.push_back("-stop");

      s2=line.find("\t", s1);field=line.substr(s1,s2-s1); s1+=s2-s1+1;
      long long int  dollars = atol (field.c_str());
      //cout<<field<<"-"<<dollars<<endl;

      /*  
      s2=line.find("\t", s1);field=line.substr(s1,s2-s1); s1+=s2-s1+1;
      long long int  average = atol (field.c_str());
      //cout<<s1<<"-"<<s2<<endl;

      s2=line.find("\n", s1);field=line.substr(s1,line.size()); s1+=s2-s1+1;
      long long int  number_donations = atol (field.c_str());
      //cout<<s1<<"-"<<s2<<endl;
      */
	
      //cout<<"**"<<field<<endl;

      //cout<<s2<<" "<<dollars<<" "<<average<<"  "<<number_donations<<endl;

	s=symbols.begin();

	//if (*s!="NAME")
	//if (*s=="TRANSACTION_AMT")
	{
	  //graph0->input( s, dollars, number_donations);
	  graph0->input( s, dollars, 1);
	}
      
    } 
 
  }

  //cout<<count<<endl;

  //cout<<graph0->branches_map.size()<<endl;

  list<Node>::iterator b =graph0->branches.begin();
  for (               ;b!=graph0->branches.end();b++){

    cout<<"--- "<<b->symbol;
    if (b->symbol.size()<12) cout<<"\t";

    cout<<"\t #unique=\t"<<b->branches.size()<<endl; 
    
  }




   list<string> s_e;
   
  b =graph0->branches.begin();
  for ( ;b!=graph0->branches.end();b++){

    cout<<endl<<"--- ";      b->output1(3,0, s_e);

  }




  
 return 0;
}



//----------------------------------------
//
int roll_array( Node* graph0, string field1, string field2)
{

  /*
---     TRANSACTION_TP
0	TRANSACTION_TP	15
1	TRANSACTION_TP	15	TRANSACTION_DT
2	TRANSACTION_TP	15	TRANSACTION_DT	03/2022     	   903233622	513	1758068
  */


  Node graph1(field1, 0);
  
  
  map<string,Node*>::iterator bm = graph0->branches_map.find(field1);

  if (bm != graph0->branches_map.end()){


    list<string> column_titles;
    
    map<string,Node*>::iterator bm1 = bm->second->branches_map.begin();

    for ( ; bm1 != bm->second->branches_map.end(); bm1++){


      //cout<<bm1->second->symbol<<endl;

      column_titles.push_back(bm1->second->symbol);

      
      map<string,Node*>::iterator bm2 = bm1->second->branches_map.find(field2);

      if (bm2 != bm1->second->branches_map.end() ){

	  list<string>             symbols;
	  list<string>::iterator   s;
    
	  map<string,Node*>::iterator bm3 = bm2->second->branches_map.begin();

	  for ( ; bm3 != bm2->second->branches_map.end(); bm3++){

	    //cout<<bm3->second->symbol<<endl;

	    list<string>             symbols;
	    list<string>::iterator   s;
  
	    symbols.push_back(field2);

	    symbols.push_back(bm3->second->symbol);

	    symbols.push_back("-stop");
	    s = symbols.begin();

	    graph1.input(s, bm3->second->dollars);


	    
	  }
	  

      }
      
      graph1.roll_dollars(6);
	  
    }    // bm1

    
    list<string>::reverse_iterator c = column_titles.rbegin();

    cout<<"\t\t";
    
    for ( ;c!=column_titles.rend();++c){

      cout<<*c<<"\t";
      
    }
    cout<<endl;

   list<string> s_e;
   graph1.output1(3,0, s_e);



    
  }


  return 0;
}

 //----------------------------------------
//
int read_suid_file(Node* graph0)
{
  
  string line,field;
  int count=0;
  int count1=0;
  
  map<string,Node*>::iterator i = graph0->branches_map.find("NAME");

  Node* names = i->second;

  i = graph0->branches_map.find("CITY OF AURORA");

  if (i==graph0->branches_map.end()) cout<<"ERROR"<<endl;
  
  Node* city_suids = i->second;

  
  ifstream datafile1;  datafile1.open("il_suid.txt");  if(!datafile1.is_open()){cout<<"Error 1"<<endl;return 0;}

  while (getline(datafile1, line)){
    if(datafile1.eof()) break;

    count++;

 

    int s1 =0;
    int s2 =0;

    s2=line.find(",", s1); string suid = field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string last = field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string first= field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string middle = field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string city = field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string age = field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string sex = field=line.substr(s1,s2-s1); s1+=s2-s1+1;



    // ------------------------------ city specific study

    if (city_suids->branches_map.find(suid) == city_suids->branches_map.end()) continue;


    
    // ------------------------------ city specific study


    

    list<string>             symbols;

    if ((rand()%100) < 25)
      //if ((rand()%100) < 25)
      {

  	  
	  symbols.clear();
	  symbols.push_back("SUID1"); 
	  symbols.push_back(suid);
	  symbols.push_back("AGE"); 
	  symbols.push_back(age);
	  symbols.push_back("-stop"); 
	  graph0->input( symbols.begin(), 1 );

	  symbols.clear();
	  symbols.push_back("SUID1"); 
	  symbols.push_back(suid);
	  symbols.push_back("SEX"); 
	  symbols.push_back(sex);
	  symbols.push_back("-stop"); 
	  graph0->input( symbols.begin(), 1 );

	  symbols.clear();
	  symbols.push_back("SUID1"); 
	  symbols.push_back(suid);
	  symbols.push_back("CITY"); 
	  symbols.push_back(city);
	  symbols.push_back("-stop"); 
	  graph0->input( symbols.begin(), 1 );

      }
    
	  symbols.clear();
	  symbols.push_back("CITY1"); 
	  symbols.push_back(city);
	  symbols.push_back("-stop"); 
	  graph0->input( symbols.begin(), 1 );

	  symbols.clear();
	  symbols.push_back("SEX1"); 
	  symbols.push_back(sex);
	  symbols.push_back("-stop"); 
	  graph0->input( symbols.begin(), 1 );



	  


 
    
	  
    //cout<<suid<<" "<<last<<" "<<first<<" "<<middle<<" "<<city<<endl;    

    int flag=0;

    //if (flag==0) return 1;
    
    for (int k = 1; k!=4;k++){

      if (flag==0){
	
    string temp = last+", "+first;

    if (k==1 &&middle.size()>0 ) temp = temp + " "+middle.substr(0,1);
    if (k==2  ) temp = temp + " "+middle;

    map<string,Node*>::iterator ii = names->branches_map.find(temp);

    if (ii!= names->branches_map.end()) {

      map<string,Node*>::iterator iii = ii->second->branches_map.find("CITY");
      if (iii!= ii->second->branches_map.end()) {

	map<string,Node*>::iterator iiii = iii->second->branches_map.find(city);
	if (iiii!= iii->second->branches_map.end()) {

	  flag=1;
	  count1++;
	  //cout<<ii->first<<endl;
	  //cout<<"** "<<temp<<endl;

	  //list<string> s_e;
	  //ii->second->output1(6,0, s_e);

	  int suid_cnt=0;
	  
	  map<string,Node*>::iterator s= iiii->second->branches_map.find("SUID");

	  if (s!=iiii->second->branches_map.end()) suid_cnt = s->second->branches_map.size();

	  if (suid_cnt<3)
	    {	  
	  
	  list<string>             symbols;
	  
	  symbols.clear();
	  symbols.push_back("NAME"); 
	  symbols.push_back(temp);
	  symbols.push_back("CITY"); 
	  symbols.push_back(city);
	  symbols.push_back("SUID"); 
	  symbols.push_back(suid);
	  symbols.push_back("-stop"); 
	  graph0->input( symbols.begin(), 1 );
	  
	  }


	  map<string,Node*>::iterator	  o = iiii->second->branches_map.find("SUID");

	  if (o!=iiii->second->branches_map.end() && o->second->branches_map.size()<3   ){


	      symbols.clear();
	      symbols.push_back("MatchedVoterCount"); 
	      symbols.push_back("count");
	      symbols.push_back("-stop"); 
	      graph0->input( symbols.begin(), 1 );



	    
	  //------------------------
	  map<string,Node*>::iterator o = iiii->second->branches_map.find("OCCUPATION");

	  if (o!=iiii->second->branches_map.end()){

	      int percnt = 100/o->second->branches_map.size();

	    map<string,Node*>::iterator b = o->second->branches_map.begin();

	    for (;b!=o->second->branches_map.end();b++){

	      symbols.clear();
	      symbols.push_back("MatchedVoterSUID"); 
	      symbols.push_back(suid);
	      symbols.push_back("OCCUPATION"); 
	      symbols.push_back(b->first);
	      symbols.push_back("-stop"); 
	      graph0->input( symbols.begin(), percnt );


	      symbols.clear();
	      symbols.push_back("MatchedVoterOccupation"); 
	      
	      symbols.push_back(b->first);
	      symbols.push_back("-stop"); 
	      graph0->input( symbols.begin(), percnt );
	      
	    }
	  }

	    
	    o = iiii->second->branches_map.find("EMPLOYER");

	  if (o!=iiii->second->branches_map.end()){

	    int percnt = 100/o->second->branches_map.size();

	    map<string,Node*>::iterator b = o->second->branches_map.begin();

	    for (;b!=o->second->branches_map.end();b++){

	      symbols.clear();
	      symbols.push_back("MatchedVoterSUID"); 
	      symbols.push_back(suid);
	      symbols.push_back("EMPLOYER"); 
	      symbols.push_back(b->first);
	      symbols.push_back("-stop"); 
	      graph0->input( symbols.begin(), percnt );


	      symbols.clear();
	      symbols.push_back("MatchedVoterEmployer"); 
	      
	      symbols.push_back(b->first);
	      symbols.push_back("-stop"); 
	      graph0->input( symbols.begin(), percnt );
	      
	    }
	  }

	  
	  o = iiii->second->branches_map.find("CMTE_ID");

	  if (o!=iiii->second->branches_map.end()){

	    map<string,Node*>::iterator b = o->second->branches_map.begin();

	    for (;b!=o->second->branches_map.end();b++){

	      symbols.clear();
	      symbols.push_back("MatchedVoterSUID"); 
	      symbols.push_back(suid);
	      symbols.push_back("CMTE_ID"); 
	      symbols.push_back(b->first);
	      symbols.push_back("-stop"); 
	      graph0->input( symbols.begin(),b->second->dollars );

	      symbols.clear();
	      symbols.push_back("MatchedVoterCMTE_ID"); 
	      
	      symbols.push_back(b->first);
	      symbols.push_back("-stop"); 
	      graph0->input( symbols.begin(), b->second->dollars );
	    }
	  }
	  
	  } // SUID size<3

	  
	  //------------------------

	  
	  symbols.clear();
	  symbols.push_back("MatchedVoterAge"); 
	  symbols.push_back(age);
	  symbols.push_back("-stop"); 
	  graph0->input( symbols.begin(), 1 );

	      symbols.clear();
	      symbols.push_back("MatchedVoterSUID"); 
	      symbols.push_back(suid);
	      symbols.push_back("AGE"); 
	  symbols.push_back(age);
	  symbols.push_back("-stop"); 
	  graph0->input( symbols.begin(), 1 );


	  
	  symbols.clear();
	  symbols.push_back("MatchedVoterSex"); 
	  symbols.push_back(sex);
	  symbols.push_back("-stop"); 
	  graph0->input( symbols.begin(), 1 );

	      symbols.clear();
	      symbols.push_back("MatchedVoterSUID"); 
	      symbols.push_back(suid);
	      symbols.push_back("SEX"); 
	  symbols.push_back(sex);
	  symbols.push_back("-stop"); 
	  graph0->input( symbols.begin(), 1 );


	  //------------------------


	
	}
      }
    }


      }// flag==0
    }// k


 


    
  }


  cout<<"count= "<<count<<"   count1= "<<count1<<endl;
  return 1;
}
//----------------------------------------
//
int read_voter_history_file3(Node* graph0)
{
  extern map<string,list<string> > voter_map1;
  
  string line,field;
 
  int count=0;
  int count1=0;
 int count3=0;


 map<string,string> voter_covidvbm;
 
  
  ifstream datafile1;  datafile1.open("il_votehistory_3.15.33.csv");  if(!datafile1.is_open()){cout<<"Error 1"<<endl;return 0;}

  while (getline(datafile1, line)){
    if(datafile1.eof()) break;

    count++;

    //if (count>3000000) break;
    int s1 =1;
    int s2 =0;

    s2=line.find("\",", s1); string suid = field=line.substr(s1,s2-s1); s1+=s2-s1+3;

    s2=line.find("\",", s1); string date = field=line.substr(s1,s2-s1); s1+=s2-s1+3;

    int year1 = atoi(date.substr(date.size()-4,4).c_str());
    //cout<<year1<<endl;
    
    s2=line.find("\",", s1); string type = field=line.substr(s1,s2-s1); s1+=s2-s1+3;

    s2=line.find("\"", s1); string party = field=line.substr(s1,s2-s1); s1+=s2-s1+3;

    //cout<<suid<<" "<<date<<" "<<type<<" "<<party<<endl;


    map<string,list<string> >::iterator v = voter_map1.find(suid);


    string age="*";
    string age1="*";
    string il_district="*";
    string county="*";
    string ward="*";
    string city="*";
    string jurisdiction="*";
    string address;
    string state;
    string zip;

    
    if (v!=voter_map1.end()){

      //cout<<v->second.size()<<endl;
      
      if (v->second.size()==5){
	
	list<string>::iterator f = v->second.begin();

	age = *f++;

	jurisdiction = *f++;

	/*
	city = *f++;               


	address = *f++;
	state = *f++;
	zip = *f++;
	*/	

	il_district = *f++;
	
	county = *f++;
	

	ward = *f++;               


	int age11= atoi(age.c_str()) - (2022 - year1);
	age1 = std::to_string(age11);
      }
      

    }

    /*
    // for geocoding
    //if (jurisdiction == "45" && date =="11/3/2020" ){
    //if (jurisdiction == "45" && date =="3/17/2020" && party == "DEMOCRATIC" ){
    //if (jurisdiction == "45" && date =="3/17/2020" && party == "REPUBLICAN" ){
    //if (jurisdiction == "45" && date =="3/15/2016" ){
    {
  
      count3++;
      
      cout<<count3<<","<<address<<","<<city<<","<<state<<","<<zip<<endl;
    }
    */

    if (jurisdiction == "105" && date =="11/3/2020" && age == "30" ){


      cout<< suid<<endl;
      
    }


    
    if (jurisdiction == "49" && ( date =="3/17/2020" || date =="11/6/2018" || date =="3/20/2018" )  )
      {

	voter_covidvbm.insert(pair<string,string>(suid,suid) );	
      }
    
      
    list<string>             symbols;
	  
    symbols.clear();
    symbols.push_back("district date age"); 
    symbols.push_back(il_district);
   symbols.push_back(date);
   symbols.push_back(age);
    symbols.push_back("-stop"); 
    //graph0->input( symbols.begin(), 1 );



    symbols.clear();
    symbols.push_back("date"); 
    symbols.push_back(date);
    symbols.push_back("-stop"); 
    graph0->input( symbols.begin(), 1 );

    symbols.clear();
    symbols.push_back("date party"); 
    symbols.push_back(date);
    symbols.push_back(party);
    symbols.push_back("-stop"); 
    graph0->input( symbols.begin(), 1 );


    

   symbols.clear();
    symbols.push_back("age_at_vote"); 

   symbols.push_back(age1);
    symbols.push_back("-stop"); 
    //graph0->input( symbols.begin(), 1 );


    symbols.clear();
    symbols.push_back("date age_at_vote"); 
  symbols.push_back(date);
   symbols.push_back(age1);
    symbols.push_back("-stop"); 
    //graph0->input( symbols.begin(), 1 );


    symbols.clear();
    symbols.push_back("district date age_at_vote"); 
    symbols.push_back(il_district);
    symbols.push_back(date);
    //symbols.push_back("*");
    symbols.push_back(age1);
    symbols.push_back("-stop"); 
    //graph0->input( symbols.begin(), 1 );

    
   symbols.clear();
    symbols.push_back("county date city"); 
    symbols.push_back(jurisdiction);
    symbols.push_back(date);
    symbols.push_back(city);
    //symbols.push_back(age1);
    symbols.push_back("-stop"); 
    //graph0->input( symbols.begin(), 1 );

   symbols.clear();
    symbols.push_back("county date party"); 
    symbols.push_back(jurisdiction);
    symbols.push_back(date);
    symbols.push_back(party);
    //symbols.push_back(age1);
    symbols.push_back("-stop"); 
    graph0->input( symbols.begin(), 1 );

    symbols.clear();
    symbols.push_back("county date age_at_vote"); 
    symbols.push_back(jurisdiction);
    symbols.push_back(date);
    symbols.push_back(age1);
    symbols.push_back("-stop"); 
    graph0->input( symbols.begin(), 1 );



    symbols.clear();
    symbols.push_back("date district age_at_vote"); 
    symbols.push_back(date);
    symbols.push_back(il_district);
    symbols.push_back(age1);
    symbols.push_back("-stop"); 
    //graph0->input( symbols.begin(), 1 );



   symbols.clear();
    symbols.push_back("jurisdiction age_at_vote"); 
    symbols.push_back(jurisdiction);
     symbols.push_back(age1);
    symbols.push_back("-stop"); 
    //graph0->input( symbols.begin(), 1 );


    symbols.clear();
    symbols.push_back("jur_county date age_at_vote"); 
    symbols.push_back(jurisdiction);
    symbols.push_back(date);
    symbols.push_back(age1);
    symbols.push_back("-stop"); 
    //graph0->input( symbols.begin(), 1 );

    symbols.clear();
    symbols.push_back("city date age_at_vote"); 
    symbols.push_back(ward);
    symbols.push_back(date);
    symbols.push_back(age1);
    symbols.push_back("-stop"); 
    //graph0->input( symbols.begin(), 1 );


   symbols.clear();
    symbols.push_back("district county date age_at_vote"); 
    symbols.push_back(il_district);
    symbols.push_back(jurisdiction);
    symbols.push_back(date);
    symbols.push_back(age1);
    symbols.push_back("-stop"); 
    //graph0->input( symbols.begin(), 1 );


    
    
  }

  cout<<count<<endl;

  cout<<"covid vbm ballots should be "<<voter_covidvbm.size()<<endl;


  return 1;
}

    
//----------------------------------------
//
int read_voter_history_file(Node* graph0)
{

  
  string line,field;
  int count=0;
  int count1=0;

  map<string,Node*>::iterator suid0 = graph0->branches_map.find("SUID1");

  if (suid0==graph0->branches_map.end()) cout<<"ERROR"<<endl;
  
  map<string,Node*>::iterator i = graph0->branches_map.find("NAME");

  Node* names = i->second;

  
  ifstream datafile1;  datafile1.open("il_votehistory_3.15.33.csv");  if(!datafile1.is_open()){cout<<"Error 1"<<endl;return 0;}

  while (getline(datafile1, line)){
    if(datafile1.eof()) break;

    count++;

    //if (count>1000000) break;
    int s1 =1;
    int s2 =0;

    s2=line.find("\",", s1); string suid = field=line.substr(s1,s2-s1); s1+=s2-s1+3;

    s2=line.find("\",", s1); string date = field=line.substr(s1,s2-s1); s1+=s2-s1+3;

    int year1 = atoi(date.substr(date.size()-4,4).c_str());
    //cout<<year1<<endl;
    
    s2=line.find("\",", s1); string type = field=line.substr(s1,s2-s1); s1+=s2-s1+3;

    s2=line.find("\"", s1); string party = field=line.substr(s1,s2-s1); s1+=s2-s1+3;

    //cout<<suid<<" "<<date<<" "<<type<<" "<<party<<endl;


    
    list<string>             symbols;
	  
    symbols.clear();
    symbols.push_back("ElectionDate"); 
    symbols.push_back(date);
    symbols.push_back("ElectionType"); 
    symbols.push_back(type);
    symbols.push_back("-stop"); 
    graph0->input( symbols.begin(), 1 );

    symbols.clear();
    symbols.push_back("ElectionType"); 
    symbols.push_back(type);
    symbols.push_back("-stop"); 
    graph0->input( symbols.begin(), 1 );

    //cout<<suid<<endl;
   map<string,Node*>::iterator s = suid0->second->branches_map.find(suid);

    if (s!= suid0->second->branches_map.end()){


 
      string age="";
     string age1="";
      
      map<string,Node*>::iterator a = s->second->branches_map.find("AGE");
      if (a!=s->second->branches_map.end()){

	//cout<<"here"<<endl;
       map<string,Node*>::iterator aa = a->second->branches_map.begin();

       age = aa->second->symbol;
       
	symbols.clear();
	symbols.push_back("MatchedVoter1_4m"); 
	symbols.push_back("AgeAtVote"); 

	int age11= atoi(age.c_str()) - (2022 - year1);

	age1 = std::to_string(age11);
	
	symbols.push_back( age1);
	symbols.push_back("-stop"); 
	graph0->input( symbols.begin(), 1 );

	//cout<< date<<" "<< age<<" "<<age1<<endl;     
     }



      a = s->second->branches_map.find("SEX");
      if (a!=s->second->branches_map.end()){

	map<string,Node*>::iterator aa = a->second->branches_map.begin();

	string sex = aa->second->symbol;

	symbols.clear();
	symbols.push_back("MatchedVoter1_4m"); 
	symbols.push_back("SexAtVote"); 
	symbols.push_back( sex);
	symbols.push_back("-stop"); 
	graph0->input( symbols.begin(), 1 );

	symbols.clear();
	symbols.push_back("MatchedVoter1_4m"); 
	symbols.push_back("AgeSexAtVote"); 
	symbols.push_back( sex);
	symbols.push_back( age1);
	symbols.push_back("-stop"); 
	graph0->input( symbols.begin(), 1 );




      }

     a = s->second->branches_map.find("CITY");
      if (a!=s->second->branches_map.end()){

	map<string,Node*>::iterator aa = a->second->branches_map.begin();

	string city = aa->second->symbol;

	symbols.clear();
	symbols.push_back("MatchedVoter1_4m"); 
	symbols.push_back("CityAtVote"); 
	symbols.push_back( city);
	symbols.push_back("-stop"); 
	graph0->input( symbols.begin(), 1 );
      }


      

      suid0 = graph0->branches_map.find("MatchedVoterSUID");
      
      if (suid0==graph0->branches_map.end()) cout<<"ERROR"<<endl;

      s = suid0->second->branches_map.find(suid);
  
      if (s!= suid0->second->branches_map.end()){

    
      map<string,Node*>::iterator o = s->second->branches_map.find("OCCUPATION");
      if (o!=s->second->branches_map.end()){
	int percnt = 100/o->second->branches_map.size();

	  map<string,Node*>::iterator b = o->second->branches_map.begin();

	  for (;b!=o->second->branches_map.end();b++){

	
	    symbols.clear();
	    symbols.push_back("MatchedVoter1"); 
	    symbols.push_back("ElectionType"); 
	    symbols.push_back(type);
 
	    symbols.push_back("OCCUPATION"); 
	    symbols.push_back(b->first);
	    
	    symbols.push_back("-stop"); 
	    //graph0->input( symbols.begin(), percnt );

	    symbols.clear();
	    symbols.push_back("MatchedVoter1"); 
	    symbols.push_back("OCCUPATION"); 
	    symbols.push_back(b->first);
	    symbols.push_back("AGE"); 
	    symbols.push_back(age1);
	    
	    symbols.push_back("-stop"); 
	    graph0->input( symbols.begin(), percnt );
	   	    
	  }		
      }


      o = s->second->branches_map.find("EMPLOYER");
      if (o!=s->second->branches_map.end()){
	int percnt = 100/o->second->branches_map.size();

	  map<string,Node*>::iterator b = o->second->branches_map.begin();

	  for (;b!=o->second->branches_map.end();b++){

	
	    symbols.clear();
	    symbols.push_back("MatchedVoter1"); 
	    symbols.push_back("EMPLOYER"); 
	    symbols.push_back(b->first);
	    symbols.push_back("-stop"); 
	    graph0->input( symbols.begin(), percnt );
	  }
      }
      

      }

     
    }

  }  //getline

  cout<<"count= "<<count<<endl; 

  return 1;
  
}

//----------------------------------------
//
int read_voter_district_file(Node* graph0)
{
  string line,field;
  int count=0;
  int count1=0;

extern map<string,list<string> > voter_map1;
  

  ifstream datafile1;  datafile1.open("scr1.csv");  if(!datafile1.is_open()){cout<<"Error 1"<<endl;return 0;}
  //ifstream datafile1;  datafile1.open("il_districts_3.15.22.csv");  if(!datafile1.is_open()){cout<<"Error 1"<<endl;return 0;}
  //ifstream datafile1;  datafile1.open("scr.csv");  if(!datafile1.is_open()){cout<<"Error 1"<<endl;return 0;}

  getline(datafile1, line);  //skip first line



  string suid0="";
  string ct_type="";
  string cg_type="";
  string wd_type="";
  string aj_type="";
  string cb_type="";

  int missing =0;
  
  while (getline(datafile1, line)){
    //if(datafile1.eof()) break;

    count++;

    //if (count>1000000) break;

    int s1 =1;
    int s2 =0;

    s2=line.find("\",", s1); string suid =line.substr(s1,s2-s1); s1+=s2-s1+3;

    s2=line.find("\",", s1); string district_type =line.substr(s1,s2-s1); s1+=s2-s1+3;

    s2=line.find("\"", s1); string district_name =line.substr(s1,s2-s1); s1+=s2-s1+3;



    if (suid!=suid0){


      //if (ct_type"")
	{

	  count1++;
	  
	list<string>             symbols;
	  
	symbols.clear();
	symbols.push_back("CT_type"); 
	symbols.push_back(ct_type);
	symbols.push_back(wd_type);
	symbols.push_back(suid0);
	symbols.push_back("-stop"); 
	//graph0->input( symbols.begin(), 1 );


	symbols.clear();
	symbols.push_back("AJ_type"); 
	symbols.push_back(aj_type);
	//symbols.push_back(cb_type);
	symbols.push_back(suid0);
	symbols.push_back("-stop"); 
	//graph0->input( symbols.begin(), 1 );

	symbols.clear();
	symbols.push_back("*district county ward*"); 
	symbols.push_back(cg_type);
	symbols.push_back(cb_type);
	symbols.push_back(wd_type);
	symbols.push_back("-stop"); 
	//graph0->input( symbols.begin(), 5 );

	symbols.clear();
	symbols.push_back("*district ward*"); 
	symbols.push_back(cg_type);

	symbols.push_back(wd_type);
	symbols.push_back("-stop"); 
	//graph0->input( symbols.begin(), 5 );

	//cout<<cg_type<<" - "<<cb_type<<" - "<<wd_type<<endl;
	


	map<string,list<string> >::iterator v = voter_map1.find(suid0);

	if (v!=voter_map1.end()){

	  v->second.push_back(cg_type);
	  v->second.push_back(cb_type);
	  v->second.push_back(ct_type);

	}
	else{
	  //cout<<suid0<<endl;
	  missing++;
	}

	
	suid0=suid;
	ct_type="";
	wd_type="";
	aj_type="";
	cg_type="";
	cb_type="";


      }

    }

    if (district_type=="CT") ct_type=district_name;
    if (district_type=="WD") wd_type=district_name;     // ward

    if (district_type=="AJ") aj_type=district_name;
    //if (district_type=="CB") cb_type=district_name;     // county
    if (district_type=="CO") cb_type=district_name;     // county


    if (district_type=="CG") cg_type=district_name;    // congressional district



    if (district_type=="AA") district_type =     "Airport Authority District";		
    if (district_type=="AJ") district_type =     "Appellate Judicial District";		
    if (district_type=="AM") district_type =     "Ambulance District";			
    if (district_type=="AS") district_type =     "Assessment District";			
    if (district_type=="BD") district_type =     "Bonds District";				
    if (district_type=="BR") district_type =     "County Board of Review District";		
    if (district_type=="CB") district_type =     "County Board District";	
    if (district_type=="CC") district_type =     "Community College District";		
    if (district_type=="CD") district_type =     "Conservation District";			
    if (district_type=="CE") district_type =     "Cemetery District";			
    if (district_type=="CG") district_type =     "Federal Congressional District";		
    if (district_type=="CM") district_type =     "Community Building District";		
    if (district_type=="CO") district_type =     "County District";				
    if (district_type=="CS") district_type =     "College Sub District";			
    if (district_type=="CT") district_type =     "City District";				
    if (district_type=="CU") district_type =     "City District";				
    if (district_type=="CZ") district_type =     "College Board District";			
    if (district_type=="DD") district_type =     "Drainage District";			
    if (district_type=="EZ") district_type =     "Enterprise Zone District";		
    if (district_type=="FP") district_type =     "Fire Protection District";		
    if (district_type=="FR") district_type =     "Forest Preserve District";		
    if (district_type=="FZ") district_type =     "Flood Zone District";			
    if (district_type=="HP") district_type =     "Hospital District";			
    if (district_type=="JC") district_type =     "Judicial Circuit District";		
    if (district_type=="JS") district_type =     "Judicial Subcircuit District";		
    if (district_type=="LB") district_type =     "Library District";			
    if (district_type=="LC") district_type =     "Land Commission District";		
    if (district_type=="LE") district_type =     "State Legislative (Senate) District";     
    if (district_type=="LT") district_type =     "Lighting District";				       
    if (district_type=="LV") district_type =     "Levee District";					       
    if (district_type=="MA") district_type =     "Mass Transit District";				       
    if (district_type=="MD") district_type =     "Museum District";					       
    if (district_type=="MQ") district_type =     "Mosquito District";				       
    if (district_type=="MT") district_type =     "Multi-Township Assessor District";		       
    if (district_type=="N1") district_type =     "Other";						       
    if (district_type=="N2") district_type =     "Other";						       
    if (district_type=="N3") district_type =     "Other	";					       
    if (district_type=="P2") district_type =     "Precinct & Splits";				       
    if (district_type=="PC") district_type =     "Park Commissioner District";			       
    if (district_type=="PD") district_type =     "Proposed District";				       
    if (district_type=="PK") district_type =     "Park District";					       
    if (district_type=="PR") district_type =     "Precinct District";				       
    if (district_type=="RB") district_type =     "Regional Board fo Education District";		       
    if (district_type=="RC") district_type =     "River Conservancy District";			       
    if (district_type=="RD") district_type =     "Road District";					       
    if (district_type=="RE") district_type =     "State Representative District";			       
    if (district_type=="RI") district_type =     "Regional Superintendant of Schools District";	       
    if (district_type=="RQ") district_type =     "Rescue District";					       
    if (district_type=="RR") district_type =     "Recreational District";				       
    if (district_type=="RS") district_type =     "Educational Service Region District";		       
    if (district_type=="SA") district_type =     "Single Township Assessment District";		       
    if (district_type=="SC") district_type =     "School District";					       
    if (district_type=="SH") district_type =     "High School District";				       
    if (district_type=="SN") district_type =     "Sanitary District";				       
    if (district_type=="SP") district_type =     "Special Reporting District";			       
    if (district_type=="SS") district_type =     "Sub School District";				       
    if (district_type=="SU") district_type =     "Unified School District";				       
    if (district_type=="SV") district_type =     "Service Area District";
    if (district_type=="SW") district_type =     "Sewer District";			                                    
    if (district_type=="TC") district_type =     "Congressional Township District";	      
    if (district_type=="TN") district_type =     "Town District";			      
    if (district_type=="TW") district_type =     "Township District";		      
    if (district_type=="UN") district_type =     "Unincorporated Areas District";	      
    if (district_type=="UT") district_type =     "Utility District";		      
    if (district_type=="VL") district_type =     "Village District";		      
    if (district_type=="WD") district_type =     "Ward District";			      
    if (district_type=="WR") district_type =     "Water Reclamation District";	      
    if (district_type=="WS") district_type =     "Watershed District";		      
    if (district_type=="WT") district_type =     "Water District";
    						 
						 
    /*						 
    cout<< suid<<endl;				 
    cout<<district_type<<endl;			 
    cout<<district_name<<endl<<endl;		 
    */

   list<string>             symbols;
	  
    symbols.clear();
    symbols.push_back("district_type"); 
    symbols.push_back(district_type);
    symbols.push_back(district_name);
    symbols.push_back("-stop"); 
    graph0->input( symbols.begin(), 1 );

    symbols.clear();
    symbols.push_back("district_name"); 
    symbols.push_back(district_name);
    symbols.push_back("-stop"); 
    graph0->input( symbols.begin(), 1 );



  }

  cout<<count<<" -- "<<count1<<"  -   "<<missing<<endl;


  /*
 list<string> s_e;
   
  list<Node>::iterator b =graph0->branches.begin();
    
  for ( ;b!=graph0->branches.end();b++){

    cout<<endl<<"--- ";      b->output1(2,0, s_e);
   cout<<endl<<"--- ";      b->output1(3,0, s_e);
   cout<<endl<<"--- ";      b->output1(4,0, s_e);
   cout<<endl<<"--- ";      b->output1(5,0, s_e);
  }

  */


  
  return 1;
}
  //----------------------------------------
//
int read_suid_file1(Node* graph0)
{
  // graph0 = aurora1.txt
  
  string line,field;
  int count=0;
  int count1=0;
  
  map<string,Node*>::iterator i = graph0->branches_map.find("CITY OF AURORA");

  Node* suids = i->second;

   i = graph0->branches_map.find("ReadVoterHistory1");

  Node* suids_history = i->second;

  i = graph0->branches_map.find("MatchedVoterSUID");

  Node* matched_suids = i->second;

  
  ifstream datafile1;  datafile1.open("il_suid1.txt");  if(!datafile1.is_open()){cout<<"Error 1"<<endl;return 0;}

  while (getline(datafile1, line)){
    if(datafile1.eof()) break;

    count++;

 

    int s1 =0;
    int s2 =0;

    s2=line.find(",", s1); string suid = field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string last = field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string first= field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string middle = field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string city = field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string age = field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string sex = field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string phone = field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string number = field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string street = field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string email = field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string regdate = field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string lastdate = field=line.substr(s1,s2-s1); s1+=s2-s1+1;

    //cout<<suid<<endl;
    //cout<<suids->branches_map.size()<<endl;

    i = suids->branches_map.find(suid);

    if (i!= suids->branches_map.end() && i->second->branches_map.size()>0){

      map<string,Node*>::iterator w = i->second->branches_map.begin();   // ward


 
      cout<< w->first <<"|"<<
	last   <<"|"<<
	first  <<"|"<<
	middle <<"|"<<
	city   <<"|"<<
	age    <<"|"<<
	phone  <<"|"<<
	number <<"|"<<
	street <<"|"<<
	email  <<"|"<<
	suid  <<"|"<<
	regdate<<"|"<<
	lastdate<<"|";


  

      int rep=0;
      int dem=0;
      int non=0;
      int grn=0;
      int gp=0;
      int ge=0;
      int ce=0;
      int cp=0;
      int ne=0;
      int sp=0;
      int se=0;

 	
      
      map<string,Node*>::iterator h= suids_history->branches_map.find(suid);

      if (h!= suids_history->branches_map.end() ){

	map<string,Node*>::iterator h1;

	h1=h->second->branches_map.find("REPUBLICAN");
	if (h1!=h->second->branches_map.end()) rep = h1->second->dollars;

	h1=h->second->branches_map.find("DEMOCRATIC");
	if (h1!=h->second->branches_map.end())  dem= h1->second->dollars;

	h1=h->second->branches_map.find("NONPARTISAN");
	if (h1!=h->second->branches_map.end())  non= h1->second->dollars;

	h1=h->second->branches_map.find("GP");
	if (h1!=h->second->branches_map.end())  gp= h1->second->dollars;

	h1=h->second->branches_map.find("GE");
	if (h1!=h->second->branches_map.end())  ge= h1->second->dollars;

	h1=h->second->branches_map.find("CP");
	if (h1!=h->second->branches_map.end())  cp= h1->second->dollars;

	h1=h->second->branches_map.find("CE");
	if (h1!=h->second->branches_map.end()) ce = h1->second->dollars;

	h1=h->second->branches_map.find("NE");
	if (h1!=h->second->branches_map.end()) ne = h1->second->dollars;

	h1=h->second->branches_map.find("SE");
	if (h1!=h->second->branches_map.end()) se = h1->second->dollars;

	h1=h->second->branches_map.find("SP");
	if (h1!=h->second->branches_map.end()) sp = h1->second->dollars;

	h1=h->second->branches_map.find("GREEN");
	if (h1!=h->second->branches_map.end()) grn = h1->second->dollars;
	
      }


     cout<< rep<<"|"<<
	   dem <<"|"<<
	   non <<"|"<<
	   grn <<"|"<<
	   ge <<"|"<<
	   gp <<"|"<<
	   ce <<"|"<<
	   cp <<"|"<<
	   se <<"|"<<
	   sp <<"|"<<
       ne; // <<endl;      



     string employers;
      
     map<string,Node*>::iterator c= matched_suids->branches_map.find(suid);

     if (c!= matched_suids->branches_map.end() ){

       map<string,Node*>::iterator e =c->second->branches_map.find("EMPLOYER");

       if (e!=c->second->branches_map.end() ){

	 map<string,Node*>::iterator e1 =e->second->branches_map.begin();

	 for (;e1!=e->second->branches_map.end();e1++){

	   if (employers!="") employers +=":";
			      
	   employers += e1->second->symbol;	

	   list<string>             symbols;
	   symbols.clear();
	   symbols.push_back("CityVotersEmployers"); 
	   symbols.push_back(e1->second->symbol);
	   symbols.push_back("-stop"); 
	   graph0->input( symbols.begin(), 1 );


	 }
	 
       }
     }
    cout<<"|"<<employers;


    string occupations;
      
     c= matched_suids->branches_map.find(suid);

     if (c!= matched_suids->branches_map.end() ){

       map<string,Node*>::iterator e =c->second->branches_map.find("OCCUPATION");

       if (e!=c->second->branches_map.end() ){

	 map<string,Node*>::iterator e1 =e->second->branches_map.begin();

	 for (;e1!=e->second->branches_map.end();e1++){

	   if (occupations!="") occupations +=":";
			      
	   occupations += e1->second->symbol;	

	   list<string>             symbols;
	   symbols.clear();
	   symbols.push_back("CityVotersOccupations"); 
	   symbols.push_back(e1->second->symbol);
	   symbols.push_back("-stop"); 
	   graph0->input( symbols.begin(), 1 );


	 }
	 
       }
     }
     cout<<"|"<<occupations;   //<<endl;



     string cmtes="";
     
     int dollars_cmte=0;

     c= matched_suids->branches_map.find(suid);

     if (c!= matched_suids->branches_map.end() ){

       map<string,Node*>::iterator e =c->second->branches_map.find("CMTE_ID");

       if (e!=c->second->branches_map.end() ){

	 dollars_cmte= e->second->dollars;

	 map<string,Node*>::iterator e1 =e->second->branches_map.begin();

	 for (;e1!=e->second->branches_map.end();e1++){

	   if (cmtes!="") cmtes +=":";
	   
	   cmtes += e1->second->symbol;
	 }
       }
     }

     cout<<"|"<<dollars_cmte<<"|"<<cmtes  <<endl;
    
     
    }   // output if-then

      

      
  }

  return 0;    
}

//----------------------------------------------------------------------
int read_voter_history_file1(Node* graph0)
{
  
  string line,field;
  int count=0;
  int count1=0;

  map<string,Node*>::iterator suids = graph0->branches_map.find("CITY OF AURORA");

  if (suids==graph0->branches_map.end()) cout<<"ERROR"<<endl;
  

  
  ifstream datafile1;  datafile1.open("il_votehistory_3.15.33.csv");  if(!datafile1.is_open()){cout<<"Error 1"<<endl;return 0;}

  while (getline(datafile1, line)){
    if(datafile1.eof()) break;

    count++;

    //if (count>1000000) break;
    int s1 =1;
    int s2 =0;

    s2=line.find("\",", s1); string suid = field=line.substr(s1,s2-s1); s1+=s2-s1+3;

    s2=line.find("\",", s1); string date = field=line.substr(s1,s2-s1); s1+=s2-s1+3;

    int year1 = atoi(date.substr(date.size()-4,4).c_str());
    //cout<<year1<<endl;
    
    s2=line.find("\",", s1); string type = field=line.substr(s1,s2-s1); s1+=s2-s1+3;

    s2=line.find("\"", s1); string party = field=line.substr(s1,s2-s1); s1+=s2-s1+3;

    //cout<<suid<<" "<<date<<" "<<type<<" "<<party<<endl;


    

  map<string,Node*>::iterator i = suids->second->branches_map.find(suid);

  if (i!= suids->second->branches_map.end() ){
  
            list<string>             symbols;

    symbols.push_back("ReadVoterHistory2"); 
    symbols.push_back("election_type");
    symbols.push_back(type);
    symbols.push_back("-stop"); 
    graph0->input( symbols.begin(), 1 );


       symbols.clear();
    symbols.push_back("ReadVoterHistory3"); 
    symbols.push_back("party");
    symbols.push_back(party);
    symbols.push_back("-stop"); 
    graph0->input( symbols.begin(), 1 );



	  
    symbols.clear();
    symbols.push_back("ReadVoterHistory1"); 
    symbols.push_back(suid);
    symbols.push_back(type);
    symbols.push_back("-stop"); 
    graph0->input( symbols.begin(), 1 );

     symbols.clear();
    symbols.push_back("ReadVoterHistory1"); 
    symbols.push_back(suid);
    symbols.push_back(party);
    symbols.push_back("-stop"); 
    graph0->input( symbols.begin(), 1 );

   
  }

  }

  /*
  list<Node>::iterator b =graph0.branches.begin();
    for ( ;b!=graph0.branches.end();b++){
  list<string> s_e;
    cout<<endl<<"--- ";      b->output1(2,0, s_e);
   cout<<endl<<"--- ";      b->output1(3,0, s_e);
   cout<<endl<<"--- ";      b->output1(4,0, s_e);
    }
  */
  return 0;
}



//----------------------------------------------------------------------
int read_voter_history_file2( map<string,list<int> >* suid_map )
{
  
  string line,field;
  int count=0;
  int count1=0;

  Node graph0;
  
  //  map<string,Node*>::iterator suids = graph0->branches_map.find("CITY OF AURORA");

  //if (suids==graph0->branches_map.end()) cout<<"ERROR"<<endl;
  



  // ----- SUID filter file

  //map<string,list<int> > suid_map;
  
  //ifstream datafile2;  datafile2.open("aj3_suids.txt");  if(!datafile2.is_open()){cout<<"Error 2"<<endl;return 0;}
  //ifstream datafile2;  datafile2.open("aurora_suids.txt");  if(!datafile2.is_open()){cout<<"Error 2"<<endl;return 0;}
  //ifstream datafile2;  datafile2.open("aurora_john_suids.txt");  if(!datafile2.is_open()){cout<<"Error 2"<<endl;return 0;}
  ifstream datafile2;  datafile2.open("kendall_vbm_suids.txt");  if(!datafile2.is_open()){cout<<"Error 2"<<endl;return 0;}


  //getline(datafile1, line);  //  1st line
 
  while ( getline(datafile2, line) ){

    list<int> datalist;
    
    suid_map->insert(pair<string,list<int>>(line,datalist));

    count++;
    
  }


  cout<<"suid "<<count<<endl;

  //int i = 1; if (i) return 1;
  
  // ----- SUID filter file




  string suid0="";

  int	num_repub=0;
  int	num_dem=0;
  int	num_ge=0;
  int	num_gp=0;
  int	num_ce=0;
  int	num_cp=0;

  

  count=0;
  
  ifstream datafile1;  datafile1.open("il_votehistory_3.15.33_sort.csv");  if(!datafile1.is_open()){cout<<"Error 1"<<endl;return 0;}

  while (getline(datafile1, line)){
    if(datafile1.eof()) break;

    count++;

    //if (count>1000000) break;
    int s1 =1;
    int s2 =0;

    s2=line.find("\",", s1); string suid = field=line.substr(s1,s2-s1); s1+=s2-s1+3;

    s2=line.find("\",", s1); string date = field=line.substr(s1,s2-s1); s1+=s2-s1+3;

    int year1 = atoi(date.substr(date.size()-4,4).c_str());
    //cout<<year1<<endl;
    
    s2=line.find("\",", s1); string type = field=line.substr(s1,s2-s1); s1+=s2-s1+3;

    s2=line.find("\"", s1); string party = field=line.substr(s1,s2-s1); s1+=s2-s1+3;

    //cout<<suid<<" "<<date<<" "<<type<<" "<<party<<endl;


    

    map<string,list<int>>::iterator i = suid_map->find(suid);

  if (i!= suid_map->end() )
    {

      if (suid!= suid0){

	map<string,list<int>>::iterator ii = suid_map->find(suid0);
	
	count1++;
	suid0=suid;


	if (ii != suid_map->end()){           // skip first time thru suid0=""
	  
	  ii->second.push_back(num_cp);
	  ii->second.push_back(num_ce);
	  ii->second.push_back(num_gp);
	  ii->second.push_back(num_ge);
	  ii->second.push_back(num_dem);
	  ii->second.push_back(num_repub);

	//cout<<suid<<" "<<num_repub<<"  "<<num_dem<<" "<<num_ge<<" "<<num_gp<<" "<<num_ce<<" "<<num_cp<<endl;


	   list<string>             symbols;
	   symbols.clear();
	   symbols.push_back(to_string(num_ge)); 
	   symbols.push_back(to_string(num_cp+num_ce));
	   //symbols.push_back(to_string(num_gp));
	   symbols.push_back("-stop"); 
	   graph0.input( symbols.begin(), 1 );





	}

	
	num_repub=0;
	num_dem=0;
	num_ge=0;
	num_gp=0;
	num_ce=0;
	num_cp=0;


      }

      if (party=="REPUBLICAN") num_repub++;
      if (party=="DEMOCRATIC") num_dem++;

      if (type=="GE") num_ge++;
      if (type=="GP") num_gp++;
      if (type=="CE") num_ce++;
      if (type=="CP") num_cp++;
      if (type=="SE") num_ce++;
      if (type=="SP") num_cp++;





    
  }

  }


  cout<<"cnt1,2 "<<count<<"  "<<count1<<endl;

  

  list<Node>::iterator b =graph0.branches.begin();
    for ( ;b!=graph0.branches.end();b++){
  list<string> s_e;
  cout<<endl<<"--- ";      b->output1(2,0, s_e);
  //cout<<endl<<"--- ";      b->output1(3,0, s_e);
  //cout<<endl<<"--- ";      b->output1(4,0, s_e);
    }



    // --------------------------------- make aurora matrix


    Node graph1;
  
    for (int i=30;i!=-1;i--){

      cout<<i<<endl;

      list<Node>::iterator b =graph0.branches.begin();
      for ( ;b!=graph0.branches.end();b++){
    
	int count = 0;

	map<string,Node*>::iterator b1 =b->branches_map.find(to_string(i));

	if (b1 != b->branches_map.end()) count = b1->second->dollars;


	list<string>             symbols;
	symbols.push_back(b->symbol); 
	symbols.push_back("-stop"); 
	graph1.input( symbols.begin(), count );

      }

      graph1.roll_dollars(6);

    }  // for i 1->25

    b =graph1.branches.begin();
    for ( ;b!=graph1.branches.end();b++){
      list<string> s_e;
      cout<<"---\t";      b->output1(1,0, s_e);
      
    }
	    

    // --------------------------------- make aurora matrix

    



    
  return 0;
}




//----------------------------------------
//
int read_voter_file(Node* graph0)
{
  string line,field;
  int count=0;
  int count1=0;

 

//----------------------------------------------------------------------------  missing 680

  map<string,string> missing680;
  
  //ifstream datafile3;  datafile3.open("2020VBMGPGE.xlsx - 2020 VBM GP.csv");  if(!datafile3.is_open()){cout<<"Error 1"<<endl;return 0;}
  ifstream datafile3;  datafile3.open("Kane2020GE_vbm_total.csv");
  

 getline(datafile3, line);  // skip header
 

 
 while (getline(datafile3, line)){
   if(datafile3.eof()) break;

   int s1 =0;
   int s2 =0;

   string temp;

   s2=line.find(",", s1);  temp =line.substr(s1,s2-s1); s1+=s2-s1+1;
   s2=line.find(",", s1);  temp =line.substr(s1,s2-s1); s1+=s2-s1+1;
   s2=line.find(",", s1);  temp =line.substr(s1,s2-s1); s1+=s2-s1+1;

   s2=line.find(",", s1); string suid =line.substr(s1,s2-s1); s1+=s2-s1+1;

   //if (suid=="") cout<<"here"<<endl;

   if (suid!="") missing680.insert(pair<string,string>(suid, suid));
   
 }


 cout<<"missing "<<missing680.size()<<endl;

//----------------------------------------------------------------------------  missing 680





  //--------------------------------------------------- Kane County VBM

  int count2 =0; 
  int novbm=0;
  
  map<string, string > kane_vbm_voters;


  
  ifstream datafile2;  datafile2.open("2020VBMGPGE.xlsx - 2020 VBM GP.csv");  if(!datafile2.is_open()){cout<<"Error 1"<<endl;return 0;}
  //ifstream datafile2;  datafile2.open("2020VBMGPGE.xlsx - 2020 VBM GE.csv");  if(!datafile2.is_open()){cout<<"Error 1"<<endl;return 0;}
  //ifstream datafile2;  datafile2.open("Kane2020GE_vbm_total.csv");
  if(!datafile2.is_open()){cout<<"Error 1"<<endl;return 0;}


 getline(datafile2, line);  // skip header
 

   while (getline(datafile2, line)){
    if(datafile2.eof()) break;

    count2++;
    
    int s1 =0;
    int s2 =0;

    string temp;
    
    /*
    s2=line.find(",", s1);  temp =line.substr(s1,s2-s1); s1+=s2-s1+1;
    s2=line.find(",", s1);  temp =line.substr(s1,s2-s1); s1+=s2-s1+1;
    s2=line.find(",", s1);  temp =line.substr(s1,s2-s1); s1+=s2-s1+1;
    */
    
    s2=line.find(",", s1); string suid =line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1);  string vbm_app =line.substr(s1,s2-s1); s1+=s2-s1+1;
    s2=line.find(",", s1);  temp =line.substr(s1,s2-s1); s1+=s2-s1+1;
    s2=line.find(",", s1);  temp =line.substr(s1,s2-s1); s1+=s2-s1+1;
    s2=line.find(",", s1); string vbm_rcv =line.substr(s1,s2-s1); s1+=s2-s1+1;

    //cout<<suid<<"  "<<vbm_rcv<<endl;

    //cout<<count++<<"  "<<vbm_rcv<<"--"<<vbm_rcv.size()<<endl;

    map<string, string >::iterator k = kane_vbm_voters.find(suid);

    if (k!=kane_vbm_voters.end()) {cout<<"duplicate "<<suid<<endl; continue;}   // blank SUID

    //if (vbm_app!="8/31/2020" ) { continue;} 
    //if (vbm_app=="8/31/2020" ) { continue;} 

    //if (vbm_rcv=="" ) { novbm++; /*cout<<novbm<<endl;*/ continue;} 
    //if (vbm_rcv.size()==1 ) { novbm++; /*cout<<novbm<<endl;*/ continue;} 
    
    //kane_vbm_voters.insert(pair<string,string>(suid,suid));

    map<string, string >::iterator m = missing680.find(suid);

    //if (m!=missing680.end()) kane_vbm_voters.insert(pair<string,string>(suid,suid));
    if (m==missing680.end()) kane_vbm_voters.insert(pair<string,string>(suid,suid));
    
    //kane_vbm_voters.insert(pair<string,string>(suid,suid));


   }

   cout<<"count2 "<<count2<<endl;

   cout<<"Kane map size= "<< kane_vbm_voters.size()<<endl;
   

  //--------------------------------------------------- Kane County VBM

  
extern map<string,list<string> > voter_map1;


  ifstream datafile1;  datafile1.open("il_voters_3.15.22.csv");  if(!datafile1.is_open()){cout<<"Error 1"<<endl;return 0;}


  //getline(datafile1, line);  //skip first line



  multimap<string,list<string> > voter_map;
  //map<string,list<string> > voter_map;

  int skip_count=0; 
  
  while (getline(datafile1, line)){
    if(datafile1.eof()) break;

    count++;

    //if (count>2000000) break;

    int s1 =1;
    int s2 =0;

    s2=line.find("\",", s1); string suid =line.substr(s1,s2-s1); s1+=s2-s1+3;


	for (int i =0; i!= suid.size();i++){
	  suid[i] = toupper(suid[i]);
	}

  //--------------------------------------------------- Kane County VBM
    map<string, string >::iterator k = kane_vbm_voters.find(suid);

    if (k==kane_vbm_voters.end()) {skip_count++; continue;}
    //if (k!=kane_vbm_voters.end()) {skip_count++; continue;}
  //--------------------------------------------------- Kane County VBM
	
    
    s2=line.find("\",", s1); string jurisdiction =line.substr(s1,s2-s1); s1+=s2-s1+3;

    s2=line.find("\"", s1); string last_name =line.substr(s1,s2-s1); s1+=s2-s1+3;

    s2=line.find("\"", s1); string first_name =line.substr(s1,s2-s1); s1+=s2-s1+3;

    string t1;
    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;
    s2=line.find("\"", s1); string suffix =line.substr(s1,s2-s1); s1+=s2-s1+3;
    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;

    s2=line.find("\"", s1); string age =line.substr(s1,s2-s1); s1+=s2-s1+3;

    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;
    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;
    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;

    s2=line.find("\"", s1); string telephone =line.substr(s1,s2-s1); s1+=s2-s1+3;

    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;
    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;
    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;
    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;
    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;
    //s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;

     s2=line.find("\"", s1); string address =line.substr(s1,s2-s1); s1+=s2-s1+3;
     s2=line.find("\"", s1); string city    =line.substr(s1,s2-s1); s1+=s2-s1+3;
     s2=line.find("\"", s1); string state   =line.substr(s1,s2-s1); s1+=s2-s1+3;
     s2=line.find("\"", s1); string zip     =line.substr(s1,s2-s1); s1+=s2-s1+3;


    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;
    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;
    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;
    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;
    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;
    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;
    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;
    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;
    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;
    s2=line.find("\"", s1); t1 =line.substr(s1,s2-s1); s1+=s2-s1+3;


    s2=line.find("\"", s1); string email =line.substr(s1,s2-s1); s1+=s2-s1+3;


    transform(last_name.begin(), last_name.end(), last_name.begin(), ::toupper); 
    transform(first_name.begin(), first_name.end(), first_name.begin(), ::toupper); 

    list<string> fields;
    /*
    fields.push_back(last_name);
    fields.push_back(first_name);
    fields.push_back(address);
    fields.push_back(city);
    fields.push_back(zip+","+telephone);
    //fields.push_back(telephone);
    fields.push_back(email);
    */
    fields.push_back(age);
   fields.push_back(jurisdiction);

   /*
   fields.push_back(city);

    fields.push_back(address);
    fields.push_back(state);
    fields.push_back(zip);
   */
    

    //voter_map.insert(pair<string, list<string> >(first_name+" "+last_name, fields)  );


    map<string,list<string> >::iterator v= voter_map1.find(suid);

    if (v!=voter_map1.end()) cout<< suid<<endl;

    //cout<<rand()%100<<endl;
    
     voter_map1.insert(pair<string, list<string> >(suid, fields)  );
     //if ((rand()%100) < 25) voter_map1.insert(pair<string, list<string> >(suid, fields)  );
    
   //cout<<suid<<" "<< jurisdiction<< " " << last_name<<"  "<<address<<"  "<<city<<"  "<<state<<" "<<zip<<"   "<<telephone<<"  "<< email<<endl;



	list<string>             symbols;
	  
	symbols.clear();
	symbols.push_back("first_name"); 
	symbols.push_back(first_name); 
	symbols.push_back("-stop"); 
	graph0->input( symbols.begin(), 1 );


	symbols.clear();
	symbols.push_back("last_name"); 
	symbols.push_back(last_name); 
	symbols.push_back("-stop"); 
	graph0->input( symbols.begin(), 1 );



	symbols.clear();
	symbols.push_back("suffix"); 
	symbols.push_back(suffix); 
	symbols.push_back("-stop"); 
	graph0->input( symbols.begin(), 1 );


	




	
  }

  cout<<count<<endl;


  cout<<voter_map.size()<<endl;
  cout<<voter_map1.size()<<endl;


  cout<<"skip count= "<<skip_count<<endl;




  /*
  
  ifstream datafile3;  datafile3.open("2020VBMGPGE.xlsx - 2020 VBM GP.csv");  if(!datafile3.is_open()){cout<<"Error 1"<<endl;return 0;}
  //ifstream datafile3;  datafile3.open("Kane2020GE_vbm_total.csv");
  

 getline(datafile3, line);  // skip header
 
 int missing =0;
 
 while (getline(datafile3, line)){
   if(datafile3.eof()) break;

   int s1 =0;
   int s2 =0;

   string temp;
 
   //s2=line.find(",", s1);  temp =line.substr(s1,s2-s1); s1+=s2-s1+1;
   //s2=line.find(",", s1);  temp =line.substr(s1,s2-s1); s1+=s2-s1+1;
   //s2=line.find(",", s1);  temp =line.substr(s1,s2-s1); s1+=s2-s1+1;
 
   s2=line.find(",", s1); string suid =line.substr(s1,s2-s1); s1+=s2-s1+1;

   map<string, string >::iterator k = kane_vbm_voters.find(suid);
   if (k==kane_vbm_voters.end()) {
     missing++;
     cout<<suid<<endl;
   }

    
 }


 cout<<"missing "<<missing<<endl;

*/




   
  /*
  //--------------------------------------------------- read in David Cannon csv files


  //ifstream datafile2;  datafile2.open("Dupage.csv");  if(!datafile2.is_open()){cout<<"Error 1"<<endl;return 0;}
 ifstream datafile2;  datafile2.open("Boone.csv");  if(!datafile2.is_open()){cout<<"Error 1"<<endl;return 0;}

 getline(datafile2, line);   // save first line
 string line0= line;         // save first line
 
  while (getline(datafile2, line)){
    if(datafile2.eof()) break;

    line0=line;
    
    count1++;

    //cout<<line<<endl;

    int s1 =1;
    int s2 =0;

    s2=line.find(",", s1); string f1 =line.substr(s1,s2-s1); s1+=s2-s1+1;

    s2=line.find(",", s1); string f2 =line.substr(s1,s2-s1); s1+=s2-s1+1;
    s2=line.find(",", s1); string f3 =line.substr(s1,s2-s1); s1+=s2-s1+1;
    s2=line.find(",", s1); string f4 =line.substr(s1,s2-s1); s1+=s2-s1+1;
    s2=line.find(",", s1); string f5 =line.substr(s1,s2-s1); s1+=s2-s1+1;
    s2=line.find(",", s1); string f6 =line.substr(s1,s2-s1); s1+=s2-s1+1;
    s2=line.find(",", s1); string f7 =line.substr(s1,s2-s1); s1+=s2-s1+1;
    s2=line.find(",", s1); string f8 =line.substr(s1,s2-s1); s1+=s2-s1+1;
    s2=line.find(",", s1); string f9 =line.substr(s1,s2-s1); s1+=s2-s1+1;
    s2=line.find(",", s1); string f10 =line.substr(s1,s2-s1); s1+=s2-s1+1;
    s2=line.find(",", s1); string f11 =line.substr(s1,s2-s1); s1+=s2-s1+1;
    s2=line.find(",", s1); string f12 =line.substr(s1,s2-s1); s1+=s2-s1+1;

    transform(f3.begin(), f3.end(), f3.begin(), ::toupper); 
    transform(f5.begin(), f5.end(), f5.begin(), ::toupper); 
    transform(f4.begin(), f4.end(), f4.begin(), ::toupper); 
    transform(f6.begin(), f6.end(), f6.begin(), ::toupper); 

    
    //cout<<f3<<" "<<f5<<endl;

    //string vname = f4+" "+f6;
    string vname = f3+" "+f5;

    cout<<vname<<endl;
    
    multimap< string, list<string> >::iterator v = voter_map.find(vname);

    //cout<<line<<"test";
    //cout<<endl;
    if (v== voter_map.end()) cout<<line<<endl;
   if (v!= voter_map.end()){


      pair<multimap<string,list<string> >::iterator, multimap<string,list<string> >::iterator > range;
      range = voter_map.equal_range(vname);
    
      for (v=range.first; v!=range.second; ++v){

	int pos;
	if ((pos =line0.find('\n')) != string::npos) line.erase(pos);
	
	cout<<line0.substr(0,line0.size()-1) +",";
	
	list<string>::iterator l = v->second.begin();
	for(;l!=v->second.end();l++){
	  cout<<*l<<",";
	}
      cout<<endl;      

      }
      //cout<<endl;
    }
  }

  cout<<count1<<endl;
  
  //--------------------------------------------------- read in David Cannon csv files
  */





  

  return 0;}

//----------------------------------------
//


map<string,list<string> > voter_map1;

map<string,list<int> > suid_map;


int main()
{

  Node graph0;

  graph0.symbol="graph0";

  
  //------------------------------------------ Underwood / Trump



  read_voter_file(&graph0);
  
  read_voter_district_file(&graph0);


  read_voter_history_file3(&graph0);

  list<string> s_e;
   
  list<Node>::iterator b =graph0.branches.begin();
    
  for ( ;b!=graph0.branches.end();b++){

    cout<<endl<<"--- ";      b->output1(1,0, s_e);
    cout<<endl<<"--- ";      b->output1(2,0, s_e);
   cout<<endl<<"--- ";      b->output1(3,0, s_e);
  cout<<endl<<"--- ";      b->output1(4,0, s_e);
 cout<<endl<<"--- ";      b->output1(5,0, s_e);
 

  }



  
  //main2(&graph0);         // cat date_age.txt |./a.out> scr.txt


   
  //------------------------------------------ Underwood / Trump



  //read_voter_file(&graph0);
    
  //read_voter_history_file1(&graph0);

  //read_voter_history_file2(&suid_map);


  //main1();

  //read_voter_district_file(&graph0);

  

  //main2(&graph0);         // read in data from command line into graph0


 
  //read_voter_history_file1(&graph0);
 
  //read_suid_file(&graph0);    //match suid's to NAME's
  
  //read_suid_file1(&graph0);    

    /*
    */

  
   


 

    /*
  read_voter_history_file(&graph0);


 


  list<string> s_e;
   
  list<Node>::iterator b =graph0.branches.begin();
    
  for ( ;b!=graph0.branches.end();b++){

    cout<<endl<<"--- ";      b->output1(2,0, s_e);
   cout<<endl<<"--- ";      b->output1(3,0, s_e);
   cout<<endl<<"--- ";      b->output1(4,0, s_e);
    //cout<<endl<<"--- ";      b->output1(5,0, s_e);
    //cout<<endl<<"--- ";      b->output1(6,0, s_e);

  }

 */  


 

  
  
  
  //roll_array(&graph0, "TRANSACTION_TP", "TRANSACTION_DT");
}
