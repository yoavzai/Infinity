#include <iostream> 

using namespace std; 
  
// base class 
class Vehicle  
{ 
  public: 
    Vehicle() 
    { 
      cout << "This is a Vehicle" << endl; 
    } 
    ~Vehicle()
    {
        cout << "Vehicle dtor\n";
    }
}; 
class fourWheeler: public Vehicle 
{  public: 
    fourWheeler() 
    { 
      cout<<"Objects with 4 wheels are vehicles"<<endl; 
    } 
}; 
// sub class derived from two base classes 
class Car: public fourWheeler{ 
   public: 
     Car() 
     { 
       cout<<"Car has 4 Wheels"<<endl; 
     }
     virtual ~Car()
     {
         cout << "Car dtor\n";
     }
}; 
  
// main function 
int main() 
{
    Car car;

    return 0;    
}