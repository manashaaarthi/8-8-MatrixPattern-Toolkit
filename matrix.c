#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 8
#define ORANGE 1
#define BLUE 0
#define GREEN 2

int mat[N][N] = {
{1,1,1,1,1,1,1,1},
{1,0,0,1,1,0,0,1},
{1,0,0,0,0,0,0,1},
{1,1,0,0,0,0,1,1},
{1,1,0,0,0,0,1,1},
{1,1,0,0,0,0,1,1},
{1,1,1,0,0,1,1,1},
{1,1,1,1,1,1,1,1}

};

// Utility: print matrix
void printMatrix(int a[N][N]) {
    printf("Matrix (%dx%d):\n", N, N);
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

// 1. Store (allow user to overwrite default)
void storeMatrix() {
    char choice;
    printf("Use default sample matrix? (y/n): ");
    scanf(" %c",&choice);
    if (choice=='n' || choice=='N') {
        printf("Enter %d x %d values row-wise (0-blue,1-orange):\n", N, N);
        for (int i=0;i<N;i++){
            for (int j=0;j<N;j++){
                int v;
                scanf("%d",&v);
                mat[i][j] = v;
            }
        }
    }
    printf("Matrix stored.\n");
    printMatrix(mat);
}

// 2. Count color blocks
void countColors() {
    int countBlue = 0, countOrange = 0;
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            if (mat[i][j]==BLUE) countBlue++;
            else if (mat[i][j]==ORANGE) countOrange++;
        }
    }
    printf("Total Blue (0) = %d\nTotal Orange (1) = %d\n", countBlue, countOrange);

    int r,c;
    printf("To count in a specific row and column, enter row index (0..%d) and col (0..%d), or -1 -1 to skip: ", N-1, N-1);
    scanf("%d %d",&r,&c);
    if (r>=0 && r<N) {
        int rb=0, ro=0;
        for (int j=0;j<N;j++) {
            if (mat[r][j]==BLUE) rb++; else if (mat[r][j]==ORANGE) ro++;
        }
        printf("Row %d -> Blue=%d Orange=%d\n", r, rb, ro);
    }
    if (c>=0 && c<N) {
        int cb=0, co=0;
        for (int i=0;i<N;i++) {
            if (mat[i][c]==BLUE) cb++; else if (mat[i][c]==ORANGE) co++;
        }
        printf("Col %d -> Blue=%d Orange=%d\n", c, cb, co);
    }
}

// 3. Detect shape / pattern: print coordinates of blue blocks; check vertical symmetry
void printBlueCoordinates() {
    printf("Coordinates of Blue squares (value 0):\n");
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            if (mat[i][j]==BLUE) {
                printf("(%d,%d) ", i, j);
            }
        }
    }
    printf("\n");
}

// Check symmetry vertical (mirror around middle column) and horizontal

//4.Extract inner and outer
void extractBorderElements(int matrix[N][N]) {
    printf("Border Elements:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Border condition → first/last row OR first/last column
           if(matrix[i][j]==1)
           {
                printf("%d ", matrix[i][j]);
            } else {
                printf("  "); // spacing for better visualization
            }
        }
        printf("\n");
    }
}

// Function to print inner matrix (excluding border)
void extractInnerMatrix(int matrix[N][N]) {
    printf("Inner Matrix (excluding border):\n");
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1; j++) {
            if(matrix[i][j]==0||matrix[i][j]==2)
           { printf("%d ", matrix[i][j]);
           }
           else
           {
               printf("  ");
           }
        }
        printf("\n");
    }
}
void borderVsCenter(int matrix[N][N]) {
    extractBorderElements(matrix);
    printf("\n");
    extractInnerMatrix(matrix);
}

// 5. Rotation 90° clockwise
void rotate90(int out[N][N]) {
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            out[j][N-1-i] = mat[i][j];
        }
    }
}

// 6. Submatrix extraction (center 3x3 and all possible k x k)
void central3x3() {
    if (N < 3) { printf("Matrix too small\n"); return;}
    int start = (N-3)/2;
    printf("Central 3x3 submatrix (rows %d..%d):\n", start, start+2);
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            printf("%d ", mat[start+i][start+j]);
        }
        printf("\n");
    }
}

void allKxK() {
    int k;
    printf("Enter k for k x k submatrices (1 <= k <= %d): ", N);
    scanf("%d",&k);
    if (k<1 || k> N) { printf("Invalid k\n"); return; }
    printf("All %dx%d submatrices:\n", k, k);
    for (int si=0; si <= N-k; si++){
        for (int sj=0; sj <= N-k; sj++){
            printf("Submatrix at (%d,%d):\n", si, sj);
            for (int i=0;i<k;i++){
                for (int j=0;j<k;j++){
                    printf("%d ", mat[si+i][sj+j]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
}

// 7. Symmetry check (vertical/horizontal)
int isVerticallySymmetric() {
    for (int i=0;i<N;i++){
        for (int j=0;j<N/2;j++){
            if (mat[i][j] != mat[i][N-1-j]) return 0;
        }
    }
    return 1;
}

int isHorizontallySymmetric() {
    for (int i=0;i<N/2;i++){
        for (int j=0;j<N;j++){
            if (mat[i][j] != mat[N-1-i][j]) return 0;
        }
    }
    return 1;
}
void symmetryCheck() {
    printf("Vertical symmetry: %s\n", isVerticallySymmetric() ? "YES" : "NO");
    printf("Horizontal symmetry: %s\n", isHorizontallySymmetric() ? "YES" : "NO");
}

// 8. Largest connected region of blue (treat BLUE as 1 for graph)
int visited[N][N];
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

int dfs_count(int r, int c) {
    if (r<0||r>=N||c<0||c>=N) return 0;
    if (visited[r][c]) return 0;
    if (mat[r][c] != BLUE) return 0;
    visited[r][c] = 1;
    int cnt = 1;
    for (int d=0;d<4;d++){
        cnt += dfs_count(r+dr[d], c+dc[d]);
    }
    return cnt;
}

void largestBlueComponent() {
    memset(visited,0,sizeof(visited));
    int best = 0;
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            if (!visited[i][j] && mat[i][j]==BLUE) {
                int size = dfs_count(i,j);
                if (size > best) best = size;
            }
        }
    }
    printf("Largest connected component size (4-direction) of Blue (0) = %d\n", best);
}

// 9. Replace pattern color: change all BLUE to GREEN
void replaceBlueToGreen() {
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            if (mat[i][j]==BLUE) mat[i][j] = GREEN;
        }
    }
    printf("All blue (0) replaced by green (2). New matrix:\n");
    printMatrix(mat);
}

// 10. Pattern matching: search a smaller k x k inside the N x N
int matchAt(int si, int sj, int k, int pat[k][k]){
    for (int i=0;i<k;i++){
        for (int j=0;j<k;j++){
            if (mat[si+i][sj+j] != pat[i][j]) return 0;
        }
    }
    return 1;
}
void patternMatching() {
    int k;
    printf("Enter size k of pattern (k <= %d): ", N);
    scanf("%d",&k);
    if (k<1 || k> N) { printf("Invalid k\n"); return; }
    int pat[k][k];
    printf("Enter pattern values (%d x %d) row-wise (use 0/1/2):\n", k, k);
    for (int i=0;i<k;i++) for (int j=0;j<k;j++) scanf("%d",&pat[i][j]);

    int found = 0;
    for (int si=0; si<=N-k; si++){
        for (int sj=0; sj<=N-k; sj++){
            if (matchAt(si,sj,k,pat)){
                printf("Pattern found at top-left (%d,%d)\n", si, sj);
                found = 1;
            }
        }
    }
    if (!found) printf("Pattern not found.\n");
}

// Menu logic
int main() {
    int choice;
    do {
        printf("\n--- 8x8 Matrix Pattern Toolkit (0 to exit) ---\n");
        printf("0. Exit\n");
        printf("1. Store matrix (use default or enter new)\n");
        printf("2. Count color blocks (total + row/column counts)\n");
        printf("3. Detect shape: list blue coordinates and vertical symmetry check\n");
        printf("4. Border vs inner extraction\n");
        printf("5. Rotate matrix 90 degrees clockwise and show result\n");
        printf("6. Submatrix extraction (central 3x3 and all kxk)\n");
        printf("7. Symmetry check (vertical & horizontal)\n");
        printf("8. Largest connected region of Blue (0)\n");
        printf("9. Replace all Blue with Green (0 -> 2)\n");
        printf("10. Pattern matching (search small matrix inside big matrix)\n");
        printf("Choose option: ");
        scanf("%d", &choice);

        switch(choice) {
            case 0:
                printf("Exiting.\n"); break;
            case 1:
                storeMatrix(); break;
            case 2:
                countColors(); break;
            case 3:
                printBlueCoordinates();
                printf("Is symmetric about vertical axis? %s\n", isVerticallySymmetric() ? "YES" : "NO");
                break;
            case 4: {
                 borderVsCenter(mat);
                 break;
                    }
            case 5: {
                int out[N][N];
                rotate90(out);
                printf("Rotated 90deg clockwise:\n");
                for (int i=0;i<N;i++){
                    for (int j=0;j<N;j++) printf("%d ", out[i][j]);
                    printf("\n");
                }
                break;
            }
            case 6:
                central3x3();
                allKxK();
                break;
            case 7:
                symmetryCheck();
                break;
            case 8:
                largestBlueComponent();
                break;
            case 9:
                replaceBlueToGreen();
                break;
            case 10:
                patternMatching();
                break;
            default:
                printf("Invalid choice\n");
        }

    } while (choice != 0);

    return 0;
}