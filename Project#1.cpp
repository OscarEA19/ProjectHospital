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
    bool atendido;
    string specialty;
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
nodoDate *createDate(int doctorCode, string day, string hour,string dni,bool atendido, string specialty){
    nodoDate *aux =  new (struct nodoDate);
    aux -> doctorCode = doctorCode;
    aux -> day = day;
    aux -> hour = hour;
    aux -> dni = dni;
    aux->atendido = atendido;
    aux->specialty = specialty;
    aux -> next = NULL;
    return aux;
} 

//add record 
void addrecord(listaRecord &cab, string fullName, string attentionDate, int doctorCode, string symptoms, string medicines,string exam){
	
	nodoRecord *newRecord; 
	
	newRecord = createRecord(fullName,attentionDate,doctorCode,symptoms, medicines, exam);
	if(cab == NULL ){
		cab = newRecord; 
		cout<< "EXPEDIENTE ALMACENADO CORRECTAMENTE";
	}else{
		newRecord -> next = cab;
		cab= newRecord;
		cout<< "EXPEDIENTE ALMACENADO CORRECTAMENTE";
	}	
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
//show Date
void showDate(listaDate cab){
	
	listaDate aux;
	
	if(cab == NULL)
	cout <<"Lista vacia" << endl;
	else
	{
		aux=cab;
		while(aux!=NULL)
		{
			cout << "Codigo del doctor: " << aux -> doctorCode <<endl;
			cout << "Dia de la cita: " << aux -> day <<endl;
			cout << "Hora de la cita: " << aux -> hour <<endl;
			cout << "Cedula del paciente: " << aux -> dni <<endl;
			cout << "Atendido: " << aux -> atendido <<endl;
			cout << "Especialidad del doctor: " << aux->specialty <<endl;
			cout << "----------------------------------"<<endl;
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
void addDate(listaDate &cab, int doctorCode, string day, string hour,string dni,string specialty){
	
	nodoDate *newDate; 
	
	newDate = createDate( doctorCode, day, hour,dni,false,specialty);
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
			cout <<"CITA ALTERADA CORRECTAMENTE..";
		}
		else{
			ant =aux;
			while(aux!=NULL){
				if(aux -> dni == dni && aux->doctorCode==doctorCode && aux -> next !=NULL){
					ant->next=aux->next;
					aux->next=NULL;
					delete(aux);
					aux=cab;
					cout <<"CITA ALTERADA CORRECTAMENTE..";
				}
				else{
					if(aux -> dni == dni && aux->doctorCode==doctorCode && aux->next==NULL){
						ant->next=NULL;
						delete(aux);
						aux=cab;
						cout <<"CITA ALTERADA CORRECTAMENTE..";
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
	string specialty;
	bool asignar = true;
	
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
				specialty = auxDoctor->specialty;
			}
			else if(auxDoctor ->specialty == "Odontologo" && symptoms == "Caries"){
				doctorCode = auxDoctor ->doctorCode;
				cout <<"DOCTOR CON ESPECIALIDAD:"<<auxDoctor ->specialty<< endl;
				specialty = auxDoctor->specialty;
			}else if(auxDoctor ->specialty == "Dermatologia" && symptoms == "Acne"){
				doctorCode = auxDoctor ->doctorCode;
				cout <<"DOCTOR CON ESPECIALIDAD:"<<auxDoctor ->specialty<< endl;
				specialty = auxDoctor->specialty;
			}else if(auxDoctor ->specialty == "Neumologia" && symptoms == "Asma"){
				doctorCode = auxDoctor ->doctorCode;
				cout <<"DOCTOR CON ESPECIALIDAD:"<<auxDoctor ->specialty<< endl;
				specialty = auxDoctor->specialty;
			}else if(auxDoctor ->specialty == "Neurologia" && symptoms == "Mareos"){
				doctorCode = auxDoctor ->doctorCode;
				cout <<"DOCTOR CON ESPECIALIDAD:"<<auxDoctor ->specialty<< endl;
				specialty = auxDoctor->specialty;
			}
			else{
				if(specialty == " "){
				cout <<"NO SE ENCONTRO UN DOCTOR PARA ASIGNAR"<< endl;
				asignar= false;	
				}
			}
			auxDoctor=auxDoctor->next ;
		}
	}
	
	if(asignar){
			//Check list Date for get a doctor available
		if(CheckDoctorAvailable(cab,doctorCode,hour, day)){
			addDate(cab, doctorCode, day, hour,dni,specialty);
		}else{
			cout <<"INTENTALO DE NUEVO" << endl;
		}
	}else{
		cout <<"NO EXISTE DOCTORES DISPONIBLES" << endl;
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
void modifyDateAtendido(listaDate &cab, string dni,int doctorCode){
	listaDate aux;
	
	if(cab == NULL)
	cout <<"Lista vacia" << endl;
	else
	{
		aux=cab;
		while(aux!=NULL)
		{
			if(aux->doctorCode==doctorCode && aux->dni ==dni){
				aux->atendido=true;
			}
			aux=aux->next ;
		}
	}
}

//add a patient in a Record
void addPatientInRecord(listaDoctor cabDoctor,listaPatient cabPatient,listaRecord &cab,listaDate &cabDate,string dni,int doctorCode,string exam,string medicines){
	
	listaPatient auxPatient;
	listaDoctor auxDoctor;
	
	string fullName;
	string symptoms;
	string attentionDate;
	
	bool existDoctor = false;
	
	//Check list doctor for exit doctor
	if(cabDoctor == NULL)
	cout <<"Lista doctores vacias" << endl;
	else
	{
		auxDoctor=cabDoctor;
		while(auxDoctor!=NULL)
		{
			if(auxDoctor->doctorCode == doctorCode){
				existDoctor = true;
			}
			auxDoctor=auxDoctor->next;
		}
	}
	
	if(!existDoctor){
		cout <<"No existe el doctor con este codigo: "<<doctorCode<< endl;
	}
	
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
	listaDate auxDate;
		
	if(cabDate == NULL)
	cout <<"Lista de citas vacias" << endl;
	else
	{
		auxDate=cabDate;
		while(auxDate!=NULL)
		{
			if(auxDate->dni == dni && auxDate->doctorCode==doctorCode){
				attentionDate = auxDate->day+"_"+auxDate->hour;
			}
			auxDate=auxDate->next ;
		}
	}
	
	//add 
	addrecord(cab,fullName,attentionDate,doctorCode, symptoms, medicines, exam);
	
	//Delete date
	modifyDateAtendido(cabDate, dni,doctorCode);
	
}


void verificarCountDoctoresWithEspecialidad(listaDoctor cab, string specialty){
	
	int count=0;
	listaDoctor aux;
	
	if(cab == NULL)
	cout <<"Lista vacia" << endl;
	else
	{
		aux=cab;
		while(aux!=NULL)
		{
			if(aux->specialty == specialty){
				count++;
			}
			
			aux=aux->next ;
		}
	}	
	cout <<"TOTAL DE DOCTORES CON LA ESPECIALIDAD "<<specialty << ": " <<count<< endl;
}

void verifiDoctor(listaDoctor cab,int doctorCode){
	
	listaDoctor aux;
	
	if(cab == NULL)
	cout <<"Lista vacia" << endl;
	else
	{
		aux=cab;
		while(aux!=NULL)
		{
			if(aux->doctorCode==doctorCode){
				cout << "Nombre: " << aux -> fullName <<endl;
				cout << "Especialidad: " << aux -> specialty <<endl;
				cout << "Codigo Doctor: " << aux -> doctorCode <<endl;
			}			
			aux=aux->next ;
		}
	}
}
	

void verifiPatient(listaPatient cab,string dni){
	
	listaPatient aux;
	
	if(cab == NULL)
	cout <<"Lista vacia" << endl;
	else
	{
		aux=cab;
		while(aux!=NULL)
		{
			if(aux->dni == dni){
				cout << "Nombre: " << aux -> fullName <<endl;
				cout << "Cedula: " << aux -> dni <<endl;
				cout << "Numero Telefonico: " << aux -> phoneNumber <<endl;
				cout << "Sintomas: " << aux -> symptoms <<endl;
				cout << "Fecha de entrada: " << aux -> entryDate <<endl;
			}
			aux=aux->next ;
		}
	}
}

void verificarCitasPorFecha(listaDate cab, string day){
	listaDate aux;
	
	if(cab == NULL)
	cout <<"Lista vacia" << endl;
	else
	{
		aux=cab;
		while(aux!=NULL)
		{
			if(aux->day==day){
				cout << "Codigo del doctor: " << aux -> doctorCode <<endl;
				cout << "Dia de la cita: " << aux -> day <<endl;
				cout << "Hora de la cita: " << aux -> hour <<endl;
				cout << "Cedula del paciente: " << aux -> dni <<endl;
				cout << "Atendido: " << aux -> atendido <<endl;
				cout << "----------------------------------"<<endl;
			}
			aux=aux->next ;
		}
	}
}


void verificarCantidadPacientesPorEspecialidadAndAtendido(listaDate cab, string specialty){
	
	listaDate aux;
	int count=0;
	
	if(cab == NULL)
	cout <<"Lista vacia" << endl;
	else
	{
		aux=cab;
		while(aux!=NULL)
		{
			if(aux->specialty==specialty && aux->atendido ==true){
				count++;
			}
			aux=aux->next ;
		}
	}
	cout << "Cantidad de pacientes segun la especialidad " << specialty << ": " <<count <<endl;
}

void verificarCantidadPacienteAtendidoPorDoctor(listaDate cab, int doctorCode){
	
	listaDate aux;
	int count=0;
	
	if(cab == NULL)
	cout <<"Lista vacia" << endl;
	else
	{
		aux=cab;
		while(aux!=NULL)
		{
			if(aux->doctorCode==doctorCode && aux->atendido ==true){
				count++;
			}
			aux=aux->next ;
		}
	}
	cout << "Cantidad de pacientes segun el codigo del doctor " << doctorCode << ", atendidos: " <<count <<endl;
}

void verificarPacienteDoctorCita( listaDate cab,listaPatient cabPatient, string dni){
	
	listaPatient auxPatient;
	
	if(cabPatient == NULL)
	cout <<"Lista vacia" << endl;
	else
	{
		auxPatient=cabPatient;
		while(auxPatient!=NULL)
		{
			if(auxPatient->dni ==dni){
				cout << "Nombre del paciente: " << auxPatient->fullName <<endl;
			}
			auxPatient=auxPatient->next ;
		}
	}
	
	listaDate aux;
	
	if(cab == NULL)
	cout <<"Lista vacia" << endl;
	else
	{
		aux=cab;
		while(aux!=NULL)
		{
			if(aux->dni==dni){
				cout << "Codigo del doctor: " << aux -> doctorCode <<endl;
				cout << "Dia de la cita: " << aux -> day <<endl;
				cout << "Hora de la cita: " << aux -> hour <<endl;
				cout << "Cedula del paciente: " << aux -> dni <<endl;
				cout << "----------------------------------"<<endl;
			}
			aux=aux->next ;
		}
	}		
}

void doctoresTotales(listaDoctor cab){
	
	listaDoctor aux;
	int count=0;
	
	if(cab == NULL)
	cout <<"Lista vacia" << endl;
	else
	{
		aux=cab;
		while(aux!=NULL)
		{
			count++;
			aux=aux->next ;
		}
	}
	cout << "Cantidad de doctores totales: " << count<<endl;
}

void menu(){
	
	listaUser ListaUser = NULL;
	addUser(ListaUser ,"Oscar Espinoza", 1, 'A', "oscarrrr", "Oscar12%");
	addUser(ListaUser, "Carlos Austin",3,'E',"Carlosrt","Carlos12%");
	listaDoctor ListaDoctor = NULL;
	addDoctor(ListaDoctor,"Monse","Cardiologo");
	addDoctor(ListaDoctor,"oscar","Neurologia");
    listaPatient ListaPatient = NULL;
	addPatient(ListaPatient,"Aaron R","123456789","88888888","Taquicardia","16/08/2022");
    addPatient(ListaPatient,"samuel","22222222","88888888","Mareos","16/08/2022");
    listaRecord ListaRecord = NULL;
    
    listaDate ListaDate =NULL;
    addDate(ListaDate,41,"18/08/2022","12","123456789","Cardiologo");
    
    
    	
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
	//Data Record
	string medicine;
	string exam;
	do{
		system("color 71");
		system("cls");
		cout <<"*************MENU PARA USUARIOS*************\n"<<endl;
		cout <<"1.LOGIN COMO ADMINISTRADOR"<<endl;
		cout <<"2.LOGIN COMO ESTANDAR"<<endl;
		cout <<"3.VER LISTA VERIFICAR"<<endl;
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
						system("color 71");
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
					system("color 71");
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
						system("color 71");
						system("cls");
						cout <<"*************MENU PARA USUARIOS ESTANDAR*************\n"<<endl;
						cout <<"1.INGRESAR UN PACIENTE"<<endl;
						cout <<"2.ELIMINAR UN PACIENTE"<<endl;
						cout <<"3.MODIFICAR LA INFORMACION DE UN PACIENTE POR MEDIO DE LA CEDULA"<<endl;
						cout <<"4.ASIGNAR UNA CITA A UN PACIENTE"<<endl;
						cout <<"5.MODIFICAR UNA CITA"<<endl;
						cout <<"6.ELIMINAR UNA CITA"<<endl;
						cout <<"7.ATENDER PACIENTE"<<endl;
						cout <<"8.VER EXPEDIENTE DEL LOS PACIENTE"<<endl;
						cout <<"9.VER LISTA PACIENTES"<<endl;
						cout <<"10.VER LISTA CITAS"<<endl;
						cout <<"11.SALIR\n";
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
								cout <<"DIGITE EL CODIGO DEL DOCTOR QUE LO ATENDIO: ";
								cin >> doctorCode;
								cout <<"DIGITE LAS MEDICINAS ENVIADAS AL PACIENTE: ";
								cin >> medicine;
								cout <<"DIGITE LOS EXAMENES ENVIADOS AL PACIENTE: ";
								cin >> exam;
								addPatientInRecord(ListaDoctor,ListaPatient,ListaRecord,ListaDate,dni,doctorCode,exam,medicine);								
								system("Pause");
								break;
							}
							case 8:{
								system("cls");
								showRecord(ListaRecord);
								system("Pause");
								break;
							}
							case 9:{
								system("cls");
								showPatien(ListaPatient);
								system("Pause");
								break;
							}
							case 10:{
								system("cls");
								showDate(ListaDate);
								system("Pause");
								break;
							}
						}
					}while(opcionEstandar!=11);	
					system("color 71");
				}else{
					cout <<"NO SE ENCONTRO EL USUARIO ESTANDAR";
				}
				system("Pause");
				break;
			}
			case 3: {
				system("cls");
				cout <<"*********************OPCIONES VERFICAR*********************\n";		
				int opcionEstandar;
					do{
						system("color 71");
						system("cls");
						cout <<"*********************OPCIONES VERFICAR*********************\n";
						cout <<"1.VERIFICAR LOS DATOS DE UN PACIENTE POR LA CEDULA"<<endl;
						cout <<"2.VERIFICAR LOS DATOS DE UN DOCTOR POR EL CODIGO DEL DOCTOR"<<endl;
						cout <<"3.VERIFICAR LAS CITAS ESTABLECIDAS POR EN UNA FECHA"<<endl;
						cout <<"4.VERIFICAR LA CANTIDAD DE PACIENTE ATENDIDOS SEGUN LA ESPECIALIDAD"<<endl;
						cout <<"5.VERIFICAR LOS PACIENTES POR EL NOMBRE Y NUMERO DE CEDULA, ASI COMO EL DOCTOR QUE LOS ATIENDE Y LA HORA DE LA CITA POR MEDIO DEL DIA Y MES"<<endl;
						cout <<"6.VERIFICAR LA CANTIDAD DE DOCTORES DE ACUERDO A LA ESPECIALIDA"<<endl;
						cout <<"7.VERIFICAR LA CANTIDAD TOTAL DE DOCTORES EN LA CLINICA"<<endl;
						cout <<"8.VERIFICAR LA CANTIDAD DE PACIENTES ATENDIDOS POR DOCTOR"<<endl;
						cout <<"9.SALIR\n";
						cin >> opcionEstandar;
						
						switch(opcionEstandar){
							case 1:{
								system("cls");
								cout <<"DIGITE LA CEDULA DEL PACIENTE: ";
								cin >> dni;
								verifiPatient(ListaPatient , dni);
								system("Pause");
								break;
							}
							case 2:{
								system("cls");
								cout <<"DIGITE EL CODIGO DEL DOCTOR: ";
								cin >> doctorCode;
								verifiDoctor(ListaDoctor,doctorCode);
								system("Pause");
								break;
							}
							case 3:{
								system("cls");
								cout <<"DIGITE LA FECHA: ";
								cin >> day;
								verificarCitasPorFecha(ListaDate, day);
								system("Pause");
								break;
							}
							case 4:{
								system("cls");
								cout <<"DIGITE LA ESPECIALIDAD: ";
								cin >> specialty;
								verificarCantidadPacientesPorEspecialidadAndAtendido(ListaDate, specialty);
								system("Pause");
								break;
							}
							case 5:{
								system("cls");
								cout <<"DIGITE LA CEDULA DEL PACIENTE: ";
								cin >> dni;
								verificarPacienteDoctorCita(ListaDate,ListaPatient,dni);
								system("Pause");
								break;
							}
							case 6:{
								system("cls");
								cout <<"DIGITE LA ESPECIALIDAD: ";
								cin >> specialty;
								verificarCountDoctoresWithEspecialidad(ListaDoctor,specialty);
								system("Pause");
								break;
							}
							case 7:{
								system("cls");
								doctoresTotales(ListaDoctor);
								system("Pause");
								break;
							}
							case 8:{
								system("cls");
								cout <<"DIGITE EL CODIGO DEL DOCTOR: ";
								cin >> doctorCode;
								verificarCantidadPacienteAtendidoPorDoctor(ListaDate, doctorCode);
								system("Pause");
								break;
							}
						}
					}while(opcionEstandar!=9);
					system("color 71");	
				system("Pause");
				break;	
			}
		}
	}while(opcionUser != 4);
	system("color 71");
}

int main(){
	menu();
}
