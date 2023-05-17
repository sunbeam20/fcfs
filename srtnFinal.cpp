#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;

class Process
{
public:
int pID; 
int arrivalTime;
int priority;
int burstTime;



};

void setProcessId (Process p[], int n)
{
	for(int i=0;i<n;i++)
	{
		p[i].pID=i;
	}
}

void bubbleSort(Process a[], int size)
{
	for(int i=0; i<size; i++) //or for(int i=1; i<=size-1; i++)
	{
		
			for(int k=0; k<size-1; k++) //or for(int k=0; k<=size-2; k++)
			{
				if(a[k].arrivalTime>a[k+1].arrivalTime)
				{
					Process temp= a[k];
					a[k]=a[k+1];
					a[k+1]=temp;
				}
			}
		 
	}
}

Process sortbypriority(Process a[], int size)
{
	for(int i=0; i<size; i++) //or for(int i=1; i<=size-1; i++)
	{
		
			for(int k=0; k<size-1; k++) //or for(int k=0; k<=size-2; k++)
			{
				if(a[k].priority>a[k+1].priority)
				{
					Process temp= a[k];
					a[k]=a[k+1];
					a[k+1]=temp;
				}
			}
		 
	}
	return a[0];
}

Process lowestBurstTime(Process a[], int size)
{
	Process Q[size];
	for(int i=0; i<size; i++)
	{
		Q[i]=a[i];
	}
	for(int i=0; i<size; i++) //or for(int i=1; i<=size-1; i++)
	{
		
			for(int k=0; k<size-1; k++) //or for(int k=0; k<=size-2; k++)
			{
				if(Q[k].burstTime>Q[k+1].burstTime)
				{
					Process temp= Q[k];
					Q[k]=Q[k+1];
					Q[k+1]=temp;
				}
		}
	}	
		if(Q[0].burstTime==Q[1].burstTime)
		{
			int lbt=Q[0].burstTime;
			Process N[size];
			int j=0;
			for(int i=0; i<size; i++)
			{
				if(Q[i].burstTime==lbt)
				{
					while(j<size)
					{
						N[j]=Q[i];
						j++;
						break;
					}
				}
			}
			Process T=sortbypriority(N, j);
			int markedInd;
			for(int i=0; i<size; i++)
			{
				if(Q[i].pID==T.pID)
				{
					markedInd=i;
				}
			}
			Process tempo=Q[0];
			Q[0]=Q[markedInd];
			Q[markedInd]=Q[0];
		}
		
	return Q[0];
}

void srchArrvdProWithLowBt(Process P[],int size,int ct)
{
	Process R[size];
	int j=0;
	for(int i=0; i<size; i++)
	{
		if(P[i].arrivalTime<=ct)
		{
			while(j<size)
			{
				R[j]=P[i];
				j++;
				break;
			}
		}
	}
	Process S=lowestBurstTime(R, j);
    int markedIndex;
	for(int i=0; i<size; i++)
	{
		if(P[i].pID==S.pID)
		{
			markedIndex=i;
		}
	}
	if(P[0].pID!=S.pID)
	{
		if(markedIndex==size-1)
		{
			Process f=P[size-1];
			for(int i=markedIndex; i>0; i--)
			{
				P[i]=P[i-1];
			}
			P[0]=f;
		}
		else
		{
			Process temp=P[0];
			P[0]=P[markedIndex];
			P[markedIndex]=temp;
			Process temp2=P[markedIndex];
			for(int i=markedIndex; i<size-1; i++)
			{
				P[i]=P[i+1];
			}
			P[size-1]=temp2;
		}	
	}
}

int main()
{
	int n,ct=0,sumOfbt=0;
	cout<<"enter the no. of processes: ";
	cin>>n;
	Process p[n];
    
	setProcessId (p, n);
	
	cout<<"input arrivalTime of processes:"<<endl;
		
	for(int i=0;i<n;i++)
	{
		cin>>p[i].arrivalTime;
	} 	
    cout<<"input priority of processes:"<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>p[i].priority;
	} 	
    cout<<"input burstTime of processes:"<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>p[i].burstTime;
	}
	
	for(int i=0;i<n;i++)
	{
		sumOfbt=sumOfbt+p[i].burstTime;
	}
	
	bubbleSort(p, n);
	
	cout<<"sorted arrivalTime";
	cout<<endl<<endl<<endl;
	
	cout<<"Sum of BurstTime= "<<sumOfbt;
	cout<<endl<<endl;
	cout<< "Arrival Time "<< " Priority "<< " Burst Time "<<endl;
	for(int i=0;i<n;i++)
	{
	cout<<p[i].arrivalTime<<"              "<<p[i].priority<<"           "<<p[i].burstTime<<endl;
	}
    cout<<endl<<endl;
    
	srchArrvdProWithLowBt(p, n, ct);
	
	cout<<ct<<"-"<<"P"<<p[0].pID<<"-";
	int printedpID=p[0].pID;
	
	int z=0;
	while(ct<sumOfbt)
	{
		    if(p[1].arrivalTime<(p[0].burstTime+ct))
			{
				if(z==n-1)
				{
					    ct+=p[0].burstTime;
						p[0].burstTime=0;
						for(int i=0; i<n-1; i++)
						{
							p[i]=p[i+1];
						}
						n=n-1;
						srchArrvdProWithLowBt(p, n, ct);
						if(printedpID!=p[0].pID)
						{ 
							cout<<ct<<"-"<<"P"<<p[0].pID<<"-";
							printedpID=p[0].pID;
						}
				    z=0;
				}	
				else
				{	
					
					
					if(p[1].arrivalTime>ct && p[1].arrivalTime<(p[0].burstTime+ct))
					{
						if(p[1].burstTime<((ct+p[0].burstTime)-p[1].arrivalTime))
						{
							p[0].burstTime=p[0].burstTime-(p[1].arrivalTime-ct);
							ct=p[1].arrivalTime;
							
							Process tem= p[0];
							for(int i=0; i<n-1; i++)
							{
								p[i]=p[i+1];
							}
							p[n-1]=tem;
							cout<<ct<<"-"<<"P"<<p[0].pID<<"-";
							printedpID=p[0].pID;
						}
						
							
						else if(p[1].burstTime==((ct+p[0].burstTime)-p[1].arrivalTime))
						{
							if(p[1].priority<p[0].priority)
							{
								p[0].burstTime=p[0].burstTime-(p[1].arrivalTime-ct);
								ct=p[1].arrivalTime;
								
								Process temp= p[0];
								for(int i=0; i<n-1; i++)
								{
									p[i]=p[i+1];
								}
								p[n-1]=temp;
								cout<<ct<<"-"<<"P"<<p[0].pID<<"-";
								printedpID=p[0].pID;
							
							}
							else
							{
								Process ted= p[1];
								for(int i=1; i<n-1; i++)
								{
									p[i]=p[i+1];
								}
								p[n-1]=ted;
								
							}						
						}
						else
						{
							Process temp2= p[1];
							for(int i=1; i<n-1; i++)
							{
								p[i]=p[i+1];
							}
							p[n-1]=temp2;
							
						}
					}
                    else
					{
						Process t=p[1];
					    for(int i=1; i<n-1; i++)
						{
							p[i]=p[i+1];
						}
						p[n-1]=t;
					}					
					
				
				
				}
			z++;	
            }
			if(p[1].arrivalTime>=(ct+p[0].burstTime))
					{
						
						ct+=p[0].burstTime;
						p[0].burstTime=0;
						if(printedpID!=p[0].pID)
						{ 
							cout<<ct<<"-"<<"P"<<p[0].pID<<"-";
							printedpID=p[0].pID;
						}
						for(int i=0; i<n-1; i++)
							{
								p[i]=p[i+1];
							}
						n=n-1;
                        srchArrvdProWithLowBt(p, n, ct);
						if(printedpID!=p[0].pID)
						{ 
							cout<<ct<<"-"<<"P"<<p[0].pID<<"-";
							printedpID=p[0].pID;
						}
					z=0;
					}
			if(n==1)
			{
				ct+=p[0].burstTime;
				p[0].burstTime=0;
				if(printedpID!=p[0].pID)
				{ 
					cout<<ct<<"-"<<"P"<<p[0].pID;
					printedpID=p[0].pID;
				}
			}		
	}
	cout<<ct;
return 0;
}