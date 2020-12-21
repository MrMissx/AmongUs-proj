/*Among Us game features
Objectives:
	1. create number of crewmate and impostor object
	2. create player struct with color_id, status, lifestat
	3. randomize status and color
	4. create number of event and print what happened (the event is completely random in this case)
	5. if all impostor status = dead, WIN
	6. if impostor = crewmate, LOSE
*/


#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Player{
    int color;
    bool impostor;
    int lifestat;
}player[10];
int plyr=-1;
int imp=0;


void clear(){  // clear console
    system("cls");
}


void MenuHeader(){
    puts("============== AMONG US ==============");
    puts("There will be 4 up to 10");
    printf("Insert number of player(s) : ");
    while(plyr < 4 || plyr > 10){
        scanf("%d", &plyr); getchar();
        if (plyr < 4 || plyr > 10){
            puts("Whoaa... you can't play with that player\ninsert a number 4-10");
        }
    }
    printf("%d players\nNext is how many impostor(s) in this game\n", plyr);
    printf("Insert number of impostor(s) (1-3): ");
    while(imp < 1 || imp > 3){
        scanf("%d", &imp); getchar();
        if (imp < 1 || imp > 3){
            puts("Insert only 1-3 please");
        }
    }
    printf("Ok...\n%d impostor(s) and %d crewmate(s)\n", imp, plyr-imp);
}


const char* color(int x){
    switch(x){
        case 1: return "Red";
        case 2: return "Blue";
        case 3: return "Yellow";
        case 4: return "Green";
        case 5: return "Purple";
        case 6: return "Pink";
        case 7: return "White";
        case 8: return "Black";
        case 9: return "Brown";
        case 10: return "Orange";
    }
    return "bug";  // pls don't go to this
}


int GetRandom(){
    return (rand()%plyr)+1;  // random int (1-player count)
}


void GenPlayer(){
    clear();
    puts("Generating Player");
    // color
    int tempc[15]={0};
    for (int i=0; i < plyr; i++){
        bool unique=false;
        int num = GetRandom();
        while(!unique && i != 0){  // Make sure no double color
            for (int j=0; j < 15; j++){
                if(num != tempc[j]){
                    unique = true;
                } else {
                    unique = false;
                    break;
                }
            }
            if(!unique){
                num = GetRandom();
            }
        }
        // printf("Player %d, %d\n", i+1, num);
        tempc[i] = num;
        player[i].color = num;
    }

    // impostor
    for (int i=0; i < imp; i++){
        while(1){  // loop until the random int is unique
            int num = GetRandom();
            if(!player[num].impostor){
                player[num].impostor = true;
                break;
            }
        }
    }

    // set alive status
    for (int i=0; i < plyr; i++){
        player[i].lifestat = 1;
    }
}


void DisplayPlayer(bool reveal){  // add param to reveal impostor
    // display player list
    for (int i=0; i < plyr; i++){
        printf("player %d: \n", i+1);
        printf("    color: %s\n", color(player[i].color));
        if(reveal){  // if wan't to reveal who's impostor
            printf(player[i].impostor ? "    is impostor\n" : "    is crewmate\n");
            printf(player[i].lifestat ? "    Still alive\n" : "    RIP...\n");
        }
        puts("");
    }
}


void next_round(int i){
    printf("Press enter to start round %d\n", i);
    getchar();
}


void kill(){
    int to_kill;
    while(1){  // loop until the random int is unique
        to_kill = GetRandom();
        if(!player[to_kill].impostor){  // don't kill impostor
            if(player[to_kill].lifestat == 1){
                player[to_kill].lifestat = 0;
                printf("%s is dead, He is killed by the impostor\n\n", color(player[to_kill].color));
                break;
            }
        }
    }
}


bool vote(){
    int to_vote;
    bool is_impos;
    while(1){  // loop until the random int is unique
        to_vote = GetRandom();
        if(player[to_vote].lifestat == 1){
            player[to_vote].lifestat = 0;
            printf("%s ejected, voted by the crewmate\n\n", color(player[to_vote].color));
            if(player[to_vote].impostor){
                is_impos = true;
            }else {
                is_impos = false;
            }
            break;
        }
    }
    return is_impos;
}


void Start_The_Game(){
	int round=1;  // round counter
    int crew = plyr-imp;
    while(1){
        // printf("impos = %d, crew = %d\n", imp, crew); // debuging player
        if(imp==0 || imp >= crew){
            if(imp == 0) puts("VICTORY!!!!");
            else if (imp >= crew) puts("DEFEAT!");
            DisplayPlayer(true);
            break;  // exit
        }
        next_round(round);
		printf("Round %d\n", round);
        if(round % 2 != 0){
            kill();
            crew--;
        } else {
            bool impostor = vote();
            if(impostor){  // if impostor voted
                imp--;
            }else{
                crew--;
            }
        }
        round++;
    }
}


int main(){
    srand(time(NULL));  // sanity for random
    MenuHeader();
    puts("Press enter to continue"); getchar();
    GenPlayer();
    DisplayPlayer(false);
    Start_The_Game();
    return 0;
}

