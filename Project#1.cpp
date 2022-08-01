#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//Model User 
struct nodoUser{
    string fullName;//full name person 
    int userCode;//user code 
    char userType;//user type -> ('E' or 'A')
    string userAccount;//user account max-length: 8 char 
    string password;//user password max-length: 8 char and format -> (number,special char,upperCase letters, lowerCase letters)
    bool accountStatus;// account status -> (true or false)
    nodoUser *next;
};
//Model Doctor
struct nodoDoctor{
  string fullName;//full name doctor
  string specialty;//the doctor specialty
  int doctorCode;//doctor code this number is random
  nodoDoctor *next;
};
//Model Patient
struct nodoPatient{
    string fullName;//full name patient
    string dni;//the id numbero of a patient
    string phoneNumber;//the phone number of a patient
    string symptoms;//the symptoms of a patient
    string entryDate;//entry date 
    nodoPatient *next; 
};
//Model Record-> expediente:registro
struct nodoRecord{
    string fullName;//full name of a patient
    string attentionDate;//the date of the patient seen
    int doctorCode;//the doctor code
    string symptoms;//the symptoms of a patient
    string medicines;//the patient medicine 
    string exam;//A test extra
    nodoRecord *next; 
};

typedef struct nodoUser *listaUser;
typedef struct nodoDoctor *listaDoctor;
typedef struct nodoPatient *listaPatient;
typedef struct nodoRecord *listaRecord;

//Create an User
nodoUser *createUser(string fullName, int userCode, char userType, string userAccount, string password, bool accountStatus){
    nodoUser *aux =  new (struct nodoUser);
    aux -> fullName = fullName;
    aux -> userCode = userCode;
    aux -> userType = userType;
    aux -> userAccount = userAccount;
    aux -> password = password;
    aux -> accountStatus = accountStatus;
    aux -> next = NULL;
    return aux;
}
//Create a Doctor
nodoDoctor *createDoctor(string fullName, string specialty, int doctorCode){
    nodoDoctor *aux = new (struct nodoDoctor);
    aux -> fullName = fullName;
    aux -> specialty = specialty;
    aux -> doctorCode = doctorCode;
    aux -> next = NULL;
    return aux;
}

//Create a Patient
nodoPatient *createPatient(string fullName, string dni, string phoneNumber, string symptoms, string entryDate){
    nodoPatient *aux = new (struct nodoPatient);
    aux -> fullName = fullName;
    aux -> dni = dni;
    aux -> phoneNumber = phoneNumber;
    aux -> symptoms = symptoms;
    aux -> entryDate = entryDate;
    aux -> next = NULL;
    return aux;
}

//Create a record 
nodoRecord *createRecord(string fullName, string attentionDate, int doctorCode, string symptoms, string medicines, string exam){
    nodoRecord *aux =  new (struct nodoRecord);
    aux -> fullName = fullName;
    aux -> attentionDate = attentionDate;
    aux -> doctorCode = doctorCode;
    aux -> symptoms = symptoms;
    aux -> medicines = medicines;
    aux -> exam = exam;
    aux -> next = NULL;
    return aux;
} 

bool checkPassword(string password){
    int n = password.length();
    bool hasLower = false, hasUpper = false;
    bool hasDigit = false, specialChar = false;
    string normalChars = "abcdefghijklmnopqrstu" "vwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";

    for (int i = 0; i < n; i++) {
        if (islower(password[i])){
        	hasLower = true;
		}
        if (isupper(password[i])){
        	hasUpper = true;
		}
        if (isdigit(password[i])){
        	hasDigit = true;
		}
        size_t special = password.find_first_not_of(normalChars);
        if (special != string::npos){
        	specialChar = true;
		}
    }
    if (hasLower && hasUpper && hasDigit && specialChar && (n >= 8)) return true;
    else if ((hasLower || hasUpper) && specialChar && (n >= 6)) return false;
    else return false;
}

//Add user
void addUser(listaUser &cab , string fullName, int userCode, char userType, string userAccount, string password){
	
	if(userType == 'E' || userType == 'A'){
	    if(userAccount.length() == 8){
	        if(checkPassword(password)){
	        	//----------------------------------------------------------------------------------
	        	nodoUser *newUser;
	        	
	            newUser = createUser(fullName,userCode,userType,userAccount,password,true);
                if(cab == NULL){
                    cab = newUser;
                    cout <<"CUENTA ALMACENADA CORRECTAMENTE...\n";
                }else{
                    newUser -> next = cab;
                    cab = newUser;
                    cout <<"CUENTA ALMACENADA CORRECTAMENTE...\n";
                }
                //----------------------------------------------------------------------------------
	        }else{
	            cout <<"LA PASSWORD TIENE QUE TENER 8 CARACTERES Y ESTAR CONFORMADAD POR (NUMEROS, CARACTERES ESPECIALES, LETRAS(MAYUSCULAS,MINUSCULAS))\n"<<endl;
	            return;  
	        }
	    }else{
	        cout <<"LA CUENTA DE USUARIO TIENE QUE TENER UN SIZE IGUAL A 8 CARACTERES\n"<<endl;
	        return; 
	    }
	}else{
	    cout <<"EL TIPO DE USARIO DISPONIBLE SON : 'A' -> ADMINISTRADOR, 'E' -> ESTANDAR\n"<<endl;
	   		return; 
	}
}

// Show User
void showUser(listaUser cab){
	
	listaUser aux;
	
	if(cab == NULL)
	cout <<"Lista vacia" << endl;
	else
	{
		aux=cab;
		while(aux!=NULL)
		{
			cout << "Nombre: " << aux -> fullName <<endl;
			cout << "Codigo: " << aux -> userCode <<endl;
			cout << "Tipo: " << aux -> userType <<endl;
			cout << "Cuenta: " << aux -> userAccount <<endl;
			cout << "Estado: " << aux -> accountStatus <<endl;
			cout << "----------------------------\n" <<endl;
			aux=aux->next ;
		}
	}	
}

//Check that person exists in data base
bool checkLogin(listaUser cab, string fullName, string password , char userType){
	listaUser aux;
	
	if(cab == NULL){
		cout <<"Lista vacia" << endl;
	}else{
		aux = cab;
		while(aux != NULL){
			if(aux -> fullName == fullName && aux -> password == password && aux -> userType == userType){
				return true;
			}
			aux = aux -> next;
		}
		return false;		
	}
}


void menu(){
	
	listaUser ListaUser = NULL;
	listaDoctor ListaDoctor = NULL;
    listaPatient ListaPatient = NULL;
    listaRecord ListaRecord = NULL;
    	
	int opcionUser;
	
	//Data User	
	string fullName;
	int userCode;
	char userType;
	string userAccount;
	string password;
	
	do{
		system("cls");
		cout <<"*************MENU PARA USUARIOS*************\n"<<endl;
		cout <<"1.CREAR CUENTA PARA USUARIO(ADMINISTRADOR)"<<endl;
		cout <<"2.CREAR CUENTA PARA USUARIO(ESTANDAR)"<<endl;
		cout <<"3.LOGIN COMO ADMINISTRADOR"<<endl;
		cout <<"4.LOGIN COMO ESTANDAR"<<endl;
		cout <<"5.VER BASE DE DATOS DE USUARIOS"<<endl;
		cout <<"6.SALIR\n"<<endl;
		cout <<"INGRESE LA OPCION QUE DESEA: ";
		cin >> opcionUser;
		
		switch (opcionUser){
			case 1: {
				system("cls");
				cout <<"DIGITE EL NOMBRE COMPLETO: ";
				cin >> fullName;
				cout <<"DIGITE EL CODIGO DEL USUARIO: ";
				cin >> userCode;
				userType = 'A';
				cout <<"DIGITE LA CUENTA DEL USUARIO CON UN SIZE DE 8 CARACTERES: ";
				cin >> userAccount;
				cout <<"DIGITE LA PASSWORD: ";
				cin >> password;
				addUser(ListaUser ,fullName, userCode, userType, userAccount, password);
				system("Pause");
				break;
			}
			case 2: {
				system("cls");
				cout <<"DIGITE EL NOMBRE COMPLETO: ";
				cin >> fullName;
				cout <<"DIGITE EL CODIGO DEL USUARIO: ";
				cin >> userCode;
				userType = 'E';
				cout <<"DIGITE LA CUENTA DEL USUARIO CON UN SIZE DE 8 CARACTERES: ";
				cin >> userAccount;
				cout <<"DIGITE LA PASSWORD: ";
				cin >> password;
				addUser(ListaUser , fullName, userCode, userType, userAccount, password);
				system("Pause");
				break;
			}
			case 3: {
				system("cls");
				cout <<"*********************LOGIN*********************\n";
				cout <<"DIGITE EL NOMBRE COMPLETO: ";
				cin >> fullName;
				cout <<"DIGITE LA PASSWORD: ";
				cin >> password;
				
				//all opcion admin
				if(checkLogin(ListaUser , fullName , password , 'A')){
					cout <<"BIENVENID@ ADMINISTRAD@R";











				}else{
					cout <<"NO SE ENCONTRO EL USUARIO ADMINISTRADOR";
				}
				system("Pause");
				break;
			}
			case 4: {
				system("cls");
				cout <<"*********************LOGIN*********************\n";
				cout <<"DIGITE EL NOMBRE COMPLETO: ";
				cin >> fullName;
				cout <<"DIGITE LA PASSWORD: ";
				cin >> password;
				
				//all opcion standard
				if(checkLogin(ListaUser , fullName , password , 'E')){
					cout <<"BIENVENID@ USUARI@ ESTANDAR";
					
					
					
					
					
					
					
					
					
					
					
					
					

				}else{
					cout <<"NO SE ENCONTRO EL USUARIO ESTANDAR";
				}
				system("Pause");
				break;
			}
			case 5: {
				system("cls");
				showUser(ListaUser);
				system("Pause");
				break;
			}
		}
	}while(opcionUser != 6);
}

int main(){
	menu();
}
