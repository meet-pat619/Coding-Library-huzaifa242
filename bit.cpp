//Distinct AND/OR of SUBARRAY
//Usage init_fwd -> nxtchg_generator -> fwd_distinct
//poss,pose will have position of range of distinct number and fdist will have actual numbers

#define bts 64
vector<long long int> poss[MAX],pose[MAX],zbit[bts],fdist[MAX];
long long int nxtchg[MAX][bts];
void init_fwd(long long int n)
{
	long long int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<bts;j++)
		nxtchg[i][j]=n;
		poss[i].clear();
    	pose[i].clear();
    	fdist[i].clear();
	}
}
void nxtchg_generator(long long int n)
{
	long long int i,j,k;
	for(j=0;j<bts;j++)
	{
		for(i=n-1;i>=0;i--)
		{
			k=a[i]&(1<<j);
			if(!zbit[j].empty() && k)//if(!zbit[j].empty() && !k) for OR
			{
				nxtchg[i][j]=min(nxtchg[i][j],zbit[j][zbit[j].size()-1]);
			}
			if(!k)// if(k) for OR
			{
				zbit[j].push_back(i);
			}
		}
	}
	for(i=0;i<n;i++)
	sort(nxtchg[i],nxtchg[i]+bts);
	/*cout<<"Zbit:\n";
	for(i=0;i<bts;i++)
	{
		if(!zbit[i].empty())
		{
			cout<<i<<": i\n";
			for(j=0;j<zbit[i].size();j++)
			{
				cout<<zbit[i][j]<<" ";
			}
			cout<<"\n";
		}
	}*/ 
	/*for(i=0;i<n;i++)
	{
		cout<<"Nxtchg: "<<i<<endl;
	    for(j=0;j<bts;j++)
	    cout<<nxtchg[i][j]<<" ";
	    cout<<endl;
	}*/	
}
void fwd_distinct(long long int n)
{
	long long int i,j,k,an;
	init_fwd(n);
	nxtchg_generator(n);
	for(i=0;i<n;i++)
	{
		an=a[i];
	   	if(1)//condition to include distinct
	   	{
	   		j=nxtchg[i][0];
	   		fdist[i].push_back(an);
	   		poss[i].push_back(i);
	   	}
	   	for(k=0;k<bts;k++)
	   	{
	   		j=nxtchg[i][k];
	   		if(an==0)//if(an==(1<<bts)-1) for OR
	   		{
	   			pose[i].push_back(n-1);
	   			break;
	   		}
	   		if(j==n)
	   		{
	   			if(1)//condition to include distinct
	   			{
	   				pose[i].push_back(n-1);
	   			}
	   			break;
	   		}
	   		if(k==0 && j!=i)
	   		{
	   			if(1)//condition to include distinct
	   			{
	   				pose[i].push_back(j-1);
	   			}
	   			an&=a[j];//| for OR
	   			if(1)//condition to include distinct
	   			{
	   				//cout<<i<<":i "<<k<<" *:k"<<an<<":an\n";
	   				poss[i].push_back(j);
	   				fdist[i].push_back(an);
	   			}
	   		}
	   		else if( k==0 && j==i)
	   		{
	    	}
	    	else if(nxtchg[i][k]!=nxtchg[i][k-1])
	    	{
	    		if(1)//condition to include distinct
	    		{
	    			pose[i].push_back(j-1);
	    		}
	    		an&=a[j];//| for OR
	   			if(1)//condition to include distinct
	   			{
	   				//cout<<i<<":i "<<k<<" #:k "<<an<<":an\n";
	   				poss[i].push_back(j);
	   				fdist[i].push_back(an);
	   			}
	   		}
	   	}
	   	// Pose > Poss
	   	/*cout<<i<<":i\n";
	    cout<<"Poss:\n";
	    for(j=0;j<poss[i].size();j++)
		cout<<poss[i][j]<<" ";
		cout<<"\n";
	    cout<<"Pose:\n";
	    for(j=0;j<pose[i].size();j++)
	    cout<<pose[i][j]<<" ";
	    cout<<"\n";
	    cout<<"fdist:\n";
	    for(j=0;j<fdist[i].size();j++)
	    cout<<fdist[i][j]<<" ";
	    cout<<"\n";*/
	}
}
vector<long long int>rposs[MAX],rpose[MAX],rzbit[bts],rdist[MAX];
long long int prvchg[MAX][bts];
void init_rev(long long int n)
{
	long long int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<bts;j++)
		prvchg[i][j]=-1;
		rposs[i].clear();
		rpose[i].clear();
		rdist[i].clear();
	}
}
void prvchg_generator(long long int n)
{
	long long int i,j,k;
	for(j=0;j<bts;j++)
	{
		for(i=0;i<n;i++)
	    {
	    	k=a[i]&(1<<j);
	    	if(!rzbit[j].empty() && k)
	    	{
	    		prvchg[i][j]=max(prvchg[i][j],rzbit[j][rzbit[j].size()-1]);
	    	}
	    	if(!k)
	    	rzbit[j].push_back(i);
	    }
	}
	for(i=0;i<n;i++)
	sort(prvchg[i],prvchg[i]+bts, greater<long long int>());
	/*cout<<"RZbit:\n";
	for(i=0;i<bts;i++)
	    {
	    if(!rzbit[i].empty())
	    {
	    	cout<<i<<": i\n";
	    	for(j=0;j<rzbit[i].size();j++)
	    	{
	    		cout<<rzbit[i][j]<<" ";
	    	}
			cout<<"\n";
		}
	}*/ 
	/*for(i=0;i<n;i++)
	{
		cout<<"Prvchg: "<<i<<endl;
	    for(j=0;j<bts;j++)
	    cout<<prvchg[i][j]<<" ";
	    cout<<endl;
	}*/	
}
void rev_distinct(long long int n)
{
	long long int i,j,k,an;
	init_rev(n);
	prvchg_generator(n);
	for(i=n-1;i>=0;i--)
	{
		an=a[i];
	 	if(1)//condition to include distinct
	   	{
	   		j=prvchg[i][0];
	   		rposs[i].push_back(i);
	   		rdist[i].push_back(an);
	   	}
	   	for(k=0;k<bts;k++)
	   	{
	   		j=prvchg[i][k];
	   		if(an==0)//if(an==(1<<bts)-1) for OR
	   		{
	   			rpose[i].push_back(0);
	   			break;
	   		}
	   		if(j==-1)
	   		{
	   			if(1)//condition to include distinct
	   			{
	   				rpose[i].push_back(0);
	   			}
	   			break;
	   		}
	   		if(k==0 && j!=i)
	   		{
	   			if(1)//condition to include distinct
	   			{
	   				rpose[i].push_back(j+1);
	   			}
	   			an&=a[j];//| for OR
	   			if(1)//condition to include distinct
	   			{
	   				//cout<<i<<":i "<<k<<" *:k"<<an<<":an\n";
	   				rposs[i].push_back(j);
	   				rdist[i].push_back(an);
	   			}
	   		}
	   		else if( k==0 && j==i)
	   		{
	   		}
	   		else if(prvchg[i][k]!=prvchg[i][k-1])
	   		{
	   			if(1)//condition to include distinct
	   			{
	   				rpose[i].push_back(j+1);
	   			}
	   			an&=a[j];//| for OR
	   			if(1)//condition to include distinct
	   			{
	   				//cout<<i<<":i "<<k<<" #:k "<<an<<":an\n";
	   				rposs[i].push_back(j);
	   				rdist[i].push_back(an);
	   			}
	  		}
	   	}
	   	//rposs > rpose
	    /*cout<<i<<":i\n";
	    cout<<"rPoss:\n";
	    for(j=0;j<rposs[i].size();j++)
	    cout<<rposs[i][j]<<" ";
	    cout<<"\n";
	    cout<<"rPose:\n";
	    for(j=0;j<rpose[i].size();j++)
	    cout<<rpose[i][j]<<" ";
	    cout<<"\n";
	    cout<<"rsrpre:\n";
	    for(j=0;j<rdist[i].size();j++)
	    cout<<rdist[i][j]<<" ";
	   	cout<<"\n";*/
	}
}
