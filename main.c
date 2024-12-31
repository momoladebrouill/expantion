#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define VIDE 0
// Equipes Lupercule, Vazogo et Cougilis
#define LUP 1
#define VAZ 2
#define COU 3

typedef struct cell{
    bool gen;
    unsigned int type:2;
}cell;

typedef struct grid{
    int w;
    int h;
    cell * t;
} grid;


bool validpos(grid *g, int x,int y){
    return 0 <= x && x < g->w && 0 <= y && y < g->h;
}

int convert_to_addr(grid *g, int x, int y){
    return y*g->w + x;
}

void set(grid *g,bool gen, int x,int y, int v){
    if(validpos(g,x,y)){
        int pos = convert_to_addr(g,x,y);
        g->t[pos].gen = gen;
        g->t[pos].type = v;
    }
}

cell * get(grid *g, int x, int y){
    if(validpos(g,x,y)){
        return g->t+convert_to_addr(g,x,y);
    }
    return NULL;
}

bool exists_void(grid *g){
    for(int i=0;i<g->w*g->h;i++){
        if(g->t[i].type == VIDE){
            return 1;
        }
    }
    return 0;
}

void draw(grid *g){
    for(int y=0;y<g->h;y++){
        for(int x=0;x<g->w;x++){
            char c = '.';
            int type = get(g,x,y)->type;
            if(type == LUP){
                c = '4';
            } else if(type == VAZ){
                c = '5';
            } else if(type == COU){
                c = '6';
            } else if(type == VIDE){
                c = '0';
            } else{
                c = '0';
                printf("%d",type);
            }
            char lettre = '@';
            if(c == '0'){
                lettre = '0' + get(g,x,y)->type;
            }
            printf("\033[3%cm%c\033[0m",c,lettre);
        }
        printf("\n");
    }
}

bool is_eatable(cell *vois){
    return (bool) vois && vois->type == VIDE;
}

int nb_vois_vide(grid *g, int x, int y){
    int qqty = 0;
    for(int dy=-1;dy<2;dy++){
        for(int dx=-1;dx<2;dx++){
            cell * vois = get(g,x+dx,y+dy);
            qqty += is_eatable(vois);
        }
    }
    return qqty;
}

// mettre mon voisin i à la ma valeur 
void set_vois_n(grid *g, bool gen, int x, int y, int i){
    int qqty = 0;
    for(int dy=-1;dy<2;dy++){
        for(int dx=-1;dx<2;dx++){
            cell * vois = get(g,x+dx,y+dy);
            if(qqty == i && is_eatable(vois)){
                set(g,gen,x+dx,y+dy,get(g,x,y)->type);
                return;
            }
            qqty += is_eatable(vois);
        }
    }
}


void update(grid *g, int gen){
    for(int y = 0; y<g->h;y++){
        for(int x = 0; x<g->w;x++){
            int type = get(g,x,y)->type;
            if(type!=VIDE  && get(g,x,y)->gen != gen){
                int n = nb_vois_vide(g,x,y);
                if(n)
                    set_vois_n(g,gen,x,y,rand()%n);
            }
        }
    }
}


int main(int argv, char *argc[]){
    srand(time(NULL));
    int w,h;
    if(argv == 3){
        w = atoi(argc[1]);
        h = atoi(argc[2]);
    }else{
        printf("Usage : ./fight [width heigth]\n");
        w = 25;
        h = 25;
    }
    printf("Using size w = %d, h = %d\n", w,h);

    grid *g = malloc(sizeof(grid));
    int size = w*h;
    g->w = w;
    g->h = h;
    cell *t = calloc(size,sizeof(cell));
    g->t = t;
    int current_gen = 1;
    set(g,0,w/2-1,h/2-1,LUP);
    set(g,0,w/2+1,h/2+1,VAZ);
    set(g,0,w/2+1,h/2-1,COU);
    while(exists_void(g)){
        current_gen = !current_gen;
        update(g,current_gen);
        draw(g);
        printf("Press enter to continue\n");
        getchar();
    }
}
