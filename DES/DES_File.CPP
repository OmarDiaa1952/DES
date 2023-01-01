#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// you should path the direction of file by correctly way
string storeData(string fileName)
{
  string str , output;
  ifstream file(fileName);
  if (!file)
  {
    cout << "the file failed to open, please enter the correct FileName " << endl;
    return 0;
  }
  while (getline(file, str))
  {
    // Line contains string of length > 0 then save it in vector
    if (str.size() > 0)
        output += str ;
  }
  return output ; 
}
int main(){
string x = storeData("C:\\Users\\ahmed abdallah\\Downloads\\test - Copy.txt");
cout<<x;

    return 0 ;
}