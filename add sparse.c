#include<stdio.h>
#include<stdlib.h>
typedef struct
{
    int row,coloumn,value;
}term;


term* sparse(int **ar,int m,int n)
{
    int count=0;int index=1;int i,j;
    term* ptr=(term*)malloc(sizeof(term)*(m*n));
    ptr[0].row=m;ptr[0].coloumn=n;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            if(*(*(ar+i)+j)!=0)
            {
                count++;
                ptr[index].row=i;
                ptr[index].coloumn=j;
                ptr[index].value=*(*(ar+i)+j);
                index++;
             }
        }
    }
    ptr[0].value=count;return ptr;
}


term* add(term* a, term* b)
{
    term* ptr=(term*)malloc(sizeof(term)*((a[0].row * a[0].coloumn)+1));
    ptr[0].row=a[0].row;
    ptr[0].coloumn=a[0].coloumn;    
    int ac=0,bc=0,resc=0,index=1,i=1,j=1;
    while(ac<a[0].value && bc<b[0].value)
    {
        if(b[j].row>a[i].row)
        {
            ptr[index].row=a[i].row;
            ptr[index].coloumn=a[i].coloumn;
            ptr[index].value=a[i].value;
            i++;
            index++;
            ac++;
        }
        else if(b[j].row<a[i].row)
        {
            ptr[index].row=b[j].row;
            ptr[index].coloumn=b[j].coloumn;
            ptr[index].value=b[j].value;
            j++;
            index++;
            bc++;
        }
        else if(b[j].coloumn>a[i].coloumn)
        {
            ptr[index].row=a[i].row;
            ptr[index].coloumn=a[i].coloumn;
            ptr[index].value=a[i].value;
            i++;
            index++;
            ac++;
        }
        else if(b[j].coloumn<a[i].coloumn)
        {
            ptr[index].row=b[j].row;
            ptr[index].coloumn=b[j].coloumn;
            ptr[index].value=b[j].value;
            j++;
            index++;
            bc++;
        }
        else
        {
            ptr[index].row=b[j].row;
            ptr[index].coloumn=b[j].coloumn;
            ptr[index].value=b[j].value+a[i].value;
            j++;
            i++;
            index++;
            bc++;
            ac++;
        }
    }
 
    while(ac<a[0].value)
    {
        ptr[index].row=a[i].row;
        ptr[index].coloumn=a[i].coloumn;
        ptr[index].value=a[i].value;
        i++;
        index++;
        ac++;
    }
    while(bc<b[0].value)
    {
        ptr[index].row=b[j].row;
        ptr[index].coloumn=b[j].coloumn;
        ptr[index].value=b[j].value;
        j++;
        index++;
        bc++;
    }
    ptr[0].value=index-1;
    return ptr;
}


int main()
{
     int m,n;
    printf("\nEnter rows and columns\n");
    scanf("%d %d",&m,&n);
    int **a=(int**)malloc(m*sizeof(int*));
    int i,j;
    for(i=0;i<m;i++)
        *(a+i)=(int*)malloc(n*sizeof(int));
    printf("\nEnter Values\n");
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    term* x=sparse(a,m,n);
    printf("\n-----SPARSE REPRESENTATION--------\n");
    for(i=0;i<(x[0].value+1);i++)
    {
        printf("%d %d %d \n",x[i].row,x[i].coloumn,x[i].value);
    }
    printf("\nEnter rows and columns\n");
    scanf("%d %d",&m,&n);
    a=(int**)malloc(m*sizeof(int*));
    for(i=0;i<m;i++)
        *(a+i)=(int*)malloc(n*sizeof(int));
    printf("\nEnter Values\n");
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    term* y=sparse(a,m,n);
    printf("\n-----SPARSE REPRESENTATION--------\n");
    for(i=0;i<(y[0].value+1);i++)
    {
        printf("%d %d %d \n",y[i].row,y[i].coloumn,y[i].value);
    }
    if(x[0].row!=y[0].row || x[0].coloumn!=y[0].coloumn)
    {
        printf("Addition not possible");
    }
    else
    {
        term* res=add(x,y);
        printf("\nResult:\n");
        for(i=0;i<(res[0].value+1);i++)
        {
            printf("%d %d %d \n",res[i].row,res[i].coloumn,res[i].value);
        }
        free(res);
    }
    for(i=0;i<m;i++)
        free(a[i]);
    free(a);
    free(x);
    free(y);
    return 0;
}
 
