#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

string inter[100];
string town[100];
vector<string>arc;
int n,m;

int exist(string ch)
{
    int veref=0;
    for(int i=0;i<n;i++)
        if(ch==inter[i])
        {
            veref=i;
            break;
        }
    return veref;
}


void tree_input()
{
    string const file("arbre_minimal.txt");
    ofstream flow(file.c_str());
    string beginning,target;
    int dist,j,k,cpt(1);
    bool here=false,there(false);
    cin>>beginning>>target>>dist;
    flow<<0<<" "<<1<<" "<<dist<<endl;
    inter[0]=beginning; inter[1]=target;
    for(int i=1;i<m;i++)
    {
        cin>>town[i]>>town[i+1]>>dist;
        here=false;there=false;
        for(int e=0;e<n;e++)
        {
            if(town[i]==inter[e]){ here=true; break; }
        }

        for(int e=0;e<n;e++)
        {
            if(town[i+1]==inter[e]){ there=true; break; }
        }
        if(here==false && there==false)
            {
                inter[cpt+1]=town[i];
                inter[cpt+2]=town[i+1];
                cpt+=2;
                j=exist(town[i]);
                k=exist(town[i+1]);
                flow<<j<<" "<<k<<" "<<dist<<endl;
            }
        else if(here==true && there==false)
            {
                inter[cpt+1]=town[i+1];
                cpt++;
                j=exist(town[i]);
                k=exist(town[i+1]);
                flow<<j<<" "<<k<<" "<<dist<<endl;
            }
        else if(here==false && there==true)
            {
                inter[cpt+1]=town[i];
                cpt++;
                j=exist(town[i]);
                k=exist(town[i+1]);
                flow<<j<<" "<<k<<" "<<dist<<endl;
            }
        else if(here==true && there==true)
            {
                j=exist(town[i]);
                k=exist(town[i+1]);
                flow<<j<<" "<<k<<" "<<dist<<endl;
            }
    }

}









struct Arrete{
       int a; // Premier sommet
       int b; // Deuxième sommet
       int p; // Poids de l'arrête
       };
int main()
{
    struct Arrete Arretes[100];
    int Parent[20];
    int i,j,poids;
    int tmp,orgA,orgB;
    int first,second,dist;
    // Lecture du nombre de sommets
    printf("Donnez le nombre de sommets: ");
    scanf("%d",&n);
    // Lecture du nombre d'arrêtes
    printf("Donnez le nombre d'arretes: ");
    scanf("%d",&m);
    // Lecture des arrêtes
    tree_input();
    ifstream find("arbre_minimal.txt");
    int k(0);
        while(!find.eof())
        {
            find>>first>>second>>dist;
            Arretes[k].a=first;
            Arretes[k].b=second;
            Arretes[k].p=dist;
            k++;
        }
    // Tri dss arrêtes dans l'ordre croissant des poids
    for(i=0;i<m;i++)
    {
       for(j=1;j<m-i;j++)
       {
          if(Arretes[j-1].p > Arretes[j].p)
          {
            // Permutation des premiers sommets
            tmp=Arretes[j-1].a;
            Arretes[j-1].a=Arretes[j].a;
            Arretes[j].a=tmp;
            // Permutation des deuxièmes sommets
            tmp=Arretes[j-1].b;
            Arretes[j-1].b=Arretes[j].b;
            Arretes[j].b=tmp;
            // Permutation des poids
            tmp=Arretes[j-1].p;
            Arretes[j-1].p=Arretes[j].p;
            Arretes[j].p=tmp;
          }
       }
    }
    poids=0; // cette variable contienda le poids totale de la solution
    for(i=0;i<n;i++) Parent[i]=i;
    printf("Les arrEtes choisies sont:\n");
    for(i=0;i<m;i++)
    {
       // Recherche de l'origine du premier sommet
       j = Parent[Arretes[i].a];
       while(j != Parent[j]) j = Parent[j];
       orgA=j;
       // Recherche de l'origine du deuxième sommet
       j = Parent[Arretes[i].b];
       while(j != Parent[j]) j = Parent[j];
       orgB=j;
       //comparaison des deux origines
       if(orgA!=orgB) // Dans ce cas l'arrête ne crée pas de cycle
       {
           // Unir les deux groupements
           Parent[orgB]=orgA;
           // On affecte aux sommets leur origine comme parent
           // pour accélérer la recherche des origines
           Parent[Arretes[i].a]=orgA;
           Parent[Arretes[i].b]=orgA;
           // On somme les poids des arrêtes sélectionnées
           poids+=Arretes[i].p;
           // On affiche les arrêtes qui ne créent pas de cycle
           printf("(%d, %d) ",Arretes[i].a,Arretes[i].b);
           arc.push_back(inter[Arretes[i].a]);
           arc.push_back(inter[Arretes[i].b]);
       }
    }
    printf("\n");
    int size=arc.size();
    for(int v=0;v<size;v+=2)
        cout<<"("<<arc[v]<<", "<<arc[v+1]<<")"<<" ";
    printf("\nLe poids optimal est %d\n",poids);
    return 0;
}
