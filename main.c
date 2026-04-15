#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef long long elementtype;
typedef struct SanPham *Hanghoa;

struct SanPham{
    char masp[10];
    char tensp[50];
    char size[10];
    elementtype gia;
    elementtype soluong;
    struct SanPham *next;
};

void init(Hanghoa l);
void themcuoi(Hanghoa l,Hanghoa sanpham);
void docfile(Hanghoa l, const char filename[]);
void hienthidanhsachsanpham(Hanghoa l);
void nhapsanpham(Hanghoa l);
void themsanpham(Hanghoa l);
void SearchMasp(Hanghoa l);
void SearchTensp(Hanghoa l);
void SearchGia(Hanghoa l);
void dispose(Hanghoa l);
void menu();
int main(){
    Hanghoa list;
    int test=1,k;
    init(list);
    docfile(list,"sp.txt");
    list=list->next; 
    while(test==1){
        menu();
        printf("nhap lua chon: ");
        scanf("%d",&k);
        getchar();
        switch(k){
            case 1: 
                hienthidanhsachsanpham(list);
                break;
            case 2:
                themsanpham(list);
                break;
            case 3:
                test=0;
                dispose(list);
                break;
            default:
                printf("Nhap loi! Xin hay nhap lai.\n");
        }

    }
    return 0;
}

void init(Hanghoa l){
    l = NULL;
}
void themcuoi(Hanghoa l, Hanghoa sanpham){
    if(l == NULL){
        l = sanpham;
    }
    else{
        Hanghoa p=l;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = sanpham;
    }
}
void docfile(Hanghoa l,const char filename[]){
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
void hienthidanhsachsanpham(Hanghoa l){
    if(l == NULL){
        printf("Khong co du lieu\n");
        return;
    } 
    Hanghoa p=l;
    while(p != NULL){
        printf("Ma san pham: %-3s | ",p->masp);
        printf( "Ten san pham: %-3s | ",p->tensp);
        printf( "Size san pham: %-3s | ",p->size);
        printf( "Gia san pham: %-3ld | ",p->gia);
        printf( "So luong san pham con lai: %-3ld |\n",p->soluong);
        p = p->next;
    }
}
void nhapsanpham(Hanghoa l){
    char masp[10],tensp[50],size[10];
    elementtype gia,soluong;
    printf( "thong tin san pham moi\n");
    printf( "Ma san pham: ");
    scanf("%s",&masp);
    printf( "Ten san pham: ");
    scanf("%s",&tensp);
    printf( "Size san pham: ");
    scanf("%s",&size);
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
void themsanpham(Hanghoa l){
    FILE *file;
    file = fopen("sp.txt","a");
    Hanghoa p = malloc(sizeof(*p));
    p->next = NULL;
    nhapsanpham(p);
    themcuoi(l,p);
    fprintf(file,"\n");
    fprintf(file,"%s | %s | %s | %-3ld | %-8ld",p->masp,p->tensp,p->size,p->gia,p->soluong);
    fclose(file);
}
void dispose(Hanghoa l){
    Hanghoa p;
    while(l != NULL){
        p=l;
        l = l->next;
        free(p);
    }
}
void menu(){
    printf( "--------------MENU------------------\n");
    printf( "1: In danh sach san pham\n");
    printf( "2: Them san pham moi\n");
    printf( "3: thoat chuong trinh\n");
}