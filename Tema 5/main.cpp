#include <iostream>
#include <cstdlib>

using namespace std;

struct Node
{
    int info, inal;
    Node* st, *dr;
};

int inaltime(Node *nod)
{
    if(nod==NULL)
        return 0;
    return nod->inal;
}

int maxim(int a, int b)
{
    if(a>b) return a;
    else return b;
}

Node* nodNou(int x)
{
    Node* nod = new Node();
    nod->info = x;
    nod->st=NULL;
    nod->dr=NULL;
    nod->inal=1;
    return nod;
}

Node* rotdr(Node* b)
{
    Node* a = b->st;
    Node* t = a->dr;

    a->dr=b;
    b->st=t;

    b->inal=maxim(inaltime(b->st), inaltime(b->dr)) + 1;
    a->inal=maxim(inaltime(a->st), inaltime(a->dr)) + 1;

    return a;
}

Node* rotst(Node* a)
{
    Node* b = a->dr;
    Node* t = b->st;

    b->st = a;
    a->dr = t;

    a->inal=maxim(inaltime(a->st), inaltime(a->dr)) + 1;
    b->inal=maxim(inaltime(b->st), inaltime(b->dr)) + 1;

    return b;
}

int dif(Node *nod)
{
    if(nod==NULL)
        return 0;
    return inaltime(nod->st) - inaltime(nod->dr);
}

Node* inserare(Node* nod, int info)
{
    if(nod==NULL)
        return(nodNou(info));

    if(info < nod->info)
        nod->st = inserare(nod->st, info);
    else if(info > nod->info)
        nod->dr = inserare(nod->dr, info);
    else return nod; ///nu see pot adauga chei egale

    nod->inal = 1 + maxim(inaltime(nod->st), inaltime(nod->dr));

    int diferenta = dif(nod);

    if(diferenta > 1 && info < nod->st->info)
        return rotdr(nod);

    if(diferenta < -1 && info > nod->dr->info)
        return rotst(nod);

    if(diferenta > 1 && info > nod->st->info)
    {
        nod->st = rotst(nod->st);
        return rotdr(nod);
    }

    if(diferenta < -1 && info < nod->dr->info)
    {
        nod->dr = rotdr(nod->dr);
        return rotst(nod);
    }

    return nod;
}

void RSD(Node* nod)
{
    if(nod!=NULL)
    {
        cout<<nod->info<<" ";
        RSD(nod->st);
        RSD(nod->dr);
    }
}

void SRD(Node* nod)
{
    if(nod!=NULL)
    {
        SRD(nod->st);
        cout<<nod->info<<" ";
        SRD(nod->dr);
    }
}

void Merge(int *a, int st, int dr, int mij)
{
    int i, j, k, aux[dr-st+1];
    i=st;
    k=0;
    j=mij+1;
    while(i<=mij && j<=dr)
    {
        if(a[i]<a[j])
        {
            aux[k] = a[i];
            k++;
            i++;
        }

        else
        {
            aux[k] = a[j];
            k++;
            j++;
        }
    }

    while(i<=mij)
    {
        aux[k] = a[i];
        k++;
        i++;
    }

    while(j<=dr)
    {
        aux[k] = a[j];
        k++;
        j++;
    }

    for(i=st; i<=dr; i++)
        a[i] = aux[i-st];
}

void MergeSort(int *a, int st, int dr)
{
    int mij;
    if(st<dr)
    {
        mij = (st+dr) / 2;
        MergeSort(a, st, mij);
        MergeSort(a, mij+1, dr);

        Merge(a, st, dr, mij);
    }


}

void sch(int *a, int *b)
{
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

int Partition(int a[], int mic, int mare)
{
    int pivot, index, i;
    index = mic;
    pivot = mare;
    for(i=mic; i<mare; i++)
    {
        if(a[i]<a[pivot])
        {
            sch(&a[i], &a[index]);
            index++;
        }
    }
    sch(&a[pivot], &a[index]);
    return index;
}

int RandomPiv(int a[], int mic, int mare)
{
    int p, n, aux;
    n=rand();
    p = mic + n%(mare-mic+1);
    sch(&a[mare], &a[p]);
    return Partition(a, mic, mare);
}

int QuickSort(int a[], int mic, int mare)
{
    int pozindex;
    if(mic<mare)
    {
        pozindex = RandomPiv(a, mic, mare);
        QuickSort(a, mic, pozindex-1);
        QuickSort(a, pozindex+1, mare);
    }
}

void heapify(int v[], int n, int i)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if(l<n && v[l] > v[largest])
        largest = l;
    if(r<n && v[r] > v[largest])
        largest = r;

    if(largest!=i)
    {
        swap(v[i], v[largest]);
        heapify(v, n, largest);
    }

}

void heapSort(int v[], int n)
{
    for(int i = n/2 - 1; i>=0; i--)
        heapify(v, n, i);

    for(int i = n-1; i>=0; i--)
    {
        swap(v[0], v[i]);
        heapify(v, i, 0);
    }
}

int main()
{
    ///pb1
    Node * root = NULL;

    int ok=1;
    while(ok)
    {
        cout<<"1-Adaugare"<<endl;
        cout<<"2-Afisare preordine"<<endl;
        cout<<"3-Afisare inordine"<<endl;
        cout<<"4-stop"<<endl;
        int com, val;
        cin>>com;
        switch(com)
        {
        case 1:
            cin>>val;
            root = inserare(root, val);
            break;
        case 2:
            RSD(root);
            break;
        case 3:
            SRD(root);
            break;
        case 4:
            ok=0;
            break;
        }
    }
/*  root = inserare(root, 5);
    root = inserare(root, 7);
    root = inserare(root, 9);
    root = inserare(root, 12);
    root = inserare(root, 3);
    root = inserare(root, 15);

    cout<<"Preordine: ";
    RSD(root);
    cout<<endl;
    cout<<"Inordine: ";
    SRD(root);
*/
    cout<<endl<<endl<<endl;

    ///pb2
    int n;
    cin>>n;
    int v[n];
    for(int i=0; i<n; i++)
        cin>>v[i];

    MergeSort(v, 0, n-1);
    cout<<"Vector sortat: ";
    for(int i=0; i<n; i++)
        cout<<v[i]<<" ";

    cout<<endl;


    ///pb3
    int m;
    cin>>m;
    int u[m];
    for(int i=0; i<m; i++)
        cin>>u[i];

    QuickSort(u, 0, m-1);
    cout<<"Vector sortat: ";
    for(int i=0; i<m; i++)
        cout<<u[i]<<" ";

    ///pb4
    int q;
    cin>>q;
    int x[q];
    for(int i=0; i<q; i++)
        cin>>x[i];

    heapSort(x, q);

    cout<<endl;
    cout<<"Vector sortat: ";
    for(int i=0; i<q; i++)
        cout<<x[i]<<" ";
}
