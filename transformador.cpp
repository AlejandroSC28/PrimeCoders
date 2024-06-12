#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <sstream> 

std::string to_string(int numero) {
    std::ostringstream oss;
    oss << numero;
    return oss.str();
}
using namespace std;

const int ROWS = 2, COMLUMNS = 4;

int numberOfMinterms = 0;
int DecimalMinterms[7];

struct KmapElement
{
	int state;
	int DecimalMinterm;
	int inclusion = 0;
	string binaryminterm;
};
struct Implicant
{
	vector <KmapElement> minterms;
	int Size;
};
KmapElement Kmap[ROWS][COMLUMNS];

vector <KmapElement> V1, V2, V3, V4, V5, V6, AllElemntsInImplicant;;
vector <Implicant> AllImplicants;

string FinalExpression = "";
void GetInput();
void IntializeKMap(), IntializeBinaryMintermsKMap();
void PrintKMap();
void AlgorithmFindImplicants();
vector <KmapElement> GetVectorOfMaxSize(vector<KmapElement> V1, vector<KmapElement> V2, vector<KmapElement> V3, vector<KmapElement> V4, vector<KmapElement> V5);
void SortAllImplicantsBySizeInAscendingOrder();
void AssignInclusionTimesToImplicants();
void RemoveDuplicateImplicants();
void DecreaseInclusionOfMintermsInDeletedImplicant(int i);
void GetEssentialPrimeImplicants();
void GetFinalExpression();

void showInstructions() {
    cout << "Este programa es un conversor de números binarios, decimales, octales y hexadecimales." << endl;
    cout << "Permite realizar las siguientes conversiones:" << endl;
    cout << "1. Decimal a Binario" << endl;
    cout << "2. Binario a Decimal" << endl;
    cout << "3. Octal a Decimal" << endl;
    cout << "4. Hexadecimal a Decimal" << endl;
    cout << "5. Binario a Hexadecimal" << endl;
    cout << "6. Binario a Octal" << endl;
    cout << "7. Decimal a Hexadecimal" << endl;
    cout << "8. Decimal a Octal" << endl;
    cout << "9. Hexadecimal a Binario" << endl;
    cout << "10. Hexadecimal a Octal" << endl;
    cout << "11. Octal a Binario" << endl;
    cout << "12. Octal a Hexadecimal" << endl;
    cout << "13. Representación IEEE 754 de un número decimal" << endl;
    cout << "Integrantes: Jhonn Saeteros, Andres Ayala, Ana Preciado, Rommel Rivera, Alejandro Sangucho." << endl;
}

// Función que muestra el menú de operaciones disponibles
void showMenu() {
    cout << "Seleccione la operación que desea realizar:" << endl;
    cout << "1. Decimal a Binario" << endl;
    cout << "2. Binario a Decimal" << endl;
    cout << "3. Octal a Decimal" << endl;
    cout << "4. Hexadecimal a Decimal" << endl;
    cout << "5. Binario a Hexadecimal" << endl;
    cout << "6. Binario a Octal" << endl;
    cout << "7. Decimal a Hexadecimal" << endl;
    cout << "8. Decimal a Octal" << endl;
    cout << "9. Hexadecimal a Binario" << endl;
    cout << "10. Hexadecimal a Octal" << endl;
    cout << "11. Octal a Binario" << endl;
    cout << "12. Octal a Hexadecimal" << endl;
    cout << "13. Representación IEEE 754 de un número decimal" << endl;
    cout << "14. Volver al menú principal" << endl;
}

// Función que convierte un número decimal a binario
void decimalABinario() {
    int numero_decimal;
    cout << "Ingrese un número decimal: ";
    cin >> numero_decimal;

    string binario = "";

    if (numero_decimal == 0) binario = "0";

    while (numero_decimal > 0) {
        int resto = numero_decimal % 2;
        binario = to_string (resto) + binario;
        numero_decimal /= 2;
    }
    to_string;

    cout << "En binario es " << binario << endl;
}

// Función que convierte un número binario a decimal
void binarioADecimal() {
    string numero_binario;
    cout << "Ingrese un número binario: ";
    cin >> numero_binario;

    int numero_decimal = 0;

    for (int i = 0; i < numero_binario.length(); i++) {
        if (numero_binario[i] == '1') {
            numero_decimal += pow(2, numero_binario.length() - 1 - i);
        }
    }

    cout << "En decimal es " << numero_decimal << endl;
}

// Función que convierte un número octal a decimal
void octalADecimal() {
    string numero_octal;
    cout << "Ingrese un número octal: ";
    cin >> numero_octal;

    int numero_decimal = 0;

    for (int i = 0; i < numero_octal.length(); i++) {
        int digito = numero_octal[i] - '0';
        numero_decimal += digito * pow(8, numero_octal.length() - 1 - i);
    }

    cout << "En decimal es " << numero_decimal << endl;
}

// Función que convierte un número hexadecimal a decimal
void hexaADecimal() {
    string numero_hexadecimal;
    cout << "Ingrese un número hexadecimal: ";
    cin >> numero_hexadecimal;

    int numero_decimal = 0;

    for (int i = 0; i < numero_hexadecimal.length(); i++) {
        char c = toupper(numero_hexadecimal[i]);
        int digito;
        if (c >= '0' && c <= '9') {
            digito = c - '0';
        } else {
            digito = c - 'A' + 10;
        }
        numero_decimal += digito * pow(16, numero_hexadecimal.length() - 1 - i);
    }

    cout << "En decimal es " << numero_decimal << endl;
}

// Función que convierte un número binario a hexadecimal
void binarioAHexadecimal() {
    string numero_binario;
    cout << "Ingrese un número binario: ";
    cin >> numero_binario;

    int numero_decimal = 0;

    for (int i = 0; i < numero_binario.length(); i++) {
        if (numero_binario[i] == '1') {
            numero_decimal += pow(2, numero_binario.length() - 1 - i);
        }
    }

    string hexadecimal = "";

    if (numero_decimal == 0) hexadecimal = "0";

    while (numero_decimal > 0) {
        int resto = numero_decimal % 16;
        if (resto < 10) {
            hexadecimal = to_string(resto) + hexadecimal;
        } else {
            hexadecimal = char(resto - 10 + 'A') + hexadecimal;
        }
        numero_decimal /= 16;
    }

    cout << "En hexadecimal es " << hexadecimal << endl;
}

// Función que convierte un número binario a octal
void binarioAOctal() {
    string numero_binario;
    cout << "Ingrese un número binario: ";
    cin >> numero_binario;

    int numero_decimal = 0;

    for (int i = 0; i < numero_binario.length(); i++) {
        if (numero_binario[i] == '1') {
            numero_decimal += pow(2, numero_binario.length() - 1 - i);
        }
    }

    string octal = "";

    if (numero_decimal == 0) octal = "0";

    while (numero_decimal > 0) {
        int resto = numero_decimal % 8;
        octal = to_string(resto) + octal;
        numero_decimal /= 8;
    }

    cout << "En octal es " << octal << endl;
}

// Función que convierte un número decimal a hexadecimal
void decimalAHexadecimal() {
    int numero_decimal;
    cout << "Ingrese un número decimal: ";
    cin >> numero_decimal;

    string hexadecimal = "";

    if (numero_decimal == 0) hexadecimal = "0";

    while (numero_decimal > 0) {
        int resto = numero_decimal % 16;
        if (resto < 10) {
            hexadecimal = to_string(resto) + hexadecimal;
        } else {
            hexadecimal = char(resto - 10 + 'A') + hexadecimal;
        }
        numero_decimal /= 16;
    }

    cout << "En hexadecimal es " << hexadecimal << endl;
}

// Función que convierte un número decimal a octal
void decimalAOctal() {
    int numero_decimal;
    cout << "Ingrese un número decimal: ";
    cin >> numero_decimal;

    string octal = "";

    if (numero_decimal == 0) octal = "0";

    while (numero_decimal > 0) {
        int resto = numero_decimal % 8;
        octal = to_string(resto) + octal;
        numero_decimal /= 8;
    }

    cout << "En octal es " << octal << endl;
}

// Función que convierte un número hexadecimal a binario
void hexaABinario() {
    string numero_hexadecimal;
    cout << "Ingrese un número hexadecimal: ";
    cin >> numero_hexadecimal;

    int numero_decimal = 0;

    for (int i = 0; i < numero_hexadecimal.length(); i++) {
        char c = toupper(numero_hexadecimal[i]);
        int digito;
        if (c >= '0' && c <= '9') {
            digito = c - '0';
        } else {
            digito = c - 'A' + 10;
        }
        numero_decimal += digito * pow(16, numero_hexadecimal.length() - 1 - i);
    }

    string binario = "";

    if (numero_decimal == 0) binario = "0";

    while (numero_decimal > 0) {
        int resto = numero_decimal % 2;
        binario = to_string(resto) + binario;
        numero_decimal /= 2;
    }

    cout << "En binario es " << binario << endl;
}

// Función que convierte un número hexadecimal a octal
void hexaAOctal() {
    string numero_hexadecimal;
    cout << "Ingrese un número hexadecimal: ";
    cin >> numero_hexadecimal;

    int numero_decimal = 0;

    for (int i = 0; i < numero_hexadecimal.length(); i++) {
        char c = toupper(numero_hexadecimal[i]);
        int digito;
        if (c >= '0' && c <= '9') {
            digito = c - '0';
        } else {
            digito = c - 'A' + 10;
        }
        numero_decimal += digito * pow(16, numero_hexadecimal.length() - 1 - i);
    }

    string octal = "";

    if (numero_decimal == 0) octal = "0";

    while (numero_decimal > 0) {
        int resto = numero_decimal % 8;
        octal = to_string(resto) + octal;
        numero_decimal /= 8;
    }

    cout << "En octal es " << octal << endl;
}

// Función que convierte un número octal a binario
void octalABinario() {
    string numero_octal;
    cout << "Ingrese un número octal: ";
    cin >> numero_octal;

    int numero_decimal = 0;

    for (int i = 0; i < numero_octal.length(); i++) {
        int digito = numero_octal[i] - '0';
        numero_decimal += digito * pow(8, numero_octal.length() - 1 - i);
    }

    string binario = "";

    if (numero_decimal == 0) binario = "0";

    while (numero_decimal > 0) {
        int resto = numero_decimal % 2;
        binario = to_string(resto) + binario;
        numero_decimal /= 2;
    }

    cout << "En binario es " << binario << endl;
}

// Función que convierte un número octal a hexadecimal
void octalAHexadecimal() {
    string numero_octal;
    cout << "Ingrese un número octal: ";
    cin >> numero_octal;

    int numero_decimal = 0;

    for (int i = 0; i < numero_octal.length(); i++) {
        int digito = numero_octal[i] - '0';
        numero_decimal += digito * pow(8, numero_octal.length() - 1 - i);
    }

    string hexadecimal = "";

    if (numero_decimal == 0) hexadecimal = "0";

    while (numero_decimal > 0) {
        int resto = numero_decimal % 16;
        if (resto < 10) {
            hexadecimal = to_string(resto) + hexadecimal;
        } else {
            hexadecimal = char(resto - 10 + 'A') + hexadecimal;
        }
        numero_decimal /= 16;
    }

    cout << "En hexadecimal es " << hexadecimal << endl;
}

// Función para imprimir los bits manualmente
void imprimirBits(unsigned int n, int bits) {
    for (int i = bits - 1; i >= 0; --i) {
        cout << ((n >> i) & 1);
    }
}

// Función para imprimir la representación binaria del número en formato IEEE 754
void imprimirIEEE754(float num) {
    // Unión para acceder a los bits del número flotante
    union {
        float entrada;
        unsigned int salida;
    } datos;
    
    datos.entrada = num;

    // Obtener el signo
    unsigned int signo = (datos.salida >> 31) & 0x1;
    
    // Obtener el exponente con sesgo
    unsigned int exponenteSesgado = (datos.salida >> 23) & 0xFF;
    // Obtener el exponente real
    int exponente = exponenteSesgado - 127;
    
    // Obtener la mantisa
    unsigned int mantisa = datos.salida & 0x7FFFFF;
    
    // Imprimir el signo
    cout << "Signo: " << signo << endl;
    
    // Imprimir el exponente con sesgo y el exponente real
    cout << "Exponente binario: ";
    imprimirBits(exponenteSesgado, 8);
    cout << " (Decimal: " << exponenteSesgado << ")" << endl;
    cout << "Exponente: " << exponente << endl;
    
    // Imprimir la mantisa
    cout << "Mantisa: ";
    imprimirBits(mantisa, 23);
    cout << endl;
}

// Función que muestra el menú principal
void showMainMenu() {
    cout << "Menú Principal:" << endl;
    cout << "1. Ver Instrucciones" << endl;
    cout << "2. Ver Opciones de Conversión" << endl;
    cout << "3. Salir" << endl;
}

// Función principal que ejecuta el menú y las opciones
int main() {
    int mainOption;
    do {
        showMainMenu();
        cout << "Ingrese su opción: ";
        cin >> mainOption;

        switch (mainOption) {
            case 1:
                showInstructions();
                break;
            case 2: {
                int conversionOption;
                do {
                    showMenu();
                    cout << "Ingrese su opción: ";
                    cin >> conversionOption;

                    switch (conversionOption) {
                        case 1:
                            decimalABinario();
                            break;
                        case 2:
                            binarioADecimal();
                            break;
                        case 3:
                            octalADecimal();
                            break;
                        case 4:
                            hexaADecimal();
                            break;
                        case 5:
                            binarioAHexadecimal();
                            break;
                        case 6:
                            binarioAOctal();
                            break;
                        case 7:
                            decimalAHexadecimal();
                            break;
                        case 8:
                            decimalAOctal();
                            break;
                        case 9:
                            hexaABinario();
                            break;
                        case 10:
                            hexaAOctal();
                            break;
                        case 11:
                            octalABinario();
                            break;
                        case 12:
                            octalAHexadecimal();
                            break;
                        case 13: {
                            float num;
                            cout << "Ingrese un número decimal: ";
                            cin >> num;
                            cout << "Representación IEEE 754 de " << num << ":\n";
                            imprimirIEEE754(num);
                            break;
                        }
                        case 14:
                            cout << "Volviendo al menú principal..." << endl;
                            break;
                        default:
                            cout << "Opción no válida, por favor intente nuevamente." << endl;
                            break;
                    }
                    cout << endl;
                } while (conversionOption != 14);
                break;
            }
            case 3:
                GetInput();
	            IntializeKMap();
	            IntializeBinaryMintermsKMap();
            	PrintKMap();
	            AlgorithmFindImplicants();
	            SortAllImplicantsBySizeInAscendingOrder();
	            AssignInclusionTimesToImplicants();
	            RemoveDuplicateImplicants();
	            GetEssentialPrimeImplicants();
	            GetFinalExpression();
            	cout << "F(A, B, C) = " << FinalExpression << endl;
                break;
            case 4:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida, por favor intente nuevamente." << endl;
                break;
        }
        cout << endl;
    } while (mainOption != 3);

    return 0;
}
void GetInput()
{
	cout << "INGRESE LOS EL NUMERO DE MINTERMINOS" << endl;
	cin >> numberOfMinterms;
	cout << "INGRESE LOS MINTERMINOS" << endl;
	int i = 0;
	int tempMinterm;
	do
	{
		do
		{
			cin >> tempMinterm;

		} while (tempMinterm > 7 || tempMinterm < 0);
		DecimalMinterms[i] = tempMinterm;
		i++;
	} while (i < numberOfMinterms);

}

void IntializeKMap()
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COMLUMNS; j++)
			Kmap[i][j].state = 0;

	Kmap[0][0].DecimalMinterm = 0;
	Kmap[0][1].DecimalMinterm = 1;
	Kmap[0][2].DecimalMinterm = 3;
	Kmap[0][3].DecimalMinterm = 2;
	Kmap[1][0].DecimalMinterm = 4;
	Kmap[1][1].DecimalMinterm = 5;
	Kmap[1][2].DecimalMinterm = 7;
	Kmap[1][3].DecimalMinterm = 6;


	for (int i = 0; i < numberOfMinterms; i++)
	{
		if (DecimalMinterms[i] == 0)
			Kmap[0][0].state = 1;
		else if (DecimalMinterms[i] == 1)
			Kmap[0][1].state = 1;
		else if (DecimalMinterms[i] == 3)
			Kmap[0][2].state = 1;
		else if (DecimalMinterms[i] == 2)
			Kmap[0][3].state = 1;
		else if (DecimalMinterms[i] == 4)
			Kmap[1][0].state = 1;
		else if (DecimalMinterms[i] == 5)
			Kmap[1][1].state = 1;
		else if (DecimalMinterms[i] == 7)
			Kmap[1][2].state = 1;
		else if (DecimalMinterms[i] == 6)
			Kmap[1][3].state = 1;
	}
}

void IntializeBinaryMintermsKMap()
{
	Kmap[0][0].binaryminterm = "000";
	Kmap[0][1].binaryminterm = "001";
	Kmap[0][2].binaryminterm = "011";
	Kmap[0][3].binaryminterm = "010";
	Kmap[1][0].binaryminterm = "100";
	Kmap[1][1].binaryminterm = "101";
	Kmap[1][2].binaryminterm = "111";
	Kmap[1][3].binaryminterm = "110";
}

void PrintKMap()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << Kmap[i][j].state << "  ";
		cout << endl;
	}
}


void AlgorithmFindImplicants()
{
	if (numberOfMinterms == 8)
	FinalExpression = "1";
	else if (numberOfMinterms == 0)
		FinalExpression = "0";
	else
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COMLUMNS; j++)
			{
				int implicantNum = 0;
				if (Kmap[i][j].state == 1)
				{
					V1.push_back(Kmap[i][j]);
					if (Kmap[i][(j + 1) % COMLUMNS].state == 1)
					{
						V2.push_back(Kmap[i][j]);
						V2.push_back(Kmap[i][(j + 1) % COMLUMNS]);
					}
					if (Kmap[(i + 1) % ROWS][j].state == 1)
					{
						V3.push_back(Kmap[i][j]);
						V3.push_back(Kmap[(i + 1) % ROWS][j]);
					}
					if (Kmap[i][(j + 1) % COMLUMNS].state == 1 && Kmap[(i + 1) % ROWS][j].state == 1 && Kmap[(i + 1) % ROWS][(j + 1) % COMLUMNS].state == 1)
					{
						V4.push_back(Kmap[i][j]);
						V4.push_back(Kmap[i][(j + 1) % COMLUMNS]);
						V4.push_back(Kmap[(i + 1) % ROWS][j]);
						V4.push_back(Kmap[(i + 1) % ROWS][(j + 1) % COMLUMNS]);
					}
					if (Kmap[i][(j + 1) % COMLUMNS].state == 1 && Kmap[i][(j + 2) % COMLUMNS].state == 1 && Kmap[i][(j + 3) % COMLUMNS].state == 1)
					{
						V5.push_back(Kmap[i][j]);
						V5.push_back(Kmap[i][(j + 1) % COMLUMNS]);
						V5.push_back(Kmap[i][(j + 2) % COMLUMNS]);
						V5.push_back(Kmap[i][(j + 3) % COMLUMNS]);
					}
					AllElemntsInImplicant = GetVectorOfMaxSize(V1, V2, V3, V4, V5);
					for (int m = 0; m < AllElemntsInImplicant.size(); m++)
					{
						if (AllElemntsInImplicant[m].DecimalMinterm == 0)
							Kmap[0][0].inclusion = Kmap[0][0].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 1)
							Kmap[0][1].inclusion = Kmap[0][1].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 2)
							Kmap[0][3].inclusion = Kmap[0][3].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 3)
							Kmap[0][2].inclusion = Kmap[0][2].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 4)
							Kmap[1][0].inclusion = Kmap[1][0].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 5)
							Kmap[1][1].inclusion = Kmap[1][1].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 6)
							Kmap[1][3].inclusion = Kmap[1][3].inclusion + 1;
						else if (AllElemntsInImplicant[m].DecimalMinterm == 7)
							Kmap[1][2].inclusion = Kmap[1][2].inclusion + 1;
					}

					Implicant A;
					for (int k = 0; k < AllElemntsInImplicant.size(); k++)
					{
						A.minterms.push_back(AllElemntsInImplicant[k]);
						cout << AllElemntsInImplicant[k].binaryminterm << " ";
					}
					cout << endl << "Todas las implicaciones hechas" << endl;
					A.Size = AllElemntsInImplicant.size();
					AllImplicants.push_back(A);
					A.minterms.clear();
					A.Size = 0;

					implicantNum++;
				}
				V1.clear();
				V2.clear();
				V3.clear();
				V4.clear();
				V5.clear();
			}
		}
	}
}

vector <KmapElement> GetVectorOfMaxSize(vector<KmapElement> V1, vector<KmapElement> V2, vector<KmapElement> V3, vector<KmapElement> V4, vector<KmapElement> V5)
{
	int Sizes[5];
	Sizes[0] = V1.size();
	Sizes[1] = V2.size();
	Sizes[2] = V3.size();
	Sizes[3] = V4.size();
	Sizes[4] = V5.size();

	int max = -1;
	int vector_number;
	for (int i = 0; i < 5; i++)
	{
		if (Sizes[i] > max)
		{
			max = Sizes[i];
			vector_number = i + 1;
		}
	}
	if (vector_number == 1)
		return V1;
	if (vector_number == 2)
		return V2;
	if (vector_number == 3)
		return V3;
	if (vector_number == 4)
		return V4;
	if (vector_number == 5)
		return V5;
}

void SortAllImplicantsBySizeInAscendingOrder()
{
	int i, j;
	for (i = 0; i < AllImplicants.size() - 1; i++)
	{
		for (j = 0; j < AllImplicants.size() - i - 1; j++)
			if (AllImplicants[j].Size > AllImplicants[j + 1].Size)
			{
				Implicant temp = AllImplicants[j];
				AllImplicants[j] = AllImplicants[j + 1];
				AllImplicants[j + 1] = temp;
			}
	}

	for (i = 0; i < AllImplicants.size(); i++)
	{
		cout << "Despues de clasifiacion: " << i << "  ";
		for (j = 0; j < AllImplicants[i].minterms.size(); j++)
			cout << AllImplicants[i].minterms[j].binaryminterm << "  ";
		cout << endl;
	}
}



void AssignInclusionTimesToImplicants()
{
	for (int i = 0; i < AllImplicants.size(); i++)
	{
		for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
		{
			if (AllImplicants[i].minterms[j].DecimalMinterm == 0)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[0][0].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 1)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[0][1].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 2)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[0][3].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 3)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[0][2].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 4)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[1][0].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 5)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[1][1].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 6)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[1][3].inclusion;
			}
			else if (AllImplicants[i].minterms[j].DecimalMinterm == 7)
			{
				AllImplicants[i].minterms[j].inclusion = Kmap[1][2].inclusion;
			}
		}
	}
}

void RemoveDuplicateImplicants()
{
	int isEqual = 0;
	for (int i = 0; i < AllImplicants.size(); i++)
	{
		for (int k = 1; k < AllImplicants.size() - 1; k++)
		{
			for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
			{
				for (int N = 0; N < AllImplicants[k].minterms.size(); N++)
				{
					if (AllImplicants[i].minterms[j].binaryminterm == AllImplicants[k].minterms[N].binaryminterm)
					{
						isEqual++;
					}
				}

				if (isEqual == AllImplicants[i].minterms.size() && AllImplicants[i].Size == AllImplicants[k].Size)
				{
					DecreaseInclusionOfMintermsInDeletedImplicant(i);
					AllImplicants.erase(AllImplicants.begin() + i);
				}
				isEqual = 0;
			}
		}
	}
}

void DecreaseInclusionOfMintermsInDeletedImplicant(int i)
{
	int* DecimalMinterm = new int[AllImplicants[i].minterms.size()];
	for (int m = 0; m < AllImplicants[i].minterms.size(); m++)
	{
		DecimalMinterm[m] = AllImplicants[i].minterms[m].DecimalMinterm;
	}
	for (int k = 0; k < AllImplicants.size(); k++)
	{
		for (int L = 0; L < AllImplicants[k].minterms.size(); L++)
		{
			for (int S = 0; S < AllImplicants[i].minterms.size(); S++)
			{
				if (AllImplicants[k].minterms[L].binaryminterm == AllImplicants[i].minterms[S].binaryminterm)
				{
					AllImplicants[k].minterms[L].inclusion = AllImplicants[k].minterms[L].inclusion - 1;
				}
			}
		}
	}
}


void GetEssentialPrimeImplicants()
{
	cout << "Despues remover los implicantes duplicados " << endl;
	for (int i = 0; i < AllImplicants.size(); i++)
	{
		cout << "Implicante " << i << " con minterminos ";
		for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
			cout << AllImplicants[i].minterms[j].binaryminterm << " ";
		cout << endl;
	}

	int NumberOfMintermsIncludedinOtherImplicants = 0;

	for (int i = 0; i < AllImplicants.size(); i++)
	{
		NumberOfMintermsIncludedinOtherImplicants = 0;
		for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
		{
			cout << "inclusion de minterminos  " << j << " es = " << AllImplicants[i].minterms[j].inclusion << " implicante  " << i << endl;
			if (AllImplicants[i].minterms[j].inclusion > 1)
				NumberOfMintermsIncludedinOtherImplicants++;
		}

		if (NumberOfMintermsIncludedinOtherImplicants == AllImplicants[i].Size)
		{
			DecreaseInclusionOfMintermsInDeletedImplicant(i);
			AllImplicants.erase(AllImplicants.begin() + i);
			--i;
			cout << "borrar" << endl;
		}
	}
	cout << "despus de la eliminacion" << endl;
	for (int i = 0; i < AllImplicants.size(); i++)
	{
		for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
		{
			string minterm = AllImplicants[i].minterms[j].binaryminterm;
			cout << minterm << " ";
		}
		cout << i << endl;
	}
}

void GetFinalExpression()
{
	string* MintermsInPI;
	string PI = "";
	int NumOfMinterms;
	for (int i = 0; i < AllImplicants.size(); i++)
	{
		NumOfMinterms = AllImplicants[i].minterms.size();
		MintermsInPI = new string[AllImplicants[i].minterms.size()];
		for (int j = 0; j < AllImplicants[i].minterms.size(); j++)
		{
			MintermsInPI[j] = AllImplicants[i].minterms[j].binaryminterm;
			cout << MintermsInPI[j];
		}

		int NoChange = 0;

		for (int L = 0; L < 3; L++)
		{
			int m = 0;
			for (int k = 1; k < NumOfMinterms; k++)
			{
				cout << endl << "MintermsInPI[m][L] == MintermsInPI[k][L]" << MintermsInPI[m][L] << " " << MintermsInPI[k][L] << endl;
				if (MintermsInPI[m][L] == MintermsInPI[k][L])
				{
					NoChange++;
				}
			}

			cout << "Sin cambio " << NoChange << endl;

			if (NoChange == NumOfMinterms - 1)
			{
				if (MintermsInPI[0][L] == '0')
				{
					PI += "(~";
					PI += char(L + 65);
					PI += ")";
				}
				else if (MintermsInPI[0][L] == '1')
				{
					PI += "(";
					PI += char(L + 65);
					PI += ")";
				}
			}
			NoChange = 0;
		}
		PI += " + ";
	}
	FinalExpression = PI;
	FinalExpression = FinalExpression.erase(FinalExpression.size() - 2);
}
