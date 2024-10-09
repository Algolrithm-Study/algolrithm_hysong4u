#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DEGREE 101

typedef struct {
    int degree;
    float coef[MAX_DEGREE];
} polynomial;

int MAX(int a, int b) {
    return (a > b) ? a : b;
}

polynomial poly_add1(polynomial A, polynomial B) {
    polynomial C; // 결과 다항식
    int Apos = 0, Bpos = 0, Cpos = 0;
    int degree_a = A.degree;
    int degree_b = B.degree;

    C.degree = MAX(A.degree, B.degree);

    while (Apos <= A.degree && Bpos <= B.degree) {
        if (degree_a > degree_b) {
            C.coef[Cpos++] = A.coef[Apos++];
            degree_a--;
        } else if (degree_a == degree_b) {
            C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
            degree_a--;
            degree_b--;
        } else {
            C.coef[Cpos++] = B.coef[Bpos++];
            degree_b--;
        }
    }

    return C; // `while` 루프 밖으로 이동
}

void print_poly(polynomial p) {
    for (int i = p.degree; i > 0; i--) {
        printf("%3.1fx^%d ", p.coef[p.degree - i], i);
        if (i > 1) {
            printf("+ ");
        }
    }
    // 상수항 출력
    printf("%3.1f\n", p.coef[p.degree]);
}

int main() {
    polynomial a = {5, {3, 6, 0, 0, 0, 10}};  
    polynomial b = {4, {7, 0, 5, 0, 1}};      
    polynomial c;

    printf("Polynomial A: ");
    print_poly(a);

    printf("Polynomial B: ");
    print_poly(b);

    c = poly_add1(a, b);

    printf("Polynomial A + B: ");
    print_poly(c);

    return 0;
}
