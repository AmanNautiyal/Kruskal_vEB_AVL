#include "vEBTree.h"
#include "AVL.h"
#define uni_size 65536
using namespace std;
ll findparent(vector<ll> &parent, ll v)
{
	while(parent[v]!=-1)
	{
		v=parent[v];
	}
	return v;
}
void Union(vector<ll> &parent,ll a,ll b)
{
	if(a!=b)
		parent[a]=b;	
}
// int main()
// {
// 	ifstream myfile("Input.txt");
// 	if(!myfile.is_open())
// 	{
// 		cout<<"File not found\n";
// 		return 0;
// 	}
// 	ll nodes,edges,maxweight;
// 	myfile>>nodes>>edges;
// 	ll a,b,weight;
// 	avlnode *avlroot;
// 	vEBnode *root=create_node(uni_size);
// 	unordered_map<ll,forward_list<pair<ll,ll>>> wtedge;
// 	for(ll i=0;i<edges;i++)
// 	{
// 		myfile>>a>>b>>weight;
// 		if(wtedge.find(weight)==wtedge.end())//weight doesn't exist
// 		{
// 			//new entry
// 			forward_list<pair<ll,ll>> temp;
// 			temp.push_front(make_pair(a,b)); // new list with a ,b
// 			wtedge[weight]=temp;//insert in map
// 		}
// 		else
// 		{
// 			forward_list<pair<ll,ll>> temp=wtedge.at(weight);
// 			temp.push_front(make_pair(a,b));
// 			wtedge[weight]=temp;
// 		}
// 	}
// 	forward_list<pair<ll,ll>> temp;
// 	for(auto i:wtedge)
// 	{
// 		cout<<i.first<<"::\t";
// 		temp=i.second;
// 		for(auto j:temp)
// 			cout<<j.first<<" "<<j.second<<",";
// 		cout<<endl;
// 	}
// 	return 0;
// }
pair<ll,ll> withAVL(string file)
{
	ifstream myfile(file);
	if(!myfile.is_open())
	{
		cout<<"File not found\n";
		return make_pair(-1,-1);
	}
	ll nodes,edges,maxweight;
	myfile>>nodes>>edges;
	ll a,b,weight;
	AVL root;
	auto start = std::chrono::high_resolution_clock::now();
	unordered_map<ll,forward_list<pair<ll,ll>>> wtedge;
	for(ll i=0;i<edges;i++)
	{
		myfile>>a>>b>>weight;
		if(wtedge.find(weight)==wtedge.end())//weight doesn't exist
		{
			//new entry
			forward_list<pair<ll,ll>> temp;
			//cout<<"Insert "<<weight<<":";
			root.insert(weight);
			//cout<<"Done "<<endl;
			temp.push_front(make_pair(a,b)); // new list with a ,b
			wtedge[weight]=temp;//insert in map
		}
		else
		{
			forward_list<pair<ll,ll>> temp=wtedge.at(weight);
			temp.push_front(make_pair(a,b));
			wtedge[weight]=temp;
		}
	}
	myfile.close();
	forward_list<pair<ll,ll>> temp;
	vector<ll> parent(nodes,-1);
	ll num=0,mstweight=0;
	ll minweight,pa,pb;
	while(num<(nodes-1) && !root.isempty())
	{
		minweight=root.minval();
		temp=wtedge[minweight];
		a=temp.front().first;
		b=temp.front().second;
		temp.pop_front();
		wtedge[minweight]=temp;
		if(temp.empty())
		{
			wtedge.erase(minweight);
			root.del(minweight);
		}
		pa=findparent(parent,a);
		pb=findparent(parent,b);
		if(pa!=pb) // no cycle
		{
			Union(parent,pa,pb);
			mstweight+=minweight;
			num++;
		}
	}
	cout<<edges<<"\t";
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long ms = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout<<ms<<endl;
	return make_pair(edges,(ll)ms);
	// for(auto i:wtedge)
	// {
	// 	cout<<i.first<<"::\t";
	// 	temp=i.second;
	// 	for(auto j:temp)
	// 		cout<<j.first<<" "<<j.second<<",";
	// 	cout<<endl;
	// }
}
pair<ll,ll> withVEB(string file)
{
	// setlogs();
	vEBnode *root=create_node(uni_size);
	ifstream myfile(file);
	if(!myfile.is_open())
	{
		cout<<"File not found\n";
		return make_pair(-1,-1);
	}
	ll nodes,edges,maxweight;
	myfile>>nodes>>edges;
	ll a,b,weight;
	std::ios::sync_with_stdio(false);
	auto start = std::chrono::high_resolution_clock::now();
	unordered_map<ll,forward_list<pair<ll,ll>>> wtedge;
	for(ll i=0;i<edges;i++)
	{
		myfile>>a>>b>>weight;
		if(wtedge.find(weight)==wtedge.end())//weight doesn't exist
		{
			//new entry
			forward_list<pair<ll,ll>> temp;
			insert(root,weight);
			temp.push_front(make_pair(a,b)); // new list with a ,b
			wtedge[weight]=temp;//insert in map
		}
		else
		{
			forward_list<pair<ll,ll>> temp=wtedge.at(weight);
			temp.push_front(make_pair(a,b));
			wtedge[weight]=temp;
		}
	}
	myfile.close();
	forward_list<pair<ll,ll>> temp;
	vector<ll> parent(nodes,-1);
	ll num=0,mstweight=0;
	ll minweight,pa,pb;
	while(num<(nodes-1) && root->min!=-1)
	{
		minweight=root->min;
		temp=wtedge[minweight];
		a=temp.front().first;
		b=temp.front().second;
		temp.pop_front();
		wtedge[minweight]=temp;
		if(temp.empty())
		{
			wtedge.erase(minweight);
			del_element(root,minweight);
		}
		pa=findparent(parent,a);
		pb=findparent(parent,b);
		if(pa!=pb) // no cycle
		{
			Union(parent,pa,pb);
			mstweight+=minweight;
			num++;
		}
	}
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long ms = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	
	// freelogs()
	std::ios::sync_with_stdio(true);
	cout<<edges<<"\t";
	cout<<ms<<endl;
	return make_pair(edges,(ll)ms);
	// for(auto i:wtedge)
	// {
	// 	cout<<i.first<<"::\t";
	// 	temp=i.second;
	// 	for(auto j:temp)
	// 		cout<<j.first<<" "<<j.second<<",";
	// 	cout<<endl;
	// }
}
int main()
{
	for(int j=5;j<=5;j++){
	ofstream outfile_avl("Records"+to_string(j)+"avl.txt");
	ofstream outfile_veb("Records"+to_string(j)+"veb.txt");
	pair<ll,ll> res;
	for(int i=0;i<=149;i++)
	{
		string fl="inpwt"+to_string(j)+"/inpwt"+to_string(i)+".txt";
		res=withVEB(fl);
		outfile_veb<<res.first<<" "<<res.second<<"\n";
		res=withAVL(fl);
		outfile_avl<<res.first<<" "<<res.second<<"\n";
	}
	outfile_avl.close();
	outfile_veb.close();
	}
	return 0;
}