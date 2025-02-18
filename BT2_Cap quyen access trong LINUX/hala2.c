#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hàm giải nén file từ file ZIP
void extract_file(const char *zip_filename, const char *filename, const char *output_filename) {
    char command[256];
    snprintf(command, sizeof(command), "unzip -p %s %s > %s", zip_filename, filename, output_filename);
    system(command);
}

// Hàm xác thực người dùng
int authenticate_user(const char *username, const char *password) {
    FILE *file = fopen("users.txt", "r");
    char file_username[50], file_password[50];
    int access;

    while (fscanf(file, "%s %s %d", file_username, file_password, &access) != EOF) {
        if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0 && access == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// Hàm cập nhật trạng thái quyền truy cập
void update_access_status(const char *username, int access_status) {
    FILE *file = fopen("users.txt", "r+");
    char file_username[50], file_password[50];
    int access;
    long pos;
    
    while ((pos = ftell(file)) >= 0 && fscanf(file, "%s %s %d", file_username, file_password, &access) != EOF) {
        if (strcmp(username, file_username) == 0) {
            fseek(file, pos, SEEK_SET);
            fprintf(file, "%s %s %d\n", file_username, file_password, access_status);
            break;
        }
    }
    fclose(file);
}

// Hàm biên dịch và chạy kernel
void compile_and_run_kernel() {
    system("unzip -o kernel.zip kernel.c");
    system("gcc kernel.c -o kernel");
    system("./kernel");
}

int main() {
    char username[50];
    char password[50];
    
    // Giải nén file users.txt từ file ZIP
    extract_file("kernel.zip", "users.txt", "users.txt");
    
    // Yêu cầu nhập tài khoản và mật khẩu
    printf("Nhập tên đăng nhập: ");
    scanf("%s", username);
    printf("Nhập mật khẩu: ");
    scanf("%s", password);
    
    // Xác thực người dùng
    if (authenticate_user(username, password)) {
        printf("Đăng nhập thành công!\n");
        
        // Cập nhật trạng thái quyền truy cập
        update_access_status(username, 1);
        
        // Giải nén, biên dịch và chạy kernel
        compile_and_run_kernel();
        
        // Reset quyền truy cập
        update_access_status(username, 0);
        
    } else {
        printf("Sai tên đăng nhập hoặc mật khẩu!\n");
    }
    
    return 0;