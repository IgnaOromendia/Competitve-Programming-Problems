using namespace std;

// Implemenatción a mano
int S = 0;
int x, i;

int main() {

    // Agregar el elemento x
    S |= (1 << x);

    // Eliminar el i-esimo elemento
    S &= ~(1 << i);

}
