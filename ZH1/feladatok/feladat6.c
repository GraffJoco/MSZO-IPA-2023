#include <math.h>
#include <stdio.h>

struct vektor {
    double x, y, z;
};

struct vektor plus(struct vektor v1, struct vektor v2) {
    return (struct vektor){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

struct vektor minus(struct vektor v1, struct vektor v2) {
    return (struct vektor){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

struct vektor scale(struct vektor v, double scalar) {
    return (struct vektor){v.x * scalar, v.y * scalar, v.z * scalar};
}

struct vektor cross(struct vektor v1, struct vektor v2) {
    return (struct vektor){
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x};
}

double scalar(struct vektor v1, struct vektor v2) {
    return v1.x * v2.x +
           v1.y * v2.y +
           v1.z * v2.z;
}

double length(struct vektor v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

void vektorKiir(struct vektor v) {
    printf("{%lf; %lf; %lf}\n", v.x, v.y, v.z);
}

int main() {
    struct vektor v1, v2, eredmeny;
    char teendo;
    double skalarertek;

    // Beolvasás
    scanf_s("%lf", &v1.x);
    scanf_s("%lf", &v1.y);
    scanf_s("%lf", &v1.z);
    scanf_s("%lf", &v2.x);
    scanf_s("%lf", &v2.y);
    scanf_s("%lf", &v2.z);
    printf("Mit tegyünk a vektorokkal? ");
    //Szóköz %c előtt fontos, mellőzi az üreshely-karaktereket
    scanf_s(" %c", &teendo);

    switch (teendo) {
        case '+':
            vektorKiir(plus(v1, v2));
            break;
        case '-':
            vektorKiir(minus(v1, v2));
            break;
        case '*':
            printf("%lf\n", scalar(v1, v2));
            break;
        case 'x':
            vektorKiir(cross(v1, v2));
            break;
        case 's':
            scanf_s("%lf", &skalarertek);
            vektorKiir(scale(v1, skalarertek));
            break;
        case 'l':
            printf("%lf\n", length(v1));
            break;
        default:
            printf("Rossz input!");
            break;
    }
}