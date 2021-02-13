#include <bits/stdc++.h>
using namespace std;

//------------------------------------
char str[20];
int actual_size[4];
int last_idx[4],last_idx_res;
int pr,n;
struct s {
	char c;
	int nofc;
	int pr;
}arr[4][20],res[100];

void push(char ch,int s,int p){
	int i;
	for ( i=0;i<4;i++){
		if (actual_size[i]+s<20){// 21
			arr[i][last_idx[i]].c=ch;
			arr[i][last_idx[i]].nofc=s;
			arr[i][last_idx[i]].pr=p;
			last_idx[i]++;
			actual_size[i]+=s;
			break;
		}
	}
}
void destroy_list(int idx){
	actual_size[idx]=0;
	last_idx[idx]=0;
}

void update_request_data(char ch,int s,int pID){
	int i,j;
	for ( i=0;i<4;i++){
		for ( j=0;j<last_idx[i];j++){
			if (arr[i][j].c==ch&&arr[i][j].nofc==s)arr[i][j].pr=pID;
		}
	}
}

void find_with_priority_usingBF(int pid){
	int i;
	for ( i=0;i<4;i++){
		cout<<"The list number -->"<<i<<endl;
		int j;
		for ( j=0;j<last_idx[i];j++){
			if (arr[i][j].pr==pid)cout<<j+1<< '\n';
		}
		cout<< endl;
		cout<< "----------";
		cout<<endl;
	}

	return ;
}
void find_with_priority_and_req_usingBF(int pid,char ch,int s){
	int i;
	for ( i=0;i<4;i++){
		cout<<"The list number -->"<<i<<endl;
		int j;
		for ( j=0;j<last_idx[i];j++){
			if (arr[i][j].pr==pid&&arr[i][j].c==ch&&arr[i][j].nofc==s)cout<<j+1<< ' ';
		}
		cout<< endl;
		cout<< "----------";
		cout<<endl;
	}
	return ;
}

void find_with_request_usingBS(char ch,int s){
	int lo=0,hi=last_idx_res,med,first_occcurece=0,last_occcurece=-1;
	while(lo<=hi){
		med=(lo+hi)/2;
		if (res[med].c>ch||(res[med].c==ch&&res[med].nofc>s))hi=med-1;
		else if (res[med].c<ch||(res[med].c==ch&&res[med].nofc<s))lo=med+1;
		else {
			first_occcurece=med;
			hi=med-1;
		}
	}
	lo=0;
	hi=last_idx_res;
	while(lo<=hi){
		med=(lo+hi)/2;
		if (res[med].c>ch||(res[med].c==ch&&res[med].nofc>s))hi=med-1;
		else if (res[med].c<ch||(res[med].c==ch&&res[med].nofc<s))lo=med+1;
		else {
			last_occcurece=med;
			lo=med+1;
		}
	}
	int i;
	for ( i=first_occcurece;i<=last_occcurece;i++){
		cout<<i+1<< ' ';
	}
	cout<<endl;
	return ;
}

void join_list_to_list(int f,int s){
	if (actual_size[f]+actual_size[s]>20)return ;
	int ptr2=0;
	while(ptr2<last_idx[s]){
		arr[f][last_idx[f]]=arr[s][ptr2];
		last_idx[f]++;
		ptr2++;
	}
	actual_size[f]+=actual_size[s];
	destroy_list(s);
}
void mix_all_list_in_one(){
	last_idx_res=0;
	int i,j;
	for ( i=0;i<4;i++){
		for ( j=0;j<last_idx[i];j++){
			res[last_idx_res]=arr[i][j];
			last_idx_res++;
		}
	}
	for ( i=0;i<last_idx_res;i++){
		for ( j=i+1;j<last_idx_res;j++){
			if (res[i].c>res[j].c||(res[i].c==res[j].c&&res[i].nofc>res[j].nofc)){
					res[99]=res[i];
					res[i]=res[j];
					res[j]=res[99];
			}
		}
	}
}
void sort_list_by_requsts(int idx){
	int i,j;
	for ( i=0;i<last_idx[idx];i++){
		for ( j=i+1;j<last_idx[idx];j++){
			//if ((*arr[i]).c>(*arr[j]).c||((*arr[i]).c==(*arr[j]).c&&(*arr[i]).nofc>(*arr[j]).nofc))swap((*arr[i]),(*arr[j]));
			if (arr[idx][i].c>arr[idx][j].c||(arr[idx][i].c==arr[idx][j].c&&arr[idx][i].nofc>arr[idx][j].nofc)){

					res[99]=arr[idx][i];
					arr[idx][i]=arr[idx][j];
					arr[idx][j]=res[99];
					//swap(arr[idx][i],arr[idx][j]);
			}
		}
	}
	return;
}
void sort_list_by_priority(){
		int i,j;
		for (i=0;i<last_idx_res;i++){
		for ( j=i+1;j<last_idx_res;j++){
			if (res[i].pr<res[j].pr||(res[i].pr==res[j].pr&&res[i].nofc<res[j].nofc)){
					res[99]=res[i];
					res[i]=res[j];
					res[j]=res[99];
			}
		}
	}
	return;
}
void erase_all_requests(char ch){
	last_idx_res=0;
	int i,j;
	for ( i=0;i<4;i++){
		int erased_elements=0;
		for ( j=0;j<last_idx[i];j++){
			if (arr[i][j].c==ch){
				erased_elements++;
				actual_size[i]-=arr[i][j].nofc;
				res[last_idx_res]=arr[i][j];
				last_idx_res++;
				arr[i][j].c='}';		// >z
			}
		}
	sort_list_by_requsts(i);
	last_idx[i]-=erased_elements;
	}
}

void print_all_requests(){
	int i,j;
	for ( i=0;i<last_idx_res;i++){
		cout<<"the prority is-->"<<res[i].pr<< ' ' ;
		for ( j=0;j<res[i].nofc;j++)cout<<res[i].c;
		cout<<endl;
	}
}
void print_the_first_pr(int pr){
	int flag=0;
	int i,j;
	for ( i=0;i<4;i++){
		for ( j=0;j<last_idx[i];j++){
			if (arr[i][j].pr==pr){
				cout<<"THE LIST-->"<<i+1<<" IN THE IDX "<<j+1<<endl;
				flag=1;
				break;
			}
		}
		if (flag)break;
	}
	if (flag==0)cout<<"NOT FOUUND";

}
void sort_all_lists(){
	int i,j;
	for ( i=0;i<4;i++)sort_list_by_requsts(i);
}
void destroy_all_list(){
	int i,j;
	for ( i=0;i<4;i++)destroy_list(i);
}
void getlen(){
	n=0;
	for (;str[n]>='a'&&str[n]<='z';n++);
	return ;
}

void test(){
		cout<< endl;
			cout<< "HEEEEEEEEEEREEEEEEEEEE \n\n";
		//	for (int j=0;j<last_idx_res;j++)
			//	cout<<res[j].c<< ' '<<res[j].nofc<< ' '<<res[j].pr<< "---\n";
			int i,j;
			for ( i=0;i<4;i++){
				cout<< i+1<< "---->";
				for (j=0;j<last_idx[i];j++){
					cout<<arr[i][j].c<< ' '<<arr[i][j].nofc<< ' '<<arr[i][j].pr<< "---";
				}
				cout<<endl;
			}
}
int main()
{
	int t;
	//cin>>t;
	while(2){
		int q;
		scanf("%d",&q);
		if (q==1){
			int x,y;
			scanf("%d%d",&x,&y);
			join_list_to_list(x-1,y-1);
		}
		else if (q==2){
			destroy_all_list();         				  // destroy list

		}
		else if (q==3){                    			 // update request for pririty mo3iana
			scanf("%s%d",&str,&pr);
			getlen();
			update_request_data(str[0],n,pr);
		}
		else if (q==4){                      		// find request
			scanf("%s",&str);
			getlen();
			mix_all_list_in_one();
			find_with_request_usingBS(str[0],n);
		}
		else if (q==5){ 							//find priority using brute force
			scanf("%d",&pr);
			find_with_priority_usingBF(pr);
		}
		else if (q==6){								//find priority_with_request
			scanf("%s%d",&str,&pr);
			getlen();
			find_with_priority_and_req_usingBF(pr,str[0],n);
		}
		else if (q==7){								// print all queris and detele it
			char c;
			scanf("%c",&c);
			erase_all_requests(c);
			sort_list_by_priority();
			print_all_requests();
		}
		else if (q==8){
			scanf("%s%d",&str,&pr);
			getlen();
			push(str[0],n,pr);
		}
		else if (q==9){
			scanf("%d",&pr);
			getlen();
			print_the_first_pr(pr);
		}
		sort_all_lists();

		test();
		//cin>>t;
	}
return 0;
}
