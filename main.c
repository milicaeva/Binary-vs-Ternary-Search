#include <stdio.h>
#include <stdlib.h>

int nad(int n, int k){
    if (k==0 || k==n) return 1;
    int rez=1;

    for (int i=1; i<=k; i++) {
        rez*=(n-i+1);
        rez/=i;
    }
    return rez;
}

int binarnaPretraga(int* niz,int n,int kljuc){
    int d=0,g=n/2,brojac=0;
    while (d<=g){
        brojac++;
        int s=(d+g)/2;
        printf("\nKorak: %d \n\n",brojac);
        printf("Gornja granica: %d\n",g);
        printf("Donja granica: %d\n",d);
        printf("Sredina: %d\n\n",s);
        printf("Niz:\n");
        for (int k=d;k<=g;k++){
            printf("%d ",niz[k]);
        }
        printf("\n");
        if (niz[s]==kljuc) return brojac;
        else if(niz[s]>kljuc) g=s-1;
        else d=s+1;
    }
    return brojac;
}

int ternarnaPretraga(int* niz, int n, int kljuc){
    int d=0,g=n/2,brojac=0;
    while (d<=g){
        brojac++;
        int s1=d+(g-d)/3, s2=g-(g-d)/3;
        printf("\nKorak: %d \n\n",brojac);
        printf("Gornja granica: %d\n",g);
        printf("Donja granica: %d\n",d);
        printf("Sredina 1: %d\n",s1);
        printf("Sredina 2: %d\n\n",s2);
        printf("Niz:\n");
        for (int k=d; k<=g; k++){
            printf("%d ",niz[k]);
        }
        printf("\n");
        if (niz[s1]==kljuc || niz[s2]==kljuc){
            printf("\nKljuc %d je pronadjen!\n",kljuc);
            return brojac;
        }
        if (niz[s1]>kljuc) g=s1-1;
        else if (niz[s2]<kljuc) d=s2+1;
        else{
            d=s1+1; g=s2-1;
        }
    }
    printf("\nKljuc %d nije pronadjen!\n",kljuc);
    return brojac;
}

int** lozanicevTrougao(int n) {
    int** trougao = malloc(n*sizeof(int*));
    for (int i=0; i<n; i++) {
        trougao[i] = malloc((i+1)*sizeof(int));
        for (int j=0; j<=i; j++) {
            if (j==0 || j==i) {
                trougao[i][j] = 1;
            }
            else {
                int ind = 0;
                if (i%2==1 || j%2==0) ind = 1;
                int pom1=i/2, pom2=j/2;
                trougao[i][j]=0.5*(nad(i,j)+ind*nad(pom1,pom2));
            }
        }
    }
    return trougao;
}

void ispisiTrougao(int** trougao,int n){
    for (int i=0; i<n; i++) {
        for (int j=0; j<n-i; j++) printf("   ");
        for (int j=0; j<=i; j++) printf("%6d", trougao[i][j]);
        printf("\n");
    }
}

int* simulacija(int** matrica){
    int redni, brKljuceva,brojacBin,brojacTer,zbirBin=0,zbirTer=0;

    printf("Unesi redni broj reda u kojem zelis da se izvrsi pretraga (indeksi od nule): ");
    scanf("%d",&redni);
    printf("Unesi broj kljuceva: ");
    scanf("%d",&brKljuceva);

    int* red=malloc(brKljuceva*sizeof(int));
    for (int i=0; i<brKljuceva; i++){
        printf("Kljuc %d:",i+1);
        scanf(" %d",&red[i]);
    }
    putchar('\n');
    for (int i=0; i<brKljuceva; i++){
        printf("Binarna pretraga za kljuc %d: \n",red[i]);
        brojacBin=binarnaPretraga(matrica[redni],redni,red[i]);
        printf("\nTernarna pretraga za kljuc %d: \n",red[i]);
        brojacTer=ternarnaPretraga(matrica[redni],redni,red[i]);
        putchar('\n');
        zbirBin+=brojacBin;
        zbirTer+=brojacTer;
    }
    free(red);
    int* resenje=malloc(3*sizeof(int));
    resenje[0]=brKljuceva; resenje[1]=zbirBin; resenje[2]=zbirTer;
    return resenje;
}

int main() {
    int br,n, *resenje=NULL,** trougao=NULL;
    while(1){
        printf("1. Napravi Lozanicev trougao\n2. Pokreni simulaciju\n3. Ispisi performanse\n0. Prekini izvrsavanje programa\n\nIzaberi:");
        scanf("%d",&br);
        putchar('\n');
        if(br<0 || br>3) {
            printf("Izabrao/la si opciju koja ne postoji!\nPokusaj ponovo!\n");
            continue;
        }
        if(br==0){
            for (int i=0; i<n; i++) free(trougao[i]);
            free(trougao);
            exit(0);
        }
        if(br==1) {
            printf("Unesi broj redova u Lozanicevom trouglu: ");
            scanf("%d",&n);
            putchar('\n');
            trougao=lozanicevTrougao(n);
            ispisiTrougao(trougao,n);
            putchar('\n');
        }
        if(br==2) {
            if(trougao==NULL) printf("Ne moze da se uradi simulacija ako se ne kreira Lozanicev trougao!");
            else resenje=simulacija(trougao);
        }
        if(br==3) {
            if(resenje==NULL) printf("Ne mogu se ispisati performanse ako se ne pokrene simulacija!");
            else{
                double rezBin=(double)resenje[1]/resenje[0];
                double rezTer=(double)resenje[2]/resenje[0];
                printf("|  Binarna pretraga   |   Ternarna pretraga   |\n");
                printf("+---------------------+-----------------------+\n");
                printf("|        %5.2f        |         %5.2f         |\n", rezBin, rezTer);
                printf("+---------------------+-----------------------+\n");
                free(resenje);
            }
        }
    }
}