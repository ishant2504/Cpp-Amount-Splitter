#include<iostream>
#include<unordered_map>
#include<set>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
class person_comp{
	public:
	bool operator()(const pair<string,int>&p1, const pair<string, int>&p2)
	{
		if(p1.second==p2.second)
		return p1.first<p2.first;
		
		return p1.second<p2.second;
	}
};
class transaction{
	public:
		string dp,cp;
		int amt;
		
		transaction(string dp, string cp, int amt)
		{
			this->dp=dp;
			this->cp=cp;
			this->amt=amt;
		}
};

bool vec_comp(const transaction& t1, const transaction& t2)
{
	return(t1.dp < t2.dp);
}
int main()
{
	int num_t;//number of transactions
	cout<<"Enter number of transactions: ";
	cin>>num_t;
	
	unordered_map<string,int>record;
	
	//when p1 has to pay amt to p2
	string p1,p2;
	int amt;
	
	//fetching transaction data
	int tn=1; // transaction number
	while(num_t--)
	{
		cout<<"Enter Transaction "<<tn++<<endl;
		cout<<"Payee's name: ";
		cin.ignore();
		getline(cin, p1);
		
		cout<<"Reciever's name: ";
		getline(cin, p2);
		
		cout<<"Enter amt: ";
		cin>>amt;
		
		record[p1]-=amt;
		record[p2]+=amt;
		if(record[p1]==0)
		record.erase(p1);
		
		if(record[p2]==0)
		record.erase(p2);
	}
	
	set<pair<string, int>,person_comp>finalrec;
	for(auto &p: record)
	{
		finalrec.insert({p.first, p.second});
	}
	vector<transaction>mtr; //minimum trnasactions required
	while(!finalrec.empty())
	{
		auto low= finalrec.begin();
		auto hi= prev(finalrec.end());
		
		int debit=low->second;
		string debit_person=low->first;
		finalrec.erase(low);
		
		int credit=hi->second;
		string credit_person=hi->first;
		finalrec.erase(hi);
		
		int settled_amt=min(-debit, credit);
		if(debit+settled_amt!=0)
		finalrec.insert({debit_person, settled_amt+debit});
		
		if(credit-settled_amt!=0)
		finalrec.insert({credit_person, credit-settled_amt});
		
		transaction t(debit_person, credit_person, settled_amt);
		mtr.push_back(t);
		
//		cout<<debit_person<<" pay "<<settled_amt<<" to "<<credit_person<<endl;
	}
	sort(mtr.begin(), mtr.end(), vec_comp);
	cout<<"Updated ledger : "<<mtr.size()<<" transactions"<<endl;
	for(int i=0;i<mtr.size();i++)
	cout<<mtr[i].dp<<" pay "<<mtr[i].amt<<" to "<<mtr[i].cp<<endl;
	
//	
//	for(auto i: finalrec)
//	cout<<i.first<<"->"<<i.second<<endl;
}
