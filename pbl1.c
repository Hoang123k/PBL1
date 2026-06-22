#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100

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

typedef struct {
    char maSP[20];
    char tenSP[50];
    char size[10];
    elementtype gia;
    elementtype soLuong;
    elementtype donGia;
    elementtype thanhTien;
} ChiTietHD;

typedef struct {
    char maHD[20];
    char ngay[15];
    ChiTietHD ds[MAX];
    elementtype soMatHang;
    elementtype tongTien;
} HoaDon;

HoaDon dsHD[MAX];

// khoi tao va doc file
void init(Hanghoa *l);
void themcuoi(Hanghoa *l,Hanghoa sanpham);
void docfile(Hanghoa *l, const char filename[]);
void docfile_hoadon(HoaDon dsHD[], int *sl_hd, const char filename[]);
int empty(Hanghoa l);

// check
int checkmasp(Hanghoa l, char masp[]);
int checktensp(Hanghoa l, char tensp[]);

// out
void hienthidanhsachsanpham(Hanghoa l);
void canhbaosp(Hanghoa l);

void nhapsanpham(Hanghoa l, struct SanPham *p);
Hanghoa checksanpham(Hanghoa l, Hanghoa p);
// Hanghoa travesanphamtrung(Hanghoa l, Hanghoa p);
// them sp
void themsanpham(Hanghoa *l);

// search
Hanghoa travesanpham(Hanghoa l,char masp[]);
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
void dispose(Hanghoa *l);
void xoa1sp(Hanghoa *l);
void xoa(Hanghoa *l);

// update
void upma(Hanghoa l,struct SanPham *p);
void upten(Hanghoa l,struct SanPham *p);
void upsize(struct SanPham *l);
void upgia(struct SanPham *l);
void upSL(struct SanPham *l);
void upthongtin(Hanghoa l, struct SanPham *p);
void updt(Hanghoa *l);

//Hoa don
int tongHD = 0;
int HD=0;
    // hoa don ban hang
int kiemtratrungHD(HoaDon *hd,char *maSP);
void xuly_congthem(HoaDon *hd, Hanghoa vt, int viTrisP);
void xuly_thaymoi(HoaDon *hd, Hanghoa vt, int viTrisP);
int kiemtrangay(char ngay[]);
void themVaoHD(HoaDon *hd, Hanghoa l);
void taoHD(HoaDon *hd,Hanghoa l);
void hienthisp_hd(HoaDon hd);
void thanhtoan(HoaDon *hd);
    //thong ke hoa don
void thongke_theongay(HoaDon dsHD[]);
void thongke_theothang(HoaDon dsHD[]);
void thongke_theonam(HoaDon dsHD[]);
void thongke_tatcathoigian(HoaDon dsHD[]);
char* bestseller(HoaDon dsHD[],char *thoigian);
void chinhsuaHD(HoaDon dsHD[], Hanghoa *l);
void hienthihoadon(void);

// save
void save_file(Hanghoa l);

// 3 ham thuc thi chinh
void khohang(Hanghoa *l);
void banhang(HoaDon *hd, Hanghoa *l);
void hethong(HoaDon dsHD[],Hanghoa *l);

// menu
void menu_timkiem();
void menu_sx();
void menu_update();
void menu_xoa();
void menu_bestseller();
void menu_chinhsuaHD();
void save_menu();
void menu_khohang();
void menu_banhang();
void menu_hethong();
void menu();
void clear_display();
void stop_display();

int main(){
    printf("Nhom 14\n");
    printf("Mai Le Ba Hoang\n");
    printf("Huynh Ngoc Duong\n");
    Hanghoa list;
    int test=1,k;
    HoaDon hd;
    hd.soMatHang = 0; 
    HD = 0;
    init(&list);
    docfile(&list,"sp.txt");
    docfile_hoadon(dsHD, &tongHD, "hd.txt");
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
                khohang(&list);
                break;
            case 2:
                banhang(dsHD,&list);
                save =0;
                break;
            case 3:
                hethong(dsHD,&list);
                break;
            case 0:
                if(save == 0){
                    save_menu();
                    int savefile;
                    printf("Nhap lua chon: ");
                    if(scanf("%d",&savefile)==1 && savefile==1) {save_file(list); printf("Luu du lieu thanh cong\n");}
                    save =1;
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
// Tham số dsHD là mảng chứa các hóa đơn, sl_hd là tổng số hóa đơn đang có
void docfile_hoadon(HoaDon dsHD[], int *sl_hd, const char filename[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong mo duoc file hoa don!\n");
        return;
    }
    char line[256];
    *sl_hd = 0; 
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) continue;
        int i = *sl_hd;
        char *dulieu = strtok(line, "|");
        if (dulieu != NULL) strcpy(dsHD[i].maHD, dulieu);
        dulieu = strtok(NULL, "|");
        if (dulieu != NULL) strcpy(dsHD[i].ngay, dulieu);
        dulieu = strtok(NULL, "|");
        if (dulieu != NULL) dsHD[i].soMatHang = atoi(dulieu);
        dulieu = strtok(NULL, "|");
        if (dulieu != NULL) dsHD[i].tongTien = atol(dulieu);
        for (int j = 0; j < dsHD[i].soMatHang; j++) {
            fgets(line, sizeof(line), file);
            line[strcspn(line, "\n")] = 0;
            char *dl_sp = strtok(line, "|");
            if (dl_sp != NULL) strcpy(dsHD[i].ds[j].maSP, dl_sp);
                dl_sp = strtok(NULL, "|");
            if (dl_sp != NULL) strcpy(dsHD[i].ds[j].tenSP, dl_sp);
                dl_sp = strtok(NULL, "|");
            if (dl_sp != NULL) strcpy(dsHD[i].ds[j].size, dl_sp);
            dl_sp = strtok(NULL, "|");
            if (dl_sp != NULL) dsHD[i].ds[j].gia = atol(dl_sp);            
            dl_sp = strtok(NULL, "|");
            if (dl_sp != NULL) dsHD[i].ds[j].soLuong = atoi(dl_sp);            
            dl_sp = strtok(NULL, "|");
            if (dl_sp != NULL) dsHD[i].ds[j].donGia = atol(dl_sp);            
            dl_sp = strtok(NULL, "|");
            if (dl_sp != NULL) dsHD[i].ds[j].thanhTien = atol(dl_sp);
        }
        (*sl_hd)++;
    }

    printf("Doc file hoa don thanh cong! (Tong cong: %d hoa don)\n", *sl_hd);    fclose(file);
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
void canhbaosp(Hanghoa l){
    int canhbao=0;
    Hanghoa p=l;
    while (p!=NULL){
        if(p->soluong<=10) {printf("San pham %s sap het hang!\n",p->masp); canhbao=1;}
        else if(p->soluong==0){ printf("SAN PHAM %s DA HET! XIN VUI LONG NHAP THEM!\n",p->masp); canhbao=1;}
        p=p->next;
    }
    if(canhbao==0) {printf("Khong co san pham nao sap het hang\n");}
}

int checkmasp(Hanghoa l, char masp[]){
    Hanghoa p=l;
    while(p!=NULL){
        if (!strcmp(p->masp,masp)) return 1;
        p=p->next;
    }
    return 0;
}
int checktensp(Hanghoa l, char tensp[]){
    Hanghoa p=l;
    while(p!=NULL){
        if (!strcmp(p->tensp,tensp)) return 1;
        p=p->next;
    }
    return 0;
}

void nhapsanpham(Hanghoa l, struct SanPham *p){
    printf("--- Thong tin san pham moi ---\n");
    char masp[10];
    printf("Ma san pham: ");
    scanf(" %[^\n]", masp);
    while(checkmasp(l,masp)){
        printf("Ma san pham da ton tai!\n");
        printf("Nhap lai ma san pham: ");
        scanf(" %[^\n]",masp);
    }
    strcpy(p->masp,masp);
    char tensp[15];
    printf("Ten san pham: ");
    scanf(" %[^\n]", tensp);
    while(checktensp(l,tensp)){
        printf("Ten san pham da ton tai!\n");
        printf("Nhap lai ten san pham: ");
        scanf(" %[^\n]",tensp);
    }
    strcpy(p->tensp,tensp);
    printf("Size san pham: ");
    scanf(" %[^\n]", p->size);
    printf("Gia san pham: ");
    while (scanf("%ld", &p->gia) != 1 || p->gia <= 0) {
        printf("Loi: Gia phai la so va khong duoc am. Moi nhap lai: ");
        while(getchar() != '\n'); 
    }
    printf("So luong san pham: ");
    while (scanf("%ld", &p->soluong) != 1 || p->soluong <= 0) {
        printf("Loi: So luong phai la so va khong duoc am. Moi nhap lai: ");
        while(getchar() != '\n'); 
    }
    getchar(); 
    p->next = NULL;
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
    nhapsanpham(*l,p);
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
            nhapsanpham(*l,p);
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
Hanghoa travesanpham(Hanghoa l,char masp[]){
    if(!empty(l)){
        Hanghoa p=l;
        while(p!=NULL){
            if (strcmp(masp,p->masp)==0) return p;
            p=p->next;
        }
    }
    return NULL;
}

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
    if(min>=0 && max>=min) return 1;
    return 0;
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
        while (scanf("%d", &k) != 1) {
            printf("Loi: Vui long nhap SO! Nhap lua chon: ");
            while(getchar() != '\n');
        }
        clear_display();
        switch(k){
            case 1:
                char masp[10];
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
                while(!checkkhoanggia(min,max)){
                    clear_display();
                    printf("Khoang gia loi! Xin vui long nhap lai.");
                    printf("Nhap khoang gia moi\n");
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
void swapData(Hanghoa a, Hanghoa b) {
    struct SanPham temp = *a;
    strcpy(a->masp,b->masp);
    strcpy(a->tensp,b->tensp);
    strcpy(a->size,b->size);
    a->gia = b->gia;
    a->soluong =b->soluong;
    strcpy(b->masp,temp.masp);
    strcpy(b->tensp,temp.tensp);
    strcpy(b->size,temp.size);
    b->gia = temp.gia;
    b->soluong = temp.soluong;
}
void sapxeptheoMasp(Hanghoa l) {
    for (Hanghoa i = l; i != NULL && i->next != NULL; i = i->next) {
        for (Hanghoa j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->masp,j->masp)>0) swapData(i, j);
        }
    }
    printf("Da sap xep theo Ma San Pham!\n");
    save =0;
}
void sapxeptheoTensp(Hanghoa l) {
    for (Hanghoa i = l; i != NULL && i->next != NULL; i = i->next) {
        for (Hanghoa j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->tensp,j->tensp)>0) swapData(i, j);
        }
    }
    printf("Da sap xep theo Ten San Pham!\n");
    save =0;
}
void sapxeptheoGiasp(Hanghoa l) {
    for (Hanghoa i = l; i != NULL && i->next != NULL; i = i->next) {
        for (Hanghoa j = i->next; j != NULL; j = j->next) {
            if (i->gia>j->gia) swapData(i,j);
        }
    }
    printf("Da sap xep theo Gia San Pham!\n");
    save =0;
}
void sapxeptheoSLsp(Hanghoa l) {
    for (Hanghoa i = l; i != NULL && i->next != NULL; i = i->next) {
        for (Hanghoa j = i->next; j != NULL; j = j->next) {
            if (i->soluong>j->soluong) swapData(i,j);
        }
    }
    printf("Da sap xep theo So Luong!\n");
    save =0;
}
void sx(Hanghoa *l) { 
    int k, test = 1;
    menu_sx();
    while(test) {
        test = 0;
        printf("Nhap lua chon: ");
        while (scanf("%d", &k) != 1) {
            printf("Loi: Vui long nhap SO! Nhap lua chon: ");
            while(getchar() != '\n');
        }
        clear_display();
        switch(k) {
            case 1: { 
                sapxeptheoMasp(*l);
                stop_display();
                break;
            }
            case 2:
                sapxeptheoTensp(*l);
                stop_display();
                break;
            case 3:
                sapxeptheoGiasp(*l);
                stop_display();
                break;
            case 4:
                sapxeptheoSLsp(*l);
                stop_display();
                break;
            case 0:
                break;
            default:
                printf("Nhap loi! Xin vui long nhap lai\n");
                menu_sx();
                test = 1;
                break;
        }
    }
}

// update

void upma(Hanghoa l, struct SanPham *p){
    printf("Nhap ma san pham moi: ");
    char masp[10];
    scanf(" %[^\n]",masp);
    while(!strcmp(p->masp,masp)){
        printf("Ma san pham trung voi ma san pham hien tai!\n");
        printf("Nhap lai ma san pham: ");
        scanf(" %[^\n]",masp);
    }
    Hanghoa q=l;
    while(checkmasp(q,masp)){
        printf("Ma san pham da ton tai xin hay nhap lai: ");
        scanf(" %[^\n]",masp);
    }
    strcpy(p->masp,masp);
    save = 0;
}
void upten(Hanghoa l, struct SanPham *p){
    printf("Nhap ten san pham moi: ");
    char tensp[15];
    scanf(" %[^\n]",tensp);
    while(!strcmp(p->tensp,tensp)){
        printf("ten san pham trung voi ten san pham hien tai!\n");
        printf("Nhap lai ten san pham: ");
        scanf(" %[^\n]",tensp);
    }
    Hanghoa q=l;
    while(checktensp(l,tensp)){
        printf("ten san pham da ton tai xin hay nhap lai: ");
        scanf(" %[^\n]",tensp);
    }
    strcpy(p->tensp,tensp);
    save = 0;
}
void upsize(struct  SanPham *l){
    printf("Nhap size san pham moi:");
    char size[5];
    scanf(" %[^\n]",size);
    strcpy(l->size,size);
    save = 0;
}
void upgia(struct SanPham *l){
    printf("Nhap gia san pham thay doi: ");
    elementtype gia;
    scanf("%ld",&gia);
    l->gia = gia;
    save = 0;
}
void upSL(struct SanPham *l){
    printf("Nhap so luong san pham thay doi: ");
    int soluong;
    scanf("%d",&soluong);
    l->soluong = soluong;
    save = 0;
}
void upthongtin(Hanghoa l, struct SanPham* p){
    upma(l,p);
    upten(l,p);
    printf("Nhap size moi: ");
    scanf(" %[^\n]", p->size);            
    printf("Nhap gia moi: ");
    while (scanf("%ld", &p->gia) != 1 || p->gia <= 0) {
        printf("Loi! Nhap lai gia: ");
        while(getchar() != '\n');
    }            
    printf("Nhap so luong moi: ");
    while (scanf("%ld", &p->soluong) != 1 || p->soluong <= 0) {
        printf("Loi! Nhap lai so luong: ");
        while(getchar() != '\n');
    }
    printf("-> Cap nhat thanh cong!\n");
    save = 0;

}
void updt(Hanghoa *l) {
    if (*l == NULL) {
        printf("Danh sach rong!\n");
        return;
    }

    char masp[15];
    printf("Nhap ma cua san pham can cap nhat: ");
    scanf(" %[^\n]", masp);
    menu_update();
    printf("Nhap lua chon: ");
    int k;
    int found = 0;
    while (scanf("%d", &k) != 1) {
        printf("Loi: Vui long nhap SO! Nhap lua chon: ");
        while(getchar() != '\n');
    }
    Hanghoa p=*l;
    while (p != NULL) {
        if (strcmp(p->masp, masp) == 0) {
            found=1;
            switch(k){
                case 1:
                    upthongtin(*l,p);
                    break;
                case 2:
                    upma(*l,p);
                    break;
                case 3:
                    upten(*l,p);
                    break;
                case 4:
                    upsize(p);
                    break;
                case 5:
                    upgia(p);
                    break;
                case 6:
                    upSL(p);
                    break;
            }
        }
        p=p->next;
    }
    if (!found) {
        printf("Khong tim thay san pham co ma: %s\n", masp);
    }
    stop_display();
}

// xoa
void xoa1sp(Hanghoa *l) {
    if (*l == NULL) return;
    char masp[10];
    printf("Nhap ma san pham can xoa: ");
    scanf(" %[^\n]", masp);
    Hanghoa p = *l, prev = NULL;
    if (strcmp(p->masp, masp) == 0) {
        *l = p->next;
        free(p);
        printf("Xoa thanh cong!\n");
        save = 0;
        return;
    }
    while (p != NULL && strcmp(p->masp, masp)) {
        prev = p;
        p = p->next;
    }

    if (p == NULL) {
        printf("Khong tim thay san pham!\n");
        } 
    else{
        prev->next = p->next;
        free(p);
        printf("Xoa thanh cong!\n");
        save =0;
    }
}
void xoa(Hanghoa *l){
    int k,test = 1;
    menu_xoa();
    while(test){
        test = 0;
        printf("Nhap lua chon: ");
        while (scanf("%d", &k) != 1) {
            printf("Loi: Vui long nhap SO! Nhap lua chon: ");
            while(getchar() != '\n');
        }
        clear_display();
        switch(k){
            case 1:
                xoa1sp(l);
                stop_display();
                break;
            case 2:
                dispose(l);
                printf("Xoa thanh cong\n");
                save =0;
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

//HOA DON
int kiemtrangay(char ngay[]){
    int day, month, year;
   if (strlen(ngay) != 10) {
        return 0; 
    }
    if (ngay[2] != '/' || ngay[5] != '/') {
        return 0;
    }
    if (sscanf(ngay, "%d/%d/%d", &day, &month, &year) != 3) {
        return 0;
    }
    if (month > 12 || month < 1 || day < 1 || year < 2000 || year > 2100)  return 0;
    switch(month){
        case 4:
        case 6:
        case 9:
        case 11:
            if(day>30) return 0;
            break;
        case 2:
            if(year%4==0 && year%100!=0){
                if(day>29) return 0;
            }
            else{
                if(day>28) return 0;
            }
            break;
        default:
            if(day>31) return 0;
            break;
    };
    return 1;
}
int kiemtratrungHD(HoaDon *hd, char *maSP) {
    for (int i = 0; i < hd->soMatHang; i++) {
        if (strcmp(hd->ds[i].maSP, maSP) == 0) {
            return i;
        }
    }
    return -1; 
}
void xuly_congthem(HoaDon *hd, Hanghoa vt, int viTrisP) {
    elementtype sl_them;

    if (vt->soluong <= 0) {
        printf("Sản phẩm đã hết hàng trong kho, không thể cộng thêm!\n");
        return;
    }
    printf("Số lượng có thể mua thêm trong kho: %ld\n", vt->soluong);
    printf("Nhap so luong muon CONG THEM: ");
    while (!scanf("%ld", &sl_them) || sl_them <= 0 || sl_them > vt->soluong) {
        while (getchar() != '\n');
        printf("So luong khong hop le!\n");
        printf("Nhap lai so luong muon cong them: ");
    }
    hd->ds[viTrisP].soLuong += sl_them;
    hd->ds[viTrisP].thanhTien = hd->ds[viTrisP].soLuong * vt->gia;
    hd->tongTien += sl_them * vt->gia;
    vt->soluong -= sl_them;

    printf("Da cong don san pham vao hoa don thanh cong!\n");
}
void xuly_thaymoi(HoaDon *hd, Hanghoa vt, int viTrisP) {
    elementtype sl_moi;
    elementtype sl_cu = hd->ds[viTrisP].soLuong;
    long controng = vt->soluong + sl_cu;
    printf("So luong toi da co the thay moi (Kho + San pham cu): %ld\n", controng);
    printf("Nhap so luong THAY MOI hoan toan: ");
    while (!scanf("%ld", &sl_moi) || sl_moi <= 0 || sl_moi > controng) {
        while (getchar() != '\n');
        printf("So luong khong hop le!\n");
        printf("Nhap lai so luong thay moi: ");
    }
    hd->tongTien -= hd->ds[viTrisP].thanhTien;
    vt->soluong += sl_cu;
    hd->ds[viTrisP].soLuong = sl_moi;
    hd->ds[viTrisP].thanhTien = sl_moi * vt->gia;
    hd->tongTien += hd->ds[viTrisP].thanhTien;
    vt->soluong -= sl_moi;
    printf("Da thay moi so luong san pham trong hoa don!\n");
}
void themVaoHD(HoaDon *hd, Hanghoa l) {
    char ma[20];
    elementtype sl;

    printf("Nhap ma SP: ");
    scanf(" %[^\n]", ma);
    Hanghoa vt = travesanpham(l,ma);
    if(vt == NULL) {
        printf("Khong tim thay san pham!\n");
        return;
    }

    int vi_tri_trung = kiemtratrungHD(hd, vt->masp);

    if (vi_tri_trung != -1) {
        int lua_chon = 0;
        printf("San pham nay da co trong hoa don (So luong hien tai: %ld).\n", hd->ds[vi_tri_trung].soLuong);
        printf("Ban muon cong them hay thay moi san pham nay?\n");
        printf("1. Cong them\n");
        printf("2. Thay moi\n");
        printf("Nhap lua chon cua ban (1 hoac 2): ");
        while (!scanf("%d", &lua_chon) || lua_chon < 1 || lua_chon > 2) {
            while (getchar() != '\n');
            printf("Lua chon khong hop le! Nhap lai (1/2): ");
        }
        if (lua_chon == 1) {
            xuly_congthem(hd, vt, vi_tri_trung);
        } else {
            xuly_thaymoi(hd, vt, vi_tri_trung);
        }
    } 
    else {
        if (hd->soMatHang >= MAX) {
            printf("Hoa don day, khong the them mat hang moi!\n");
            return;
        }

        if (vt->soluong <= 0) {
            printf("Mat hang da het\n");
            return;
        }

        elementtype sl;
        printf("So luong hien co trong kho: %ld\n", vt->soluong);
        printf("Nhap so luong mua: ");
        while (!scanf("%ld", &sl) || sl <= 0 || sl > vt->soluong) {
            while (getchar() != '\n');
            printf("So luong khong hop le!\n");
            printf("Nhap lai so luong mua: ");
        }
        int i = hd->soMatHang;
        strcpy(hd->ds[i].maSP, vt->masp);
        strcpy(hd->ds[i].tenSP,vt->tensp);
        strcpy(hd->ds[i].size,vt->size);
        hd->ds[i].gia = vt->gia;
        hd->ds[i].soLuong = sl;
        hd->ds[i].donGia = vt->gia;
        hd->ds[i].thanhTien = sl * vt->gia;
        hd->tongTien += hd->ds[i].thanhTien;
        vt->soluong -= sl;
        hd->soMatHang++;
        
        printf("Them vao hoa don thanh cong!\n");
    }
    save =0;
}
void taoHD(HoaDon *hd, Hanghoa l) {
    sprintf(hd->maHD, "HD%03d", tongHD + 1);
    while (1) {
        printf("Nhap ngay cho hoa don (dd/mm/yyyy): ");
        scanf(" %[^\n]", hd->ngay);
        if (kiemtrangay(hd->ngay)) {
            break;
        }
        printf("Ngay cua hoa don khong hop le! Vui long kiem tra lai.\n");
    }
    hd->soMatHang = 0;
    hd->tongTien = 0;
    int t=1;
    char tiep_tuc;
    
    hienthidanhsachsanpham(l);
    do{        
        themVaoHD(hd,l);
        if(hd->soMatHang>=MAX) break;
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Ban co muon tiep tuc them san pham vao hoa don nay? (y/n): ");
        scanf(" %c", &tiep_tuc);
    }while (tiep_tuc == 'y' || tiep_tuc == 'Y');
    printf("Da tao hoa don %s\n", hd->maHD);
}
void hienthisp_hd(HoaDon hd){
    if(!hd.soMatHang) {printf("Hoa don rong!\n"); return;}
    printf("Ma hoa Don :%s\n",hd.maHD);
    printf("Ngay: %s\n",hd.ngay);
    printf("%-10s | %-20s | %-10s | %-15s | %-10s | %-15s\n", 
           "Ma SP", "Ten San Pham", "Size", "Gia/SP(VND)", "So luong", "Thanh tien(VND)");
    printf("---------------------------------------------------------------------------------------------------------\n");
    for(int i = 0; i < hd.soMatHang; i++) {
        printf("%-10s | %-20s | %-10s | %-15d | %-10d | %-15d\n",
               hd.ds[i].maSP,
               hd.ds[i].tenSP,
               hd.ds[i].size,
               hd.ds[i].gia,
               hd.ds[i].soLuong,
               hd.ds[i].thanhTien);
    }
    printf("Tong tien: %ld\n",hd.tongTien);
}

void thanhtoan(HoaDon *hd) {
    if(tongHD >= MAX){
        printf("Hoa don day!\n");
        return;
    }
    if(hd->soMatHang == 0) {
        printf("Hoa don rong!\n");
        return;
    }

    printf("\nHoa don %s\n", hd->maHD);
    printf("%-10s | %-20s | %-10s | %-15s | %-10s | %-15s\n", 
           "Ma SP", "Ten San Pham", "Size", "Gia/SP(VND)", "So luong", "Thanh tien");
    printf("---------------------------------------------------------------------------------------------------------\n");
    for(int i = 0; i < hd->soMatHang; i++) {
        printf("%-10s | %-20s | %-10s | %-15d | %-10d | %-15d\n",
               hd->ds[i].maSP,
               hd->ds[i].tenSP,
               hd->ds[i].size,
               hd->ds[i].gia,
               hd->ds[i].soLuong,
               hd->ds[i].thanhTien);
    }

    printf("Tong tien: %ld VND\n", hd->tongTien);
    dsHD[tongHD] = *hd; 
    tongHD++;
    HD = 0; 
    hd->soMatHang = 0; 
    hd->tongTien = 0;
    memset(hd->maHD, 0, sizeof(hd->maHD));
    save = 0;
    printf("Thanh toan hoa don thanh cong\n");

}
void thongke_theongay(HoaDon dsHD[]){
    char ngay_nhap[30];
    char tham_so_loc[30];
    HoaDon hd_temp;

    while (1) {
        printf("Nhap ngay muon thong ke (dd/mm/yyyy): ");
        scanf(" %[^\n]", ngay_nhap);
        if (kiemtrangay(ngay_nhap)) {
            strcpy(tham_so_loc, ngay_nhap);
            break;
        }
        printf("Ngay nhap khong dung thuc te hoac sai dinh dang! Vui long nhap lai.\n");
    }
    printf("\n=> San pham ban chay nhat ngay %s la: %s \n", tham_so_loc, bestseller(dsHD, tham_so_loc));
    
}
void thongke_theothang(HoaDon dsHD[]) {
    int mm, yyyy;
    char tham_so_loc[30];

    printf("Nhap thang (1-12): ");
    while (!scanf("%d", &mm) || mm < 1 || mm > 12) {
        while (getchar() != '\n');
        printf("Thang khong hop le! Nhap lai: ");
    }
    printf("Nhap nam: ");
    while (!scanf("%d", &yyyy) || yyyy < 1) {
        while (getchar() != '\n');
        printf("Nam khong hop le! Nhap lai: ");
    }
    sprintf(tham_so_loc, "%02d/%04d", mm, yyyy);
    printf("\n=> San pham ban chay nhat trong thang %s la: %s\n", tham_so_loc, bestseller(dsHD, tham_so_loc));
}
void thongke_theonam(HoaDon dsHD[]) {
    int yyyy;
    char tham_so_loc[30];

    printf("Nhap nam muon thong ke: ");
    while (!scanf("%d", &yyyy) || yyyy < 1) {
        while (getchar() != '\n');
        printf("Nam khong hop le! Nhap lai: ");
    }
    sprintf(tham_so_loc, "%04d", yyyy);
    printf("\n=> San pham ban chay nhat trong nam %s la: %s\n", tham_so_loc, bestseller(dsHD, tham_so_loc));
}
void thongke_tatcathoigian(HoaDon dsHD[]) {
    printf("\n=> San pham ban chay nhat tu truoc den nay la: %s\n", bestseller(dsHD, ""));
}
char *bestseller(HoaDon dsHD[], char *thoiGian) {
    if (tongHD == 0) {
        return "Khong co hoa don nao de thong ke";
    }
    typedef struct {
        char tenSP[50];
        elementtype tongBan;
    } ThongKe;
    
    ThongKe tk[1000]; 
    int soLoaiSP = 0; 
    
    for (int i = 0; i < tongHD; i++) {
        if (strlen(thoiGian) > 0 && strstr(dsHD[i].ngay, thoiGian) == NULL) {
            continue; 
        }

        for (int j = 0; j < dsHD[i].soMatHang; j++) {
            char *ten_hien_tai = dsHD[i].ds[j].tenSP;
            elementtype sl_hien_tai = dsHD[i].ds[j].soLuong;

            int found = 0;
            for (int k = 0; k < soLoaiSP; k++) {
                if (strcmp(tk[k].tenSP, ten_hien_tai) == 0) {
                    tk[k].tongBan += sl_hien_tai; 
                    found = 1;
                    break;
                }
            }
            if (found == 0) {
                if (soLoaiSP < 1000) {
                    strcpy(tk[soLoaiSP].tenSP, ten_hien_tai);
                    tk[soLoaiSP].tongBan = sl_hien_tai;
                    soLoaiSP++;
                }
            }
        }
    }
    if (soLoaiSP == 0) {
        return "Khong co du lieu san pham ban ra trong thoi gian nay";
    }

    elementtype max_sl = tk[0].tongBan;
    for (int i = 1; i < soLoaiSP; i++) {
        if (tk[i].tongBan > max_sl) {
            max_sl = tk[i].tongBan;
        }
    }
    static char tensp[255]; 
    strcpy(tensp, "");     
    int first = 1;
    for (int i = 0; i < soLoaiSP; i++) {
        if (tk[i].tongBan == max_sl) {
            if (first == 0) {
                strcat(tensp, ", ");
            }
            strcat(tensp, tk[i].tenSP);
            first = 0;
        }
    }
    return tensp;
}

void thongke_bestseller(HoaDon dsHD[]) {
    int k;
    int test = 1;
    while(test) {
        test = 0;
        menu_bestseller();
        printf("Nhap lua chon: ");
        if (scanf("%d", &k) != 1) {
            while(getchar() != '\n');
            k = -1;
        }
        clear_display();
        switch(k) {
            case 1: 
                thongke_theongay(dsHD);
                stop_display(); 
                break;
            case 2:
                thongke_theothang(dsHD); 
                stop_display(); 
                break;
            case 3: 
                thongke_theonam(dsHD); 
                stop_display(); 
                break;
            case 4: 
                thongke_tatcathoigian(dsHD); 
                stop_display(); 
                break;
            case 0: 
                break;
            default:
                printf("Nhap loi! Vui long nhap lai.\n");
                test = 1;
                break;
        }
    }
}
void chinhsuaHD(HoaDon dsHD[], Hanghoa *l) {
    if (tongHD == 0) {
        printf("Chua co hoa don nao trong he thong de chinh sua!\n");
        return;
    }

    char ma[20];
    printf("Nhap ma hoa don can chinh sua (Vi du: HD001): ");
    scanf(" %[^\n]", ma);
    int vi_tri_hd = -1;
    for (int i = 0; i < tongHD; i++) {
        if (strcmp(dsHD[i].maHD, ma) == 0) {
            vi_tri_hd = i;
            break;
        }
    }

    if (vi_tri_hd == -1) {
        printf("Khong tim thay hoa don %s trong he thong!\n", ma);
        return;
    }
    clear_display();
    printf("--- DANG CHINH SUA HOA DON: %s ---\n", dsHD[vi_tri_hd].maHD);
    hienthisp_hd(dsHD[vi_tri_hd]);
    for (int i = 0; i < dsHD[vi_tri_hd].soMatHang; i++) {
        Hanghoa vt = travesanpham(*l, dsHD[vi_tri_hd].ds[i].maSP);
        if (vt != NULL) {
            vt->soluong += dsHD[vi_tri_hd].ds[i].soLuong;
        }
    }

    int lua_chon = -1;
    do {
        printf("\n[Hien tai dang sua hoa don %s]\n",dsHD[vi_tri_hd].maHD);
        menu_chinhsuaHD();
        printf("Nhap lua chon cua ban: ");
        if (scanf("%d", &lua_chon) != 1) {
            while (getchar() != '\n');
            lua_chon = -1;
            continue;
        }
        clear_display();

        switch (lua_chon) {
            case 1: {
                char ngay_moi[15];
                while (1) {
                    printf("Nhap ngay moi cho hoa don (dd/mm/yyyy): ");
                    scanf(" %[^\n]", ngay_moi);
                    if (kiemtrangay(ngay_moi)) {
                        strcpy(dsHD[vi_tri_hd].ngay, ngay_moi);
                        printf("Cap nhat ngay hoa don thanh cong!\n");
                        break;
                    }
                    printf("Ngay khong hop le chuẩn 10 ky tu! Nhap lai.\n");
                }
                break;
            }
            case 2:
                themVaoHD(&dsHD[vi_tri_hd], *l); 
                break;

            case 3: {
                if (dsHD[vi_tri_hd].soMatHang == 0) {
                    printf("Hoa don nay hien tai khong co san pham nao de sua!\n");
                    break;
                }
                char ma_sp[20];
                printf("Nhap ma san pham can dieu chinh trong hoa don: ");
                scanf(" %[^\n]", ma_sp);

                int idx_sp = kiemtratrungHD(&dsHD[vi_tri_hd], ma_sp);
                if (idx_sp == -1) {
                    printf("San pham ma %s khong ton tai trong hoa don nay!\n", ma_sp);
                    break;
                }

                Hanghoa vt = travesanpham(*l, ma_sp);
                if (vt == NULL) {
                    printf("San pham nay khong con ton tai trong danh muc kho hang goc!\n");
                    break;
                }

                int opt = 0;
                printf("San pham: %s | So luong cu trong HD: %ld | Kho hien tai: %ld\n", 
                       dsHD[vi_tri_hd].ds[idx_sp].tenSP, dsHD[vi_tri_hd].ds[idx_sp].soLuong, vt->soluong);
                printf("Ban muon: 1. Cong them | 2. Thay moi so luong: ");
                while (!scanf("%d", &opt) || opt < 1 || opt > 2) {
                    while (getchar() != '\n');
                    printf("Nhap lai (1/2): ");
                }

                if (opt == 1) {
                    xuly_congthem(&dsHD[vi_tri_hd], vt, idx_sp);
                } else {
                    xuly_thaymoi(&dsHD[vi_tri_hd], vt, idx_sp);
                }
                break;
            }
            case 0:
                printf("Dang luu lai toan bo thay doi va chot hoa don...\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
                break;
        }
    } while (lua_chon != 0);
    dsHD[vi_tri_hd].tongTien = 0;
    for (int i = 0; i < dsHD[vi_tri_hd].soMatHang; i++) {
        dsHD[vi_tri_hd].ds[i].thanhTien = dsHD[vi_tri_hd].ds[i].soLuong * dsHD[vi_tri_hd].ds[i].gia;
        dsHD[vi_tri_hd].tongTien += dsHD[vi_tri_hd].ds[i].thanhTien;
        Hanghoa vt = travesanpham(*l, dsHD[vi_tri_hd].ds[i].maSP);
        if (vt != NULL) {
            vt->soluong -= dsHD[vi_tri_hd].ds[i].soLuong;
        }
    }
    save = 0;
    printf("\n=> CHINH SUA HOA DON %s THANH CONG!\n", dsHD[vi_tri_hd].maHD);
    hienthisp_hd(dsHD[vi_tri_hd]);
}
void hienthihoadon(void) {
    if (tongHD == 0) {
        printf("Chua co hoa don nao trong danh sach thong ke!\n");
        return;
    }
    printf("\n========== DANH SACH CAC HOA DON DA XUAT ==========\n");
    for (int i = 0; i < tongHD; i++) {
        hienthisp_hd(dsHD[i]);
        printf("---------------------------------------------------\n");
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
    file = fopen("hd.txt", "w");
    if(file == NULL){
        printf("Loi mo file hoa don de ghi!\n");
        return;
    }
    
    for(int i = 0; i < tongHD; i++){
        fprintf(file, "%s|%ld|%ld\n", dsHD[i].maHD, dsHD[i].soMatHang, dsHD[i].tongTien);
        for(int j = 0; j < dsHD[i].soMatHang; j++){
            fprintf(file, "%s|%s|%s|%ld|%ld|%ld|%ld\n",
                dsHD[i].ds[j].maSP,
                dsHD[i].ds[j].tenSP,
                dsHD[i].ds[j].size,
                dsHD[i].ds[j].gia,
                dsHD[i].ds[j].soLuong,
                dsHD[i].ds[j].donGia,
                dsHD[i].ds[j].thanhTien);
        }
    }
    fclose(file);
}

//DISPOSE
void dispose(Hanghoa *l){
    Hanghoa p;
    while(*l != NULL){
        p=*l;
        *l = (*l)->next;
        free(p);
    }
}

// 3 ham thuc thi chinh
void khohang(Hanghoa *l) {
    int lua_chon = -1;
    do {
        menu_khohang();
        printf("Nhap lua chon cua ban: ");
        if (scanf("%d", &lua_chon) != 1) {
            while (getchar() != '\n');
            lua_chon = -1;
            printf("Lua chon khong hop le!\n");
            continue;
        }
        clear_display();
        switch (lua_chon) {
            case 1: 
                hienthidanhsachsanpham(*l); 
                stop_display();
                break;
            case 2: 
                themsanpham(l); 
                break;
            case 3: 
                search(*l); 
                break;
            case 4: 
                sx(l); 
                break;
            case 5: 
                updt(l); 
                break;
            case 6: 
                xoa(l); 
                break;
            case 7: 
                canhbaosp(*l); 
                break;
            case 0: 
                printf("Dang quay lai Menu chinh...\n"); 
                break;
            default: 
                printf("Lua chon khong ton tai!\n"); 
                break;
        }
        
    } while (lua_chon != 0);
}

void banhang(HoaDon *hd, Hanghoa *l){
    static HoaDon hd_hien_tai; 
    int lua_chon = -1;
    do {
        menu_banhang(); 
        printf("Nhap lua chon cua ban: ");
        if (!scanf("%d", &lua_chon)) {
            while (getchar() != '\n');
            lua_chon = -1;
            printf("Lua chon khong hop le!\n");
            continue;
        }
        clear_display();
        switch (lua_chon) {
            case 1: 
                taoHD(&hd_hien_tai, *l); 
                break; 
            case 2: 
                themVaoHD(&hd_hien_tai, *l); 
                break;
            case 3: 
                hienthisp_hd(hd_hien_tai); 
                break;
            case 4: 
                thanhtoan(&hd_hien_tai); 
                break;
            case 0: 
                printf("Dang quay lai Menu chinh...\n"); 
                break;
            default: 
                printf("Lua chon khong ton tai!\n"); 
                break;
        }
    } while (lua_chon != 0);
}
void hethong(HoaDon dsHD[], Hanghoa *l) {
    int lua_chon = -1;
    do {
        menu_hethong();
        printf("Nhap lua chon cua ban: ");
        if (!scanf("%d", &lua_chon)) {
            while (getchar() != '\n'); 
            lua_chon = -1;
            printf("Lua chon khong hop le!\n");
            continue;
        }
        clear_display();
        switch (lua_chon) {
            case 1:
                thongke_bestseller(dsHD);
                break;
            case 2:
                hienthihoadon();
                break;
            case 3:
                chinhsuaHD(dsHD,l);
                break;
            case 4:
                save_file(*l);
                printf("Ghi du lieu vao file sp.txt va hd.txt thanh cong!\n");
                break;
            case 0:
                printf("Dang quay lai Menu chinh...\n");
                break;
            default:
                printf("Lua chon khong ton tai!\n");
                break;
        }
    } while (lua_chon != 0);
}

// MENU
void menu_timkiem(){
    printf( "TIM KIEM THEO TIEU CHI\n");
    printf( "1: Ma san pham\n");
    printf( "2: Ten san pham\n");
    printf( "3: Gia san pham\n");
    printf( "0: Tro lai menu chinh\n");
}
void menu_sx(){
    printf( "SAP XEP THEO TIEU CHI:\n");
    printf( "1: Ma san pham\n");
    printf( "2: Ten san pham\n");
    printf( "3: Gia san pham\n");
    printf( "4: So luong san pham\n");
    printf( "0: Tro lai menu chinh\n");
}
void menu_update(){
    printf( "CAP NHAT THEO TIEU CHI:\n");
    printf( "1: Thong tin san pham\n");
    printf( "2: Ma san pham\n");
    printf( "3: Ten san pham\n");
    printf( "4: Size san pham\n");
    printf( "5: Gia san pham\n");
    printf( "6: So luong san pham\n");
    printf( "0: Tro lai menu chinh\n");
}
void menu_xoa(){
    printf( "--------------XOA------------------\n");
    printf( "1: 1 san pham\n");
    printf( "2: Tat ca san pham\n");
    printf( "0: Tro lai menu chinh\n");
}
void menu_bestseller(){
    printf("---------------- THỐNG KÊ BEST SELLER ----------------\n");
    printf("1: Thong ke theo ngay (dd/mm/yyyy)\n");
    printf("2: Thong ke theo thang (mm/yyyy)\n");
    printf("3: Thong ke theo nam (yyyy)\n");
    printf("4: Thong ke theo tat ca thoi gian\n");
    printf("0: Quay lai menu chinh\n");
}
void menu_chinhsuaHD() {
    printf("\n------ CHINH SUA HOA DON DA THANH TOAN ------\n");
    printf("1. Chinh sua ngay hoa don\n");
    printf("2. them san pham moi vao hoa don nay\n");
    printf("3. Dieu chinh san pham da co (Cong don/Thay moi)\n");
    printf("0. Hoan tat va Luu thay doi\n");
    printf("---------------------------------------------\n");
}
void save_menu(){
    printf("DU LIEU CHUA DUOC LUU!\n");
    printf( "1: Thoat va luu du lieu vao file\n");
    printf( "phim khac: Thoat va khong luu du lieu\n");
}
void menu_khohang(){
    printf("\n------------ QUAN LY KHO HANG ------------\n");
    printf("1: In danh sach san pham\n");
    printf("2: Them san pham moi\n");
    printf("3: Tim kiem san pham\n");
    printf("4: Sap xep san pham\n");
    printf("5: Cap nhat san pham\n");
    printf("6: Xoa san pham\n");
    printf("7: Cac san pham sap het trong kho\n");
    printf("0: Quay lai Menu chinh\n");
}
void menu_banhang(){
    printf("\n------- QUAN LY HOA DON & BAN HANG -------\n");
    printf("1: Tao hoa don moi\n");
    printf("2: Them san pham vao hoa don\n");
    printf("3: Hien thi san pham trong hoa don hien tai\n");
    printf("4: Thanh toan hoa don\n");
    printf("0: Quay lai Menu chinh\n");
}
void menu_hethong(){
    printf("\n----------- THONG KE & HE THONG -----------\n");
    printf("1: Xem san pham Best Seller\n");
    printf("2: Hien thi danh sach cac hoa don da xuat\n");
    printf("3: Chinh sua hoa don\n");
    printf("4: Luu du lieu vao File\n");
    printf("0: Quay lai Menu chinh\n");
}
void menu(){
    printf( "--------------MENU------------------\n");
    printf("1: Quan ly KHO HANG (San pham)\n");
    printf("2: Quan ly HOA DON & BAN HANG\n");
    printf("3: THONG KE & HE THONG\n");
    printf("0: Thoat chuong trinh\n");
}
void clear_display(){
    system("cls");
}
void stop_display() {
    printf("\nNhan Enter de tiep tuc");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}