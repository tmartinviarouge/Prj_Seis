//***************************************************************************************
//
// librairie de classes mettants en oeuvre les sockets et thread demon et de reception
//
//***************************************************************************************
//	Version 3.3
//	===========
// 	auteur :  Joël Voyé  	
//	date derniere mise à jour : 30 novembre 2017
//	============================================
//	version 1:  classes sockets uniquement pour tcp mais sans classes multi-threading
//	version 2:  classes sockets uniquement pour tcp avec les classes multi-threading
//	version 3.0:  classes sockets TCP et UDP avec les classes multithreading
//	version 3.1:  ajout de la méthode 'socket_active() 
//	version 3.2:  ajout de la méthode autoriserBroadcast(bool autorisation) pour les 
//		       sockets UDP autorisation = vrai pour autoriser l'envoie en broadcast
//	version 3.3:  ajout de l'abonnement local à un groupe de lecteur multicasts 

//	liste des classes et leurs méthodes potentiellement utilisables par un programmeur :
//	------------------------------------------------------------------------------------
//
//*****************************************************************************
//				classes sockets TCP
//*****************************************************************************
//	class _Socket
//	~~~~~~~~~~~~~	
//	classe de base , elle n'est pas instanciable mais des méthodes suivante sont 
//	utilisables au travers des classes héritières
//		int getCanal ( );		
//		int getPortLocal ( );
//		int getPortDistant ( );
//		void fermer_socket();
//		bool socket_active(); // retourne 'vrai' si le descripteur (canal) est >= à 0
//
//	class c_socketTCP : public _Socket
//	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	c'est la socket dite 'de service' :
//	cette classe  est spécifique aux sockets TCP, elle n'est pas utilisble en tant que socket
//	ni active ni passive car elle n'a pas de méthode de création, en revanche elle sert pour 
//	les sockets de service puis qu'elle propose les méthodes 'lire' et 'écrire' en TCP
//		int lire(string &);
//		int ecrire(string );
//		
//	class socketClientTcp : public c_socketTCP		
//	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	c'est, en terme de laison, une socket pour l'element actif dans l'éetablissement de 
//	la conexion TCP
//	classe de socket active (en généralpor les applications clientes)
//		bool creerSocket (int port = 0 );  que si la socket a pas été fermée avant
//		bool seConnecterA( string adressServeur, int portServeur );
//
//	class socketServeurTcp : public _Socket	
//	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	classe de socket speciale démon, elle ne sert qu'à gérer les demandes de conexions des 
//	clients, elle n'a pas de méthodes 'lire' ni 'ecrire' effectives car les sockets démons
//	ne peuvent servire ni à la ecture ni à l'écriture
//		c_socketTCP * accepterDemandeConnexion();
//		bool creerSocket (int port , int nbPlaceAttente = 10);
//		
//	class socketClientTcpLo : public socketClientTcp
//	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	c'est une classe de socket cliente attachée uniquement à l'inerface loopback, donc 
//	inutilisable pour les échanges sur les interfaces physiques
//		bool creerSocket (int port = 0 );
//		bool seConnecterA( int portServeur );
//
//	class socketServeurTcpLo : public socketServeurTcp		
//	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	c'est une classe de socket démon attachée uniquement à l'inerface loopback, donc 
//	inutilisable pour les échanges sur les interfaces physiques
//		bool creerSocket (int port = 0 );
//		bool seConnecterA( int portServeur );
//		
//
//
//*****************************************************************************
//				classes sockets UDP
//*****************************************************************************
//	classe _socketBaseUDP  : public _Socket
//	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	classe de base udp elle permet de pouvoir attacher le socket sur le port et/ou 
//	l'interface qu'on desire, et de recevoir des messages. elle ne peut écrire de 
//	messages car elle va être parente de la classes inicast et multicast. cette 
//	classe est interne à la librairie
//	pour la programmation il faut utiliser une des deux classes ne commencant pas
//	par un '_' dans tout les cas l'expediteur du dernier message est enregistré 
//	dans l'attribut CoordDistant de la clase _Socket
//	  	_socketUDP(int localport = 0, string interface = STR_ANYADDR);
//
//		int lireDe(string &chaine,string & adress, int port); réception de chaine de caracteres
//		int lireDe(char *datas, int taille,string & adress, int port); 	réception de flux d'octets
//		int lire(string &chaine); 
//		int lire(char *datas, int taille);
//
//
//	classe _SocketMulticast  : public _socketBaseUDP
//	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Cette classe fournie les resources por s'incrire a un groupe auprès du noyau du système 
//	d'exploitation, elle possede les ressources pour lire mais aucune nullement pour écrire
//    		_SocketMulticast(int portDiffusion, string interface = STR_ANYADDR);
//		bool s_abonnerAuGroupeMulticast(string AdressseGroupe, bool exclusif=False);
//
//	classe SocketRecepteurMulticast  : public _socketBaseUDP
//	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Cette classe fournie les resources por s'incrire a un groupe auprès du noyau du système 
//	d'exploitation, elle possede les ressources pour lire mais aucune nullement pour écrire
//    		SocketRecepteurMulticast(int portDiffusion);
//
//	classe SocketRrecepteurMulticastLo  : public _socketBaseUDP
//	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	même classe quela précédante mais limite sa lecture à l'interface loopBack
//    		SocketRecepteurMulticastLo(int portDiffusion);
//
//	classe _socketUDP  : public _socketBaseUDP
//	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	classe de base des socket UDP unicaste. l'expediteur du dernier message est enregistré 
//	dans l'attribut CoordDistant de la clase _Socket
//		_socketUDP(int localport = 0, string interface = STR_ANYADDR);
//		int ecrireA(char *datas, int taille,string & adress, int port); envoie de binaire
//		int ecrireA(string chaine,string adress, int port); 	envoi de texte
//	dans les méthodes qui suivent le port et adresse de l'expediteur et destinataire ne sont pas 
//	précisés mais ce sont celles enregesitrées dans l'attribut CoordDistant de la clase _Socket
//		int repondre (char *datas, int taille); envoie de binaire en réponse à la dernière réception
//		int repondre (string chaine);	envoie de texte en réponse à la dernière réception
//		void autoriserBroadcast(bool autorisation);
//
//	classe c_socketUDP : public _socketUDP
//	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 	c_socketUDP(int localport=0);
//
//	classe c_socketUDPLo : public _socketUDPLo
//	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	c_socketUDPLo(int localport=0);
//
//
//*****************************************************************************
//			classes de mise en oeuvre du multi-threading  
//			utilisable aussi bien en TCP qu'en UDP
//*****************************************************************************
//	classe Demon
//	~~~~~~~~~~~
//	il ne s'agit pas d'un classe de socket mais de la classe de mise en oeuvre d'un thread 
//	démon. Cette classe doit etre héritée par la classe d'application qui devra surchager 
//	la methode 'traitementDemandeConnexion' de façon spécifique par l'application. Pour  
//	mettre en oevure le demon il s'uffit d'appeler la méthode 'activerDemon()'
//
// prototypes de ces deux méthodes :
// ---------------------------------
//		virtual void traitementDemandeConnexion()=0;
//		bool activerDemon();
//
// 	voir l'exemple "exemple_serveur2.1.cpp"
//	
//*****************************************************************************
//	classe Recepteur
//	~~~~~~~~~~~~~~~	
//	il ne s'agit pas d'un classe de socket mais de la classe de mise en oeuvre d'un thread 
//	de reception. Cette classe doit être héritée par les classes d'application clientes mais 
//	aussi par les stub coté application serveur. 
//	qui devra surchager 
//	la methode 'traitementSurReception' doit être surchargée de façon spécifique à son rôle 
//	et usage. 
//	Pour mettre en oeuvre le thread d'écoute de réception il s'uffit d'appeler la méthode 'activerReception()'
//
// prototypes de ces deux méthodes :
// ---------------------------------
//		virtual void traitementSurReception()=0;
//		bool activerReception();
//	
//	voir l'exemple "exemple_serveur2.1.cpp" et "exemple_cleint2.1.cpp"
//				
//-----------------------------------------------------------------------------------
// 	modification:
//	auteur :
//	date :
//***************************************************************************************

#ifndef _SOCKET_H
#define _SOCKET_H

#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <pthread.h>

#define STR_ANYADDR	"0.0.0.0"
#define	STR_LOOPBACK	"127.0.0.1"
#define	SOCKADDR_IN	struct sockaddr_in

#define TAILLE_BUFFER	1500

using namespace std;

//*************************************************
//	classe _Socket
//*************************************************
class _Socket
{
public:

  _Socket(int localport=0 , int remoteport=0, string remoteaddr="0.0.0.0",int nbPlaceAttente=0 ,bool M_cast=false);

  ~_Socket ( );

   bool creer_sock(int type, int port,in_addr_t Adrs_Interface, bool exclusif=false);

   int getCanal ( )   {return canal;}
   int getPortLocal ( )   {  return portLocal;  }
   int getPortDistant ( );
   string getAdresseDistante ( );
   int getNbPlacesAttente ( ){ return nbPlacesAttenteDemandeDeConnexion; }
   void fermer_socket();
   bool socket_active();

   enum CODE_ERREUR{
		PAS_D_ERREUR	= 0,
		ERR_CREATION	= -1,
		ERR_BIND	= -2,
		ERR_CONNEXION	= -3,
		ERR_LECTURE	= -4,
		ERR_ECOUTE	= -5,
		ERR_FORMAT_IPV4	= -6,
		ERR_CANAL_INVALIDE	= -7,
		ERR_NON_SURCHARGEE	= -10,
   };
   virtual int lire(char *datas, int taille) {return -ERR_NON_SURCHARGEE;};
   virtual int ecrire(char *datas, int taille) {return -ERR_NON_SURCHARGEE;};
   virtual int lireDe(char *datas, int taille,string & adress, int port) {return -ERR_NON_SURCHARGEE;};
   virtual int ecrireA(char *datas, int taille,string & adress, int port) {return -ERR_NON_SURCHARGEE;};


protected:
  int canal;
  CODE_ERREUR codErr;
  int portLocal;
  SOCKADDR_IN CoordDistant;
  bool MultiCast;
  int nbPlacesAttenteDemandeDeConnexion;
};


//*************************************************
//	classe _socketBaseUDP
//*************************************************
class _socketBaseUDP  : public _Socket
{
public:
   _socketBaseUDP(int localport = 0, string interface = STR_ANYADDR, bool M_cast=false);

   int lireDe(string &chaine,string & adress, int &port);
   int lireDe(char *datas, int taille,string & adress, int &port);
   int lire(string &chaine);
   int lire(char *datas, int taille);

};

//*************************************************
//	classe _SocketMulticast
//*************************************************
class _SocketMulticast  : public _socketBaseUDP
{
public:
    _SocketMulticast(int portDiffusion);
    bool sAbonnerAuGroupeMulticast(string AdressseGroupe, bool exclusif=false , string interface=STR_ANYADDR);
};

//*************************************************
//	classe SocketRecepteurMulticast
//*************************************************
class SocketRecepteurMulticast  : public _SocketMulticast
{
public:
    SocketRecepteurMulticast(int portDiffusion);
};



//*************************************************
//	classe _socketUDP
//*************************************************
class _socketUDP : public _socketBaseUDP
{
public:
   _socketUDP(int localport = 0, string interface = STR_ANYADDR);
   int ecrireA(string chaine,string & adress, int port);
   int ecrireA(char *datas, int taille,string adress, int port);
   int repondre (char *datas, int taille);
   int repondre (string chaine);
   void autoriserBroadcast(bool autorisation);

protected:
   int broadcastPossible;
};


//*************************************************
//	classe c_socketUDP
//*************************************************
class c_socketUDP : public _socketUDP
{
public:
   c_socketUDP(int localport=0);
};


//*************************************************
//	classe c_socketUDPLo
//*************************************************
class c_socketUDPLo : public _socketUDP
{
public:
   c_socketUDPLo(int localport=0);
};

//*************************************************
//	classe c_socketTCP
//*************************************************
class c_socketTCP : public _Socket
{
public:
   c_socketTCP( int canal =0 ,int localport=0, int remoteport=0,string remoteaddr="0.0.0.0", int nbPlaceAttente=0);

   int lire(string &chaine);
   int ecrire(string chaine);
   int lire(char *datas, int taille) ;
   int ecrire(char *datas, int taille);

};

//*************************************************
//	classe socketClientTcp 
//*************************************************
class socketClientTcp : public c_socketTCP
{
public:
  socketClientTcp (int port = 0 );
  ~socketClientTcp ( );
  bool creerSocket (int port = 0 );
  bool seConnecterA(string adressServeur, int portServeur );

};

//*************************************************
//	classe socketServeurTcp
//*************************************************
class socketServeurTcp : public _Socket
{
public:
   socketServeurTcp ();
   socketServeurTcp (int port , int nbPlaceAttente = 10);
   ~socketServeurTcp ( );
   c_socketTCP * accepterDemandeConnexion();
   bool creerSocket (int port , int nbPlaceAttente = 10);

protected:
   struct sockaddr_in coordClient;
};

//*************************************************
//	classe socketClientTcpLo
//*************************************************
class socketClientTcpLo : public socketClientTcp
{
public:
  socketClientTcpLo ( );
  ~socketClientTcpLo ( );
  bool creerSocket (int port = 0 );
  bool seConnecterA( int portServeur );

};


//*************************************************
//	classe socketServeurTcpLo
//*************************************************
class socketServeurTcpLo : public socketServeurTcp
{
public:
   socketServeurTcpLo (int port , int nbPlaceAttente = 10);
   bool creerSocket (int port , int nbPlaceAttente = 10);

};

//*************************************************
//	classe _SOCK_THREAD
//*************************************************
class _SOCK_THREAD
{
public:
	_SOCK_THREAD();
	~_SOCK_THREAD();

	virtual void _Corps()= 0;
	virtual bool activerDemon();
	virtual bool activerReception();

protected :
	void ActiverThread();

private :
	static void *StartStatic(void *pUser);
	pthread_t _pthread;
};


//*************************************************
//	classe DemonSock
//*************************************************
class Demon : public  _SOCK_THREAD
{
public:
	Demon();
	virtual void traitementDemandeConnexion()=0;
	bool activerDemon();

protected :
	void _Corps(){ traitementDemandeConnexion();};
};


//*************************************************
//	classe RecepteurSock
//*************************************************
class Recepteur : public  _SOCK_THREAD
{
public:
	Recepteur();
	virtual void traitementSurReception()=0;
	bool activerReception();

protected :
	void _Corps(){ traitementSurReception();};
};


#endif // _SOCKET_H

//=====================FIN_FICHIER==============================================================

