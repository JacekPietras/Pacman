
#define MAX_WIERZCHOLKOW 8000 
#define MAX_WIELOKATOW 8000 

typedef struct{
    float x,y,z;
}wierzcholek;

typedef struct{
    int a,b,c;
}wielokat;

typedef struct{
    float u,v;
}punkt_tekstury;

typedef struct {
	char name[20];
    
	int ile_wierzcholkow;
    int ile_wielokatow;

    wierzcholek wierzcholki[MAX_WIERZCHOLKOW]; 
    wielokat wielokaty[MAX_WIELOKATOW];
    punkt_tekstury punkty_tekstur[MAX_WIERZCHOLKOW];
    int id_tekstury;
} siatka;
