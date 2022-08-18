#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

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
//Date
struct nodoDate{
    int doctorCode;//doctor Code
    string dni;//the id numbero of a patient
    string day;//day for the date
    string hour;//hour for the date
    nodoDate *next; 
};

typedef struct nodoUser *listaUser;
typedef struct nodoDoctor *listaDoctor;
typedef struct nodoPatient *listaPatient;
typedef struct nodoRecord *listaRecord;
typedef struct nodoDate *listaDate;


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
 
//Create a date
nodoDate *createDate(int doctorCode, string day, string hour,string dni){
    nodoDate *aux =  new (struct nodoDate);
    aux -> doctorCode = doctorCode;
    aux -> day = day;
    aux -> hour = hour;
    aux -> dni = dni;
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

//this method check a doctor for diff code 
bool checkCodeDoctor(listaDoctor cab, int doctorCode){
		
	listaDoctor aux;
	
	aux=cab;
	while(aux!=NULL){
		if(aux -> doctorCode == doctorCode){
			return true; 
		}
		aux=aux->next ;
	}
	return false;
	
}

//Add Doctor
void addDoctor(listaDoctor &cab ,string fullName, string specialty){
	
	nodoDoctor *newDoctor; 
	
	int doctorCode = (rand()%100);
	
	if(checkCodeDoctor(cab, doctorCode)){
		addDoctor(cab,fullName ,specialty);
	}
    else {
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
}

//add patient 
void addPatient(listaPatient &cab, string fullName, string dni, string phoneNumber, string symptoms, string entryDate){
	
	nodoPatient *newPatient; 
	
	newPatient = createPatient( fullName, dni, phoneNumber, symptoms, entryDate);
	if(cab == NULL ){
		cab = newPatient; 
		cout<< "PACIENTE ALMACENADO CORRECTAMENTE";
	}else{
		newPatient -> next = cab;
		cab= newPatient;
		cout<< "PACIENTE ALMACENADO CORRECTAMENTE";
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

//Delete a Patient
void deletePatient(listaPatient &cab,string dni){
	listaPatient aux,ant;
	
	if(cab == NULL){
	    cout <<"Lista vacia";
	}
	else{
		aux =cab;
		if(aux -> dni == dni){
			cab = aux -> next;
			aux -> next = NULL;
			delete(aux);
			aux =cab;
			cout <<"PACIENTE ELIMINADO CORRECTAMENTE..";
		}
		else{
			ant =aux;
			while(aux!=NULL){
				if(aux->dni == dni && aux -> next !=NULL){
					ant->next=aux->next;
					aux->next=NULL;
					delete(aux);
					aux=cab;
					cout <<"PACIENTE ELIMINADO CORRECTAMENTE..";
				}
				else{
					if(aux->dni==dni && aux->next==NULL){
						ant->next=NULL;
						delete(aux);
						aux=cab;
						cout <<"PACIENTE ELIMINADO CORRECTAMENTE..";
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

//Change data doctor
void modifyDataDoctor(listaDoctor &cab,int doctorCode){
	listaDoctor aux= NULL;
	listaDoctor edit = cab;
	bool doctorEncontrado = false;
	
	//Data Doctor
	string fullName;
    string specialty;
	
	if(cab == NULL){
	    cout <<"Lista vacia";
	}
	else{
		aux=cab;
		while(aux!=NULL){
			if(aux->doctorCode==doctorCode){
    			cout <<"Doctor encontrado correctamente \n";
    			doctorEncontrado = true;
 			}	
			aux=aux->next;
		}
		
		if(doctorEncontrado){
			cout <<"DIGITE EL NUEVO NOMBRE DEL DOCTOR: \n";
			cin >> fullName;
			cout <<"DIGITE LA ESPECIALIDAD DEL DOCTOR: \n"; 
			cin >> specialty;
		
			while(edit != NULL){
				if(edit->doctorCode == doctorCode){
					edit -> fullName = fullName;
					edit -> specialty = specialty;
					cout <<"DOCTOR ACTUALIZADO CORRECTAMENTE: \n";
				}		
				edit = edit->next;				
			}	
		}else{
			cout << "DOCTOR NOT FOUND \n";
		}
	}
}

//Change data patient
void modifyDataPatient(listaPatient &cab,string dni){
	listaPatient aux= NULL;
	listaPatient edit = cab;
	bool patientFound;
	
	//Data Patient
	string fullName;
	string phoneNumber;
	string symptom;
	string entryDate;
	
	if(cab == NULL){
	    cout <<"Lista vacia";
	}
	else{
		aux=cab;
		while(aux!=NULL){
			if(aux->dni==dni){
    			cout <<"Paciente encontrado correctamente \n";
    			patientFound = true;
 			}	
			aux=aux->next;
		}
		
		if(patientFound){
			cout <<"DIGITE EL NUEVO NOMBRE DEL PACIENTE: \n";
			cin >> fullName;
			cout <<"DIGITE EL NUEVO NUMERO TELEFONICO DEL PACIENTE: \n"; 
			cin >> phoneNumber;
			cout <<"DIGITE LOS NUEVOS SINTOMAS DEL PACIENTE: \n"; 
			cin >> symptom;
			cout <<"DIGITE LA NUEVO FECHA DE ENTRADA DEL PACIENTE: \n"; 
			cin >> entryDate;
			
			while(edit != NULL){
				if(edit->dni == dni){
					edit -> fullName = fullName;
					edit -> phoneNumber = phoneNumber;
					edit -> symptoms = symptom;
					edit -> entryDate = entryDate;
					cout <<"PACIENTE ACTUALIZADO CORRECTAMENTE: \n";
				}		
				edit = edit->next;				
			}	
		}else{
			cout << "PATIENT NOT FOUND";
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
			cout << "----------------------------\n" <<endl;
			aux=aux->next ;
		}
	}	
}
//Show Patient
void showPatien(listaPatient cab){
	
	listaPatient aux;
	
	if(cab == NULL)
	cout <<"Lista vacia" << endl;
	else
	{
		aux=cab;
		while(aux!=NULL)
		{
			cout << "Nombre: " << aux -> fullName <<endl;
			cout << "Cedula: " << aux -> dni <<endl;
			cout << "Numero Telefonico: " << aux -> phoneNumber <<endl;
			cout << "Sintomas: " << aux -> symptoms <<endl;
			cout << "Fecha de entrada: " << aux -> entryDate <<endl;
			cout << "----------------------------\n" <<endl;
			aux=aux->next ;
		}
	}
}
//show Record
void showRecord(listaRecord cab){
	
	listaRecord aux;
	
	if(cab == NULL)
	cout <<"Lista vacia" << endl;
	else
	{
		aux=cab;
		while(aux!=NULL)
		{
			cout << "Nombre: " << aux -> fullName <<endl;
			cout << "Fecha de atencion: " << aux -> attentionDate <<endl;
			cout << "Codigo del doctor: " << aux -> doctorCode <<endl;
			cout << "Sintomas del paciente: " << aux -> symptoms <<endl;
			cout << "Medicamentos: " << aux -> medicines <<endl;
			cout << "Examenes: " << aux -> exam <<endl;
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

//add date 
void addDate(listaDate &cab, int doctorCode, string day, string hour,string dni){
	
	nodoDate *newDate; 
	
	newDate = createDate( doctorCode, day, hour,dni);
	if(cab == NULL ){
		cab = newDate; 
		cout<< "CITA ALMACENADA CORRECTAMENTE";
	}else{
		newDate -> next = cab;
		cab= newDate;
		cout<< "CITA ALMACENADA CORRECTAMENTE";
	}	
}

//CheckDoctorAvailable
bool CheckDoctorAvailable(listaDate cab,int doctorCode,string hour,string day){
	int countDate;
	listaDate aux;
	
	aux=cab;
	while(aux!=NULL)
	{
		if(aux->doctorCode == doctorCode && aux->hour==hour && aux->day==day){
			countDate++;
		}
		aux=aux->next ;
	}
	
	if(countDate>=2){
		cout <<"NO HAY DOCTOR DISPONIBLE PARA ESTA HORA" << endl;
		return false;	
	}else{
		return true;
	}
	
}

//Delete a date
void deleteDate(listaDate &cab,string dni,int doctorCode){
	listaDate aux,ant;
	
	if(cab == NULL){
	    cout <<"Lista vacia";
	}
	else{
		aux =cab;
		if(aux -> dni == dni && aux->doctorCode==doctorCode){
			cab = aux -> next;
			aux -> next = NULL;
			delete(aux);
			aux =cab;
			cout <<"CITA ELIMINADA CORRECTAMENTE..";
		}
		else{
			ant =aux;
			while(aux!=NULL){
				if(aux -> dni == dni && aux->doctorCode==doctorCode && aux -> next !=NULL){
					ant->next=aux->next;
					aux->next=NULL;
					delete(aux);
					aux=cab;
					cout <<"CITA ELIMINADA CORRECTAMENTE..";
				}
				else{
					if(aux -> dni == dni && aux->doctorCode==doctorCode && aux->next==NULL){
						ant->next=NULL;
						delete(aux);
						aux=cab;
						cout <<"CITA ELIMINADA CORRECTAMENTE..";
					}	
				}
				ant = aux;
				aux = aux ->next;
			}
		}
	}
}

void methodCreateADate(listaDoctor cabDoctor,listaPatient cabPatient,listaDate &cab, string dni,string day,string hour){
	string symptoms;
	int doctorCode;
	
	listaPatient auxPatient;
	listaDoctor auxDoctor;
	
	
	//Check list patient for get the symptoms
	if(cabPatient == NULL)
	cout <<"Lista de Pacientes vacia" << endl;
	else
	{
		auxPatient=cabPatient;
		while(auxPatient!=NULL)
		{
			if(auxPatient ->dni == dni){
				symptoms = auxPatient ->symptoms;
			}
			auxPatient=auxPatient->next ;
		}
	}
	//Check list Doctor for get the doctorCode, where the specialty is 'equal' to symptoms
	if(cabDoctor == NULL)
	cout <<"Lista de Doctores vacia" << endl;
	else
	{
		auxDoctor=cabDoctor;
		while(auxDoctor!=NULL)
		{
			if(auxDoctor ->specialty == "Cardiologo" && symptoms == "Taquicardia"){
				doctorCode = auxDoctor ->doctorCode;
				cout <<"DOCTOR CON ESPECIALIDAD: "<<auxDoctor ->specialty<< endl;
			}
			else if(auxDoctor ->specialty == "Odontologo" && symptoms == "Caries"){
				doctorCode = auxDoctor ->doctorCode;
				cout <<"DOCTOR CON ESPECIALIDAD:"<<auxDoctor ->specialty<< endl;
			}else if(auxDoctor ->specialty == "Dermatologia" && symptoms == "Acne"){
				doctorCode = auxDoctor ->doctorCode;
				cout <<"DOCTOR CON ESPECIALIDAD:"<<auxDoctor ->specialty<< endl;
			}else if(auxDoctor ->specialty == "Neumologia" && symptoms == "Asma"){
				doctorCode = auxDoctor ->doctorCode;
				cout <<"DOCTOR CON ESPECIALIDAD:"<<auxDoctor ->specialty<< endl;
			}else if(auxDoctor ->specialty == "Neurologia" && symptoms == "Mareos"){
				doctorCode = auxDoctor ->doctorCode;
				cout <<"DOCTOR CON ESPECIALIDAD:"<<auxDoctor ->specialty<< endl;
			}else{
				cout <<"NO SE ENCONTRO UN DOLOR PARA ASIGNAR"<< endl;	
			}
			auxDoctor=auxDoctor->next ;
		}
	}
	
	//Check list Date for get a doctor available
	if(CheckDoctorAvailable(cab,doctorCode,hour, day)){
		addDate(cab, doctorCode, day, hour,dni);
	}else{
		cout <<"INTENTALO DE NUEVO" << endl;
	}
}

//Change data date
void modifyDataDate(listaDate &cab,int doctorCode,string day,string hour,string dni){
	listaDate aux= NULL;
	listaDate edit = cab;
	bool dateFound = false;
	
	//Data date
	string newDay;
    string newHour;
	
	if(cab == NULL){
	    cout <<"Lista vacia";
	}
	else{
		aux=cab;
		while(aux!=NULL){
			if(aux->doctorCode == doctorCode && aux->day==day && aux->hour == hour && aux->dni ==dni){
    			cout <<"Cita encontrada correctamente \n";
    			dateFound = true;
 			}	
			aux=aux->next;
		}
		
		if(dateFound){
			cout <<"DIGITE EL NUEVO DIA DE SU CITA: \n";
			cin >> newDay;
			cout <<"DIGITE LA NUEVA HORA DE SU CITA: \n"; 
			cin >> newHour;
		
			while(edit != NULL){
				if(aux->doctorCode==doctorCode && aux->day==day && aux->hour ==hour){
					edit -> day = day;
					edit -> hour = hour;
					cout <<"CITA ACTUALIZADA CORRECTAMENTE: \n";
				}		
				edit = edit->next;				
			}	
		}else{
			cout << "CITA NOT FOUND \n";
		}
	}
}

//add a patient in a Record
void addPatientInRecord(listaPatient cabPatient,listaRecord &cab,listaDate &cabDate,string dni,string attentionDate,int doctorCode,string exam){
	
	listaPatient auxPatient;
	
	string fullName;
	string symptoms;
	string attentionDate;
	
	//Check list patient for get the symptoms
	if(cabPatient == NULL)
	cout <<"Lista de Pacientes vacia" << endl;
	else
	{
		auxPatient=cabPatient;
		while(auxPatient!=NULL)
		{
			if(auxPatient ->dni == dni){
				fullName = auxPatient ->fullName;
				symptoms = auxPatient ->symptoms;
			}
			auxPatient=auxPatient->next;
		}
	}
	
	//check list date get the 
	
	
	
	
	
	
	
	
	
	
	
	nodoRecord *newRecord; 
	
	newRecord = createRecord( fullName, attentionDate,doctorCode, symptoms,phoneNumber,exam);
	if(cab == NULL ){
		cab = newPatient; 
		cout<< "PACIENTE ALMACENADO CORRECTAMENTE";
	}else{
		newPatient -> next = cab;
		cab= newPatient;
		cout<< "PACIENTE ALMACENADO CORRECTAMENTE";
	}	
	
}

void menu(){
	
	listaUser ListaUser = NULL;
	addUser(ListaUser ,"Oscar Espinoza", 1, 'A', "oscarrrr", "Oscar12%");
	addUser(ListaUser, "Carlos Austin",3,'E',"Carlosrt","Carlos12%");
	listaDoctor ListaDoctor = NULL;
	addDoctor(ListaDoctor,"Monse","Cardiologo");
    listaPatient ListaPatient = NULL;
	addPatient(ListaPatient,"Aaron R","123456789","88888888","Fiebre","16/08/2022");
    
    listaRecord ListaRecord = NULL;
    
    listaDate ListaDate =NULL;
    
    
    	
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
	//Data Patient
	string dni;
	string phoneNumber;
	string symptom; 
	string entryDate;
	//Data Date
	string day;
	string hour;
	
	
	
	
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
				cout <<"\nDIGITE LA PASSWORD: "<<endl;
				cin >> password;
				cin.ignore(1, '\n');
				cout <<"\nDIGITE EL NOMBRE COMPLETO:";
				getline (cin, fullName);
				
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
								addDoctor(ListaDoctor, fullName, specialty);
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
								system("cls");
								cout <<"DIGITE EL CODIGO DEL DOCTOR QUE DESEA EDITAR: ";
								cin >> doctorCode;
								modifyDataDoctor(ListaDoctor , doctorCode);
								system("Pause");
								break;
							}
							case 8:{
								system("cls");
								cout <<"DIGITE EL NOMBRE COMPLETO DEL PACIENTE: ";
								cin >> fullName;
								cout <<"DIGITE LA CEDULA DEL PACIENTE: ";
								cin >> dni;
								cout <<"DIGITE EL NUMERO TELEFONICO DEL PACIENTE: ";
								cin >> phoneNumber;
								cout <<"DIGITE LOS SINTOMAS DEL PACIENTE: ";
								cin >> symptom;
								cout <<"DIGITE LA FECHA DE ENTRADA DEL PACIENTE: ";
								cin >> entryDate;
								addPatient(ListaPatient,fullName,dni,phoneNumber,symptom,entryDate);
								system("Pause");
								break;
							}
							case 9:{
								system("cls");
								cout <<"DIGITE LA CEDULA DEL PACIENTE QUE DESEA ELIMINAR: ";
								cin >> dni;
								deletePatient(ListaPatient,dni);
								system("Pause");
								break;
							}
							case 10:{
								system("cls");
								cout <<"DIGITE LA CEDULA DEL PACIENTE QUE DESEA EDITAR: ";
								cin >> dni;
								modifyDataPatient(ListaPatient,dni);
								system("Pause");
								break;
							}
							case 11:{
								system("cls");
								showUser(ListaUser);
								system("Pause");
								break;
							}
							case 12:{
								system("cls");
								showDoctor(ListaDoctor);
								system("Pause");
								break;
							}
							case 13:{
								system("cls");
								showPatien(ListaPatient);
								system("Pause");
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
				cout <<"\nDIGITE LA PASSWORD: "<<endl;
				cin >> password;
				cin.ignore(1, '\n');
				cout <<"\nDIGITE EL NOMBRE COMPLETO:";
				getline (cin, fullName);
				
				//all opcion standard
				if(checkLogin(ListaUser , fullName , password , 'E')){
					cout <<"BIENVENID@ USUARI@ ESTANDAR";
					
				int opcionEstandar;
					
					do{
						system("cls");
						cout <<"*************MENU PARA USUARIOS ESTANDAR*************\n"<<endl;
						cout <<"1.INGRESAR UN PACIENTE"<<endl;
						cout <<"2.ELIMINAR UN PACIENTE"<<endl;
						cout <<"3.MODIFICAR LA INFORMACION DE UN PACIENTE POR MEDIO DE LA CEDULA"<<endl;
						cout <<"4.ASIGNAR UNA CITA A UN PACIENTE"<<endl;
						cout <<"5.MODIFICAR UNA CITA"<<endl;
						cout <<"6.ELIMINAR UNA CITA"<<endl;
						cout <<"7.ATENDER PACIENTE"<<endl;
						cout <<"8.VER EXPEDIENTE DEL PACIENTE"<<endl;
						cout <<"9.VER LISTA PACIENTES"<<endl;
						cout <<"9.VER LISTA CITAS"<<endl;
						cout <<"10.SALIR\n";
						cin >> opcionEstandar;
						
						switch(opcionEstandar){
							case 1:{
								system("cls");
								cout <<"DIGITE EL NOMBRE COMPLETO DEL PACIENTE: ";
								cin >> fullName;
								cout <<"DIGITE LA CEDULA DEL PACIENTE: ";
								cin >> dni;
								cout <<"DIGITE EL NUMERO TELEFONICO DEL PACIENTE: ";
								cin >> phoneNumber;
								cout <<"DIGITE LOS SINTOMAS DEL PACIENTE: ";
								cin >> symptom;
								cout <<"DIGITE LA FECHA DE ENTRADA DEL PACIENTE: ";
								cin >> entryDate;
								addPatient(ListaPatient,fullName,dni,phoneNumber,symptom,entryDate);
								system("Pause");
								break;
							}
							case 2:{
								system("cls");
								cout <<"DIGITE LA CEDULA DEL PACIENTE QUE DESEA ELIMINAR: ";
								cin >> dni;
								deletePatient(ListaPatient,dni);
								system("Pause");
								break;
							}
							case 3:{
								system("cls");
								cout <<"DIGITE LA CEDULA DEL PACIENTE QUE DESEA EDITAR: ";
								cin >> dni;
								modifyDataPatient(ListaPatient,dni);
								system("Pause");
								break;
							}
							case 4:{
								system("cls");
								cout <<"DIGITE LA CEDULA DEL PACIENTE AL QUE DESEA GUARDARLE UNA CITA: ";
								cin >> dni;
								cout <<"DIGITE EL DIA DE LA CITA (FORMAT-> 01/12/2022): ";
								cin >> day;
								cout <<"DIGITE LA HORA DE LA CITA (FORMAT-> 24hh): ";
								cin >> hour;
								methodCreateADate(ListaDoctor,ListaPatient,ListaDate,dni,day,hour);		
								system("Pause");
								break;
							}
							case 5:{
								system("cls");
								cout <<"DIGITE LA CEDULA DEL PACIENTE: ";
								cin >> dni;
								cout <<"DIGITE EL DIA DE LA CITA (FORMAT-> 01/12/2022): ";
								cin >> day;
								cout <<"DIGITE LA HORA DE LA CITA (FORMAT-> 24hh): ";
								cin >> hour;
								cout <<"DIGITE EL CODIGO DEL DOCTOR: ";
								cin >> doctorCode;
								modifyDataDate(ListaDate,doctorCode,day,hour,dni);
								system("Pause");
								break;
							}
							case 6:{
								system("cls");
								cout <<"DIGITE LA CEDULA DEL PACIENTE: ";
								cin >> dni;
								cout <<"DIGITE EL CODIGO DEL DOCTOR: ";
								cin >> doctorCode;
								deleteDate(ListaDate,dni,doctorCode);
								system("Pause");
								break;
							}
							case 7:{
								system("cls");
								cout <<"DIGITE LA CEDULA DEL PACIENTE QUE DESEA ATENDER: ";
								cin >> dni;
								
								system("Pause");
								break;
							}
							case 8:{
								system("cls");
								
								system("Pause");
								break;
							}
							case 9:{
								system("cls");
							
								system("Pause");
								break;
							}
						}
					}while(opcionEstandar!=10);	
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
