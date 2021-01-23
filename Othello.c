#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int position[8][8];
int count=0;
int possible_continue=0;

typedef struct set{
    int x;
    int y;
    int piece;
    int U;
    int D;
    int R;
    int L;
    int U_R;
    int U_L;
    int D_R;
    int D_L;
}Set;

Set set[60];

int sleep(unsigned long x)
{
    clock_t c1=clock(),c2;

    do{
        if((c2=clock())==-1) return 0;

    }while(1000*(c2-c1)/CLOCKS_PER_SEC<=x);

    return 1;
}

void start(void)
{
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            position[i][j]=0; //0は駒が何も置かれていないマスを示す
        }
    }

    position[3][3]=1; //1は白色の駒を示す
    position[3][4]=2; //2は黒色の駒を示す
    position[4][3]=2;
    position[4][4]=1;
}

void display(void)
{
        puts("------オセロ------");
    for(int i=-1;i<8;i++){
        for(int j=-1;j<8;j++){
            if(i==-1 && j==-1) printf("  ");
            else if(i==-1 && j!=-1){
                printf("%d ",j+1);
                if(j==7) printf("(B)");
            }
            else if(i!=-1 && j==-1) printf("%d ",i+1);
            else{
                switch(position[i][j]){
                case 0:printf("# "); break;
                case 1:printf("● "); break;
                case 2:printf("○ "); break;
                case 3:printf("⋆ "); break;
                }
            }
        }
        putchar('\n');
    }
    puts("(A)");
}

int judgement(int judge,int turn)
{
    if(judge==0){
            if(possible_continue==2){
                printf("\n\n\n\n");
                puts("両者、置ける場所がないのでゲーム終了です！");
                sleep(3200);
                system("clear");
                return 3;
            }
            if(turn==1){
                printf("\n\n\n\n");
                puts("コンピュータの置ける場所がないのでパスされます");
                sleep(2500);
                system("clear");
                turn=2;
                possible_continue++;
            }else if(turn==2){
                printf("\n\n\n\n");
                puts("プレイヤーの置ける場所がないのでパスされます");
                sleep(2500);
                system("clear");
                turn=1;
                possible_continue++;
            }
        }

    return turn;
}

int search(int turn) //1.次に駒を置くことができる場所を探す。2.ゲームが続行可能か判断
{
    int s,t;
    int my_piece=turn;
    int enemy_piece;
    int get_piece=0;
    int save_get_piece=0;
    int over_num;
    int overflow;

    switch(turn){
        case 1:enemy_piece=2; break;
        case 2:enemy_piece=1; break;
    }

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){

            if(position[i][j]==0){

                if(i!=0 && i!=1){ //上
                    over_num=i-1;
                    overflow=0;
                    save_get_piece=get_piece;
                    for(s=i-1;s>=0;s--){
                        if(s==i-1){
                            if(position[s][j]==my_piece || position[s][j]==0){
                                set[count].U=0;
                                break;
                            }
                            else{
                                get_piece++;
                                overflow++;
                            }
                        }else{
                            if(position[s][j]==enemy_piece){
                                get_piece++;
                                overflow++;
                            }
                            else if(position[s][j]==my_piece){
                                set[count].U=1;
                                break;
                            }else if(position[s][j]==0){
                                get_piece=save_get_piece;
                                set[count].U=0;
                                break;
                            }
                        }
                        if(overflow>over_num){
                            get_piece=save_get_piece;
                                set[count].U=0;
                                break;
                        }
                    }
                }

                if(i!=6 && i!=7){ //下
                    over_num=7-i-1;
                    overflow=0;
                    save_get_piece=get_piece;
                    for(s=i+1;s<=7;s++){
                        if(s==i+1){
                            if(position[s][j]==my_piece || position[s][j]==0){
                                set[count].D=0;
                                break;
                            }
                            else{
                                get_piece++;
                                overflow++;
                            }
                        }else{
                            if(position[s][j]==enemy_piece){
                                get_piece++;
                                overflow++;
                            }
                            else if(position[s][j]==my_piece){
                                set[count].D=1;
                                break;
                            }else if(position[s][j]==0){
                                get_piece=save_get_piece;
                                set[count].D=0;
                                break;
                            }
                        }
                        if(overflow>over_num){
                            get_piece=save_get_piece;
                            set[count].D=0;
                            break;
                        }
                    }
                }

                if(j!=6 && j!=7){ //右
                    over_num=7-j-1;
                    overflow=0;
                    save_get_piece=get_piece;
                    for(t=j+1;t<=7;t++){
                        if(t==j+1){
                            if(position[i][t]==my_piece || position[i][t]==0){
                                set[count].R=0;
                                break;
                            }
                            else{
                                get_piece++;
                                overflow++;
                            }
                        }else{
                            if(position[i][t]==enemy_piece){
                                get_piece++;
                                overflow++;
                            }
                            else if(position[i][t]==my_piece){
                                set[count].R=1;
                                break;
                            }else if(position[i][t]==0){
                                get_piece=save_get_piece;
                                set[count].R=0;
                                break;
                            }
                        }
                        if(overflow>over_num){
                            get_piece=save_get_piece;
                            set[count].R=0;
                            break;
                        }
                    }
                }

                if(j!=0 && j!=1){ //左
                    over_num=j-1;
                    overflow=0;
                    save_get_piece=get_piece;
                    for(t=j-1;t>=0;t--){
                        if(t==j-1){
                            if(position[i][t]==my_piece || position[i][t]==0){
                                set[count].L=0;
                                break;
                            }
                            else{
                                get_piece++;
                                overflow++;
                            }
                        }else{
                            if(position[i][t]==enemy_piece){
                                get_piece++;
                                overflow++;
                            }
                            else if(position[i][t]==my_piece){
                                set[count].L=1;
                                break;
                            }else if(position[i][t]==0){
                                get_piece=save_get_piece;
                                set[count].L=0;
                                break;
                            }
                        }
                        if(overflow>over_num){
                            get_piece=save_get_piece;
                            set[count].L=0;
                            break;
                        }
                    }
                }

                if(i!=0 && i!=1 && j!=6 && j!=7){ //右上
                    s=i; t=j;
                    while(1){
                        s--;
                        t++;
                        if(s==0){
                            over_num=i-1;
                            break;
                        }else if(t==7){
                            over_num=7-j-1;
                            break;
                        }
                    }
                    overflow=0;
                    save_get_piece=get_piece;
                    t=j+1;
                    for(s=i-1;s>=0;s--){
                        if(s==i-1){
                            if(position[s][t]==my_piece || position[s][t]==0){
                                set[count].U_R=0;
                                break;
                            }
                            else{
                                get_piece++;
                                overflow++;
                                t++;
                            }
                        }else{
                            if(position[s][t]==enemy_piece){
                                get_piece++;
                                overflow++;
                                t++;
                            }else if(position[s][t]==my_piece){
                                set[count].U_R=1;
                                break;
                            }else if(position[s][t]==0){
                                get_piece=save_get_piece;
                                set[count].U_R=0;
                                break;
                            }
                        }
                        if(overflow>over_num){
                            get_piece=save_get_piece;
                            set[count].U_R=0;
                            break;
                        }
                    }
                }

                if(i!=0 && i!=1 && j!=0 && j!=1){ //左上
                    if(i>=j) over_num=j-1;
                    else over_num=i-1;
                    overflow=0;
                    save_get_piece=get_piece;
                    t=j-1;
                    for(s=i-1;s>=0;s--){
                        if(s==i-1){
                            if(position[s][t]==my_piece || position[s][t]==0){
                                set[count].U_L=0;
                                break;
                            }
                            else{
                                get_piece++;
                                overflow++;
                                t--;
                            }
                        }else{
                            if(position[s][t]==enemy_piece){
                                get_piece++;
                                overflow++;
                                t--;
                            }else if(position[s][t]==my_piece){
                                set[count].U_L=1;
                                break;
                            }else if(position[s][t]==0){
                                get_piece=save_get_piece;
                                set[count].U_L=0;
                                break;
                            }
                        }
                        if(overflow>over_num){
                            get_piece=save_get_piece;
                            set[count].U_L=0;
                            break;
                        }
                    }
                }

                if(i!=6 && i!=7 && j!=6 && j!=7){ //右下
                    if(i>=j) over_num=7-i-1;
                    else over_num=7-j-1;
                    overflow=0;
                    save_get_piece=get_piece;
                    t=j+1;
                    for(s=i+1;s<=7;s++){
                        if(s==i+1){
                            if(position[s][t]==my_piece || position[s][t]==0){
                                set[count].D_R=0;
                                break;
                            }
                            else{
                                get_piece++;
                                overflow++;
                                t++;
                            }
                        }else{
                            if(position[s][t]==enemy_piece){
                                get_piece++;
                                overflow++;
                                t++;
                            }else if(position[s][t]==my_piece){
                                set[count].D_R=1;
                                break;
                            }else if(position[s][t]==0){
                                get_piece=save_get_piece;
                                set[count].D_R=0;
                                break;
                            }
                        }
                        if(overflow>over_num){
                            get_piece=save_get_piece;
                            set[count].D_R=0;
                            break;
                        }
                    }
                }

                if(i!=6 && i!=7 && j!=0 && j!=1){ //左下
                    s=i; t=j;
                    while(1){
                        s++;
                        t--;
                        if(s==7){
                            over_num=7-i-1;
                            break;
                        }else if(t==0){
                            over_num=j-1;
                            break;
                        }
                    }
                    overflow=0;
                    save_get_piece=get_piece;
                    t=j-1;
                    for(s=i+1;s<=7;s++){
                        if(s==i+1){
                            if(position[s][t]==my_piece || position[s][t]==0){
                                set[count].D_L=0;
                                break;
                            }
                            else{
                                get_piece++;
                                overflow++;
                                t--;
                            }
                        }else{
                            if(position[s][t]==enemy_piece){
                                get_piece++;
                                overflow++;
                                t--;
                            }else if(position[s][t]==my_piece){
                                set[count].D_L=1;
                                break;
                            }else if(position[s][t]==0){
                                get_piece=save_get_piece;
                                set[count].D_L=0;
                                break;
                            }
                        }
                        if(overflow>over_num){
                            get_piece=save_get_piece;
                            set[count].D_L=0;
                            break;
                        }
                    }
                }
            }
            if(get_piece>0){
                set[count].x=i;
                set[count].y=j;
                set[count++].piece=get_piece;
                save_get_piece=0;
                get_piece=0;
            }
        }
    }

    return count;
}

void turn_over(Set setting,int turn)
{
    int attacker=turn;
    int enemy;

    switch(attacker){
        case 1:enemy=2; break;
        case 2:enemy=1; break;
    }

    if(setting.U==1){ //上
        for(int i=setting.x-1;i>=0;i--){
            if(position[i][setting.y]==enemy){
                position[i][setting.y]=attacker;
                display();
                sleep(300);
                system("clear");
            }
            else break;
        }
    }

    if(setting.D==1){ //下
        for(int i=setting.x+1;i<8;i++){
            if(position[i][setting.y]==enemy){
                position[i][setting.y]=attacker;
                display();
                sleep(300);
                system("clear");
            }
            else break;
        }
    }

    if(setting.R==1){ //右
        for(int j=setting.y+1;j<8;j++){
            if(position[setting.x][j]==enemy){
                position[setting.x][j]=attacker;
                display();
                sleep(300);
                system("clear");
            }
            else break;
        }
    }

    if(setting.L==1){ //左
        for(int j=setting.y-1;j>=0;j--){
            if(position[setting.x][j]==enemy){
                position[setting.x][j]=attacker;
                display();
                sleep(300);
                system("clear");
            }
            else break;
        }
    }

    if(setting.U_R==1){ //右上
        int i=setting.x-1;
        int j=setting.y+1;
        do{
            if(position[i][j]==enemy){
                position[i][j]=attacker;
                display();
                sleep(300);
                system("clear");
            }
            else break;
            i--;
            j++;
        }while(i!=0 && j!=7);
    }

    if(setting.U_L==1){ //左上
        int i=setting.x-1;
        int j=setting.y-1;
        do{
            if(position[i][j]==enemy){
                position[i][j]=attacker;
                display();
                sleep(300);
                system("clear");
            }
            else break;
            i--;
            j--;
        }while(i!=0 && j!=0);
    }

    if(setting.D_R==1){ //右下
        int i=setting.x+1;
        int j=setting.y+1;
        do{
            if(position[i][j]==enemy){
                position[i][j]=attacker;
                display();
                sleep(300);
                system("clear");
            }
            else break;
            i++;
            j++;
        }while(i!=7 && j!=7);
    }

    if(setting.D_L==1){ //左下
        int i=setting.x+1;
        int j=setting.y-1;
        do{
            if(position[i][j]==enemy){
                position[i][j]=attacker;
                display();
                sleep(300);
                system("clear");
            }
            else break;
            i++;
            j--;
        }while(i!=7 && j!=0);
    }

    position[setting.x][setting.y]=attacker;

    for(int i=0;i<count;i++){
        set[i].U=0;
        set[i].D=0;
        set[i].R=0;
        set[i].L=0;
        set[i].U_R=0;
        set[i].U_L=0;
        set[i].D_R=0;
        set[i].D_L=0;
    }

    count=0;
}

void player(void)
{
    char p_a[256],p_b[256];
    int a,b;
    int numCorrect;
    int flag=0;
    int send_p;


    do{

        printf("A: "); 
        scanf("%s",p_a);
        printf("B: ");
        scanf("%s",p_b);

        if((p_a>=0 || p_a<=9) || (p_b>=0 || p_b<=9)){
            a=atoi(p_a);
            b=atoi(p_b);
            for(int i=0;i<count;i++){
                if(set[i].x==a-1 && set[i].y==b-1){
                    flag=1;
                    send_p=i;
                    break;
                }
        }
        if(flag==0) puts("その場所に置くことは出来ません");
        }else{
            puts("正しい数字を入力してください");
            continue;
        }

    }while(flag==0);

    position[set[send_p].x][set[send_p].y]=2;

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(position[i][j]==3) position[i][j]=0;
        }
    }

    system("clear");

    display();
    sleep(300);

    system("clear");

    turn_over(set[send_p],2);
}

void computer(void)
{
    int thinking_time;
    int computer_motion;
    int corner[4];
    int corner_count=0;
    int max_num=0;
    int max_piece[64];
    int max_piece_count=0;
    int send_c;

    srand(time(NULL));

    puts("コンピュータ考え中");

    thinking_time=(rand()%3+2)*1000;

    sleep(thinking_time);

    for(int i=0;i<count;i++){
        if(set[i].x==0 && set[i].y==0) corner[corner_count++]=i;
        if(set[i].x==0 && set[i].y==7) corner[corner_count++]=i;
        if(set[i].x==7 && set[i].y==0) corner[corner_count++]=i;
        if(set[i].x==7 && set[i].y==7) corner[corner_count++]=i;
    }

    for(int i=0;i<count;i++){
        if(max_num<=set[i].piece) max_num=set[i].piece;
    }

    for(int i=0;i<count;i++){
        if(set[i].piece==max_num) max_piece[max_piece_count++]=i;
    }

    if(corner_count==0){
        computer_motion=rand()%3;
        if(computer_motion==0){
            send_c=rand()%count;
        }else{
            send_c=max_piece[rand()%max_piece_count];
        }
    }else{
        send_c=corner[rand()%corner_count];
    }

    position[set[send_c].x][set[send_c].y]=1;

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(position[i][j]==3) position[i][j]=0;
        }
    }

    system("clear");

    display();
    sleep(300);
    
    system("clear");

    turn_over(set[send_c],1);

}

void result(void)
{
    system("clear");

    int black=0,white=0;
    char finish[]="GAME_OVER";

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(position[i][j]==1) white++;
            if(position[i][j]==2) black++;
        }
    }

    printf("\n\n\n\n");

    printf("プレイヤー•••%d コンピュータ•••%d\n",black,white);
    sleep(1500);

    putchar('\n');

    if(black>white){
        puts("あなたの勝利です！  ★Congratulation★");
    }else if(black==white){
        puts("引き分けです");
    }else{
        puts("あなたの負けです");
    }
    sleep(4000);

    system("clear");

    printf("\n\n\n\n\n");

    for(int i=0;i<strlen(finish);i++){
        printf("%c",finish[i]);
        fflush(stdout);
        sleep(150);
    }
    sleep(3300);

    for(int i=0;i<strlen(finish);i++){
        printf("\b \b");
        fflush(stdout);
        sleep(150);
    }

    printf("\n\n\n\n");
}

int main(void)
{
    int turn=2; //next=1...コンピューターのターン next=2...プレイヤーのターン
    int now_playing;
    int judge=1;
    int possible_continue=0;
    int game_set=0;

    start();
    display();

    sleep(2000);
    system("clear");
    printf("\n\n\n\n\nゲーム開始！！");
    fflush(stdout);
    sleep(2000);
    system("clear");

    while(1){
        now_playing=turn;
        judge=search(turn);

        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(position[i][j]==0) game_set++;
            }
        }

        if(game_set==0){
            system("clear");
            printf("\n\n\n\n\nゲーム終了");
            fflush(stdout);
            sleep(3000);
            break;
        }

        game_set=0;

        for(int i=0;i<count;i++){
            position[set[i].x][set[i].y]=3;
        }
        turn=judgement(judge,turn);

        if(turn==3) break;

        if(now_playing!=turn) continue;

        possible_continue=0;
    
        display();

        switch(turn){
            case 1:computer(); turn=2; break;
            case 2:puts("※ ⋆マークに駒を置くことが出来ます"); player(); turn=1; break;
        }

        display();
        sleep(3000);
        system("clear");
    }

    result();

    return 0;
}