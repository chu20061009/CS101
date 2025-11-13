#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
int num_in_numset(int num, int numset[], int len) {
    for (int i = 0; i < len; i++) {
        if (numset[i] == num) {
            return 1; 
        }
    }
    return 0; 
}

int main() {
    
    int n;
    int numset[7]; 
    FILE* fp;

    srand(1);
    

    scanf("%d", &n);
    fp = fopen("lotto.txt", "w");
    if (fp == NULL) {
        printf("錯誤: 無法開啟 lotto.txt 進行寫入。\n");
        return 1;
    }

    fprintf(fp, "========= lotto649 =========\n");

    for (int i = 0; i < 5; i++) {
        
        fprintf(fp, "[%d]: ", i + 1);
        
        if (i < n) {
            for (int j = 0; j < 7; ) {
                int num = (rand() % 69) + 1; 
                
                // 檢查是否重複
                if (!num_in_numset(num, numset, j)) {
                    numset[j] = num;
                    fprintf(fp, "%02d ", num); 
                    j++; 
                }
            }
            fprintf(fp, "\n");
            
        } else {
            fprintf(fp, "__ __ __ __ __ __ __\n");
        }
    }
    fprintf(fp, "========= csie@CGU =========\n");
    fclose(fp);

    
    int winning_nums[3];
    char line_buffer[256]; 

    printf("請輸入中獎號碼三個: ");
    scanf("%d %d %d", &winning_nums[0], &winning_nums[1], &winning_nums[2]);

    printf("輸入中獎號碼為:%02d %02d %02d\n", winning_nums[0], winning_nums[1], winning_nums[2]);
    printf("以下為中獎彩卷:\n");

    fp = fopen("lotto.txt", "r");
    if (fp == NULL) {
        printf("錯誤: 無法開啟 lotto.txt 進行讀取。\n");
        return 1;
    }

    while (fgets(line_buffer, 256, fp)) {
        if (line_buffer[0] == '[' && strstr(line_buffer, "__") == NULL) {
            
            int lotto_nums[7];
            sscanf(line_buffer, "[%*d]: %d %d %d %d %d %d %d", 
                   &lotto_nums[0], &lotto_nums[1], &lotto_nums[2], 
                   &lotto_nums[3], &lotto_nums[4], &lotto_nums[5], &lotto_nums[6]);
            
            int is_winner = 0;
            for (int i = 0; i < 7; i++) {

                for (int j = 0; j < 3; j++) {
                    if (lotto_nums[i] == winning_nums[j]) {
                        is_winner = 1;
                        break;
                    }
                }
                if (is_winner) {
                    break;
                }
            }
            if (is_winner) {
                printf("%s", line_buffer);
            }
        }
    }
    fclose(fp);

    return 0;
}
