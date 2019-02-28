#include<bits/stdc++.h>
using namespace std;
int main()
{
	cout<<fixed;
	cout<<setprecision(3);
	int nodes,edges,x,y,i,j,k;
	cout<<"Enter the number of pages and the number of links:"<<endl;
	cin>>nodes>>edges;
	double graph[nodes][nodes]={0},transition[nodes][nodes]={0};
	cout<<"Enter the links"<<endl;
	for (i=0;i<edges;i++)
	{
		cin>>x>>y;
		graph[x][y]=1;
	}
	for (i=0;i<nodes;i++)
	{
		double rowsum=0;
		for (j=0;j<nodes;j++)
		{
			rowsum+=graph[i][j];
		}
		if (rowsum>0)
		for (j=0;j<nodes;j++)
		transition[i][j]=graph[i][j]/rowsum;
		else
		for (j=0;j<nodes;j++)
		transition[i][j]=1.0/nodes;
	}
	double damp=0.85,ans;
	for (i=0;i<nodes;i++)
	{
		for (j=0;j<nodes;j++)
		{
			ans=transition[i][j];
			ans=(ans*damp)+(1.0-damp)/nodes;
			transition[i][j]=ans;
		}
	}
	int step=0;
	double identity[nodes][nodes];
	for (i=0;i<nodes;i++)
	for (j=0;j<nodes;j++)
	i==j?identity[i][j]=1.0:identity[i][j]=0.0;
	double product[nodes][nodes]={0};
	while (1)
	{
		for (i=0;i<nodes;i++)
		for (j=0;j<nodes;j++)
		{
			double	sum = 0.0;
			for (k = 0; k <nodes; k++)
			sum+=identity[i][k]*transition[k][j];
			product[i][j]=sum;
		}
		memcpy(identity,product,sizeof(identity));
		printf( "\n The Transition Matrix to power %d: ",step+1);
		for (i=0;i<nodes;i++)
		{
			printf( "\n         " );
			for (j=0;j<nodes;j++)
			printf( " %1.4f ", identity[ i ][ j ] );
		}
		printf( "\n" );
		double	diff,square_diff=0;
		for (j=0;j<nodes;j++)
		for (i=1;i<nodes;i++)
		{
			diff=(identity[i][j]-identity[0][j]);
			square_diff+=diff*diff;
		}
		if (square_diff<0.000000000000001)
		break;
		else
		++step;
	}
}
