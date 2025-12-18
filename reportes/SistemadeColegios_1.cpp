#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

const int MAX=1000; //Para cantidad maxima del sistema
const int MAX_PROF=100;

vector<string> materias = {
    "Programacion Avanzada",
    "Matematica I",
    "Filosofia",
    "Ecologia",
    "Realidad Nacional",
    "Matematica Discreta II",
    "Fisica"
};

class Estudiante;
class Persona;
class Nota;
class Profesor;

class Nota {
private:
    string codigoEst;
    string curso;
    float nota;
public:
    Nota(string c, string m, float n){
        codigoEst = c;
        curso = m;
        nota = n;
    }
    string getCodigoEst() { return codigoEst; }
    string getCurso() { return curso; }
    float getNota() { return nota; }
};

//CLASE BASE
class Persona{
	protected:
		string dni;
		string nombres;
		string apellidos;
	public:
		Persona(string, string, string);
		virtual void mostrarDatos();
		string getdni();
		string getnombres();
		string getapellidos();
};

Persona::Persona (string d, string n, string ap){
	dni=d;
	nombres=n;
	apellidos=ap;
}

string Persona::getdni(){
	return dni;
}
string Persona::getnombres(){
    return nombres;
}
string Persona::getapellidos(){
    return apellidos;
}
void Persona::mostrarDatos(){
	cout<<"DNI: "<<dni<<endl;
    cout<<"Nombres: "<<nombres<<endl;
    cout<<"Apellidos: "<<apellidos<<endl;
}

//Clase derivada de Persona
class Estudiante:public Persona{
	private:
		string codigo;
		string anio;
		string contrasenia;
	public:
		Estudiante(string, string, string, string, string,string);
		string getcodigo();
		string getanio();
		string getcontrasenia();
		void mostrarDatos();
};

Estudiante::Estudiante (string d, string n, string ap, string cd, string an, string contra) : Persona(d, n, ap){
	codigo=cd;
	anio=an;
	contrasenia=contra;
}

string Estudiante::getcontrasenia(){
	return contrasenia;
}
string Estudiante::getcodigo(){
	return codigo;
}
string Estudiante::getanio(){
	return anio;
}

void Estudiante::mostrarDatos(){
	system("cls");
	cout<<" --- Datos del estudiante ---"<<endl;
	Persona::mostrarDatos();
	cout<<"Codigo: "<<codigo<<endl;
    cout<<"Año: "<<anio<<endl;
    system("pause");
}

class Profesor{
private:
    string nombre;
    string contrasenia;
    string materia;
    vector<Estudiante*> estudiantes; // Lista de estudiantes del curso
public:
    Profesor(string n, string c, string m): nombre(n), contrasenia(c), materia(m){}
    string getNombre(){return nombre;}
    string getContrasenia(){return contrasenia;}
    string getMateria(){return materia;}
    vector<Estudiante*>& getEstudiantes(){return estudiantes;}
    void mostrarDatos() {
        cout<<"--- DATOS DEL PROFESOR ---\n";
        cout<<"Nombre: "<<nombre<<endl;
        cout<<"Materia: "<<materia<<endl;
    }
    void registrarNota();
    float promedioCurso();
    float notaMasAlta(); 
    void ordenarEstudiantesLista(); // implementarás con quicksort
};

void Profesor::registrarNota(){
    if(estudiantes.empty()){
        cout<<"No hay estudiantes en su curso.\n";
        return;
    }
    cout<<"--- Registrar nota para la materia: "<<materia<<" ---\n";
    cout<<"Seleccione un estudiante:\n";
    for(int i=0;i<estudiantes.size();i++){
        cout<<i+1<<". "<<estudiantes[i]->getapellidos()<<", "<<estudiantes[i]->getnombres()<<" (Codigo: "<<estudiantes[i]->getcodigo()<<")\n";
    }
    int opcion;
    cout<<"Ingrese el número del estudiante: ";
    cin>>opcion;
    if(opcion<1||opcion>estudiantes.size()){
        cout<<"Opción inválida.\n";
        return;
    }
    float nota;
    cout<<"Ingrese la nota del estudiante: ";
    cin>>nota;
    ofstream archivo("Notas.txt",ios::app);
    archivo<<estudiantes[opcion-1]->getcodigo()<<"|"<<materia<<"|"<<nota<<"|\n";
    archivo.close();
    cout<<"Nota registrada correctamente.\n";
}

float Profesor::promedioCurso(){
    vector<float> notas; 
    ifstream archivo("Notas.txt");
    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo de notas.\n";
        return 0;
    }
    string linea,codigo,curso,notaStr;
    while(getline(archivo,linea)){
        stringstream ss(linea);
        getline(ss,codigo,'|');
        getline(ss,curso,'|');
        getline(ss,notaStr,'|');
        if(curso==materia){ // Solo notas de la materia de este profesor
            notas.push_back(stof(notaStr));
        }
    }
    archivo.close();
    if(notas.empty()){
        cout<<"No hay notas registradas para esta materia.\n";
        return 0;
    }
    float suma=0;
    for(float n:notas) suma+=n;
    return suma/notas.size();
}

float Profesor::notaMasAlta(){
    if(estudiantes.empty()){
        cout<<"No hay estudiantes en el curso.\n";
        return 0;
    }

    vector<float> notasCurso;
    ifstream archivo("Notas.txt");
    string linea,codigo,curso,notaStr;
    while(getline(archivo,linea)){
        stringstream ss(linea);
        getline(ss,codigo,'|');
        getline(ss,curso,'|');
        getline(ss,notaStr,'|');
        if(curso==materia){
            notasCurso.push_back(stof(notaStr));
        }
    }
    archivo.close();

    if(notasCurso.empty()){
        cout<<"No hay notas registradas para esta materia.\n";
        return 0;
    }

    sort(notasCurso.begin(), notasCurso.end());

    int low=0, high=notasCurso.size()-1;
    float maxNota=0;
    while(low<=high){
        int mid=(low+high)/2;
        if(notasCurso[mid]>=maxNota){
            maxNota=notasCurso[mid];
            low=mid+1;
        } else {
            high=mid-1;
        }
    }

    return maxNota;
}

//Funciones declaradas
void cargarProfesores(Profesor* profesores[], int &nProf);   // Cargar desde archivo txt
void loginProfesor(Profesor* profesores[], int &nprof);       // Login para ingresar al menú de profesor
void menuProfesor(Profesor* profesor);                        // Menú del profesor
void verNotas(Estudiante *estudiante);
void menuprincipal(Estudiante *estudiantes[], Profesor *profesores[], int &n, int &nProf);
void loginestudiante(Estudiante *estudiantes[], int &n);
void menuestudiante(Estudiante *estudiante);
void asignarEstudiantesAProfesores(Profesor* profesores[], int nProf, Estudiante* estudiantes[], int n);

void cargarEstudiantes(Estudiante *estudiantes[], int &n);
void registrarEstudiante(Estudiante *estudiantes[], int &n);

bool codigoExiste(string codigo);
bool codigoYaRegistrado(string codigo);

void verNotas(Estudiante *estudiante){
    string materias[]={"Programacion Avanzada","Matematica I","Filosofia","Ecologia","Realidad Nacional","Matematica Discreta II","Fisica"};
    ifstream archivo("Notas.txt");
    string linea,codigo,curso,nota;
    map<string,string> notas;
    while(getline(archivo,linea)){
        stringstream ss(linea);
        getline(ss,codigo,'|');
        getline(ss,curso,'|');
        getline(ss,nota,'|');
        if(codigo==estudiante->getcodigo())
            notas[curso]=nota;
    }
    archivo.close();
    system("cls");
    cout<<"---- Notas del estudiante ----"<<endl;
    for(string m:materias){
        if(notas.count(m)) cout<<m<<": "<<notas[m]<<endl;
        else cout<<m<<": Sin registrar"<<endl;
    }
    cout<<endl;
    system("pause");
}

//-------------------------- FUNCIONES DE LOGIN ESTUDIANTE --------------------------
void loginestudiante(Estudiante *estudiantes[], int &n){
	int rpta;
	char resto;	
	do{
		system("cls");
		cout<<" ---- Bienvenido ----"<<endl;
		cout<<"Ingrese a su cuenta de estudiante (O registrese): ";
		cout<<"\n1. iniciar sesion\n";
		cout<<"2. Registrarse\n";
		cout<<"3. Salir";
		cout<<"\nIndique la alternativa: ";
		while(true){
			cin>>rpta;
			resto=cin.peek();
			if(cin.fail() || resto!='\n'){
				cin.clear();
				cin.ignore(1000,'\n');
				system("cls");
				cout<<"Ingrese una opcion valida: ";
			}
			else if(rpta<=0){
				system("cls");
				cout<<"Ingrese una opcion valida: ";
			}
			else
				break;
		}
		
		switch (rpta){
			case 1:
				{
				int pos=0;
				bool encontrado=false;
				string contrasenia;
				system("cls");
				cout<<"Ingrese su contraseña: ";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				getline(cin, contrasenia);
				while (pos<n){
					if(estudiantes[pos]->getcontrasenia() == contrasenia){
						encontrado=true;
						break;
					}
					pos++;
				}
				if(encontrado){
				cout<<"Inicio de sesión exitoso\n";
				Sleep(1000);
				menuestudiante(estudiantes[pos]); 
				return;
				} else {
				cout<<"Contraseña incorrecta\n";
				break;
				}
				break;	
				}
			case 2:
				registrarEstudiante(estudiantes, n);
				break;
			case 3:
				break;		
		}
	} while (rpta!=3);
}

void menuestudiante(Estudiante *estudiante){
	char opcionestudiante;
	do{
		system("cls");
		
        cout<<"--- Bienvenido "<<estudiante->getnombres()<<" ---"<<endl;
        cout<<"Ingrese opción de usuario: "<<endl;
        cout<<"A. Ver datos: "<<endl;
        cout<<"B. Ver notas: "<<endl;
        cout<<"X. Salir"<<endl; 
        cin>>opcionestudiante;
        opcionestudiante=toupper(opcionestudiante);
        switch(opcionestudiante){
            case 'A':
                cout<<"Datos de estudiante"<<endl;
				estudiante->mostrarDatos();
                break;
            case 'B':
                verNotas(estudiante);
                break;     
            case 'X':
                cout<<"Cerrando programa..."<<endl;
                break;
            default:
                cout<<"ERROR. Opcion ingresada no disponible"<<endl;
        }
    }while(opcionestudiante!='X');	
}

//-------------------------- CODIGOS AUXILIARES --------------------------
bool codigoExiste(string codigo){
	ifstream archivo("codigos.txt");
	string linea;
	if(archivo.fail()) return false;
	while(getline(archivo,linea)){
		if(linea==codigo){
			archivo.close();
			return true;
		}
	}
	archivo.close();
	return false;
}

bool codigoYaRegistrado(string codigo){
	ifstream archivo("Estudiantes.txt");
	string linea;
	if(archivo.fail()) return false;
	while(getline(archivo,linea)){
		string d,nm,ap,cod;
		stringstream ss(linea);
		getline(ss,d,'|');
		getline(ss,nm,'|');
		getline(ss,ap,'|');
		getline(ss,cod,'|');
		if(cod==codigo){
			archivo.close();
			return true;
		}
	}
	archivo.close();
	return false;
}

void registrarEstudiante(Estudiante *estudiantes[], int &n){
	string dni,nombres,apellidos,codigo,anio,contrasenia;
	system("cls");
	cout<<"--- REGISTRO DE ESTUDIANTE ---\n";
	cout<<"Ingrese codigo: ";
	cin.ignore();
	getline(cin,codigo);

	if(!codigoExiste(codigo)){
		cout<<"\nERROR: Codigo no autorizado\n";
		system("pause");
		return;
	}
	if(codigoYaRegistrado(codigo)){
		cout<<"\nERROR: Codigo ya registrado\n";
		system("pause");
		return;
	}

	cout<<"Ingrese DNI: ";
	getline(cin,dni);
	cout<<"Ingrese nombres: ";
	getline(cin,nombres);
	cout<<"Ingrese apellidos: ";
	getline(cin,apellidos);
	cout<<"Ingrese año: ";
	getline(cin,anio);
	cout<<"Ingrese contraseña: ";
	getline(cin,contrasenia);

	ofstream archivo("Estudiantes.txt", ios::app);
	archivo<<dni<<"|"<<nombres<<"|"<<apellidos<<"|"<<codigo<<"|"<<anio<<"|"<<contrasenia<<"\n";
	archivo.close();

	estudiantes[n]=new Estudiante(dni,nombres,apellidos,codigo,anio,contrasenia);
	n++;

	cout<<"\nRegistro exitoso\n";
	system("pause");
}

//-------------------------- MENU PRINCIPAL --------------------------
void menuprincipal(Estudiante *estudiantes[],Profesor *profesores[], int &n, int &nProf){
	char opcionmenu;
	do{
		system("cls");
        cout<<"--- SISTEMA DE NOTAS DE COLEGIO ---"<<endl;
        cout<<"A. Ingresar como estudiante"<<endl;
        cout<<"B. Ingresar como profesor"<<endl;
        cout<<"X. Salir"<<endl;
        cout<<"Ingrese opcion de usuario: ";
        cin>>opcionmenu;
        opcionmenu=toupper(opcionmenu);
        switch(opcionmenu){
            case 'A':
                loginestudiante(estudiantes, n);
                break;
            case 'B':
                loginProfesor(profesores, nProf);
                break;
            case 'X':
                cout<<"Cerrando programa..."<<endl;
                Sleep(1000);
                break;
            default:
                cout<<"ERROR. Opcion ingresada no disponible"<<endl;
        }
    }while(opcionmenu!='X');	
}

//-------------------------- LOGIN PROFESOR --------------------------
void loginProfesor(Profesor* profesores[], int &nProf){
    int rpta;
    char resto;
    do{
        system("cls");
        cout<<" ---- Bienvenido Profesor ----"<<endl;
        cout<<"1. Iniciar sesión\n";
        cout<<"2. Salir\n";
        cout<<"Ingrese su opción: ";
        
        while(true){
            cin >> rpta;
            resto = cin.peek();
            if(cin.fail() || resto != '\n'){
                cin.clear();
                cin.ignore(1000,'\n');
                system("cls");
                cout<<"Ingrese una opcion valida: ";
            }
            else if(rpta <= 0){
                system("cls");
                cout<<"Ingrese una opcion valida: ";
            }
            else break;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer antes de getline

        switch(rpta){
            case 1:{
                system("cls");
                string contrasenia;
                cout<<"Ingrese su contraseña: ";
                getline(cin, contrasenia);  // Ahora sí lee correctamente
                bool encontrado = false;
                int pos = 0;
                while(pos < nProf){
                    if(profesores[pos]->getContrasenia() == contrasenia){
                        encontrado = true;
                        break;
                    }
                    pos++;
                }

                if(encontrado){
                    cout<<"Inicio de sesión exitoso\n";
                    Sleep(1000);
                    menuProfesor(profesores[pos]); 
                    return;
                } else{
                    cout<<"Contraseña incorrecta\n";
                    system("pause");
                }
                break;
            }
            case 2:
                cout<<"Saliendo...\n";
                Sleep(1000);
                break;
            default:
                cout<<"Opción no válida\n";
                system("pause");
        }
    } while(rpta != 2);
}

//-------------------------- MENU PROFESOR --------------------------
void menuProfesor(Profesor* profesor){
    char opcion;
    do{
        system("cls");
		cout<<"---- Bienvenido Profesor: "<<profesor->getNombre()<<" ----"<<endl;
        cout<<"A. Ver mis datos\n";
        cout<<"B. Registrar notas\n";
        cout<<"C. Promedio de mi curso\n";
        cout<<"D. Nota más alta\n";
        //cout<<"E. Lista de estudiantes ordenada por apellido\n";
        cout<<"X. Salir\n";
        cout<<"Ingrese opción: ";
        cin>>opcion;
        opcion=toupper(opcion);

        switch(opcion){
            case 'A':
                system("cls");
    			profesor->mostrarDatos();  
   				system("pause");
   				break;
            case 'B':
                system("cls");
                profesor->registrarNota(); 
                system("pause");
                break;
            case 'C':
                system("cls");
   				cout<<"Promedio del curso ("<<profesor->getMateria()<<"): "<<profesor->promedioCurso()<<endl;
  				system("pause");
    			break;
                break;
            case 'D':
                system("cls");
                cout<<"Nota más alta del curso: "<<profesor->notaMasAlta()<<endl;
                system("pause");
                break;
            /*case 'E':
                system("cls");
                cout<<"Lista de estudiantes ordenada por apellido:\n";
                profesor->ordenarEstudiantesLista();
                system("pause");
                break;*/
            case 'X':
                cout<<"Saliendo del menú profesor...\n";
                Sleep(1000);
                break;
            default:
                cout<<"Opción inválida\n";
                system("pause");
        }
    }while(opcion!='X');
}

//-------------------------- CARGAR DATOS --------------------------
void cargarEstudiantes(Estudiante *estudiantes[], int &n){
	ifstream archivo("Estudiantes.txt");
	string linea;
	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo\n";
		exit(1);
	}
	while(getline(archivo,linea)){
		string d,nm,ap,cod,an,con;
		stringstream ss(linea);
		getline(ss,d,'|');
		getline(ss,nm,'|');
		getline(ss,ap,'|');
		getline(ss,cod,'|');
		getline(ss,an,'|');
		getline(ss,con,'|');
		estudiantes[n]=new Estudiante(d,nm,ap,cod,an,con);
		n++;
	}
	archivo.close();
}

void cargarProfesores(Profesor* profesores[], int &nProf){
    ifstream archivo("Profesores.txt");
    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo de profesores\n";
        exit(1);
    }
    string linea;
    while(getline(archivo,linea)){
        string nom,mat,con;
        stringstream ss(linea);
        getline(ss,nom,'|');
        getline(ss,mat,'|');
        getline(ss,con,'|');
        profesores[nProf]=new Profesor(nom,con,mat);
        nProf++;
    }
    archivo.close();
}

void asignarEstudiantesAProfesores(Profesor* profesores[], int nProf, Estudiante* estudiantes[], int nEst){
    for(int i=0;i<nProf;i++){
        for(int j=0;j<nEst;j++){
            profesores[i]->getEstudiantes().push_back(estudiantes[j]);
        }
    }
}

//-------------------------- MAIN --------------------------
int main (){
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	
	int n=0;
	Estudiante *estudiantes[MAX];
	cargarEstudiantes(estudiantes, n);
	
	int nProf=0;
    Profesor* profesores[MAX_PROF];
    cargarProfesores(profesores,nProf);
	asignarEstudiantesAProfesores(profesores,nProf,estudiantes,n);
    
    menuprincipal(estudiantes,profesores, n, nProf);
	
	return 0;
}
