#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef long elementtype;
typedef struct SanPham *Hanghoa;

struct SanPham{
    char masp[10];
    char tensp[50];
    char size[10];
    elementtype gia;
    elementtype soluong;
    struct SanPham *next;
};

void init(Hanghoa *l);
void themcuoi(Hanghoa *l,Hanghoa sanpham);
void docfile(Hanghoa *l, const char filename[]);
int empty(Hanghoa l);
void hienthidanhsachsanpham(Hanghoa l);
void nhapsanpham(Hanghoa l);
void themsanpham(Hanghoa *l);
void SearchMasp(Hanghoa l,char masp[]);
void SearchTensp(Hanghoa l,char tensp[]);
int checkkhoanggia(elementtype min, elementtype max);
void SearchGia(Hanghoa l, elementtype min, elementtype max);
void dispose(Hanghoa *l);
void menu();
void clear_display();
int main(){
    Hanghoa list;
    int test=1,k;
    init(&list);
    docfile(&list,"sp.txt");
    while(test==1){
        menu();
        printf("nhap lua chon: ");
        scanf("%d",&k);
        getchar();
        clear_display();
        switch(k){
            case 1: 
                hienthidanhsachsanpham(list);
                break;
            case 2:
                themsanpham(&list);
                break;
            case 3: 
                char masp[5];
                printf("Nhap ma san pham can tim: ");
                scanf(" %[^\n]",masp);
                SearchMasp(list,masp);
                break;
            case 4:
                char tensp[15];
                printf("Nhap ten san pham can tim: ");
                scanf(" %[^\n]",tensp);
                SearchTensp(list,tensp);
                break;
            case 5:
                elementtype min,max;
                printf("Nhap khoang gia:\n");
                printf("Gia thap nhat: ");
                scanf("%ld",&min);
                printf("Gia cao nhat: ");
                scanf("%ld",&max);
                while(checkkhoanggia(min,max)){
                    clear_display();
                    printf("Khoang gia loi! Xin vui long nhap lai.");
                    printf("Nhap khoang gia:\n");
                    printf("Gia thap nhat: ");
                    scanf("%ld",&min);
                    printf("Gia cao nhat: ");
                    scanf("%ld",&max);
                }
                SearchGia(list,min,max);
                break;
            case 6:
                test=0;
                dispose(&list);
                break;
            default:
                printf("Nhap loi! Xin hay nhap lai.\n");
        }

    }
    return 0;
}

void init(Hanghoa *l){
    *l = NULL;
}
void themcuoi(Hanghoa *l, Hanghoa sanpham){
    if(*l == NULL){
        *l = sanpham;
    }
    else{
        Hanghoa p=*l;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = sanpham;
    }
}
void docfile(Hanghoa *l,const char filename[]){
    FILE *file;
    file = fopen(filename,"r");
    char line[200];
    while(fgets(line,sizeof(line),file)){
        line[strcspn(line,"\n")]=0;
        if(strlen(line)==0) continue;
        Hanghoa temp = malloc(sizeof(*temp));
        temp->next = NULL;
        char *dulieu = strtok(line, "|");
        if (dulieu != NULL) strcpy(temp->masp, dulieu);
        dulieu = strtok(NULL, "|");
        if (dulieu != NULL) strcpy(temp->tensp, dulieu);
        dulieu = strtok(NULL, "|");
        if (dulieu != NULL) strcpy(temp->size, dulieu);
        dulieu = strtok(NULL, "|");
        if (dulieu != NULL) temp->gia = atoll(dulieu);
        dulieu = strtok(NULL, "|");
        if (dulieu != NULL) temp->soluong = atoll(dulieu);
        if(strlen(temp->masp)>0)
        themcuoi(l,temp);
        else free(temp);
    }
    printf("Doc file thanh cong\n");
    fclose(file);
}
int empty(Hanghoa l){
    return l == NULL;
}
void hienthidanhsachsanpham(Hanghoa l){
    if(l == NULL){
        printf("Khong co du lieu\n");
        return;
    } 
    Hanghoa p=l;
    while(p != NULL){
        printf("Ma san pham: %-5s | ",p->masp);
        printf( "Ten san pham: %-15s | ",p->tensp);
        printf( "Size san pham: %-5s | ",p->size);
        printf( "Gia san pham: %-9ld | ",p->gia);
        printf( "So luong san pham con lai: %-5ld |\n",p->soluong);
        p = p->next;
    }
}
void nhapsanpham(Hanghoa l){
    char masp[10],tensp[50],size[10];
    elementtype gia,soluong;
    printf( "thong tin san pham moi\n");
    printf( "Ma san pham: ");
    scanf(" %[^\n]",&masp);
    printf( "Ten san pham: ");
    scanf(" %[^\n]",&tensp);
    printf( "Size san pham: ");
    scanf(" %[^\n]",&size);
    getchar();
    printf( "Gia san pham: ");
    scanf ("%ld",&gia);
    printf( "So luong san pham: ");
    scanf("%ld",&soluong); 
    getchar();
    strcpy(l->masp,masp);
    strcpy(l->tensp,tensp);
    strcpy(l->size,size);
    l->gia = gia;
    l->soluong = soluong;
    l->next = NULL;
}
void themsanpham(Hanghoa *l){
    FILE *file;
    file = fopen("sp.txt","a");
    Hanghoa p = malloc(sizeof(*p));
    p->next = NULL;
    nhapsanpham(p);
    themcuoi(l,p);
    fprintf(file,"\n");
    fprintf(file,"%s | %s | %s | %-9ld | %-5ld",p->masp,p->tensp,p->size,p->gia,p->soluong);
    fclose(file);
}
void SearchMasp(Hanghoa l,char masp[]){
    if(empty(l)){
        printf("Danh sach rong\n");
        return;
    }
    int checksearch=0;
    Hanghoa p=l;
    while(p != NULL){
        if(strstr(p->masp,masp) != NULL){
            printf("Ma san pham: %-5s | ",p->masp);
            printf( "Ten san pham: %-15s | ",p->tensp);
            printf( "Size san pham: %-5s | ",p->size);
            printf( "Gia san pham: %-9ld | ",p->gia);
            printf( "So luong san pham con lai: %-5ld |\n",p->soluong);
            checksearch++;
        }
        p=p->next;
    }
    if(!checksearch){
        printf("Danh sach khong co san pham co ma %s\n ",masp);
    }
}
void SearchTensp(Hanghoa l, char tensp[]){
    if(empty(l)){
        printf("Danh sach rong\n");
        return ;
    }
    int checksearch=0;
    Hanghoa p=l;
    while(p != NULL){
        if(strstr(p->tensp,tensp) != NULL){
            printf("Ma san pham: %-5s | ",p->masp);
            printf( "Ten san pham: %-15s | ",p->tensp);
            printf( "Size san pham: %-5s | ",p->size);
            printf( "Gia san pham: %-9ld | ",p->gia);
            printf( "So luong san pham con lai: %-5ld |\n",p->soluong);
            checksearch++;
        }
        p = p->next;
    }
    if(!checksearch){
        printf("Danh sach khong co san pham co ten %s\n ",tensp);
    }
}
int checkkhoanggia(elementtype min,elementtype max){
    if(min<max || min<0 || max<0) return 0;
    return 1;
}
void SearchGia(Hanghoa l, elementtype min, elementtype max){
    if(empty(l)){
        printf("Danh sach rong\n");
        return ;
    }
    int checksearch=0;
    Hanghoa p=l;
    while(p != NULL){
        if(p->gia>=min && p->gia<=max){
            printf("Ma san pham: %-5s | ",p->masp);
            printf( "Ten san pham: %-15s | ",p->tensp);
            printf( "Size san pham: %-5s | ",p->size);
            printf( "Gia san pham: %-9ld | ",p->gia);
            printf( "So luong san pham con lai: %-5ld |\n",p->soluong);
            checksearch++;
        }
        p = p->next;
    }
    if(!checksearch){
        printf("Danh sach khong co san pham nam trong khoang gia %ld -> %ld\n",min,max);
    }
}
void dispose(Hanghoa *l){
    Hanghoa p;
    while(*l != NULL){
        p=*l;
        *l = (*l)->next;
        free(p);
    }
}
void menu(){
    printf( "--------------MENU------------------\n");
    printf( "1: In danh sach san pham\n");
    printf( "2: Them san pham moi\n");
    printf( "3: Tim kiem san pham theo ma san pham\n");
    printf( "4: Tim kiem san pham theo ten san pham\n");
    printf( "5: Tim kiem san pham theo gia san pham\n");
    printf( "6: thoat chuong trinh\n");
}
void clear_display(){
    system("cls");
}