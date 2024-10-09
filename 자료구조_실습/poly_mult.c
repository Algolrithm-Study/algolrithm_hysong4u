#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TERMS 101


typedef struct {
    int degree_x;
    int degree_y;
    float coef;
} term;


typedef struct {
    term terms[MAX_TERMS]; 
    int num_terms;         
} polynomial;


int MAX(int a, int b) {
    return (a > b) ? a : b;
}

//y에 대한 내림차순 정렬
int compare_terms(const void *a, const void *b) {
    term *term_a = (term *)a;
    term *term_b = (term *)b;

    if (term_b->degree_y != term_a->degree_y) {
        return term_b->degree_y - term_a->degree_y;
    } else {
        // y차수가 같으면 x를 기준으로 내림차순 정렬
        return term_b->degree_x - term_a->degree_x;
    }
}

term multiply_terms(term a, term b) {
    term c;
    c.coef = a.coef * b.coef; 
    c.degree_x = a.degree_x + b.degree_x; 
    c.degree_y = a.degree_y + b.degree_y; 
    return c;
}

polynomial multPoly(polynomial A, polynomial B) {
    polynomial C;
    C.num_terms = 0;

    for (int i = 0; i < A.num_terms; i++) {
        for (int j = 0; j < B.num_terms; j++) {
            term product = multiply_terms(A.terms[i], B.terms[j]);

            int k;

            // 같은 차수일 때 합산
            for (k = 0; k < C.num_terms; k++) {
                if (C.terms[k].degree_x == product.degree_x && C.terms[k].degree_y == product.degree_y) {
                    C.terms[k].coef += product.coef; 
                    break;
                }
            }

            // 새로운 항 추가
            if (k == C.num_terms && C.num_terms < MAX_TERMS) {
                C.terms[C.num_terms++] = product;
            }
        }
    }

    // 계수가 0인 항 제거
    int new_num_terms = 0;
    for (int i = 0; i < C.num_terms; i++) {
        if (C.terms[i].coef != 0) {
            C.terms[new_num_terms++] = C.terms[i];
        }
    }
    C.num_terms = new_num_terms;

    // 정렬
    qsort(C.terms, C.num_terms, sizeof(term), compare_terms);

    return C;
}


void print_term(term t) {
    if (t.coef != 0) { 
        printf("%.1fx^%dy^%d\n", t.coef, t.degree_x, t.degree_y);
    }
}


void print_poly(polynomial poly) {

    qsort(poly.terms, poly.num_terms, sizeof(term), compare_terms);

    for (int i = 0; i < poly.num_terms; i++) {
        term t = poly.terms[i];
        if (t.coef != 0) { 
            if (t.degree_y == 0 && t.degree_x == 0) { // 상수항
                printf("%.1f ", t.coef);
            } 
            else if (t.degree_x == 0) { // x^0
                printf("%.1fy^%d ", t.coef, t.degree_y);
            } 
            else if (t.degree_y == 0) { // y^0
                printf("%.1fx^%d ", t.coef, t.degree_x);
            } 
            else { // 일반 항
                printf("%.1fy^%dx^%d ", t.coef, t.degree_y, t.degree_x);
            }

            if (i < poly.num_terms - 1) {
                printf("+ ");
            }
        }
    }
    printf("\n");
}


int main() {
    printf("\n========== 2021111945 송하연 =============\n");
    // 1) 단순 case 
    polynomial a1 = {{{0, 7, 3}, {4, 0, 4}, {0, 0, -1}}, 3};   // A: 3y^7 + 4x^4 -1
    polynomial b1 = {{{4, 0, 5}, {0, 2, -3}, {0, 0, 7}}, 3};   // B: 5x^4 - 3y^2 +7
    
    printf("\n1) 단순 case:\n");
    polynomial mul_result1 = multPoly(a1, b1);
    printf("A * B: ");
    print_poly(mul_result1);


    // 2) general case
    polynomial a2 = {{{0, 7, 4}, {4, 0, -4}, {0, 0, -1}}, 3};  // A: 4y^7 - 4x^4 -1
    polynomial b2 = {{{0, 7, 2}, {1, 0, -3}, {0, 0, 1}}, 3};   // B: 2y^7 - 3x +1
    
    printf("\n2) general case\n");
    polynomial mul_result2 = multPoly(a2, b2);
    printf("A * B: ");
    print_poly(mul_result2);

    // 3) extreme case
    polynomial a3 = {{{4, 7, 15}, {0, 9, -9}, {0, 7, 21}, {8, 0, 20}}, 4};  // A: 15x^4y^7 -9y^9 +21y^7 +20x^8
    polynomial b3 = {{{4, 2, -12}, {4, 0, 23}, {0, 2, 3}, {0, 0, -7}}, 4};  // B: -12x^4y^2 +23x^4 +3y^2 -7

    printf("\n3) extreme case\n");
    polynomial mul_result3 = multPoly(a3, b3);
    printf("A * B: ");
    print_poly(mul_result3);

    return 0;
}

