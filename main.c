#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef long elementtype;
typedef struct SanPham *Hanghoa;
int save = 1;

struct SanPham{
    char masp[10];
    char tensp[50];
    char size[10];
    elementtype gia;
    elementtype soluong;
    struct SanPham *next;
};

// khoi tao va doc file
void init(Hanghoa *l);
void themcuoi(Hanghoa *l,Hanghoa sanpham);
void docfile(Hanghoa *l, const char filename[]);
int empty(Hanghoa l);

// out
void hienthidanhsachsanpham(Hanghoa l);

void nhapsanpham(Hanghoa l);
Hanghoa checksanpham(Hanghoa l, Hanghoa p);
// Hanghoa travesanphamtrung(Hanghoa l, Hanghoa p);
// them sp
void themsanpham(Hanghoa *l);

// search
void SearchMasp(Hanghoa l,char masp[]);
void SearchTensp(Hanghoa l,char tensp[]);
int checkkhoanggia(elementtype min, elementtype max);
void SearchGia(Hanghoa l, elementtype min, elementtype max);
void search(Hanghoa l);

// sx
void sapxeptheoMasp(Hanghoa l);
void sapxeptheoTensp(Hanghoa l);
void sapxeptheoGiasp(Hanghoa l);
void sapxeptheoSLsp(Hanghoa l);
void sx(Hanghoa *l);

// xoa
void xoa1sp(Hanghoa *l);
void xoansp(Hanghoa *l, int n);
void xoa(Hanghoa *l);

// update
void updatesp(Hanghoa l);
void updt(Hanghoa *l);

// save
void save_file(Hanghoa l);

// menu
void dispose(Hanghoa *l);
void menu_timkiem();
void menu_sx();
void menu_update();
void menu_xoa();
void save_menu();
void menu();
void clear_display();
void stop_display();

int main(){
    Hanghoa list;
    int test=1,k;
    init(&list);
    docfile(&list,"sp.txt");
    while(test==1){
        menu();
        printf("nhap lua chon: ");
        while (scanf("%d", &k) != 1) {
            printf("Loi: Vui long nhap SO! Nhap lua chon: ");
            while(getchar() != '\n');
        }
        clear_display();
        switch(k){
            case 1: 
                hienthidanhsachsanpham(list);
                stop_display();
                break;
            case 2:
                themsanpham(&list);
                stop_display();
                save =0;
                break;
            case 3:
                search(list);
                break;
            case 4: 
                sx(&list);
                break;
            case 5:
                xoa(&list);
                break;
            case 6:
                updt(&list);
                break;
            case 7:
                save_file(list);
                printf("Luu du lieu thanh cong\n");
                stop_display();
                break;
            case 0:
                if(save == 0){
                    save_menu();
                    int savefile;
                    printf("Nhap lua chon: ");
                    if(scanf("%d",&savefile)==1 && savefile==1) save_file(list);
                    printf("Luu du lieu thanh cong\n");
                }
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
    printf("%-10s | %-20s | %-10s | %-15s | %-10s\n", 
           "Ma SP", "Ten San Pham", "Size", "Gia (VND)", "So luong");
    printf("-----------------------------------------------------------------------------\n");
    Hanghoa p = l;
    while(p != NULL){
        printf("%-10s | %-20s | %-10s | %-15ld | %-10ld\n", 
               p->masp, p->tensp, p->size, p->gia, p->soluong);
        p = p->next;
    }
}
void nhapsanpham(Hanghoa l){
    printf("--- Thong tin san pham moi ---\n");
    printf("Ma san pham: ");
    scanf(" %[^\n]", l->masp);
    
    printf("Ten san pham: ");
    scanf(" %[^\n]", l->tensp);
    
    printf("Size san pham: ");
    scanf(" %[^\n]", l->size);
    printf("Gia san pham: ");
    while (scanf("%ld", &l->gia) != 1 || l->gia <= 0) {
        printf("Loi: Gia phai la so va khong duoc am. Moi nhap lai: ");
        while(getchar() != '\n'); 
    }
    printf("So luong san pham: ");
    while (scanf("%ld", &l->soluong) != 1 || l->soluong <= 0) {
        printf("Loi: So luong phai la so va khong duoc am. Moi nhap lai: ");
        while(getchar() != '\n'); 
    }
    getchar(); 
    l->next = NULL;
}
Hanghoa checksanpham(Hanghoa l, Hanghoa p){
    if(empty(l)) return NULL;
    Hanghoa q=l;
    while (q!=NULL){
        if(strcmp(q->masp,p->masp)==0 || strcmp(q->tensp,p->tensp)==0 ) return q;
        q = q->next;
    }
    return NULL;
}
void themsanpham(Hanghoa *l){
    Hanghoa p = malloc(sizeof(*p));
    p->next = NULL;
    int k = 0;
    nhapsanpham(p);
    Hanghoa q = checksanpham(*l, p);
    while(q != NULL){
        printf("\nDU LIEU SAN PHAM MOI TRUNG VOI SAN PHAM HIEN CO!\n");
        printf("1: Thay the du lieu cu\n");
        printf("2: Nhap lai du lieu san pham moi\n");
        printf("Nhap lua chon: ");
        scanf("%d", &k);
        getchar(); 
        
        if(k == 1){
            strcpy(q->tensp, p->tensp);
            strcpy(q->size, p->size);
            q->gia = p->gia;
            q->soluong = p->soluong;
            
            printf("-> Da thay the du lieu san pham thanh cong!\n");
            free(p); 
            return;
        }
        else if (k == 2){
            nhapsanpham(p);
            q = checksanpham(*l, p); 
        }
        else{
            printf("Lua chon loi! Vui long nhap lai.\n");
        }
    }
    themcuoi(l, p);
    printf("-> Them san pham moi thanh cong!\n");
}

// Tim kiem
void SearchMasp(Hanghoa l,char masp[]){
    if(empty(l)){
        printf("Danh sach rong\n");
        return;
    }
    int checksearch=0;
    Hanghoa p=l;
    printf("%-10s | %-20s | %-10s | %-15s | %-10s\n", 
           "Ma SP", "Ten San Pham", "Size", "Gia (VND)", "So luong");
    printf("-----------------------------------------------------------------------------\n");
    while(p != NULL){
        if(strstr(p->masp,masp) != NULL){
            printf("%-10s | %-20s | %-10s | %-15ld | %-10ld\n", 
               p->masp, p->tensp, p->size, p->gia, p->soluong);
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
    printf("%-10s | %-20s | %-10s | %-15s | %-10s\n", 
           "Ma SP", "Ten San Pham", "Size", "Gia (VND)", "So luong");
    printf("-----------------------------------------------------------------------------\n");
    while(p != NULL){
        if(strstr(p->tensp,tensp) != NULL){
            printf("%-10s | %-20s | %-10s | %-15ld | %-10ld\n", 
               p->masp, p->tensp, p->size, p->gia, p->soluong);
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
    printf("%-10s | %-20s | %-10s | %-15s | %-10s\n", 
           "Ma SP", "Ten San Pham", "Size", "Gia (VND)", "So luong");
    printf("-----------------------------------------------------------------------------\n");
    while(p != NULL){
        if(p->gia>=min && p->gia<=max){
            printf("%-10s | %-20s | %-10s | %-15ld | %-10ld\n", 
               p->masp, p->tensp, p->size, p->gia, p->soluong);
            checksearch++;
        }
        p = p->next;
    }
    if(!checksearch){
        printf("Danh sach khong co san pham nam trong khoang gia %ld -> %ld\n",min,max);
    }
}
void search(Hanghoa l){\
    int k,test = 1;
    menu_timkiem();
    while(test){
        test = 0;
        printf("Nhap lua chon: ");
        scanf("%d",&k);
        clear_display();
        switch(k){
            case 1:
                char masp[5];
                printf("Nhap ma san pham can tim: ");
                scanf(" %[^\n]",masp);
                SearchMasp(l,masp);
                stop_display();
                break;
            case 2:
                char tensp[15];
                printf("Nhap ten san pham can tim: ");
                scanf(" %[^\n]",tensp);
                SearchTensp(l,tensp);
                stop_display();
                break;
            case 3:
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
                SearchGia(l,min,max);
                stop_display();
                break;
            case 0:
                break;
            default:
                printf("Nhap loi! Xin vui long nhap lai\n");
                menu_timkiem();
                test=1;
                break;
        }
    }
}

// SX
void sx(Hanghoa *l){
    int k,test = 1;
    menu_sx();
    while(test){
        test = 0;
        printf("Nhap lua chon: ");
        scanf("%d",&k);
        clear_display();
        switch(k){
            case 1:
                stop_display();
                break;
            case 2:
                stop_display();
                break;
            case 3:
                stop_display();
                break;
            case 0:
                break;
            default:
                printf("Nhap loi! Xin vui long nhap lai\n");
                menu_sx();
                test=1;
                break;
        }
    }
}

// xoa
void xoa1sp(Hanghoa *l){
    char masp[5];
    printf("Nhap ma san pham can xoa: ");
    scanf(" %[^\n]",masp);
    Hanghoa p = *l;
    int count =1;
    if (!strcmp(p->masp,masp)) {*l=p->next; count--;}
    while(p!=NULL && count){
        if(strcmp(masp,p->next->masp)==0){
            p->next=p->next->next;
            count--;
        }
        p=p->next;
    }
    if(count) printf("San pham can xoa khong ton tai\n");
    else printf("Xoa san pham thanh cong\n");
}
void xoa(Hanghoa *l){
    int k,test = 1;
    menu_xoa();
    while(test){
        test = 0;
        printf("Nhap lua chon: ");
        scanf("%d",&k);
        clear_display();
        switch(k){
            case 1:
                xoa1sp(l);
                stop_display();
                break;
            case 2:
                stop_display();
                break;
            case 0:
                break;
            default:
                printf("Nhap loi! Xin vui long nhap lai\n");
                menu_xoa();
                test=1;
                break;
        }
    }
}

// update
void updt(Hanghoa *l){
    int k,test = 1;
    menu_update();
    while(test){
        test = 0;
        printf("Nhap lua chon: ");
        scanf("%d",&k);
        clear_display();
        switch(k){
            case 1:
                xoa1sp(l);
                stop_display();
                break;
            case 2:
                stop_display();
                break;
            case 0:
                break;
            default:
                printf("Nhap loi! Xin vui long nhap lai\n");
                menu_update();
                test=1;
                break;
        }
    }
}

// SAVE
void save_file(Hanghoa l){
    FILE *file;
    file = fopen("sp.txt","w+");
    if(l == NULL){
        fprintf(file,"Khong co du lieu\n");
        return;
    }
    Hanghoa p = l;
    while(p != NULL){
        fprintf(file, "%s|%s|%s|%ld|%ld\n", 
               p->masp, p->tensp, p->size, p->gia, p->soluong);
        p = p->next;
    }  
    fclose(file);
}

void dispose(Hanghoa *l){
    Hanghoa p;
    while(*l != NULL){
        p=*l;
        *l = (*l)->next;
        free(p);
    }
}

// MENU
void menu_timkiem(){
    printf( "1: Tim kiem san pham theo ma san pham\n");
    printf( "2: Tim kiem san pham theo ten san pham\n");
    printf( "3: Tim kiem san pham theo gia san pham\n");
    printf( "0: Tro lai menu chinh\n");
}
void menu_sx(){
    printf( "1: Sap xep san pham theo ma san pham\n");
    printf( "2: Sap xep san pham theo ten san pham\n");
    printf( "3: Sap xep san pham theo gia san pham\n");
    printf( "4: Sap xep san pham theo so luong san pham\n");
    printf( "0: Tro lai menu chinh\n");
}
void menu_update(){
    printf( "1: Cap nhat thong tin 1 san pham\n");
    printf( "2: Cap nhat thong tin nhieu san pham\n");
    printf( "0: Tro lai menu chinh\n");
}
void menu_xoa(){
    printf( "1: Xoa 1 san pham\n");
    printf( "2: Xoa nhieu san pham\n");
    printf( "0: Tro lai menu chinh\n");
}
void save_menu(){
    printf("Du lieu chua duoc luu!\n");
    printf( "1: Luu du lieu vao file\n");
    printf( "2: Khong luu giu lieu\n");
}
void menu(){
    printf( "--------------MENU------------------\n");
    printf( "1: In danh sach san pham\n");
    printf( "2: Them san pham moi\n");
    printf( "3: Tim kiem san pham\n");
    printf( "4: Sap xep san pham\n");
    printf( "5: Cap nhat san pham\n");
    printf( "6: Xoa san pham\n");
    printf( "7: Luu du lieu vao file\n");
    printf( "0: thoat chuong trinh\n");
}
void clear_display(){
    system("cls");
}
void stop_display() {
    printf("\nNhan Enter de tiep tuc");
    while(getchar() != '\n');
    getchar();
}