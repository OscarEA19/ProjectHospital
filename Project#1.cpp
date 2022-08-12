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

//Add Doctor
void addDoctor(listaDoctor &cab ,string fullName, string specialty, int doctorCode){
	
	nodoDoctor *newDoctor;
        	
    newDoctor = createDoctor(fullName,specialty, doctorCode);
    if(cab == NULL){
        cab = newDoctor;
        cout <<"DOCTOR ALMACENADA CORRECTAMENTE...\n";
    }else{
        newDoctor -> next = cab;
        cab = newDoctor;
        cout <<"DOCTOR ALMACENADA CORRECTAMENTE...\n";
    }
    
}

//Delete a user
void deleteUser(listaUser &cab,int userCode){
	listaUser aux,ant;
	
	if(cab == NULL){
	    cout <<"Lista vacia";
	}
	else{
		aux =cab;
		if(aux -> userCode == userCode){
			cab = aux -> next;
			aux -> next = NULL;
			delete(aux);
			aux =cab;
			cout <<"Usuario Eliminado Correctamente..";
		}
		else{
			ant =aux;
			while(aux!=NULL){
				if(aux->userCode == userCode && aux -> next !=NULL){
					ant->next=aux->next;
					aux->next=NULL;
					delete(aux);
					aux=cab;
					cout <<"Usuario Eliminado Correctamente..";
				}
				else{
					if(aux->userCode==userCode && aux->next==NULL){
						ant->next=NULL;
						delete(aux);
						aux=cab;
						cout <<"Usuario Eliminado Correctamente..";
					}	
				}
				ant = aux;
				aux = aux ->next;
			}
		}
	}
}

//Delete a Doctor
void deleteDoctor(listaDoctor &cab,int doctorCode){
	listaDoctor aux,ant;
	
	if(cab == NULL){
	    cout <<"Lista vacia";
	}
	else{
		aux =cab;
		if(aux -> doctorCode == doctorCode){
			cab = aux -> next;
			aux -> next = NULL;
			delete(aux);
			aux =cab;
			cout <<"Doctor Eliminado Correctamente..";
		}
		else{
			ant =aux;
			while(aux!=NULL){
				if(aux->doctorCode == doctorCode && aux -> next !=NULL){
					ant->next=aux->next;
					aux->next=NULL;
					delete(aux);
					aux=cab;
					cout <<"Doctor Eliminado Correctamente..";
				}
				else{
					if(aux->doctorCode==doctorCode && aux->next==NULL){
						ant->next=NULL;
						delete(aux);
						aux=cab;
						cout <<"Doctor Eliminado Correctamente..";
					}	
				}
				ant = aux;
				aux = aux ->next;
			}
		}
	}
}

//Modify accountStatus User
void modifyStatusUser(listaUser &cab,int userCode){
	listaUser aux= NULL;
	
	if(cab == NULL){
	    cout <<"Lista vacia";
	}
	else{
		aux=cab;
		while(aux!=NULL){
			if(aux->userCode==userCode){
    			aux->accountStatus=false;    
    			cout <<"Usuario modificado Correctamente";
 			}	
			aux=aux->next;
		}
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
			cout << "Password: " << "*********" <<endl;
			cout << "----------------------------\n" <<endl;
			aux=aux->next ;
		}
	}	
}

// Show Doctor
void showDoctor(listaDoctor cab){
	
	listaDoctor aux;
	
	if(cab == NULL)
	cout <<"Lista vacia" << endl;
	else
	{
		aux=cab;
		while(aux!=NULL)
		{
			cout << "Nombre: " << aux -> fullName <<endl;
			cout << "Especialidad: " << aux -> specialty <<endl;
			cout << "Codigo Doctor: " << aux -> doctorCode <<endl;
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
			if(aux -> fullName == fullName && aux -> password == password && aux -> userType == userType && aux -> accountStatus == true){
				return true;
			}
			aux = aux -> next;
		}
		return false;		
	}
}


void menu(){
	
	listaUser ListaUser = NULL;
	addUser(ListaUser ,"Oscar", 1, 'A', "oscarrrr", "Oscar12%");

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
	//Data Doctor
	string specialty;
	int doctorCode;
	
	
	do{
		system("cls");
		cout <<"*************MENU PARA USUARIOS*************\n"<<endl;
		cout <<"1.LOGIN COMO ADMINISTRADOR"<<endl;
		cout <<"2.LOGIN COMO ESTANDAR"<<endl;
		cout <<"3.VER BASE DE DATOS DE USUARIOS"<<endl;
		cout <<"4.SALIR\n"<<endl;
		cout <<"INGRESE LA OPCION QUE DESEA: ";
		cin >> opcionUser;
		
		switch (opcionUser){
			case 1: {
				system("cls");
				cout <<"*********************LOGIN*********************\n";
				cout <<"DIGITE EL NOMBRE COMPLETO: ";
				cin >> fullName;
				cout <<"DIGITE LA PASSWORD: ";
				cin >> password;
				
				//all opcion admin
				if(checkLogin(ListaUser , fullName , password , 'A')){
					cout <<"BIENVENID@ ADMINISTRAD@R\n";
					
					int opcionAdmin;
					
					do{
						system("cls");
						cout <<"*************MENU PARA ADMINISTRADOR*************\n"<<endl;
						cout <<"1.CREAR CUENTA PARA USUARIO(ADMINISTRADOR)"<<endl;
						cout <<"2.CREAR CUENTA PARA USUARIO(ESTANDAR)"<<endl;
						cout <<"3.ELIMINAR UN USUARIO"<<endl;
						cout <<"4.ACTIVAR O DESACTIVAR CUENTAS DE USUARIOS"<<endl;
						cout <<"5.INGRESAR UN DOCTOR"<<endl;
						cout <<"6.ELIMINAR LA INFORMACION DE UN DOCTOR POR MEDIO DEL CODIGO"<<endl;
						cout <<"7.MODIFICAR LA INFORMACION DE UN DOCTOR POR MEDIO DEL CODIGO"<<endl;
						cout <<"8.INGRESAR UN PACIENTE"<<endl;
						cout <<"9.ELIMINAR UN PACIENTE"<<endl;
						cout <<"10.MODIFICAR LA INFORMACION DE UN PACIENTE POR MEDIO DE LA CEDULA"<<endl;
						cout <<"11.VER LISTA DE USUARIOS"<<endl;
						cout <<"12.VER LISTA DE DOCTORES"<<endl;
						cout <<"13.VER LISTA DE PACIENTES"<<endl;
						cout <<"14.SALIR\n";
						cin >> opcionAdmin;
						
						switch(opcionAdmin){
							
							case 1:{
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
							case 2:{
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
								addUser(ListaUser ,fullName, userCode, userType, userAccount, password);
								system("Pause");
								break;
							}
							case 3:{
								system("cls");
								cout <<"DIGITE EL CODIGO DE USUARIO QUE DESEA ELIMINAR: ";
								cin >> userCode;
								deleteUser(ListaUser, userCode);					
								system("Pause");
								break;
							}
							case 4:{
								system("cls");
								cout <<"DIGITE EL CODIGO DE USUARIO AL QUE DESEA CAMBIARLE EL ESTADO: ";
								cin >> userCode;
								modifyStatusUser(ListaUser, userCode);					
								system("Pause");
								break;
							}
							case 5:{
								system("cls");
								cout <<"DIGITE EL NOMBRE COMPLETO DEL DOCTOR: ";
								cin >> fullName;
								cout <<"DIGITE LA ESPECIALIDAD DEL DOCTOR: ";
								cin >> specialty;
								cout <<"DIGITE EL CODIGO DEL DOCTOR";
								cin >> doctorCode;
								addDoctor(ListaDoctor, fullName, specialty, doctorCode);
								system("Pause");
								break;
							}
							case 6:{
								system("cls");
								cout <<"DIGITE EL CODIGO DEL DOCTOR QUE DESEA ELIMINAR: ";
								cin >> doctorCode;
								deleteDoctor(ListaDoctor,doctorCode);			
								system("Pause");
								break;
							}
							case 7:{
								
								break;
							}
							case 8:{
								
								break;
							}
							case 9:{
								
								break;
							}
							case 10:{
								
								break;
							}
							case 11:{
								
								break;
							}
							case 12:{
								system("cls");
								showDoctor(ListaDoctor);
								system("Pause");
								break;
							}
							case 13:{
								
								break;
							}	
						}
					}while(opcionAdmin!=14);
				}else{
					cout <<"NO SE ENCONTRO EL USUARIO ADMINISTRADOR";
				}
				system("Pause");
				break;
			}
			case 2: {
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
			case 3: {
				system("cls");
				showUser(ListaUser);
				system("Pause");
				break;
			}
		}
	}while(opcionUser != 4);
}

int main(){
	menu();
}
