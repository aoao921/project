#include <list>
#include <iostream>
using namespace std;
int main()
{
    
    list <int> c1;
    list <int>::iterator c1_Iter=c1.begin();
   
    //c1.insert(c1_Iter, 4, 100);
	 list <int>::iterator c1_Iter2=c1.end();
   
    c1.push_back(10);
    c1.push_back(20);
    c1.push_back(30); 
    c1.push_back(40); 
    c1.push_back(50); 
    c1.push_back(60); 

    cout << "c1 =";
	int p=1;
       for (c1_Iter = c1.begin(); c1_Iter != c1.end(); c1_Iter++){
       	if(p%2==0){
       		c1_Iter=c1.erase(c1_Iter);//指向下一个 地址 
       		c1_Iter--; 
		   }	
    
    	p++;
	}
  
    for (c1_Iter = c1.begin(); c1_Iter != c1.end(); c1_Iter++){
    	  cout << " " << *c1_Iter;
    	  //c1_Iter=c1.erase(c1_Iter);
    	//  c1_Iter--;
	}
      
    c1.reverse();//反向
  
}
