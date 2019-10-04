/**
* @file prob3.cpp
* @brief This Cpp file is a program used to find the maximum length of a subarray with a given sum..
*
* @author Prathamesh Katkar
*
* @date 04/09/2019
*/


#include <iostream>
#include <unordered_map>

using namespace std;
/**
* This method main() will be the driver program for the class.
* @param int argc, char const *argv[]
* @date 04/09/2019
*/
int main(int argc, char const *argv[])
{
	cout<<"Enter the length of the Array."<<endl;
	int length;
	cin >> length;
	cout<<"Enter the Arrsy."<<endl;
	int array[length];
	int cumulative_sum=0;
	unordered_map<int,int> hashmap;
	for (int i=0;i<length;i++){
		cin >> array[i];
		cumulative_sum += array[i];
		hashmap[cumulative_sum] = i;
	}
	cout<<"Enter the sum to be searched for."<<endl;
	int n;
	cin >> n;
	int begin_index,end_index;
	int max_length=0;
	int checksum=0;
	for (int j=0;j<length;j++){
		if (hashmap.find(checksum+n)!=hashmap.end()){
			int temp=hashmap[checksum+n]-j+1;
			if (temp>max_length){
				max_length=temp;
				begin_index=j;
				end_index=hashmap[checksum+n];
			}
		}
		checksum+=array[j];
	}

	if (max_length!=0){
		cout<<"Length of the longest subarray is "<<max_length<<"."<<endl;
		cout<<"Index from "<<begin_index<<" to "<<end_index<<".\n";
	}
	else
		cout<<"Subarray not found."<<endl;
	return 0;
}
