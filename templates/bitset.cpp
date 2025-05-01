using namespace std;

// Implemenatción a mano
int S = 0;
int x, i, b;

int main() {

    // Chequear si pertence
    bool pertenece = S & (1 << x);

    // Agregar el elemento x
    S |= (1 << x);

    // Eliminar el i-esimo elemento
    S &= ~(1 << i);

    // Bit menos significativo
    b = __builtin_ctz(S); 

    // Cantidad de bits prendidos
    b = __builtin_popcount(S);

}
