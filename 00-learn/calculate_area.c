#include <stdio.h>

#define PI 3.14159265

int main(int argc, char ** argv) {
    float r;
    printf("Enter radius: ");
    scanf("%f", &r);
    const float area = PI * r * r;
    printf("Area = %.2f\n", area);
}