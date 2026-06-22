void banhang(HoaDon dsHD[], Hanghoa *l) {
    static HoaDon hd_hien_tai; // Dùng biến static để giữ lại trạng thái hóa đơn đang gom hàng giữa các lần vào/ra menu
    int lua_chon = -1;

    do {
        // 1. Gọi hàm hiển thị giao diện thuần túy của bạn
        menuBanHang(); 
        
        printf("Nhap lua chon cua ban: ");
        if (!scanf("%d", &lua_chon)) {
            while (getchar() != '\n'); // Dọn dẹp bộ đệm bộ nhớ nếu nhập chữ cái bậy bạ
            lua_chon = -1;
            printf("Lua chon khong hop le! Vui long nhap so.\n");
            continue;
        }

        // 2. Switch-case xử lý tính năng trực tiếp tại đây
        switch (lua_chon) {
            case 1:
                // Truyền địa chỉ hóa đơn hiện tại và danh sách liên kết sản phẩm (*l)
                taoHD(&hd_hien_tai, *l); 
                break;
                
            case 2:
                // Thêm sản phẩm vào hóa đơn hiện hành
                themVaoHD(&hd_hien_tai, *l);
                break;
                
            case 3:
                // Hiển thị các mặt hàng đã gom trong hóa đơn hiện tại
                hienthisp_hd(hd_hien_tai);
                break;
                
            case 4:
                // Tiến hành thanh toán và đẩy hóa đơn vào mảng lưu trữ dsHD
                thanhtoan(&hd_hien_tai);
                break;
                
            case 0:
                printf("Dang quay lai Menu chinh...\n");
                break;
                
            default:
                printf("Lua chon khong ton tai! Vui long chon tu 0 den 4.\n");
                break;
        }

        // Tạo khoảng dừng màn hình cho người dùng đọc thông báo thành công/thất bại
        if (lua_chon != 0) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // Xóa bộ đệm dư
            printf("\nBam phim bat ky va Enter de tiep tuc...");
            char pause;
            scanf(" %c", &pause);
        }

    } while (lua_chon != 0);
}